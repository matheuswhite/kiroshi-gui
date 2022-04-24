/**
 * @file list_menu.c
 * @author Matheus T. dos Santos (tenoriomatheus0@gmail.com)
 * @brief
 * @version 0.1
 * @date 22/04/2022
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "kiroshi/list_menu.h"

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

static void draw_list_item(uint16_t *vram, krs_list_item_t *item, size_t idx);

krs_list_menu_t krs_new_list_menu(uint16_t *vram)
{
    return (krs_list_menu_t){
        .vram              = vram,
        .first_item        = NULL,
        .current_item      = NULL,
        .start_screen_item = NULL,
        .total_items       = 0,
    };
}

void krs_list_menu_reset(krs_list_menu_t *menu)
{
    menu->current_item      = menu->first_item;
    menu->start_screen_item = menu->first_item;
}

void krs_list_menu_add_item(krs_list_menu_t *menu, krs_list_item_t *item)
{
    if (menu->total_items == 0) {
        menu->first_item->next_item = NULL;
        menu->first_item->prev_item = NULL;

        menu->first_item                   = item;
        menu->start_screen_item            = item;
        menu->current_item                 = item;
        menu->current_item->is_highlighted = true;
    } else {
        krs_list_item_t *last_item = menu->first_item;

        for (int i = 0; i < menu->total_items - 1; ++i) {
            last_item = last_item->next_item;
        }

        last_item->next_item = item;
        item->prev_item      = last_item;
        item->next_item      = NULL;
    }

    item->index = menu->total_items;
    menu->total_items++;
}

void krs_list_menu_add_many_itens(krs_list_menu_t *menu, krs_list_item_t *itens,
                                  size_t size)
{
    for (int i = 0; i < size; ++i) {
        krs_list_menu_add_item(menu, &itens[i]);
    }
}

void krs_list_menu_next_item(krs_list_menu_t *menu)
{
    if (menu->current_item->next_item != NULL) {
        menu->current_item->is_highlighted = false;
        menu->current_item                 = menu->current_item->next_item;
        menu->current_item->is_highlighted = true;

        if (menu->current_item->index - menu->start_screen_item->index >= 6) {
            menu->start_screen_item = menu->start_screen_item->next_item;
        }

        krs_draw_list_menu(menu);
    }
}

void krs_list_menu_prev_item(krs_list_menu_t *menu)
{
    if (menu->current_item->prev_item != NULL) {
        menu->current_item->is_highlighted = false;
        menu->current_item                 = menu->current_item->prev_item;
        menu->current_item->is_highlighted = true;

        if (menu->start_screen_item->index > menu->current_item->index) {
            menu->start_screen_item = menu->start_screen_item->prev_item;
        }

        krs_draw_list_menu(menu);
    }
}

void krs_list_menu_sel_item(krs_list_menu_t *menu)
{
    if (menu->current_item != NULL) {
        menu->current_item->action();
    }
}

void krs_draw_list_menu(krs_list_menu_t *menu)
{
    krs_list_item_t *item = menu->start_screen_item;

    for (int i = 0; i < 6 && item != NULL; ++i, item = item->next_item) {
        draw_list_item(menu->vram, item, i);
    }
}

static void draw_list_item(uint16_t *vram, krs_list_item_t *item, size_t idx)
{
    uint16_t start_y = START_Y + idx * (BOX_HEIGHT + 1 + LINE_OFFSET);

    if (item->is_highlighted) {
        krs_draw_rect(vram, KRS_POINT(START_X, start_y), KRS_POINT(XSIZE, 1), TEXT_COLOR);
        krs_draw_rect(vram, KRS_POINT(START_X, start_y + LINE_OFFSET + 1),
                      KRS_POINT(XSIZE, BOX_HEIGHT), TEXT_COLOR);
        krs_draw_rect(
            vram,
            KRS_POINT(START_X, start_y + LINE_OFFSET + 1 + BOX_HEIGHT + LINE_OFFSET),
            KRS_POINT(XSIZE, 1), TEXT_COLOR);
    }

    krs_draw_string(vram,
                    KRS_POINT(START_X + 4 + (item->is_highlighted ? 4 : 0),
                              start_y + LINE_OFFSET + 1 + 3),
                    item->text, item->is_highlighted ? BACKGROUND_COLOR : TEXT_COLOR);
}
