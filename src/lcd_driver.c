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
#include "kiroshi/lcd_driver.h"

static void send_cmd(uint8_t cmd, uint8_t *data, size_t len);

int lcd_init()
{
    uint8_t buffer[4] = {0};

    spi_init(spi0, 10 * 1000 * 1000); // 1MHz
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

void lcd_refresh(uint16_t *vram, uint16_t x, uint16_t y, uint16_t w, uint16_t h)
{
    lcd_refresh_all(vram);
}

void lcd_refresh_all(uint16_t *vram)
{
    uint8_t buffer_msg[4] = {0};

    buffer_msg[0] = 0;
    buffer_msg[1] = 0;
    buffer_msg[2] = 0;
    buffer_msg[3] = SCREEN_WIDTH;
    send_cmd(0x2A, buffer_msg, 4);

    buffer_msg[0] = 0;
    buffer_msg[1] = 0;
    buffer_msg[2] = 0;
    buffer_msg[3] = SCREEN_HEIGHT;
    send_cmd(0x2B, buffer_msg, 4);

    send_cmd(0x2C, (uint8_t *) vram, SCREEN_WIDTH*SCREEN_HEIGHT*2);

    sleep_ms(100);
}
