/**
 * @file list_menu.h
 * @author Matheus T. dos Santos (tenoriomatheus0@gmail.com)
 * @brief
 * @version 0.1
 * @date 22/04/2022
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef LIST_MENU_H
#define LIST_MENU_H

#include "kiroshi/primitives.h"
#include "kiroshi/runtime.h"

typedef struct krs_list_item {
    char *text;
    bool is_highlighted;
    void (*action)(void);
    struct krs_list_item *next_item;
    struct krs_list_item *prev_item;
    size_t index;
    size_t _screen_idx;
    krs_animation_t anim;
} krs_list_item_t;

typedef struct {
    krs_list_item_t *first_item;
    krs_list_item_t *current_item;
    krs_list_item_t *start_screen_item;
    size_t total_items;
} krs_list_menu_t;

// TODO add option to rollover the list

krs_list_menu_t krs_new_list_menu();

void krs_list_menu_reset(krs_list_menu_t *menu);

void krs_list_menu_add_item(krs_list_menu_t *menu, krs_list_item_t *item);

void krs_list_menu_add_many_itens(krs_list_menu_t *menu, krs_list_item_t *itens,
                                  size_t size);

void krs_list_menu_next_item(krs_list_menu_t *menu);

void krs_list_menu_prev_item(krs_list_menu_t *menu);

void krs_list_menu_sel_item(krs_list_menu_t *menu);

krs_page_t krs_list_menu_get_page(krs_list_menu_t *menu);

#endif  // LIST_MENU_H
