#include <stdbool.h>
#include <stdio.h>
#include "pico/stdlib.h"
#include "lcd_driver.h"

#define VERY_DARK ((lcd_color_t){0, 0, 0})
#define DARK ((lcd_color_t){1, 1, 1})
#define DARK ((lcd_color_t){1, 1, 1})
#define LIGHT ((lcd_color_t){6, 6, 6})

#define DARK_THEME 1
#define LIGHT_THEME 2
#define THEME LIGHT_THEME

#if THEME == DARK_THEME
#define BACKGROUND_COLOR VERY_DARK
#define TEXT_COLOR LIGHT
#elif THEME == LIGHT_THEME
#define BACKGROUND_COLOR LIGHT
#define TEXT_COLOR VERY_DARK
#endif

#define RED ((lcd_color_t){6, 0, 0})

#define BOX_HEIGHT 15
#define LINE_OFFSET 1
#define START_Y 17
#define START_X 4
#define XSIZE 148
#define SHADOW 1  // 1 ou 2

void draw_item(char *text, uint8_t index, bool is_selected) {
    uint16_t start_y = START_Y + index * (BOX_HEIGHT + 1 + LINE_OFFSET);

    if (is_selected) {
        lcd_draw_rect(LCD_POSITION(START_X, start_y), LCD_POSITION(XSIZE, 1), TEXT_COLOR);
        lcd_draw_rect(LCD_POSITION(START_X, start_y + LINE_OFFSET + 1),
                      LCD_POSITION(XSIZE, BOX_HEIGHT), TEXT_COLOR);
        lcd_draw_rect(
                LCD_POSITION(START_X, start_y + LINE_OFFSET + 1 + BOX_HEIGHT + LINE_OFFSET),
                LCD_POSITION(XSIZE, 1), TEXT_COLOR);
    }

    lcd_draw_string(
            LCD_POSITION(START_X + 4 + (is_selected ? 4 : 0), start_y + LINE_OFFSET + 1 + 3),
            text, is_selected ? BACKGROUND_COLOR : TEXT_COLOR);
}

void draw_shadow(lcd_position_t pos, lcd_position_t size, uint8_t shadow,
                 lcd_color_t color) {
    lcd_draw_h_line(LCD_POSITION(pos.x + size.x, pos.y + shadow + 1), shadow + 1, color);
    lcd_draw_h_line(LCD_POSITION(pos.x + shadow + 1, pos.y + size.y + shadow + 1), size.x,
                    color);
    lcd_draw_v_line(LCD_POSITION(pos.x + size.x + shadow + 1, pos.y + shadow + 1),
                    size.y + 1, color);
    lcd_draw_v_line(LCD_POSITION(pos.x + shadow + 1, pos.y + size.y), shadow + 1, color);
}

_Noreturn void menu_page() {
    // xxxxxxxx xxxxxxxo o
    // xxxxxxxx xxxxxxxo o
    // xxoooooo oooooxxo o
    // xxoooooo oooooxxx x
    // xxoxxxxx xxxxoxxx x
    // xxoxxxxx xxxxoxxx x
    // xxoxxxxx xxxxoxxx x
    // xxoooooo oooooxxo o
    // xxxxxxxx xxxxxxxo o
    // xxxxxxxx xxxxxxxo o
    uint32_t battery_full[] = {
            0xfffe0000, 0xfffe0000, 0xc0060000, 0xdff78000, 0xdff78000,
            0xdff78000, 0xdff78000, 0xc0060000, 0xfffe0000, 0xfffe0000,
    };
    uint32_t battery_66[] = {
            0xfffe0000, 0xfffe0000, 0xc0060000, 0xdf878000, 0xdf878000,
            0xdf878000, 0xdf878000, 0xc0060000, 0xfffe0000, 0xfffe0000,
    };
    uint32_t battery_33[] = {
            0xfffe0000, 0xfffe0000, 0xc0060000, 0xdc078000, 0xdc078000,
            0xdc078000, 0xdc078000, 0xc0060000, 0xfffe0000, 0xfffe0000,
    };
    uint32_t battery_empty[] = {
            0xfffe0000, 0xfffe0000, 0xc0060000, 0xc0078000, 0xc0078000,
            0xc0078000, 0xc0078000, 0xc0060000, 0xfffe0000, 0xfffe0000,
    };
    uint8_t idx = 0;

    while (1) {
        lcd_clear_screen(BACKGROUND_COLOR);
        lcd_draw_bitmap(LCD_POSITION(4, 4), battery_full, 17, 10, TEXT_COLOR);
        lcd_draw_bitmap(LCD_POSITION(34, 4), battery_66, 17, 10, TEXT_COLOR);
        lcd_draw_bitmap(LCD_POSITION(64, 4), battery_33, 17, 10, TEXT_COLOR);
        lcd_draw_bitmap(LCD_POSITION(94, 4), battery_empty, 17, 10,
                        (lcd_color_t) {6, 0, 0});
        draw_item("Musicas", 0, idx == 0);
        draw_item("Playlist", 1, idx == 1);
        draw_item("Podcast", 2, idx == 2);
        draw_item("Configuracoes", 3, idx == 3);
        draw_item("Fotos", 4, idx == 4);
        draw_item("Now Playing", 5, idx == 5);
        lcd_draw_rect_empty(
                LCD_POSITION(START_X, START_Y),
                LCD_POSITION(XSIZE, 6 * (BOX_HEIGHT + 1 + LINE_OFFSET) + LINE_OFFSET),
                TEXT_COLOR);
        draw_shadow(LCD_POSITION(START_X, START_Y),
                    LCD_POSITION(XSIZE, 6 * (BOX_HEIGHT + 1 + LINE_OFFSET) + LINE_OFFSET),
                    SHADOW, TEXT_COLOR);
        lcd_refresh(LCD_POSITION(0, 0), LCD_POSITION(160, 128));

        sleep_ms(1000);
        idx = (idx + 1) % 6;
    }
}

