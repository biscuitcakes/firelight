//
// Created by alexs on 11/17/2023.
//

#include "game_screen.hpp"

#include <fstream>
#include <iterator>
#include <utility>

namespace FL::GUI {
GameScreen::GameScreen(std::unique_ptr<ContainerWidget> container,
                       FL::ControllerManager *manager,
                       FL::Graphics::Driver *driver, std::string romPath,
                       Library::Entry libEntry, SaveManager *saveMan)
    : Screen(std::move(container)), gameRomPath(std::move(romPath)),
      controllerManager(manager), gfxDriver(driver),
      libraryEntry(std::move(libEntry)), saveManager(saveMan) {}

bool GameScreen::handleEvent(Event &event) {
  if (event.type == FL::GUI::Event::TEST) {
    auto data = core->getMemoryData(libretro::SAVE_RAM);
    saveManager->write(libraryEntry.gameId, data);
    return true;
  }

  return Screen::handleEvent(event);
}

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

  auto saveData = saveManager->read(libraryEntry.gameId);
  if (!saveData.empty()) {
    core->writeMemoryData(libretro::SAVE_RAM, saveData.data());
  }

  //  std::filesystem::path path("save.whatever");
  //  std::ifstream saveFile(path, std::ios::binary);
  //  if (saveFile) {
  //    auto size = file_size(path);
  //
  //    char data[size];
  //    saveFile.read(data, size);
  //    saveFile.close();
  //
  //    core->writeMemoryData(libretro::SAVE_RAM, data);
  //  }
}

void GameScreen::exit() { Screen::exit(); }
void GameScreen::update(float deltaTime) { core->run(deltaTime); }
void GameScreen::render(const std::shared_ptr<WidgetPainter> &painter) {
  core->getVideo()->draw();
}

} // namespace FL::GUI
