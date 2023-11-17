//
// Created by alexs on 11/17/2023.
//

#ifndef FIRELIGHT_GAME_SCREEN_HPP
#define FIRELIGHT_GAME_SCREEN_HPP

#include "../lib/gui/screens/screen.hpp"
#include "controller/controller_manager.hpp"
#include "libretro/core.hpp"
#include <filesystem>
namespace FL::GUI {

class GameScreen : public Screen {
public:
  explicit GameScreen(std::unique_ptr<ContainerWidget> container,
                      FL::ControllerManager *manager,
                      FL::Graphics::Driver *driver, std::string romPath);
  void enter() override;
  void exit() override;
  void update(float deltaTime) override;
  void render(const std::shared_ptr<WidgetPainter> &painter) override;
  ~GameScreen() override = default;

private:
  std::unique_ptr<libretro::Core> core;
  std::string gameRomPath;
  FL::ControllerManager *controllerManager;
  FL::Graphics::Driver *gfxDriver;
};

} // namespace FL::GUI

#endif // FIRELIGHT_GAME_SCREEN_HPP
