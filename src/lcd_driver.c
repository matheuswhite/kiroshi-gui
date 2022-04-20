/**
 * @file lcd_driver.c
 * @author Matheus T. dos Santos (matheus.santos@edge.ufal.br)
 * @brief
 * @version 0.1
 * @date 14/04/2022
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "lcd_driver.h"

#define SCREEN_WIDTH 160
#define SCREEN_HEIGHT 128

#define abs(a) (((a) < 0) ? -(a) : (a))

#define CHECK_ERROR(func) \
    do {                  \
        int err = func;   \
        if (err) {        \
            return err;   \
        }                 \
    } while (0)

#define COLOR2U16(color) \
    ((((color).r & 0x1F) << 10) | (((color).b & 0x1F) << 5) | ((color).g & 0x1F))

static struct lcd_fields {
    uint16_t buffer[SCREEN_HEIGHT][SCREEN_WIDTH];
} self;

static void send_cmd(uint8_t cmd, uint8_t *data, size_t len);

int lcd_init()
{
    uint8_t buffer[4] = {0};

    spi_init(spi0, 1 * 1000 * 1000); // 1MHz
    gpio_set_function(PIN_NUM_MISO, GPIO_FUNC_SPI);
    gpio_set_function(PIN_NUM_MOSI, GPIO_FUNC_SPI);
    gpio_set_function(PIN_NUM_CLK, GPIO_FUNC_SPI);

    gpio_init(PIN_NUM_CS);
    gpio_set_dir(PIN_NUM_CS, GPIO_OUT);
    gpio_put(PIN_NUM_CS, 1);

    gpio_init(PIN_NUM_DC);
    gpio_set_dir(PIN_NUM_DC, GPIO_OUT);

    gpio_init(PIN_NUM_RST);
    gpio_set_dir(PIN_NUM_RST, GPIO_OUT);

    lcd_reset();

    // init sequence
    send_cmd(0x01, NULL, 0); // SWRESET
    sleep_ms(10);

    send_cmd(0x11, NULL, 0); // SLPOUT
    sleep_ms(100);

    buffer[0] = 0x04;
    send_cmd(0x26, buffer, 1);

    buffer[0] = 0x55;
    send_cmd(0x3A, buffer, 1);
    sleep_ms(20);

    buffer[0] = 0x80 | 0x20 | 0x08;
    send_cmd(0x36, buffer, 1);

    buffer[0] = SCREEN_WIDTH-1;
    send_cmd(0x2A, buffer, 4);

    buffer[0] = SCREEN_HEIGHT-1;
    send_cmd(0x2B, buffer, 4);

    send_cmd(0x13, NULL, 0);
    sleep_ms(2);

    send_cmd(0x29, NULL, 0);
    sleep_ms(100);

    return 0;
}

void lcd_reset()
{
    gpio_put(PIN_NUM_RST, 0);
    sleep_ms(100);
    gpio_put(PIN_NUM_RST, 1);
    sleep_ms(100);
}

static inline void cs_select() {
    asm volatile("nop \n nop \n nop");
    gpio_put(PIN_NUM_CS, 0);  // Active low
    asm volatile("nop \n nop \n nop");
}

static inline void cs_deselect() {
    asm volatile("nop \n nop \n nop");
    gpio_put(PIN_NUM_CS, 1);
    asm volatile("nop \n nop \n nop");
}

static void send_cmd(uint8_t cmd, uint8_t *data, size_t len)
{
    gpio_put(PIN_NUM_DC, 0); // cmd
    cs_select();
    spi_write_blocking(spi0, &cmd, 1);
    cs_deselect();

    if (data != NULL && len != 0) {
        gpio_put(PIN_NUM_DC, 1); // data
        cs_select();
        spi_write_blocking(spi0, data, len);
        cs_deselect();
    }
}

void lcd_clear_screen(lcd_color_t color)
{
    for (int i = 0; i < SCREEN_HEIGHT; ++i) {
        for (int j = 0; j < SCREEN_WIDTH; ++j) {
            self.buffer[i][j] = COLOR2U16(color);
        }
    }
}

void lcd_set_pixel(lcd_position_t pos, lcd_color_t color)
{
    self.buffer[pos.y][pos.x] = COLOR2U16(color);
}

void lcd_draw_rect(lcd_position_t top_left, lcd_position_t size, lcd_color_t color)
{
    for (int i = top_left.x; i < top_left.x + size.x; ++i) {
        for (int j = top_left.y; j < top_left.y + size.y; ++j) {
            self.buffer[j][i] = COLOR2U16(color);
        }
    }
}

void lcd_draw_rect_empty(lcd_position_t top_left, lcd_position_t size, lcd_color_t color)
{
    lcd_draw_h_line(top_left, size.x, color);
    lcd_draw_h_line((lcd_position_t){top_left.x, top_left.y + size.y}, size.x, color);
    lcd_draw_v_line(top_left, size.y, color);
    lcd_draw_v_line((lcd_position_t){top_left.x + size.x, top_left.y}, size.y + 1, color);
}

void lcd_draw_h_line(lcd_position_t pos, uint16_t length, lcd_color_t color)
{
    for (int i = pos.x; i < pos.x + length; ++i) {
        self.buffer[pos.y][i] = COLOR2U16(color);
    }
}

void lcd_draw_v_line(lcd_position_t pos, uint16_t length, lcd_color_t color)
{
    for (int i = pos.y; i < pos.y + length; ++i) {
        self.buffer[i][pos.x] = COLOR2U16(color);
    }
}

void lcd_draw_char(lcd_position_t pos, char letter, lcd_color_t color)
{
    int idx = get_index(letter);
    if (idx == -22) {
        return;
    }

    for (int i = 0; i < chicago_font[idx].height; ++i) {
        uint16_t mask = 0x8000;
        for (int j = 0; j < chicago_font[idx].width; ++j) {
            if (chicago_font[idx].img[i] & mask) {
                self.buffer[pos.y + i + chicago_font[idx].offsety][pos.x + j] =
                    COLOR2U16(color);
            }

            mask = mask >> 1;
        }
    }
}

uint16_t lcd_draw_string(lcd_position_t pos, char *str, lcd_color_t color)
{
    const size_t str_len = strlen(str);
    uint16_t offset_x    = 0;
    int idx              = 0;

    for (int i = 0; i < str_len; ++i) {
        lcd_draw_char((lcd_position_t){pos.x + offset_x, pos.y}, str[i], color);
        idx = get_index(str[i]);
        if (idx == -22) {
            if (str[i] == ' ') {
                offset_x += 3;
            }
            continue;
        }

        offset_x += chicago_font[idx].width + 1;
    }

    return offset_x;
}

void lcd_draw_bitmap(lcd_position_t pos, uint32_t *img, uint16_t width, uint16_t height,
                     lcd_color_t color)
{
    for (int i = 0; i < height; ++i) {
        uint32_t mask = 0x80000000;
        for (int j = 0; j < width; ++j) {
            if (img[i] & mask) {
                self.buffer[pos.y + i][pos.x + j] = COLOR2U16(color);
            }

            mask = mask >> 1;
        }
    }
}

void circle_points(int32_t xc, int32_t yc, int32_t x, int32_t y, lcd_color_t color)
{
    self.buffer[yc + y][xc + x] = COLOR2U16(color);
    self.buffer[yc + y][xc - x] = COLOR2U16(color);
    self.buffer[yc - y][xc + x] = COLOR2U16(color);
    self.buffer[yc - y][xc - x] = COLOR2U16(color);
    self.buffer[yc + x][xc + y] = COLOR2U16(color);
    self.buffer[yc + x][xc - y] = COLOR2U16(color);
    self.buffer[yc - x][xc + y] = COLOR2U16(color);
    self.buffer[yc - x][xc - y] = COLOR2U16(color);
}

void lcd_draw_circle(lcd_position_t center, uint16_t radius, lcd_color_t color)
{
    int x = 0;
    int y = radius;
    int m = 5 - 4 * radius;

    while (x <= y) {
        lcd_draw_h_line(LCD_POSITION(center.x - x, center.y - y), 2 * x + 1, color);
        lcd_draw_h_line(LCD_POSITION(center.x - y, center.y - x), 2 * y + 1, color);
        lcd_draw_h_line(LCD_POSITION(center.x - y, center.y + x), 2 * y + 1, color);
        lcd_draw_h_line(LCD_POSITION(center.x - x, center.y + y), 2 * x + 1, color);

        if (m > 0) {
            y--;
            m -= 8 * y;
        }

        x++;
        m += 8 * x + 4;
    }
}

void lcd_draw_line_inner(int x1, int y1, int x2, int y2, int dx, int dy, int decide,
                         lcd_color_t color)
{
    // pk is initial decision making parameter
    // Note:x1&y1,x2&y2, dx&dy values are interchanged
    // and passed in plotPixel function so
    // it can handle both cases when m>1 & m<1
    int pk = 2 * dy - dx;
    for (int i = 0; i <= dx; i++) {
        self.buffer[y1][x1] = COLOR2U16(color);
        // checking either to decrement or increment the value
        // if we have to plot from (0,100) to (100,0)
        x1 < x2 ? x1++ : x1--;
        if (pk < 0) {
            // decision value will decide to plot
            // either  x1 or y1 in x's position
            if (decide == 0) {
                pk = pk + 2 * dy;
            } else {
                //(y1,x1) is passed in xt
                pk = pk + 2 * dy;
            }
        } else {
            y1 < y2 ? y1++ : y1--;
            pk = pk + 2 * dy - 2 * dx;
        }
    }
}

void lcd_draw_line(lcd_position_t p1, lcd_position_t p2, lcd_color_t color)
{
    int dx = abs(p2.x - p1.x);
    int dy = abs(p2.y - p1.y);
    lcd_draw_line_inner(p1.x, p1.y, p2.x, p2.y, dx, dy, (dx > dy) ? 0 : 1, color);

    //    int32_t m_new = 2 * (p2.y - p1.y);
    //    int32_t slope_error_new = m_new - (p2.x - p1.x);
    //    for (int x = p1.x, y = p1.y; x <= p2.x; x++) {
    //        self.buffer[y][x] = COLOR2U16(color);
    //
    //        slope_error_new += m_new;
    //
    //        if (slope_error_new >= 0) {
    //            y++;
    //            slope_error_new -= 2 * (p2.x - p1.x);
    //        }
    //    }
}

void lcd_draw_circle_empty(lcd_position_t center, uint16_t radius, lcd_color_t color)
{
    int x = 0;
    int y = radius;
    int m = 5 - 4 * radius;

    while (x <= y) {
        self.buffer[center.y - y][center.x - x] = COLOR2U16(color);
        self.buffer[center.y - y][center.x + x] = COLOR2U16(color);
        self.buffer[center.y - x][center.x - y] = COLOR2U16(color);
        self.buffer[center.y - x][center.x + y] = COLOR2U16(color);
        self.buffer[center.y + x][center.x - y] = COLOR2U16(color);
        self.buffer[center.y + x][center.x + y] = COLOR2U16(color);
        self.buffer[center.y + y][center.x - x] = COLOR2U16(color);
        self.buffer[center.y + y][center.x + x] = COLOR2U16(color);

        if (m > 0) {
            y--;
            m -= 8 * y;
        }

        x++;
        m += 8 * x + 4;
    }
}

void lcd_refresh(lcd_position_t top_left, lcd_position_t size)
{
    lcd_refresh_all();
}

void lcd_refresh_all()
{
    uint8_t buffer[4] = {0};

    buffer[0] = 0;
    buffer[1] = 0;
    buffer[2] = 0;
    buffer[3] = SCREEN_WIDTH;
    send_cmd(0x2A, buffer, 4);

    buffer[0] = 0;
    buffer[1] = 0;
    buffer[2] = 0;
    buffer[3] = SCREEN_HEIGHT;
    send_cmd(0x2B, buffer, 4);

    send_cmd(0x2C, (uint8_t *) self.buffer, SCREEN_WIDTH*SCREEN_HEIGHT*2);

    sleep_ms(100);
}
