
#include "GL/glew.h"
#include "SDL2/SDL.h"
#include "app/controller/controller_manager.hpp"
#include "app/db/game_repository.hpp"
#include "app/db/game_scanner.hpp"
#include "app/db/in_memory_game_repository.hpp"
#include "app/libretro/core.hpp"
#include "app/metrics/gameloop.hpp"
#include "app/screen_thing.hpp"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_sdl2.h"
#include "lib/graphics/opengl/open_gl_driver.hpp"
#include "lib/graphics/opengl/shaders.hpp"
#include "lib/gui/screens/screen.hpp"
#include "lib/gui/screens/screen_manager.hpp"
#include "lib/gui/vertical_box_layout_manager.hpp"
#include "lib/gui/widget_factory.hpp"
#include "lib/gui/widgets/container_widget.hpp"

#include <thread>

using namespace FL::GUI;

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

int main(int argc, char *argv[]) {
  if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
    printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    return 1;
  }

  auto window =
      SDL_CreateWindow("Firelight", SDL_WINDOWPOS_UNDEFINED,
                       SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT,
                       SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL |
                           SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);

  if (window == nullptr) {
    printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
    return 1;
  }

  auto context = SDL_GL_CreateContext(window);
  SDL_SetWindowMinimumSize(window, 160, 144); // TODO set based on core

  if (GLEW_OK != glewInit()) {
    exit(1);
  }
  SDL_GL_SetSwapInterval(1);

  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGui::StyleColorsDark();

  // Setup Platform/Renderer backends
  ImGui_ImplSDL2_InitForOpenGL(window, context);
  ImGui_ImplOpenGL3_Init("#version 130");

  FL::DB::InMemoryGameRepository repository("games.json", "romhacks.json");
  FL::DB::GameScanner scanner(&repository);

  Uint64 NOW = SDL_GetPerformanceCounter();
  Uint64 LAST = 0;
  double deltaTime = 0;

  FL::GameLoopMetrics loopMetrics;
  Uint64 frameBegin;
  Uint64 frameEnd;
  double frameDiff;

  FL::Graphics::Shaders::initializeAll();
  FL::Graphics::Driver *driver =
      new FL::Graphics::OpenGLDriver(SCREEN_WIDTH, SCREEN_HEIGHT);
  auto widgetPainter = std::make_shared<WidgetPainter>(driver);

  FL::ControllerManager conManager;

  FL::GUI::WidgetFactory factory;

  FL::GUI::ScreenManager manager;
  FL::GUI::ScreenThing thing(&manager, &factory);
  FL::SaveManager saveManager;

  auto results =
      scanner.scanDirectory("/Users/alexs/git/firelight/_data/_games", true);
  thing.buildHomeScreen(results);
  thing.buildGameScreen(&conManager, driver, &saveManager);

  manager.pushScreen(thing.getInitialScreen());

  bool running = true;
  while (running) {
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    frameBegin = SDL_GetPerformanceCounter();
    LAST = NOW;
    NOW = SDL_GetPerformanceCounter();

    deltaTime = ((NOW - LAST) * 1000 / (double)SDL_GetPerformanceFrequency());

    SDL_Event ev;
    while (SDL_PollEvent(&ev)) {
      manager.handleSdlEvent(&ev);
      ImGui_ImplSDL2_ProcessEvent(&ev);
      switch (ev.type) {
      case SDL_CONTROLLERDEVICEADDED: {
        conManager.handleControllerAddedEvent(ev.cdevice.which);
        //            printf("holy shit we got a controller\n");
        //            auto controller =
        //            SDL_GameControllerOpen(ev.cdevice.which);
        //            printf("SDL
        //            error? %s\n", SDL_GetError()); auto gamepad = new
        //            libretro::Gamepad(controller);
        //            core->plugInGamepad(0,
        //            gamepad);
        break;
      }
      case SDL_CONTROLLERDEVICEREMOVED:
        printf("bye bye controller\n");
        //            if (controller &&
        //                ev.cdevice.which ==
        //                    SDL_JoystickInstanceID(
        // SDL_GameControllerGetJoystick(controller)))
        //                        {
        //              SDL_GameControllerClose(controller);
        //            }
        break;
      case SDL_QUIT:
        running = false;
        break;
      case SDL_WINDOWEVENT:
        switch (ev.window.event) {
        case SDL_WINDOWEVENT_CLOSE:
          running = false;
          break;
        case SDL_WINDOWEVENT_RESIZED:
          auto width = ev.window.data1;
          auto height = ev.window.data2;
          //          core->getVideo()->setScreenDimensions(0, 0, width,
          //          height);
          break;
        }
      }
    }

    //    ImGui_ImplOpenGL3_NewFrame();
    //    ImGui_ImplSDL2_NewFrame();
    //    ImGui::NewFrame();

    int width, height;
    SDL_GetWindowSize(window, &width, &height);

    glViewport(0, 0, width, height);

    manager.update(0);
    manager.render(widgetPainter);
    frameEnd = SDL_GetPerformanceCounter();
    frameDiff = ((frameEnd - frameBegin) * 1000 /
                 (double)SDL_GetPerformanceFrequency());

    //    glDisable(GL_DEPTH_TEST);

    //        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    //        glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
    //    glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
    //    ImGui::Render();
    //
    loopMetrics.recordFrameWorkDuration(frameDiff);
    //    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    SDL_GL_SwapWindow(window);
    glFinish();

    // todo: measure post-swap somehow?
  }

  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
