//
// Created by alexs on 10/27/2023.
//

#include "controller_manager.hpp"

namespace FL {

void ControllerManager::setLoadedCore(libretro::Core *core) {
  // Check if we already know about controllers and plug them in?
  loadedCore = core;
}

void ControllerManager::handleControllerAddedEvent(int32_t sdlJoystickIndex) {
  // Check if we already have a controller for this joystick index
  auto controller = SDL_GameControllerOpen(sdlJoystickIndex);
  auto gamepad = new libretro::Gamepad(controller);
  if (loadedCore != nullptr) {
    loadedCore->plugInGamepad(0, gamepad);
  }
}

void ControllerManager::handleControllerRemovedEvent(int32_t sdlInstanceId) {}
} // namespace FL