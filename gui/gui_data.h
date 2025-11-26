// gui/gui_data.h
#pragma once
#include <stdbool.h>
#include <stdint.h>

typedef struct {
    // ────── Always needed ──────
    char        current_screen[24];   // "home", "servo", "lipo", "settings"
    int         selected_index;       // highlighted item

    // ────── Generic values – rename in your head ──────
    float       value1, value2, value3, value4;
    int         int1, int2;

    // ────── Text & messages ──────
    char        message[64];
    uint32_t    message_timeout_ms;   // 0 = hidden

    // ────── Flags (uncomment what you need) ──────
    bool        is_running;
    // bool     is_connected;
    // bool     low_battery;

    // ────── Project-specific – just uncomment & rename ──────
    // RC / Servo tester
    // int      servo_channel;
    // int      servo_pulse_us;
    // float    lipo_cell[8];

    // CNC / motion
    // float    pos_x, pos_y, pos_z;
    // char     machine_state[16];

    // Clock / weather
    // int      hour, minute;
    // float    temperature;

    // ────── Magic escape hatch (your private playground) ──────
    uint8_t     payload[256];   // cast to whatever you want
} gui_data_t;

// The one global instance
extern gui_data_t gui_data;
