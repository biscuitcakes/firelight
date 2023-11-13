//
// Created by alexs on 10/27/2023.
//

#ifndef FIRELIGHT_GAMEPAD_HPP
#define FIRELIGHT_GAMEPAD_HPP

#include "SDL2/SDL.h"
#include <cstdint>

namespace libretro {

class Gamepad {
public:
  explicit Gamepad(SDL_GameController *controller);

  bool isButtonPressed(int button);
  int16_t getLeftStickXPosition();
  int16_t getLeftStickYPosition();
  int16_t getRightStickXPosition();
  int16_t getRightStickYPosition();

private:
  SDL_GameController *sdlController;
};

} // namespace libretro

#endif // FIRELIGHT_GAMEPAD_HPP
