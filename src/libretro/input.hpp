//
// Created by alexs on 10/28/2023.
//

#ifndef FIRELIGHT_INPUT_HPP
#define FIRELIGHT_INPUT_HPP

#include "gamepad.hpp"
#include <array>

using std::array;

namespace libretro {

class Input {
public:
  int16_t getInputState(unsigned port, unsigned device, unsigned index,
                        unsigned id);

  void plugInGamepad(int port, Gamepad *gamepad);

private:
  array<Gamepad *, 8> controllers;
};

} // namespace libretro

#endif // FIRELIGHT_INPUT_HPP
