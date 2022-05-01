/**
 * @file primitive.c
 * @author Matheus T. dos Santos (tenoriomatheus0@gmail.com)
 * @brief
 * @version 0.1
 * @date 22/04/2022
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "kiroshi/primitives.h"

#define COLOR2U16(color) \
    ((((color).r & 0x1F) << 10) | (((color).b & 0x1F) << 5) | ((color).g & 0x1F))

#ifndef ABS
#define ABS(a) (((a) < 0) ? -(a) : (a))
#endif

static void draw_line_inner(uint16_t *vram, int x1, int y1, int x2, int y2, int dx,
                            int dy, int decide, krs_color_t color);

void krs_clear_all(uint16_t *vram, krs_color_t color)
{
    for (int i = 0; i < SCREEN_HEIGHT; ++i) {
        for (int j = 0; j < SCREEN_WIDTH; ++j) {
            vram[i * SCREEN_WIDTH + j] = COLOR2U16(color);
        }
    }
}

void krs_set_pixel(uint16_t *vram, krs_point_t position, krs_color_t color)
{
    vram[position.y * SCREEN_WIDTH + position.x] = COLOR2U16(color);
}

void krs_draw_rect(uint16_t *vram, krs_point_t position, krs_point_t size,
                   krs_color_t color)
{
    for (int i = position.x; i < position.x + size.x; ++i) {
        for (int j = position.y; j < position.y + size.y; ++j) {
            vram[j * SCREEN_WIDTH + i] = COLOR2U16(color);
        }
    }
}

void krs_draw_rect_empty(uint16_t *vram, krs_point_t position, krs_point_t size,
                         krs_color_t color)
{
    krs_draw_h_line(vram, position, size.x, color);
    krs_draw_h_line(vram, KRS_POINT(position.x, position.y + size.y), size.x, color);
    krs_draw_v_line(vram, position, size.y, color);
    krs_draw_v_line(vram, KRS_POINT(position.x + size.x, position.y), size.y + 1, color);
}

void krs_draw_h_line(uint16_t *vram, krs_point_t position, uint16_t length,
                     krs_color_t color)
{
    for (int i = position.x; i < position.x + length; ++i) {
        vram[position.y * SCREEN_WIDTH + i] = COLOR2U16(color);
    }
}

void krs_draw_v_line(uint16_t *vram, krs_point_t position, uint16_t length,
                     krs_color_t color)
{
    for (int i = position.y; i < position.y + length; ++i) {
        vram[i * SCREEN_WIDTH + position.x] = COLOR2U16(color);
    }
}

uint16_t krs_draw_char(uint16_t *vram, krs_point_t pos, char letter, krs_color_t color)
{
    int idx = get_index(letter);
    if (idx == -22) {
        return 0;
    }

    for (int i = 0; i < chicago_font[idx].height; ++i) {
        uint16_t mask = 0x8000;
        for (int j = 0; j < chicago_font[idx].width; ++j) {
            if (chicago_font[idx].img[i] & mask) {
                vram[(pos.y + i + chicago_font[idx].offsety) * SCREEN_WIDTH + pos.x + j] =
                    COLOR2U16(color);
            }

            mask = mask >> 1;
        }
    }

    return chicago_font[idx].width;
}

uint16_t krs_draw_string(uint16_t *vram, krs_point_t position, char *str,
                         krs_color_t color)
{
    const size_t str_len = strlen(str);
    uint16_t offset_x    = 0;
    int idx              = 0;

    for (int i = 0; i < str_len; ++i) {
        krs_draw_char(vram, KRS_POINT(position.x + offset_x, position.y), str[i], color);
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

void krs_draw_bitmap(uint16_t *vram, krs_point_t position, uint32_t *img,
                     krs_point_t size, krs_color_t color)
{
    for (int i = 0; i < size.y; ++i) {
        uint32_t mask = 0x80000000;
        for (int j = 0; j < size.x; ++j) {
            if (img[i] & mask) {
                vram[(position.y + i) * SCREEN_WIDTH + position.x + j] = COLOR2U16(color);
            }

            mask = mask >> 1;
        }
    }
}

void krs_draw_circle(uint16_t *vram, krs_point_t center, uint16_t radius,
                     krs_color_t color)
{
    int x = 0;
    int y = radius;
    int m = 5 - 4 * radius;

    while (x <= y) {
        krs_draw_h_line(vram, KRS_POINT(center.x - x, center.y - y), 2 * x + 1, color);
        krs_draw_h_line(vram, KRS_POINT(center.x - y, center.y - x), 2 * y + 1, color);
        krs_draw_h_line(vram, KRS_POINT(center.x - y, center.y + x), 2 * y + 1, color);
        krs_draw_h_line(vram, KRS_POINT(center.x - x, center.y + y), 2 * x + 1, color);

        if (m > 0) {
            y--;
            m -= 8 * y;
        }

        x++;
        m += 8 * x + 4;
    }
}

void krs_draw_circle_empty(uint16_t *vram, krs_point_t center, uint16_t radius,
                           krs_color_t color)
{
    int x = 0;
    int y = radius;
    int m = 5 - 4 * radius;

    while (x <= y) {
        vram[(center.y - y) * SCREEN_WIDTH + center.x - x] = COLOR2U16(color);
        vram[(center.y - y) * SCREEN_WIDTH + center.x + x] = COLOR2U16(color);
        vram[(center.y - x) * SCREEN_WIDTH + center.x - y] = COLOR2U16(color);
        vram[(center.y - x) * SCREEN_WIDTH + center.x + y] = COLOR2U16(color);
        vram[(center.y + x) * SCREEN_WIDTH + center.x - y] = COLOR2U16(color);
        vram[(center.y + x) * SCREEN_WIDTH + center.x + y] = COLOR2U16(color);
        vram[(center.y + y) * SCREEN_WIDTH + center.x - x] = COLOR2U16(color);
        vram[(center.y + y) * SCREEN_WIDTH + center.x + x] = COLOR2U16(color);

        if (m > 0) {
            y--;
            m -= 8 * y;
        }

        x++;
        m += 8 * x + 4;
    }
}

void krs_draw_line(uint16_t *vram, krs_point_t p1, krs_point_t p2, krs_color_t color)
{
    int dx = ABS(p2.x - p1.x);
    int dy = ABS(p2.y - p1.y);
    draw_line_inner(vram, p1.x, p1.y, p2.x, p2.y, dx, dy, (dx > dy) ? 0 : 1, color);
}

void krs_invert(uint16_t *vram, krs_point_t position, krs_point_t size, krs_color_t color)
{
    uint16_t arg_color = COLOR2U16(color);

    for (int i = position.y; i < position.y + size.y; ++i) {
        for (int j = position.x; j < position.x + size.x; ++j) {
            vram[i * SCREEN_WIDTH + j] = (vram[i * SCREEN_WIDTH + j] == 0) ? arg_color : 0;
        }
    }
}

static void draw_line_inner(uint16_t *vram, int x1, int y1, int x2, int y2, int dx,
                            int dy, int decide, krs_color_t color)
{
    // pk is initial decision making parameter
    // Note:x1&y1,x2&y2, dx&dy values are interchanged
    // and passed in plotPixel function so
    // it can handle both cases when m>1 & m<1
    int pk = 2 * dy - dx;
    for (int i = 0; i <= dx; i++) {
        vram[y1 * SCREEN_WIDTH + x1] = COLOR2U16(color);
        // checking either to decrement or increment the value
        // if we have to plot from (0,100) to (100,0)
        x1 < x2 ? x1++ : x1--;
        if (pk < 0) {
            pk = pk + 2 * dy;
        } else {
            y1 < y2 ? y1++ : y1--;
            pk = pk + 2 * dy - 2 * dx;
        }
    }
}
