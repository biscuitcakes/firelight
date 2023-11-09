
#include "GL/glew.h"
#include "SDL2/SDL.h"
#include "controller/controller_manager.hpp"
#include "graphics/opengl/open_gl_driver.hpp"
#include "graphics/opengl/shaders.hpp"
#include "gui/context.hpp"
#include "gui/widgets/frame.hpp"
#include "gui/widgets/quick_menu.hpp"
#include "gui/widgets/text.hpp"
#include "imgui_impl_sdl2.h"
#include "libretro/core.hpp"
#include "metrics/gameloop.hpp"

#include <thread>

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

int main(int argc, char *argv[]) {
  const auto processor_count = std::thread::hardware_concurrency();
  printf("Got hardware concurrency: %d\n", processor_count);

  // Initialize SDL
  if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
    printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    return 1;
  }

  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

  // Create window
  auto window =
      SDL_CreateWindow("Firelight", SDL_WINDOWPOS_UNDEFINED,
                       SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT,
                       SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL |
                           SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);

  if (window == nullptr) {
    printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
    return 1;
  }

  float hDpi = 0;
  float vDpi = 0;
  float dDpi = 0;
  SDL_GetDisplayDPI(SDL_GetWindowDisplayIndex(window), &dDpi, &hDpi, &vDpi);

  printf("DPI values: d: %f h: %f v: %f", dDpi, hDpi, vDpi);

  SDL_GL_CreateContext(window);

  SDL_SetWindowMinimumSize(window, 160, 144); // TODO set based on core

  if (GLEW_OK != glewInit()) {
    exit(1);
  }
  SDL_GL_SetSwapInterval(1);

  FL::Graphics::Shaders::initializeAll();

  auto core = std::make_unique<libretro::Core>(
      "/Users/alexs/git/ember-app/_cores/snes9x_libretro.dll");

  core->setSystemDirectory(".");
  core->setSaveDirectory(".");
  core->init();

  libretro::Game game("/Users/alexs/git/ember-app/_games/smw.smc");
  core->loadGame(&game);
  core->getVideo()->initialize(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

  FL::ControllerManager conManager;
  conManager.setLoadedCore(core.get());

  Uint64 NOW = SDL_GetPerformanceCounter();
  Uint64 LAST = 0;
  double deltaTime = 0;

  FL::GameLoopMetrics loopMetrics;
  Uint64 frameBegin;
  Uint64 frameEnd;
  double frameDiff;

  FL::Math::BBox box(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

  FL::Graphics::Driver *driver =
      new FL::Graphics::OpenGLDriver(SCREEN_WIDTH, SCREEN_HEIGHT);
  FL::GUI::Context guiContext(box, driver);

  FL::GUI::Frame frame;
  //  frame.addChild(new FL::GUI::Text("heya"), FL::Math::BBox(100, 100, 400,
  //  400)); guiContext.addWidget(&frame);

  FL::GUI::QuickMenu quickMenu;
  quickMenu.addItem("Continue");
  quickMenu.addItem("Rewind");
  quickMenu.addItem("Load Suspend Point");
  quickMenu.addItem("Create Suspend Point");
  quickMenu.addItem("Game Settings");
  quickMenu.addItem("Restart Game");
  quickMenu.addItem("Quit Game");

  frame.addChild(&quickMenu, FL::Math::BBox(200, 220, 220, 280));

  guiContext.addWidget(&frame);

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
      guiContext.handleSdlEvent(&ev);
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
          core->getVideo()->setScreenDimensions(0, 0, width, height);
          guiContext.setWorkArea(
              FL::Math::BBox(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT));
          break;
        }
      }
    }

    int width, height;
    SDL_GetWindowSize(window, &width, &height);
    glViewport(0, 0, width, height);
    //
    glEnable(GL_BLEND);
    core->run(deltaTime);
    core->getVideo()->draw();
    frameEnd = SDL_GetPerformanceCounter();
    frameDiff = ((frameEnd - frameBegin) * 1000 /
                 (double)SDL_GetPerformanceFrequency());

    //    glDisable(GL_DEPTH_TEST);

    //        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    //        glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
    guiContext.render();
    //
    loopMetrics.recordFrameWorkDuration(frameDiff);
    SDL_GL_SwapWindow(window);
    glFinish();

    // todo: measure post-swap somehow?
  }
  // Destroy window
  SDL_DestroyWindow(window);

  // Quit SDL subsystems
  SDL_Quit();

  return 0;
}
