// fonts.h
#pragma once
#include <lvgl.h>

#define FONT_DEFAULT   (&lv_font_montserrat_14)
#define FONT_FOOTER    (&lv_font_montserrat_18)
#define FONT_HEADER    (&lv_font_montserrat_24)

// These are the real fonts from your .c files – must be extern
extern const lv_font_t lv_font_roboto_mono_40;
extern const lv_font_t lv_font_roboto_mono_46;

#define FONT_ROBOTO_40 (&lv_font_roboto_mono_40)
#define FONT_ROBOTO_46 (&lv_font_roboto_mono_46)
