/**
 * @file primitives.h
 * @author Matheus T. dos Santos (matheus.santos@edge.ufal.br)
 * @brief
 * @version 0.1
 * @date 22/04/2022
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef PRIMITIVES_H
#define PRIMITIVES_H

#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include "kiroshi/chicago_font.h"
#include "kiroshi/lcd_driver.h"

#define SCREEN_WIDTH 160
#define SCREEN_HEIGHT 128

#define KRS_POINT(x, y) ((krs_point_t){x, y})
#define KRS_COLOR(r, g, b) ((krs_color_t){r, g, b})

typedef struct {
    int16_t x;
    int16_t y;
} krs_point_t;

typedef struct {
    int8_t r;
    int8_t g;
    int8_t b;
} krs_color_t;

void krs_clear_all(uint16_t vram[][SCREEN_WIDTH], krs_color_t color);

void krs_set_pixel(uint16_t vram[][SCREEN_WIDTH], krs_point_t position,
                   krs_color_t color);

void krs_draw_rect(uint16_t vram[][SCREEN_WIDTH], krs_point_t position, krs_point_t size,
                   krs_color_t color);

void krs_draw_rect_empty(uint16_t vram[][SCREEN_WIDTH], krs_point_t position,
                         krs_point_t size, krs_color_t color);

void krs_draw_h_line(uint16_t vram[][SCREEN_WIDTH], krs_point_t position, uint16_t length,
                     krs_color_t color);

void krs_draw_v_line(uint16_t vram[][SCREEN_WIDTH], krs_point_t position, uint16_t length,
                     krs_color_t color);

uint16_t krs_draw_char(uint16_t vram[][SCREEN_WIDTH], krs_point_t pos,
                       char letter, krs_color_t color);

uint16_t krs_draw_string(uint16_t vram[][SCREEN_WIDTH], krs_point_t position, char *str,
                         krs_color_t color);

void krs_draw_bitmap(uint16_t vram[][SCREEN_WIDTH], krs_point_t position, uint32_t *img,
                     krs_point_t size, krs_color_t color);

void krs_draw_circle(uint16_t vram[][SCREEN_WIDTH], krs_point_t center, uint16_t radius,
                     krs_color_t color);

void krs_draw_circle_empty(uint16_t vram[][SCREEN_WIDTH], krs_point_t center,
                           uint16_t radius, krs_color_t color);

void krs_draw_line(uint16_t vram[][SCREEN_WIDTH], krs_point_t p1, krs_point_t p2,
                   krs_color_t color);

#endif  // PRIMITIVES_H
