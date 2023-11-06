//
// Created by alexs on 10/28/2023.
//

#include "input.hpp"
#include "libretro.h"
#include <cstdio>

namespace libretro {
int16_t Input::getInputState(unsigned int port, unsigned int device,
                             unsigned int index, unsigned int id) {

  // TODO: Check for weird values

  auto controller = controllers[port];
  if (controller == nullptr) {
    return 0;
  }

  if (device == RETRO_DEVICE_ANALOG) {
    if (index == RETRO_DEVICE_INDEX_ANALOG_LEFT) {
      if (id == RETRO_DEVICE_ID_ANALOG_X) {
        return controller->getLeftStickXPosition();
      } else if (id == RETRO_DEVICE_ID_ANALOG_Y) {
        return controller->getLeftStickYPosition();
      }
    } else if (index == RETRO_DEVICE_INDEX_ANALOG_RIGHT) {
      if (id == RETRO_DEVICE_ID_ANALOG_X) {
        return controller->getRightStickXPosition();
      } else if (id == RETRO_DEVICE_ID_ANALOG_Y) {
        return controller->getRightStickYPosition();
      }
    }
  } else if (device == RETRO_DEVICE_JOYPAD) {
    return controller->isButtonPressed(id);
  }

  return 0;
}

void Input::plugInGamepad(int port, Gamepad *gamepad) {
  if (controllers[port] != nullptr) {
    printf("UHHHH\n");
    // TODO: Do some error here since we're trying to plug into an occupied
    //  port. Or we could check if it's the same device and ignore it.

    return;
  }

  printf("Plugging gamepad %p into port %d\n", gamepad, port);
  //  symRetroSetControllerPortDevice(port, RETRO_DEVICE_ANALOG);
  controllers[port] = gamepad;
}

} // namespace libretro