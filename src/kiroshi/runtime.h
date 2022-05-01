/**
 * @file runtime.h
 * @author Matheus T. dos Santos (tenoriomatheus0@gmail.com)
 * @brief
 * @version 0.1
 * @date 24/04/2022
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef RUNTIME_H
#define RUNTIME_H

#include "kiroshi/primitives.h"
#include "kiroshi/hardware.h"
#include "kiroshi/tween.h"

typedef struct krs_page {
    struct krs_page *_prev;
    void *obj;
    void (*draw)(uint16_t *vram, void *obj);
} krs_page_t;

typedef struct krs_animation {
    struct krs_animation *_next;
    krs_tween_t tween;
    void *obj;
    void (*animate)(uint16_t *vram, void *obj, krs_tween_t *tween);
} krs_animation_t;

void krs_runtime_tick(void);

void krs_runtime_push_page(krs_page_t *page);

void krs_runtime_pop_page(void);

void krs_runtime_add_animation(krs_animation_t *animation);

void krs_runtime_cancel_animation(krs_animation_t *animation);

void krs_runtime_set_battery_percentage(uint8_t percent);

void krs_runtime_set_time(uint8_t hour, uint8_t minute);

void krs_runtime_set_status(const char *text, krs_color_t color);

#endif  // RUNTIME_H
