// gui/gui.cpp – bare minimum, works instantly in simulator
#include "gui/gui.h"
#include "gui/fonts.h"
#include "style_utils.h"
#include "gui/pages/page_home.h"
#include "gui/pages/page_data.h"
#include "gui/pages/page_settings.h"

static lv_obj_t *header;
static lv_obj_t *footer;
static lv_obj_t *content;
static lv_obj_t *btn_home;
static lv_obj_t *btn_prev;
static lv_obj_t *btn_next;
static lv_obj_t *btn_settings;

static GuiPage active_page = PAGE_COUNT; // sentinel so first gui_set_page runs

// Layout
static const lv_coord_t HEADER_HEIGHT = 36;
static const lv_coord_t FOOTER_HEIGHT = 32;

// Colors
static const lv_color_t COLOR_HEADER      = lv_color_hex(0x1C5C8C);
static const lv_color_t COLOR_SURFACE     = lv_color_hex(0xE9F2F9);
static const lv_color_t COLOR_TAB_ACTIVE  = lv_color_hex(0x86CC29);
static const lv_color_t COLOR_TAB_INACTIVE = lv_color_hex(0xD0D0D0);

static void btn_home_event_cb(lv_event_t *e);
static void btn_prev_event_cb(lv_event_t *e);
static void btn_next_event_cb(lv_event_t *e);
static void btn_settings_event_cb(lv_event_t *e);

