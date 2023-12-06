//
// Created by alexs on 10/27/2023.
//

#ifndef FIRELIGHT_CONTROLLER_MANAGER_HPP
#define FIRELIGHT_CONTROLLER_MANAGER_HPP

#include "../libretro/core.hpp"
#include "sdl_controller.hpp"
#include <cstdint>
#include <memory>
namespace FL {

class ControllerManager {
public:
  void setLoadedCore(libretro::Core *core);
  void handleControllerAddedEvent(int32_t sdlJoystickIndex);
  void handleControllerRemovedEvent(int32_t sdlInstanceId);

private:
  libretro::Core *loadedCore = nullptr;
  std::vector<SDL_GameController *> controllers;
  std::vector<std::unique_ptr<FL::Input::SDLGamepad>> unassignedControllers;
  std::array<std::unique_ptr<FL::Input::SDLGamepad>, 8> portAssignedControllers;
};

} // namespace FL

#endif // FIRELIGHT_CONTROLLER_MANAGER_HPP
