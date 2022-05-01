/**
 * @file runtime.c
 * @author Matheus T. dos Santos (tenoriomatheus0@gmail.com)
 * @brief
 * @version 0.1
 * @date 24/04/2022
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "kiroshi/runtime.h"

#include <stdio.h>  // TODO remove this

#include "kiroshi/primitives.h"

#define FPS_TIME_MS 33

static struct runtime {
    uint16_t vram[SCREEN_HEIGHT * SCREEN_WIDTH];
    krs_page_t *current_page;
    krs_animation_t *first_animation;
    uint8_t battery_percent;
    struct {
        uint8_t hour;
        uint8_t minute;
    } time;
    struct {
        char *text;
        krs_color_t bg_color;
        krs_color_t fg_color;
    } status_bar;
} self = {
    .vram            = {0},
    .current_page    = NULL,
    .first_animation = NULL,
    .battery_percent = 100,
    .time =
        {
            .hour   = 16,
            .minute = 39,
        },
    .status_bar =
        {
            .text     = "Idle",
            .bg_color = KRS_COLOR(0, 0, 0),
            .fg_color = KRS_COLOR(6, 6, 6),
        },
};

void krs_runtime_tick(void)
{
    krs_animation_t *current_anim;
    krs_point_t battery_pos = KRS_POINT(SCREEN_WIDTH - 17 - 8, 4);
    char time[6] = {0};

    krs_clear_all(self.vram, KRS_COLOR(0, 0, 0));

    /* Draw status bar */
    krs_draw_rect(self.vram, KRS_POINT(0, 0), KRS_POINT(SCREEN_WIDTH, 17),
                  self.status_bar.bg_color);
    krs_draw_string(self.vram, KRS_POINT(6, 4), self.status_bar.text,
                    self.status_bar.fg_color);

    /* Draw baterry */
    krs_draw_rect(self.vram, battery_pos, KRS_POINT(15, 10), self.status_bar.fg_color);
    krs_draw_rect(self.vram, KRS_POINT(battery_pos.x + 2, battery_pos.y + 2), KRS_POINT(11, 6), self.status_bar.bg_color);
    krs_draw_rect(self.vram, KRS_POINT(battery_pos.x + 3, battery_pos.y + 3), KRS_POINT(9 / (100 / self.battery_percent), 4), self.status_bar.fg_color);
    krs_draw_rect(self.vram, KRS_POINT(battery_pos.x + 15, battery_pos.y + 3), KRS_POINT(2, 4), self.status_bar.fg_color);

    if (self.battery_percent == 100) {
        krs_draw_bitmap(self.vram, KRS_POINT(SCREEN_WIDTH - 17 - 8, 4), self.batteries[0],
                        KRS_POINT(17, 10), self.status_bar.fg_color);
    }

    /* Draw time */
    sprintf(time, "%02d", self.time.hour);
    time[2] = ':';
    sprintf(time + 3, "%02d", self.time.minute);
    krs_draw_string(self.vram, KRS_POINT(SCREEN_WIDTH - 58, 4), time,
                    self.status_bar.fg_color);

    /* Draw current page */
    self.current_page->draw(self.vram, self.current_page->obj);

    current_anim = self.first_animation;
    while (current_anim != NULL) {
        if (krs_tween_is_finished(&current_anim->tween)) {
            krs_runtime_cancel_animation(current_anim);
        } else {
            /* Animate */
            current_anim->animate(self.vram, current_anim->obj, &current_anim->tween);

            /* Update the tween */
            krs_tween_tick(&current_anim->tween);
        }

        /* Get next animation */
        current_anim = current_anim->_next;
    }

    krs_hardware_refresh_all(self.vram);

    krs_hardware_sleep_ms(FPS_TIME_MS);
}

void krs_runtime_push_page(krs_page_t *page)
{
    page->_prev       = self.current_page;
    self.current_page = page;
}

void krs_runtime_pop_page(void)
{
    self.current_page = self.current_page->_prev;
}

void krs_runtime_add_animation(krs_animation_t *animation)
{
    if (self.first_animation == NULL) {
        self.first_animation = animation;
    } else {
        krs_animation_t *last_anim = self.first_animation;

        while (last_anim->_next != NULL) {
            last_anim = last_anim->_next;
        }

        last_anim->_next = animation;
    }
}

void krs_runtime_cancel_animation(krs_animation_t *animation)
{
    krs_animation_t *target_anim = self.first_animation;
    krs_animation_t *prev_anim   = NULL;

    while (target_anim != animation) {
        if (target_anim == NULL) {
            return;
        }

        prev_anim   = target_anim;
        target_anim = target_anim->_next;
    }

    if (prev_anim == NULL) {
        self.first_animation = NULL;
    } else {
        prev_anim->_next = target_anim->_next;
    }
}

void krs_runtime_set_battery_percentage(uint8_t percent)
{
    self.battery_percent = percent % 101;
}

void krs_runtime_set_time(uint8_t hour, uint8_t minute)
{
    self.time.hour = hour % 24;
    self.time.minute = minute % 60;
}

void krs_runtime_set_status(const char *text, krs_color_t color)
{
    self.status_bar.text = text;
    self.status_bar.fg_color = color;
}
