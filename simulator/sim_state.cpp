// simulator/sim_state.cpp
#include "gui/gui.h"
#include "gui/gui_data.h"
#include <cstring>

// This line makes the function visible to main.cpp
extern "C" void gui_sim_init()
{
    strcpy(gui_data.current_screen, "home");
    gui_init();        // your real CNC GUI starts here
}
