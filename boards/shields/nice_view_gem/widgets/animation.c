/*
 *
 * Copyright (c) 2023 The ZMK Contributors
 * SPDX-License-Identifier: MIT
 *
 */

#include <zephyr/kernel.h>
#include <zephyr/random/random.h>

#include "animation.h"

LV_IMG_DECLARE(balloon);
LV_IMG_DECLARE(mountain);

/**
 * Peripheral art
 *
 * Picks one of the two nice!view images at random each time the
 * peripheral boots, then leaves it in place (no ongoing animation).
 **/

void draw_animation(lv_obj_t *widget) {
    lv_obj_t *art = lv_img_create(widget);

    bool random = sys_rand32_get() & 1;
    lv_image_set_src(art, random ? &balloon : &mountain);

    lv_obj_align(art, LV_ALIGN_TOP_LEFT, 0, 0);
}