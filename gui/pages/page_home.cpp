#include "lvgl.h"
#include "gui_data.h"
#include "gui/fonts.h"

static lv_obj_t* label;

void page_home_create(lv_obj_t* parent) {
    label = lv_label_create(parent);
    lv_label_set_text(label, "LVGL Simulator on macOS!");
    lv_obj_set_style_text_align(label, LV_TEXT_ALIGN_CENTER, 0);

    lv_obj_t* desc_label = lv_label_create(parent);
    lv_label_set_text(desc_label,
        "The GUI code is completely independent "
        "from the program logic - you design the interface, perfect the "
        "look and feel, and test the user experience entirely in the simulator.");
    lv_obj_set_style_text_font(desc_label, FONT_DEFAULT, 0);
    lv_obj_set_style_text_color(desc_label, lv_color_hex(0x1D242F), 0);
    lv_obj_set_style_text_opa(desc_label, LV_OPA_COVER, 0);
    lv_obj_set_style_border_width(desc_label, 0, 0);
    lv_label_set_long_mode(desc_label, LV_LABEL_LONG_WRAP);
    lv_obj_set_width(desc_label, LV_PCT(90));
    lv_obj_align_to(desc_label, label, LV_ALIGN_OUT_BOTTOM_MID, 0, 10);
    lv_obj_set_style_text_font(label, FONT_DEFAULT, 0);
    lv_obj_set_style_text_color(label, lv_color_hex(0x1D242F), 0);
    lv_obj_set_style_text_opa(label, LV_OPA_COVER, 0);
    lv_obj_set_style_border_width(label, 0, 0);
    lv_label_set_long_mode(label, LV_LABEL_LONG_WRAP);
    lv_obj_set_width(label, LV_PCT(90));
    lv_obj_center(label);
}

void page_home_update() {
    lv_label_set_text_fmt(label,
        "Screen: %s\nValue1: %.2f\nMessage: %s",
        gui_data.current_screen,
        gui_data.value1,
        gui_data.message[0] ? gui_data.message : "—");
}
