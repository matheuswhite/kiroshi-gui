#include <pico/stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#include "kiroshi/lcd_driver.h"
#include "kiroshi/list_menu.h"
#include "kiroshi/primitives.h"

#define VERY_DARK KRS_COLOR(0, 0, 0)
#define LIGHT KRS_COLOR(6, 6, 6)
#define RED KRS_COLOR(6, 0, 0)

#define DARK_THEME 1
#define LIGHT_THEME 2
#define THEME DARK_THEME

#if THEME == DARK_THEME
#define BACKGROUND_COLOR VERY_DARK
#define TEXT_COLOR LIGHT
#elif THEME == LIGHT_THEME
#define BACKGROUND_COLOR LIGHT
#define TEXT_COLOR VERY_DARK
#endif

#define BOX_HEIGHT 15
#define LINE_OFFSET 1
#define START_Y 17
#define START_X 4
#define XSIZE 148
#define SHADOW 1  // 1 ou 2

uint16_t vram_[SCREEN_HEIGHT][SCREEN_WIDTH];

void draw_item(char *text, uint8_t index, bool is_selected)
{
    uint16_t start_y = START_Y + index * (BOX_HEIGHT + 1 + LINE_OFFSET);

    if (is_selected) {
        krs_draw_rect(vram_, KRS_POINT(START_X, start_y), KRS_POINT(XSIZE, 1), TEXT_COLOR);
        krs_draw_rect(vram_, KRS_POINT(START_X, start_y + LINE_OFFSET + 1),
                      KRS_POINT(XSIZE, BOX_HEIGHT), TEXT_COLOR);
        krs_draw_rect(
            vram_,
            KRS_POINT(START_X, start_y + LINE_OFFSET + 1 + BOX_HEIGHT + LINE_OFFSET),
            KRS_POINT(XSIZE, 1), TEXT_COLOR);
    }

    krs_draw_string(
        vram_,
        KRS_POINT(START_X + 4 + (is_selected ? 4 : 0), start_y + LINE_OFFSET + 1 + 3),
        text, is_selected ? BACKGROUND_COLOR : TEXT_COLOR);
}

void draw_shadow(krs_point_t pos, krs_point_t size, uint8_t shadow, krs_color_t color)
{
    krs_draw_h_line(vram_, KRS_POINT(pos.x + size.x, pos.y + shadow + 1), shadow + 1,
                    color);
    krs_draw_h_line(vram_, KRS_POINT(pos.x + shadow + 1, pos.y + size.y + shadow + 1),
                    size.x, color);
    krs_draw_v_line(vram_, KRS_POINT(pos.x + size.x + shadow + 1, pos.y + shadow + 1),
                    size.y + 1, color);
    krs_draw_v_line(vram_, KRS_POINT(pos.x + shadow + 1, pos.y + size.y), shadow + 1,
                    color);
}

_Noreturn void menu_page()
{
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
        krs_clear_all(vram_, BACKGROUND_COLOR);
        krs_draw_bitmap(vram_, KRS_POINT(4, 4), battery_full, KRS_POINT(17, 10),
                        TEXT_COLOR);
        krs_draw_bitmap(vram_, KRS_POINT(34, 4), battery_66, KRS_POINT(17, 10),
                        TEXT_COLOR);
        krs_draw_bitmap(vram_, KRS_POINT(64, 4), battery_33, KRS_POINT(17, 10),
                        TEXT_COLOR);
        krs_draw_bitmap(vram_, KRS_POINT(94, 4), battery_empty, KRS_POINT(17, 10), RED);
        draw_item("Musicas", 0, idx == 0);
        draw_item("Playlist", 1, idx == 1);
        draw_item("Podcast", 2, idx == 2);
        draw_item("Configuracoes", 3, idx == 3);
        draw_item("Fotos", 4, idx == 4);
        draw_item("Now Playing", 5, idx == 5);
        krs_draw_rect_empty(
            vram_, KRS_POINT(START_X, START_Y),
            KRS_POINT(XSIZE, 6 * (BOX_HEIGHT + 1 + LINE_OFFSET) + LINE_OFFSET),
            TEXT_COLOR);
        draw_shadow(KRS_POINT(START_X, START_Y),
                    KRS_POINT(XSIZE, 6 * (BOX_HEIGHT + 1 + LINE_OFFSET) + LINE_OFFSET),
                    SHADOW, TEXT_COLOR);
        lcd_refresh_all(vram_);

        sleep_ms(1000);
        idx = (idx + 1) % 6;
    }
}

