#!/bin/bash
# simulator/build_sim.sh – compile only

set -euo pipefail

INCLUDES="-I. -Ilvgl -Igui -Igui/pages -Igui/fonts"

# Build the generated LVGL font sources as plain C ahead of time to avoid
# C++ mangling and conflicting -std flags.
FONT_OBJS=()
for font_src in gui/fonts/*.c; do
    font_obj="${font_src%.c}.o"
    clang -c "$font_src" $INCLUDES -o "$font_obj"
    FONT_OBJS+=("$font_obj")
done

clang++ simulator/main.cpp simulator/sim_state.cpp \
    gui/*.cpp gui/pages/*.cpp "${FONT_OBJS[@]}" \
        $INCLUDES \
        -std=c++17 \
        lvgl/liblvgl.a -lSDL2 -o LVGL_SIM
