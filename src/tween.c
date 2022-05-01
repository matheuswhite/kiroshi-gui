/**
 * @file tween.c
 * @author Matheus T. dos Santos (tenoriomatheus0@gmail.com)
 * @brief
 * @version 0.1
 * @date 24/04/2022
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "kiroshi/tween.h"

krs_tween_t krs_new_tween_int32(int32_t begin, int32_t end, uint32_t duration_ms)
{
    return (krs_tween_t){
        .kind          = KRS_TWEEN_INT32,
        .tween.integer = {
            .begin   = begin,
            .end     = end,
            .current = begin,
            ._step   = (end - begin) / (duration_ms / KRS_ANIMATION_PERIOD_MS),
        }};
}

krs_tween_t krs_new_tween_point(krs_point_t begin, krs_point_t end, uint32_t duration_ms)
{
    const uint32_t d = duration_ms / KRS_ANIMATION_PERIOD_MS;

    return (krs_tween_t){
        .kind        = KRS_TWEEN_POINT,
        .tween.point = {
            .begin   = begin,
            .end     = end,
            .current = begin,
            ._step   = KRS_POINT((end.x - begin.x) / d, (end.y - begin.y) / d),
        }};
}

krs_tween_t krs_new_tween_color(krs_color_t begin, krs_color_t end, uint32_t duration_ms)
{
    const uint32_t d = duration_ms / KRS_ANIMATION_PERIOD_MS;

    return (krs_tween_t){
        .kind        = KRS_TWEEN_COLOR,
        .tween.color = {
            .begin   = begin,
            .end     = end,
            .current = begin,
            ._step   = KRS_COLOR((end.r - begin.r) / d, (end.g - begin.g) / d,
                                 (end.b - begin.b) / d),
        }};
}

void krs_tween_tick(krs_tween_t *tween)
{
    switch (tween->kind) {
    case KRS_TWEEN_INT32:
        tween->tween.integer.current += tween->tween.integer._step;
        break;
    case KRS_TWEEN_POINT:
        tween->tween.point.current.x += tween->tween.point._step.x;
        tween->tween.point.current.y += tween->tween.point._step.y;
        break;
    case KRS_TWEEN_COLOR:
        tween->tween.color.current.r += tween->tween.color._step.r;
        tween->tween.color.current.g += tween->tween.color._step.g;
        tween->tween.color.current.b += tween->tween.color._step.b;
        break;
    }
}

bool krs_tween_is_finished(krs_tween_t *tween)
{
    switch (tween->kind) {
    case KRS_TWEEN_INT32:
        return tween->tween.integer.current >= tween->tween.integer.end;
    case KRS_TWEEN_POINT:
        return (tween->tween.point.current.x >= tween->tween.point.end.x)
               && (tween->tween.point.current.y >= tween->tween.point.end.y);
    case KRS_TWEEN_COLOR:
        return (tween->tween.color.current.r >= tween->tween.color.end.r)
               && (tween->tween.color.current.g >= tween->tween.color.end.g)
               && (tween->tween.color.current.b >= tween->tween.color.end.b);
    }
}
