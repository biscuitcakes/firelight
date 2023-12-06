//
// Created by alexs on 12/5/2023.
//

#ifndef FIRELIGHT_SDL_CONTROLLER_HPP
#define FIRELIGHT_SDL_CONTROLLER_HPP

#include "SDL_gamecontroller.h"
#include "SDL_joystick.h"
#include <memory>
#include <string>

namespace FL::Input {

class SDLGamepad {
public:
  explicit SDLGamepad(SDL_GameController *controller);

private:
  std::string deviceName;
  SDL_GameController *sdlController;
};

} // namespace FL::Input

#endif // FIRELIGHT_SDL_CONTROLLER_HPP