void draw_inner_line_idx(krs_point_t center, uint16_t inner_circle, uint8_t index)
{
    uint32_t length = 3;

    switch (index) {
    case 0:
        krs_draw_v_line(vram_, KRS_POINT(center.x, center.y - inner_circle), length,
                        TEXT_COLOR);  // s1
        break;
    case 1:
        krs_draw_line(
            vram_, KRS_POINT(center.x + inner_circle, center.y - inner_circle),
            KRS_POINT(center.x + (inner_circle / 2), center.y - (inner_circle / 2)),
            TEXT_COLOR);  // d2
        break;
    case 2:
        krs_draw_h_line(vram_, KRS_POINT(center.x + inner_circle - length + 1, center.y),
                        length, TEXT_COLOR);  // s2
        break;
    case 3:
        krs_draw_line(
            vram_, KRS_POINT(center.x + inner_circle, center.y + inner_circle),
            KRS_POINT(center.x + (inner_circle / 2), center.y + (inner_circle / 2)),
            TEXT_COLOR);  // d3
        break;
    case 4:
        krs_draw_v_line(vram_, KRS_POINT(center.x, center.y + inner_circle - length + 1),
                        length, TEXT_COLOR);  // s3
        break;
    case 5:
        krs_draw_line(
            vram_, KRS_POINT(center.x - inner_circle, center.y + inner_circle),
            KRS_POINT(center.x - (inner_circle / 2), center.y + (inner_circle / 2)),
            TEXT_COLOR);  // d4
        break;
    case 6:
        krs_draw_h_line(vram_, KRS_POINT(center.x - inner_circle, center.y), length,
                        TEXT_COLOR);  // s4
        break;
    case 7:
        krs_draw_line(
            vram_, KRS_POINT(center.x - inner_circle, center.y - inner_circle),
            KRS_POINT(center.x - (inner_circle / 2), center.y - (inner_circle / 2)),
            TEXT_COLOR);  // d1
        break;
    }
}

void draw_inner_lines(krs_point_t center, uint16_t inner_circle, uint16_t rotation)
{
    uint8_t idx = rotation % 8;

    draw_inner_line_idx(center, inner_circle, idx % 8);
    draw_inner_line_idx(center, inner_circle, (idx + 3) % 8);
    draw_inner_line_idx(center, inner_circle, (idx + 5) % 8);
}

_Noreturn void tape_page(void)
{
    uint16_t rotation     = 0;
    uint16_t center       = 80;
    uint16_t outer_radius = 25;
    uint16_t inner_radius = 10;
    uint16_t left_radius  = outer_radius;
    uint16_t right_radius = inner_radius + 2;

    while (1) {
        krs_clear_all(vram_, BACKGROUND_COLOR);

        krs_draw_circle(vram_, KRS_POINT(center - 40, 60), left_radius, TEXT_COLOR);
        krs_draw_circle(vram_, KRS_POINT(center - 40, 60), inner_radius, BACKGROUND_COLOR);
        krs_draw_circle(vram_, KRS_POINT(center + 40, 60), right_radius, TEXT_COLOR);
        krs_draw_circle(vram_, KRS_POINT(center + 40, 60), inner_radius, BACKGROUND_COLOR);
        krs_draw_line(vram_, KRS_POINT(center - 40, 60 - left_radius),
                      KRS_POINT(center + 40, 60 - right_radius), TEXT_COLOR);
        krs_draw_line(vram_, KRS_POINT(center - 40, 60 + left_radius),
                      KRS_POINT(center + 40, 60 + right_radius), TEXT_COLOR);
        draw_inner_lines(KRS_POINT(center - 40, 60), inner_radius, rotation);
        draw_inner_lines(KRS_POINT(center + 40, 60), inner_radius, rotation + 3);

        lcd_refresh_all(vram_);

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

_Noreturn void new_menu_page(void)
{
    krs_list_menu_t menu    = krs_new_list_menu(vram_);
    krs_list_item_t itens[] = {
        {
            .text   = "Musicas",
            .action = NULL,
        },
        {
            .text   = "Playlist",
            .action = NULL,
        },
        {
            .text   = "Podcast",
            .action = NULL,
        },
        {
            .text   = "Configuracoes",
            .action = NULL,
        },
        {
            .text   = "Fotos",
            .action = NULL,
        },
        {
            .text   = "Now Playing",
            .action = NULL,
        },
    };

    for (int i = 0; i < sizeof(itens) / sizeof(krs_list_item_t); ++i) {
        krs_list_menu_add_item(&menu, &itens[i]);
    }

    while (1) {
        for (int i = 0; i < menu.total_items; ++i) {
            krs_clear_all(vram_, BACKGROUND_COLOR);
            krs_list_menu_next_item(&menu);
            lcd_refresh_all(vram_);
            sleep_ms(1000);
        }

        for (int i = 0; i < menu.total_items; ++i) {
            krs_clear_all(vram_, BACKGROUND_COLOR);
            krs_list_menu_prev_item(&menu);
            lcd_refresh_all(vram_);
            sleep_ms(1000);
        }
    }
}

_Noreturn void color_test(void)
{
    uint8_t i = 0;

    while (1) {
        krs_clear_all(vram_, BACKGROUND_COLOR);
        krs_draw_rect(vram_, KRS_POINT(50, 50), KRS_POINT(50, 50), RED);
        lcd_refresh_all(vram_);
        sleep_ms(1000);
        i++;
    }
}

int main(void)
{
    stdio_init_all();

    printf("Initing lcd...\n");
    lcd_init();

    krs_clear_all(vram_, BACKGROUND_COLOR);
    lcd_refresh_all(vram_);

//        new_menu_page();
        menu_page();
    //    tape_page();
//    color_test();
}
