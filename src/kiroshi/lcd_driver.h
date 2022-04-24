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

#include <hardware/spi.h>
#include <pico/stdlib.h>
#include <stdint.h>
#include <string.h>

#include "kiroshi/chicago_font.h"

#define PIN_NUM_MISO 4
#define PIN_NUM_MOSI 7
#define PIN_NUM_CLK 6
#define PIN_NUM_CS 5
#define PIN_NUM_DC 2
#define PIN_NUM_RST 3

#define SCREEN_WIDTH 160
#define SCREEN_HEIGHT 128

int lcd_init();

void lcd_reset();

void lcd_refresh(uint16_t vram[][SCREEN_WIDTH], uint16_t x, uint16_t y, uint16_t w, uint16_t h);

void lcd_refresh_all(uint16_t vram[][SCREEN_WIDTH]);

#endif  // LCD_DRIVER_H
