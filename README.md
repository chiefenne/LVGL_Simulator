# LVGL Project Template and Simulator

A complete LVGL v9.4 project template with desktop simulator and embedded firmware support. Build once, run everywhere - from desktop preview to ESP32 hardware.

> **Note:** This is a personal project template tailored to my workflow. If you're looking for other LVGL simulator options, check out the [official LVGL PC port](https://github.com/lvgl/lv_port_pc_vscode) or the [LVGL GUI Builder](https://github.com/qdsang/lv_gui_builder).

**The key advantage:** Develop your GUI entirely on your computer (macOS, Linux, or Windows) without the slow upload-test-debug cycle of embedded development. The simulator lets you iterate quickly - make changes, rebuild in seconds, and see results immediately. No need to flash firmware, wait for uploads, or physically interact with hardware during GUI development.

The GUI code is **completely independent** from the program logic - you design the interface, perfect the look and feel, and test the user experience entirely in the simulator. Once satisfied, the same GUI code deploys to your embedded device without modification. The separation means you can develop beautiful, responsive interfaces fast on your desktop, then integrate with hardware logic later.

## Features

- **Desktop Simulator**: Fast GUI development with SDL2 (macOS/Linux/Windows)
- **Embedded Ready**: ESP32/PlatformIO firmware skeleton included
- **Shared GUI Code**: Write your interface once, use it everywhere
- **Page-Based Navigation**: Multi-page architecture with built-in navigation system
- **Full-Screen Rendering**: Optimized for smooth 320×240 displays
- **Custom Fonts**: Easy integration of LVGL-converted fonts
- **Modern C++17**: Clean, maintainable codebase

## Project Structure

```
LVGL_Template_2025/
├── simulator/              # Desktop preview (macOS/Linux/Windows)
│   ├── main.cpp           # SDL2 wrapper for LVGL
│   ├── sim_state.cpp      # Mock data provider
│   └── build_sim.sh       # One-click build script
│
├── firmware/              # ESP32/PlatformIO project
│   ├── platformio.ini
│   └── src/
│       ├── main.cpp       # Arduino setup()/loop()
│       └── state_provider.cpp  # Hardware data interface
│
├── gui/                   # Shared GUI code
│   ├── gui.cpp/h         # Main GUI initialization
│   ├── gui_data.h        # Data structure interface
│   ├── fonts/            # Custom LVGL fonts (.c files)
│   └── pages/            # Screen implementations
│       ├── page_home.cpp/h
│       └── ...
│
├── lvgl/                 # LVGL library (v9.4.0)
└── template_files/       # Configuration templates
```

## Quick Start

### Prerequisites

- **macOS/Linux**: clang/gcc, CMake, SDL2
- **macOS**: `brew install sdl2 cmake`
- **Ubuntu/Debian**: `sudo apt install libsdl2-dev cmake build-essential`

### Installation

1. **Clone the repository**
   ```bash
   git clone https://github.com/yourusername/LVGL_Template_2025.git
   cd LVGL_Template_2025
   ```

2. **Download and build LVGL**
   ```bash
   curl -L https://github.com/lvgl/lvgl/archive/refs/tags/v9.4.0.tar.gz -o lvgl.tar.gz
   tar -xzvf lvgl.tar.gz
   rm lvgl.tar.gz
   mv lvgl-9.4.0 lvgl
   cp template_files/lv_conf.h lvgl/
   ```

3. **Build LVGL library**
   ```bash
   cd lvgl
   mkdir -p build && cd build
   cmake .. -DLVGL_BUILD_EXAMPLES=OFF -DCMAKE_BUILD_TYPE=Release -DLVGL_BUILD_STATIC=ON
   make -j$(nproc)
   cd ..
   ln -sf build/lib/liblvgl.a liblvgl.a
   cd ..
   ```

4. **Build and run simulator**
   ```bash
   bash simulator/build_sim.sh
   ./LVGL_SIM
   ```

   **Note:** The build script `simulator/build_sim.sh` must be run from the project root directory and is currently configured for macOS. For Linux or Windows, you'll need to adapt the compiler flags and library paths in the script.

## Customization

### Adding Custom Fonts

1. Convert TTF fonts using [LVGL Font Converter](https://lvgl.io/tools/fontconverter)
2. Save the generated `.c` file to `gui/fonts/`
3. Declare in `fonts.h`:
   ```cpp
   extern const lv_font_t lv_font_yourfont_24;
   #define FONT_CUSTOM (&lv_font_yourfont_24)
   ```
4. Fonts are automatically compiled by `build_sim.sh`

### Creating New Pages

1. Create `gui/pages/page_yourname.cpp` and `.h`
2. Implement `page_yourname_create(lv_obj_t* parent)`
3. Add to `gui.h` enum and `gui.cpp` switch statement

### Styling

Modify colors and layout constants in `gui/gui.cpp`:
```cpp
static const lv_color_t COLOR_HEADER = lv_color_hex(0x1C5C8C);
static const lv_coord_t HEADER_HEIGHT = 36;
```

## Configuration

- **Display size**: Edit `HRES` and `VRES` in `simulator/main.cpp`
- **Color depth**: Set `LV_COLOR_DEPTH` in `lvgl/lv_conf.h` (default: 16-bit RGB565)
- **Render mode**: Full-screen rendering enabled by default for stability

## Architecture Notes

### GUI Layout Structure

The template uses a **three-area layout** that can be adapted to your application needs:

- **Header Area** (36px): Displays page title and navigation context
- **Content Area** (dynamic): Main application content, changes per page
- **Footer Area** (32px): Navigation and settings controls

**Current Implementation:**
- Footer contains a HOME button for navigation
- Ready to expand with additional navigation controls

**Planned Enhancements:**
- 4-button footer layout: HOME, ◄ (backward), ► (forward), SETTINGS (⚙)
- Navigation arrows using LVGL symbols or custom icons
- Settings button with gear symbol instead of text
- Header updates to show current page context

This layout structure is defined in `gui/gui.cpp` and can be customized for different screen sizes and application requirements.

### Rendering Strategy

The simulator uses **full-screen rendering mode** for simplicity and reliability:
- Set via `lv_display_set_render_mode(disp, LV_DISPLAY_RENDER_MODE_FULL)`
- Always redraws the entire 320×240 display on updates
- Avoids partial update complications (stride handling, offset calculations)
- Performance is excellent for this display size (~76KB per frame)
- Eliminates rendering artifacts from incomplete updates

### Font Compilation

Custom fonts must be compiled as C (not C++) to avoid name mangling:
```bash
clang -c gui/fonts/*.c  # Preserves extern "C" linkage
```
The build script automatically handles this for all `.c` files in `gui/fonts/`.

## Troubleshooting

**Black screen or corrupted graphics?**
- Ensure `LV_COLOR_DEPTH` matches SDL pixel format (RGB565 = 16-bit)
- Verify draw buffer is properly initialized

**Font linking errors?**
- Check fonts are being compiled with `clang -c` (not `clang++`)
- Verify font declarations in `fonts.h` match `.c` file names

**Button rendering issues?**
- Full-screen render mode is enabled by default to prevent partial update artifacts

## License

This template is provided as-is for educational and commercial use. LVGL is licensed under MIT.

## Contributing

Contributions welcome! Please open an issue or PR for improvements.

## Resources

- [LVGL Documentation](https://docs.lvgl.io/)
- [LVGL Forum](https://forum.lvgl.io/)
- [Font Converter](https://lvgl.io/tools/fontconverter)
- [Image Converter](https://lvgl.io/tools/imageconverter)
