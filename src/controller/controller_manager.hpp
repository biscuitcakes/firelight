//
// Created by alexs on 10/27/2023.
//

#ifndef BLUEMBER_CONTROLLER_MANAGER_HPP
#define BLUEMBER_CONTROLLER_MANAGER_HPP

#include "../libretro/core.hpp"
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
};

} // namespace FL

#endif // BLUEMBER_CONTROLLER_MANAGER_HPP
