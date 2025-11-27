#include "lvgl.h"
#include "gui_data.h"
#include "gui/fonts.h"

static lv_obj_t* label;

void page_data_create(lv_obj_t* parent) {
    label = lv_label_create(parent);
    lv_label_set_text(label, "Data Page");
    lv_obj_set_style_text_align(label, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_set_style_text_font(label, FONT_DEFAULT, 0);
    lv_obj_set_style_text_color(label, lv_color_hex(0x1D242F), 0);
    lv_obj_set_style_text_opa(label, LV_OPA_COVER, 0);
    lv_obj_set_style_border_width(label, 0, 0);
    lv_label_set_long_mode(label, LV_LABEL_LONG_WRAP);
    lv_obj_set_width(label, LV_PCT(90));
    lv_obj_center(label);
}

void page_data_update() {
    lv_label_set_text_fmt(label,
        "Data Display\n\nValue1: %.2f\nMessage: %s",
        gui_data.value1,
        gui_data.message[0] ? gui_data.message : "—");
}
