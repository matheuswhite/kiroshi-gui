/**
 * @file lcd_driver.h
 * @author Matheus T. dos Santos (matheus.santos@edge.ufal.br)
 * @brief
 * @version 0.1
 * @date 14/04/2022
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef LCD_DRIVER_H
#define LCD_DRIVER_H

#include <stdint.h>
#include <string.h>
#include "chicago_font.h"
#include "hardware/spi.h"
#include "pico/stdlib.h"

#define PIN_NUM_MISO 4
#define PIN_NUM_MOSI 7
#define PIN_NUM_CLK 6
#define PIN_NUM_CS 5
#define PIN_NUM_DC 2
#define PIN_NUM_RST 3

#define PARALLEL_LINES 16

#define LCD_POSITION(x, y) ((lcd_position_t){(x), (y)})

typedef struct {
    uint16_t x;
    uint16_t y;
} lcd_position_t;

typedef struct {
    uint8_t r;
    uint8_t g;
    uint8_t b;
} lcd_color_t;

int lcd_init();

void lcd_reset();

void lcd_clear_screen(lcd_color_t color);

void lcd_set_pixel(lcd_position_t pos, lcd_color_t color);

void lcd_draw_rect(lcd_position_t top_left, lcd_position_t size, lcd_color_t color);

void lcd_draw_rect_empty(lcd_position_t top_left, lcd_position_t size, lcd_color_t color);

void lcd_draw_h_line(lcd_position_t pos, uint16_t length, lcd_color_t color);

void lcd_draw_v_line(lcd_position_t pos, uint16_t length, lcd_color_t color);

void lcd_draw_char(lcd_position_t pos, char letter, lcd_color_t color);

uint16_t lcd_draw_string(lcd_position_t pos, char *str, lcd_color_t color);

void lcd_draw_bitmap(lcd_position_t pos, uint32_t *img, uint16_t width, uint16_t height, lcd_color_t color);

void lcd_draw_circle(lcd_position_t center, uint16_t radius, lcd_color_t color);

void lcd_draw_circle_empty(lcd_position_t center, uint16_t radius, lcd_color_t color);

void lcd_draw_line(lcd_position_t p1, lcd_position_t p2, lcd_color_t color);

void lcd_refresh(lcd_position_t top_left, lcd_position_t size);

void lcd_refresh_all();

#endif //LCD_DRIVER_H
