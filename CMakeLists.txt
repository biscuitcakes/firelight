cmake_minimum_required(VERSION 3.26.4)
project(firelight)

#find_package(SDL REQUIRED)
#find_package(GLEW REQUIRED)
#find_package(OpenGL REQUIRED)

set(CMAKE_CXX_STANDARD 17)

include_directories(includes)
include_directories(includes/imgui)
include_directories(includes/SDL2)

link_directories(lib)

add_executable(firelight
        src/main.cpp
        src/libretro/core.cpp
        src/libretro/coreoption.cpp
        src/libretro/coreoption.hpp
        src/libretro/game.cpp
        src/libretro/game.hpp
        src/libretro/video.cpp
        src/libretro/video.hpp
        src/settings/user_settings.cpp
        src/settings/user_settings.h
        src/metrics/gameloop.cpp
        src/metrics/gameloop.hpp
        src/controller/controller_manager.cpp
        src/controller/controller_manager.hpp
        src/controller/controller_mapping.cpp
        src/controller/controller_mapping.hpp
        src/libretro/gamepad.cpp
        src/libretro/gamepad.hpp
        src/libretro/input.cpp
        src/libretro/input.hpp
        src/libretro/audio.cpp
        src/libretro/audio.hpp
        #        includes/imgui/imconfig.h
        #        includes/imgui/imgui.cpp
        #        includes/imgui/imgui.h
        #        includes/imgui/imgui_demo.cpp
        #        includes/imgui/imgui_draw.cpp
        #        includes/imgui/imgui_impl_opengl3.cpp
        #        includes/imgui/imgui_impl_opengl3.h
        #        includes/imgui/imgui_impl_opengl3_loader.h
        #        includes/imgui/imgui_impl_sdl2.cpp
        #        includes/imgui/imgui_impl_sdl2.h
        #        includes/imgui/imgui_internal.h
        #        includes/imgui/imgui_stdlib.cpp
        #        includes/imgui/imgui_stdlib.h
        #        includes/imgui/imgui_tables.cpp
        #        includes/imgui/imgui_widgets.cpp
        #        includes/imgui/imstb_rectpack.h
        #        includes/imgui/imstb_textedit.h
        #        includes/imgui/imstb_truetype.h
        #        includes/imgui/imgui_impl_opengl3.cpp
        src/gui/context.cpp
        src/gui/context.hpp
        src/gui/style.hpp
        src/gui/open_gl_painter.cpp
        src/gui/open_gl_painter.hpp
        src/gui/character.hpp
        src/graphics/shaders.hpp
        src/graphics/shaders.cpp
        src/gui/widgets/text.cpp
        src/gui/widgets/text.hpp
        src/graphics/color.hpp
        src/gui/widgets/base/new_widget.cpp
        src/gui/widgets/base/new_widget.hpp
        src/math/bbox.hpp
        src/math/bbox.cpp
        src/gui/widget_painter.hpp
        src/gui/widget_painter.cpp
        src/graphics/driver.hpp
        #        includes/GLfont/FontAtlas.cpp
        #        includes/GLfont/FTLabel.cpp
        #        includes/GLfont/GLFont.cpp
        #        includes/GLfont/GLUtils.cpp
)

target_link_libraries(firelight mingw32 SDL2main SDL2 glew32 opengl32 freetype)
target_compile_options(firelight PRIVATE -Werror -ggdb3 -O0)