void gui_init()
{
    lv_obj_t *scr = lv_screen_active();
    lv_obj_set_style_bg_color(scr, COLOR_SURFACE, 0);

    // Header
    header = lv_obj_create(scr);
    lv_obj_set_size(header, LV_PCT(100), HEADER_HEIGHT);
    lv_obj_align(header, LV_ALIGN_TOP_MID, 0, 0);
    lv_obj_set_style_bg_color(header, COLOR_HEADER, 0);
    lv_obj_set_style_border_width(header, 0, 0);
    lv_obj_set_scrollbar_mode(header, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_radius(header, 0, 0); // Square corners

    lv_obj_t *title = lv_label_create(header);
    lv_label_set_text(title, "My Header");
    lv_obj_set_style_text_color(title, lv_color_white(), 0);
    lv_obj_set_style_text_opa(title, LV_OPA_COVER, 0);
    lv_obj_set_style_text_font(title, FONT_HEADER, 0);
    lv_obj_center(title);

    // Content area
    content = lv_obj_create(scr);
    lv_obj_set_size(content, LV_PCT(100), LV_SIZE_CONTENT);
    lv_obj_set_pos(content, 0, HEADER_HEIGHT);
    lv_obj_set_flex_flow(content, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(content, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    lv_obj_set_style_bg_color(content, COLOR_SURFACE, 0);
    lv_obj_set_style_border_width(content, 0, 0);

    // Footer with 4 buttons
    footer = lv_obj_create(scr);
    lv_obj_set_size(footer, LV_PCT(100), FOOTER_HEIGHT);
    lv_obj_align(footer, LV_ALIGN_BOTTOM_MID, 0, 0);
    lv_obj_set_style_bg_color(footer, COLOR_SURFACE, 0);
    lv_obj_set_style_border_width(footer, 0, 0);
    lv_obj_set_scrollbar_mode(footer, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_radius(footer, 0, 0);
    lv_obj_set_flex_flow(footer, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(footer, LV_FLEX_ALIGN_SPACE_EVENLY, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);

    // HOME button (text)
    btn_home = lv_button_create(footer);
    lv_obj_set_style_bg_color(btn_home, COLOR_TAB_ACTIVE, 0);
    lv_obj_set_style_border_width(btn_home, 2, 0);
    lv_obj_set_style_border_color(btn_home, lv_color_black(), 0);
    lv_obj_t *lbl_home = lv_label_create(btn_home);
    lv_label_set_text(lbl_home, "HOME");
    lv_obj_set_style_text_font(lbl_home, FONT_FOOTER, 0);
    lv_obj_set_style_text_color(lbl_home, lv_color_black(), 0);
    lv_obj_set_style_text_opa(lbl_home, LV_OPA_COVER, 0);
    lv_obj_add_event_cb(btn_home, btn_home_event_cb, LV_EVENT_CLICKED, nullptr);
    lv_obj_set_style_pad_left(btn_home, 15, 0);
    lv_obj_set_style_pad_right(btn_home, 15, 0);
    lv_obj_set_style_pad_top(btn_home, 0, 0);
    lv_obj_set_style_pad_bottom(btn_home, 0, 0);

    // Previous button (◄ symbol)
    btn_prev = lv_button_create(footer);
    lv_obj_set_style_bg_color(btn_prev, COLOR_TAB_INACTIVE, 0);
    lv_obj_set_style_border_width(btn_prev, 2, 0);
    lv_obj_set_style_border_color(btn_prev, lv_color_black(), 0);
    lv_obj_t *lbl_prev = lv_label_create(btn_prev);
    lv_label_set_text(lbl_prev, LV_SYMBOL_LEFT);
    lv_obj_set_style_text_font(lbl_prev, FONT_FOOTER, 0);
    lv_obj_set_style_text_color(lbl_prev, lv_color_black(), 0);
    lv_obj_set_style_text_opa(lbl_prev, LV_OPA_COVER, 0);
    lv_obj_add_event_cb(btn_prev, btn_prev_event_cb, LV_EVENT_CLICKED, nullptr);
    lv_obj_set_style_pad_left(btn_prev, 15, 0);
    lv_obj_set_style_pad_right(btn_prev, 15, 0);
    lv_obj_set_style_pad_top(btn_prev, 0, 0);
    lv_obj_set_style_pad_bottom(btn_prev, 0, 0);

    // Next button (► symbol)
    btn_next = lv_button_create(footer);
    lv_obj_set_style_bg_color(btn_next, COLOR_TAB_INACTIVE, 0);
    lv_obj_set_style_border_width(btn_next, 2, 0);
    lv_obj_set_style_border_color(btn_next, lv_color_black(), 0);
    lv_obj_t *lbl_next = lv_label_create(btn_next);
    lv_label_set_text(lbl_next, LV_SYMBOL_RIGHT);
    lv_obj_set_style_text_font(lbl_next, FONT_FOOTER, 0);
    lv_obj_set_style_text_color(lbl_next, lv_color_black(), 0);
    lv_obj_set_style_text_opa(lbl_next, LV_OPA_COVER, 0);
    lv_obj_add_event_cb(btn_next, btn_next_event_cb, LV_EVENT_CLICKED, nullptr);
    lv_obj_set_style_pad_left(btn_next, 15, 0);
    lv_obj_set_style_pad_right(btn_next, 15, 0);
    lv_obj_set_style_pad_top(btn_next, 0, 0);
    lv_obj_set_style_pad_bottom(btn_next, 0, 0);

    // Settings button (⚙ symbol)
    btn_settings = lv_button_create(footer);
    lv_obj_set_style_bg_color(btn_settings, COLOR_TAB_INACTIVE, 0);
    lv_obj_set_style_border_width(btn_settings, 2, 0);
    lv_obj_set_style_border_color(btn_settings, lv_color_black(), 0);
    lv_obj_t *lbl_settings = lv_label_create(btn_settings);
    lv_label_set_text(lbl_settings, LV_SYMBOL_SETTINGS);
    lv_obj_set_style_text_font(lbl_settings, FONT_FOOTER, 0);
    lv_obj_set_style_text_color(lbl_settings, lv_color_black(), 0);
    lv_obj_set_style_text_opa(lbl_settings, LV_OPA_COVER, 0);
    lv_obj_add_event_cb(btn_settings, btn_settings_event_cb, LV_EVENT_CLICKED, nullptr);
    lv_obj_set_style_pad_left(btn_settings, 15, 0);
    lv_obj_set_style_pad_right(btn_settings, 15, 0);
    lv_obj_set_style_pad_top(btn_settings, 0, 0);
    lv_obj_set_style_pad_bottom(btn_settings, 0, 0);

    // Show first page
    gui_set_page(PAGE_HOME);
}

void gui_set_page(GuiPage p)
{
    active_page = p;

    lv_obj_clean(content);
    switch (p) {
        case PAGE_HOME:
            page_home_create(content);
            break;
        case PAGE_DATA:
            page_data_create(content);
            break;
        case PAGE_SETTINGS:
            page_settings_create(content);
            break;
        default:
            break;
    }
}

static void btn_home_event_cb(lv_event_t *e)
{
    LV_UNUSED(e);
    gui_set_page(PAGE_HOME);
}

static void btn_prev_event_cb(lv_event_t *e)
{
    LV_UNUSED(e);
    int next_page = (int)active_page - 1;
    if (next_page < 0) {
        next_page = PAGE_COUNT - 1;
    }
    gui_set_page((GuiPage)next_page);
}

static void btn_next_event_cb(lv_event_t *e)
{
    LV_UNUSED(e);
    int next_page = ((int)active_page + 1) % PAGE_COUNT;
    gui_set_page((GuiPage)next_page);
}

static void btn_settings_event_cb(lv_event_t *e)
{
    LV_UNUSED(e);
    gui_set_page(PAGE_SETTINGS);
}