void draw_inner_line_idx(lcd_position_t center, uint16_t inner_circle, uint8_t index) {
    uint32_t length = 3;

    switch (index) {
        case 0:
            lcd_draw_v_line(LCD_POSITION(center.x, center.y - inner_circle), length,
                            TEXT_COLOR);  // s1
            break;
        case 1:
            lcd_draw_line(
                    LCD_POSITION(center.x + inner_circle, center.y - inner_circle),
                    LCD_POSITION(center.x + (inner_circle / 2), center.y - (inner_circle / 2)),
                    TEXT_COLOR);  // d2
            break;
        case 2:
            lcd_draw_h_line(LCD_POSITION(center.x + inner_circle - length + 1, center.y),
                            length, TEXT_COLOR);  // s2
            break;
        case 3:
            lcd_draw_line(
                    LCD_POSITION(center.x + inner_circle, center.y + inner_circle),
                    LCD_POSITION(center.x + (inner_circle / 2), center.y + (inner_circle / 2)),
                    TEXT_COLOR);  // d3
            break;
        case 4:
            lcd_draw_v_line(LCD_POSITION(center.x, center.y + inner_circle - length + 1),
                            length, TEXT_COLOR);  // s3
            break;
        case 5:
            lcd_draw_line(
                    LCD_POSITION(center.x - inner_circle, center.y + inner_circle),
                    LCD_POSITION(center.x - (inner_circle / 2), center.y + (inner_circle / 2)),
                    TEXT_COLOR);  // d4
            break;
        case 6:
            lcd_draw_h_line(LCD_POSITION(center.x - inner_circle, center.y), length,
                            TEXT_COLOR);  // s4
            break;
        case 7:
            lcd_draw_line(
                    LCD_POSITION(center.x - inner_circle, center.y - inner_circle),
                    LCD_POSITION(center.x - (inner_circle / 2), center.y - (inner_circle / 2)),
                    TEXT_COLOR);  // d1
            break;
    }
}

void draw_inner_lines(lcd_position_t center, uint16_t inner_circle, uint16_t rotation) {
    uint8_t idx = rotation % 8;

    draw_inner_line_idx(center, inner_circle, idx % 8);
    draw_inner_line_idx(center, inner_circle, (idx + 3) % 8);
    draw_inner_line_idx(center, inner_circle, (idx + 5) % 8);
}

_Noreturn void tape_page(void) {
    uint16_t rotation = 0;
    uint16_t center = 80;
    uint16_t outer_radius = 25;
    uint16_t inner_radius = 10;
    uint16_t left_radius = outer_radius;
    uint16_t right_radius = inner_radius + 2;

    while (1) {
        lcd_clear_screen(BACKGROUND_COLOR);

        lcd_draw_circle(LCD_POSITION(center - 40, 60), left_radius, TEXT_COLOR);
        lcd_draw_circle(LCD_POSITION(center - 40, 60), inner_radius, BACKGROUND_COLOR);
        lcd_draw_circle(LCD_POSITION(center + 40, 60), right_radius, TEXT_COLOR);
        lcd_draw_circle(LCD_POSITION(center + 40, 60), inner_radius, BACKGROUND_COLOR);
        lcd_draw_line(LCD_POSITION(center - 40, 60 - left_radius), LCD_POSITION(center + 40, 60 - right_radius),
                      TEXT_COLOR);
        lcd_draw_line(LCD_POSITION(center - 40, 60 + left_radius), LCD_POSITION(center + 40, 60 + right_radius),
                      TEXT_COLOR);
        draw_inner_lines(LCD_POSITION(center - 40, 60), inner_radius, rotation);
        draw_inner_lines(LCD_POSITION(center + 40, 60), inner_radius, rotation + 3);

        lcd_refresh(LCD_POSITION(0, 0), LCD_POSITION(160, 128));

        sleep_ms(500);
        rotation = (rotation + 1) % 360;
        left_radius -= 1;
        if (left_radius <= inner_radius + 1) {
            left_radius = outer_radius;
        }
        right_radius += 1;
        if (right_radius > outer_radius) {
            right_radius = inner_radius + 2;
        }
    }
}

int main(void) {
    stdio_init_all();

    printf("Initing lcd...\n");
    lcd_init();

    lcd_clear_screen(BACKGROUND_COLOR);
    lcd_refresh(LCD_POSITION(0, 0), LCD_POSITION(160, 128));

    menu_page();
//    tape_page();
}
