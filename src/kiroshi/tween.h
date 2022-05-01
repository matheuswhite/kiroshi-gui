/**
 * @file tween.h
 * @author Matheus T. dos Santos (tenoriomatheus0@gmail.com)
 * @brief
 * @version 0.1
 * @date 24/04/2022
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef TWEEN_H
#define TWEEN_H

#include <stdint.h>

#include "kiroshi/primitives.h"

#define KRS_ANIMATION_PERIOD_MS 30

typedef struct {
    int32_t begin;
    int32_t end;
    int32_t current;
    int32_t _step;
} krs_tween_int32_t;

typedef struct {
    krs_point_t begin;
    krs_point_t end;
    krs_point_t current;
    krs_point_t _step;
} krs_tween_point_t;

typedef struct {
    krs_color_t begin;
    krs_color_t end;
    krs_color_t current;
    krs_color_t _step;
} krs_tween_color_t;

typedef enum {
    KRS_TWEEN_INT32,
    KRS_TWEEN_POINT,
    KRS_TWEEN_COLOR,
} krs_tween_kind_t;

typedef struct {
    krs_tween_kind_t kind;
    union {
        krs_tween_int32_t integer;
        krs_tween_point_t point;
        krs_tween_color_t color;
    } tween;
} krs_tween_t;

krs_tween_t krs_new_tween_int32(int32_t begin, int32_t end, uint32_t duration_ms);

krs_tween_t krs_new_tween_point(krs_point_t begin, krs_point_t end, uint32_t duration_ms);

krs_tween_t krs_new_tween_color(krs_color_t begin, krs_color_t end, uint32_t duration_ms);

void krs_tween_tick(krs_tween_t *tween);

bool krs_tween_is_finished(krs_tween_t *tween);

#endif  // TWEEN_H
