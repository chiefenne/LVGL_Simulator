// simulator/main.cpp
#define LV_CONF_INCLUDE_SIMPLE
#include "lvgl.h"
#include <SDL2/SDL.h>
#include <vector>
#include <cstring>
#include "gui/gui.h" // is not a compatibility shim, so we need the folder
#include "gui/gui_data.h"

constexpr int HRES = 320;
constexpr int VRES = 240;

static SDL_Texture*  tex  = nullptr;
static SDL_Renderer* ren  = nullptr;

static void flush_cb(lv_display_t* disp, const lv_area_t* area, uint8_t* data) {
    const int w = lv_area_get_width(area);
    const int h = lv_area_get_height(area);
    SDL_Rect r{area->x1, area->y1, w, h};

    // With LV_DISPLAY_RENDER_MODE_FULL, we always get the full screen,
    // so we can use the data pointer directly
    lv_draw_buf_t* draw_buf = lv_display_get_buf_active(disp);
    const int stride = draw_buf->header.stride;

    SDL_UpdateTexture(tex, &r, draw_buf->data, stride);
    SDL_RenderCopy(ren, tex, nullptr, nullptr);
    SDL_RenderPresent(ren);
    lv_display_flush_ready(disp);
}extern "C" void gui_sim_init();   // defined in sim_state.cpp

int main(int argc, char** argv) {
    int w = (argc >= 3) ? atoi(argv[1]) : HRES;
    int h = (argc >= 3) ? atoi(argv[2]) : VRES;

    lv_init();
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *win = SDL_CreateWindow("LVGL Simulator", 1000, 800, w, h,
        SDL_WINDOW_ALWAYS_ON_TOP | SDL_WINDOW_ALLOW_HIGHDPI);
    ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
    tex = SDL_CreateTexture(ren, SDL_PIXELFORMAT_RGB565,
        SDL_TEXTUREACCESS_STREAMING, w, h);

    lv_display_t* disp = lv_display_create(w, h);
    static lv_draw_buf_t draw_buf;
    static std::vector<lv_color_t> draw_buf_mem;
    draw_buf_mem.resize(static_cast<size_t>(w) * h);
    lv_result_t buf_res = lv_draw_buf_init(&draw_buf, w, h, LV_COLOR_FORMAT_NATIVE,
                                           LV_STRIDE_AUTO, draw_buf_mem.data(),
                                           draw_buf_mem.size() * sizeof(lv_color_t));
    if(buf_res != LV_RESULT_OK) {
        return 1;
    }
    lv_display_set_draw_buffers(disp, &draw_buf, nullptr);
    lv_display_set_flush_cb(disp, flush_cb);
    lv_display_set_render_mode(disp, LV_DISPLAY_RENDER_MODE_FULL);

    // Mouse = touch
    lv_indev_t* indev = lv_indev_create();
    lv_indev_set_type(indev, LV_INDEV_TYPE_POINTER);
    lv_indev_set_read_cb(indev, [](lv_indev_t*, lv_indev_data_t* d) {
        int x, y; Uint32 b = SDL_GetMouseState(&x, &y);
        d->point.x = x; d->point.y = y;
        d->state = (b & SDL_BUTTON_LMASK) ? LV_INDEV_STATE_PRESSED : LV_INDEV_STATE_RELEASED;
    });

    gui_sim_init();   // ← starts your real GUI

    Uint32 last = SDL_GetTicks();
    while (true) {
        Uint32 now = SDL_GetTicks();
        lv_tick_inc(now - last);
        last = now;
        lv_timer_handler();
        SDL_Event e;
        while (SDL_PollEvent(&e)) if (e.type == SDL_QUIT) return 0;
        SDL_Delay(5);
    }
}
