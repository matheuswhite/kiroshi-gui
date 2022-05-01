#include "kiroshi/primitives.h"
/**
 * @file sdl2.c
 * @author Matheus T. dos Santos (matheus.santos@edge.ufal.br)
 * @brief
 * @version 0.1
 * @date 28/04/2022
 *
 * @copyright Copyright (c) 2022
 *
 */
#include <stdio.h>
#include "kiroshi/list_menu.h"
#include "kiroshi/primitives.h"
#include "kiroshi/runtime.h"
#include "kiroshi/hardware.h"

#define loop while (1)

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

static uint16_t vram[SCREEN_HEIGHT * SCREEN_WIDTH];

void color_test()
{
    uint8_t i = 0;

    while (true) {
        krs_clear_all(vram, BACKGROUND_COLOR);
        krs_draw_rect(vram, KRS_POINT(50, 50), KRS_POINT(50, 50), RED);
        krs_hardware_refresh_all(vram);
        krs_hardware_sleep_ms(1000);
        i++;
    }
}

_Noreturn void runtime_test()
{
    krs_list_menu_t main_menu    = krs_new_list_menu();
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
        {
            .text   = "Videos",
            .action = NULL,
        },
        {
            .text   = "Chamadas",
            .action = NULL,
        },
    };
    size_t total_itens = sizeof(itens) / sizeof(krs_list_item_t);
    krs_list_menu_add_many_itens(&main_menu, itens, total_itens);
    krs_page_t main_page = krs_list_menu_get_page(&main_menu);
//    krs_runtime_push_page(&main_page);

    krs_calendar_t calendar = krs_new_calendar(3, 5, 2022, 3);
    krs_page_t calendar_page = krs_calendar_get_page(&calendar);
    krs_runtime_push_page(&calendar_page);

    krs_runtime_set_status("Listening", KRS_COLOR(6, 6, 0));
    krs_runtime_set_battery_percentage(50);

    bool is_down = true;
    uint8_t count = 0;
    size_t time_count = 0;

    loop {
        if (time_count >= 13) {
            time_count = 0;

            if (is_down) {
                krs_list_menu_next_item(&main_menu);
            } else {
                krs_list_menu_prev_item(&main_menu);
            }

            count++;

            if (count >= total_itens - 1) {
                count = 0;
                is_down = !is_down;
            }
        }

        time_count++;
        krs_runtime_tick();
    }
}

int main()
{
    printf("Initing lcd...\n");
    krs_hardware_init();

    krs_clear_all(vram, BACKGROUND_COLOR);
    krs_hardware_refresh_all(vram);

//    color_test();
//    new_menu_page();
    runtime_test();
}
