// gui/gui.cpp – bare minimum, works instantly in simulator
#include "gui/gui.h"
#include "fonts.h"
#include "style_utils.h"
#include "gui/pages/page_home.h"

static lv_obj_t *header;
static lv_obj_t *footer;
static lv_obj_t *content;
static lv_obj_t *btn_home;

static GuiPage active_page = PAGE_COUNT; // sentinel so first gui_set_page runs

// Layout
static const lv_coord_t HEADER_HEIGHT = 36;
static const lv_coord_t FOOTER_HEIGHT = 32;

// Colors
static const lv_color_t COLOR_HEADER      = lv_color_hex(0x1C5C8C);
static const lv_color_t COLOR_SURFACE     = lv_color_hex(0xE9F2F9);
static const lv_color_t COLOR_TAB_ACTIVE  = lv_color_hex(0x86CC29);
static const lv_color_t COLOR_TAB_INACTIVE = lv_color_hex(0xD0D0D0);

static void tab_event_cb(lv_event_t *e);

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

    // Footer with one tab
    footer = lv_obj_create(scr);
    lv_obj_set_size(footer, LV_PCT(100), FOOTER_HEIGHT);
    lv_obj_align(footer, LV_ALIGN_BOTTOM_MID, 0, 0);
    lv_obj_set_style_bg_color(footer, COLOR_SURFACE, 0);
    lv_obj_set_style_border_width(footer, 0, 0);
    lv_obj_set_scrollbar_mode(footer, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_radius(header, 0, 0); // Square corners
    lv_obj_set_flex_flow(footer, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(footer, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);

    btn_home = lv_button_create(footer);
    lv_obj_set_style_bg_color(btn_home, COLOR_TAB_ACTIVE, 0);
    lv_obj_set_style_border_width(btn_home, 2, 0);
    lv_obj_set_style_border_color(btn_home, lv_color_black(), 0);
    lv_obj_t *lbl = lv_label_create(btn_home);
    lv_label_set_text(lbl, "My Button");
    lv_obj_set_style_text_font(lbl, FONT_FOOTER, 0);
    lv_obj_set_style_text_color(lbl, lv_color_black(), 0);
    lv_obj_set_style_text_opa(lbl, LV_OPA_COVER, 0);
    lv_obj_add_event_cb(btn_home, tab_event_cb, LV_EVENT_CLICKED, nullptr);
    lv_obj_set_style_pad_left(btn_home, 20, 0);
    lv_obj_set_style_pad_right(btn_home, 20, 0);
    lv_obj_set_style_pad_top(btn_home, 0, 0);
    lv_obj_set_style_pad_bottom(btn_home, 0, 0);

    // Show first page
    gui_set_page(PAGE_HOME);
}

void gui_set_page(GuiPage p)
{
    active_page = p;

    lv_obj_clean(content);
    if (p == PAGE_HOME) {
        page_home_create(content);
    }
}

static void tab_event_cb(lv_event_t *e)
{
    LV_UNUSED(e);
    gui_set_page(PAGE_HOME);
}
