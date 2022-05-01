/**
 * @file hardware.h
 * @author Matheus T. dos Santos (matheus.santos@edge.ufal.br)
 * @brief
 * @version 0.1
 * @date 30/04/2022
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef HARDWARE_H
#define HARDWARE_H

#include <stdint.h>

#define SCREEN_WIDTH 160
#define SCREEN_HEIGHT 128

int krs_hardware_init();

void krs_hardware_reset();

void krs_hardware_refresh(uint16_t *vram, uint16_t x, uint16_t y, uint16_t w, uint16_t h);

void krs_hardware_refresh_all(uint16_t *vram);

void krs_hardware_sleep_ms(uint32_t ms);

#endif  // HARDWARE_H
