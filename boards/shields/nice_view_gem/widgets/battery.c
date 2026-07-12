#include <zephyr/kernel.h>
#include "battery.h"
#include "../assets/custom_fonts.h"

LV_IMG_DECLARE(bolt);

static void draw_level(lv_obj_t *canvas, const struct status_state *state) {
    lv_draw_label_dsc_t label_left_dsc;
    init_label_dsc(&label_left_dsc, LVGL_FOREGROUND, &pixel_operator_mono, LV_TEXT_ALIGN_LEFT);

    char text[10] = {};

    sprintf(text, "%i%%", state->battery);
    lv_canvas_draw_text(canvas, 0, 1, 40, &label_left_dsc, text);
}

static void draw_charging_level(lv_obj_t *canvas, const struct status_state *state) {
    lv_draw_img_dsc_t img_dsc;
    lv_draw_img_dsc_init(&img_dsc);
    lv_draw_label_dsc_t label_left_dsc;
    init_label_dsc(&label_left_dsc, LVGL_FOREGROUND, &pixel_operator_mono, LV_TEXT_ALIGN_LEFT);

    char text[10] = {};
    sprintf(text, "%i%%", state->battery);

    lv_canvas_draw_text(canvas, 0, 1, 40, &label_left_dsc, text);

    // Measure the actual rendered width of the text so the bolt
    // can sit right after it, regardless of digit count.
    lv_point_t text_size;
    lv_txt_get_size(&text_size, text, &pixel_operator_mono, 0, 0, LV_COORD_MAX, LV_TEXT_FLAG_NONE);

    lv_canvas_draw_img(canvas, text_size.x + 2, 3, &bolt, &img_dsc);
}

void draw_battery_status(lv_obj_t *canvas, const struct status_state *state) {
    if (state->charging) {
        draw_charging_level(canvas, state);
    } else {
        draw_level(canvas, state);
    }
}