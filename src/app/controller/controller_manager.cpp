//
// Created by alexs on 10/27/2023.
//

#include "controller_manager.hpp"

namespace FL {

void ControllerManager::setLoadedCore(libretro::Core *core) {
  // Check if we already know about controllers and plug them in?
  loadedCore = core;
  if (!controllers.empty()) {
    auto gamepad = new libretro::Gamepad(controllers[0]);
    loadedCore->plugInGamepad(0, gamepad);
  }
}

void ControllerManager::handleControllerAddedEvent(int32_t sdlJoystickIndex) {
  // Check if we already have a controller for this joystick index
  auto controller = SDL_GameControllerOpen(sdlJoystickIndex);
  if (controller == nullptr) {
    return;
  }

  unassignedControllers.push_back(
      std::make_unique<FL::Input::SDLGamepad>(controller));

  controllers.push_back(controller);
  auto gamepad = new libretro::Gamepad(controller);
  if (loadedCore != nullptr) {
    loadedCore->plugInGamepad(0, gamepad);
  }
}

void ControllerManager::handleControllerRemovedEvent(int32_t sdlInstanceId) {}

void ControllerManager::scanGamepads() {
  auto numJoys = SDL_NumJoysticks();
  for (int i = 0; i < numJoys; ++i) {
    auto controller = SDL_GameControllerOpen(i);
    if (controller == nullptr) {
      continue;
    }
    // else check if we already know about it somehow

    handleControllerAddedEvent(i);
  }
}
} // namespace FL