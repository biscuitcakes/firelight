//
// Created by alexs on 11/17/2023.
//

#include "game_screen.hpp"
#include "controller/controller_manager.hpp"

#include <utility>

namespace FL::GUI {
GameScreen::GameScreen(std::unique_ptr<ContainerWidget> container,
                       FL::ControllerManager *manager,
                       FL::Graphics::Driver *driver, std::string romPath)
    : Screen(std::move(container)), gameRomPath(std::move(romPath)),
      controllerManager(manager), gfxDriver(driver) {}

void GameScreen::enter() {
  core = std::make_unique<libretro::Core>(
      "/Users/alexs/git/ember-app/_cores/gambatte_libretro.dll", gfxDriver);

  core->setSystemDirectory(".");
  core->setSaveDirectory(".");
  core->init();

  libretro::Game game(gameRomPath);
  core->loadGame(&game);
  core->getVideo()->initialize(0, 0, 1280, 720);

  controllerManager->setLoadedCore(core.get());
}

void GameScreen::exit() { Screen::exit(); }
void GameScreen::update(float deltaTime) { core->run(deltaTime); }
void GameScreen::render(const std::shared_ptr<WidgetPainter> &painter) {
  core->getVideo()->draw();
}

} // namespace FL::GUI
