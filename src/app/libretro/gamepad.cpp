//
// Created by alexs on 10/27/2023.
//

#include "gamepad.hpp"
#include "libretro.h"
#include <cstdio>

namespace libretro {
Gamepad::Gamepad(SDL_GameController *controller) {
  printf("Creating controller with %p\n", controller);
  sdlController = controller;
}

bool Gamepad::isButtonPressed(int button) {
  if (button == RETRO_DEVICE_ID_JOYPAD_A &&
      SDL_GameControllerGetButton(sdlController, SDL_CONTROLLER_BUTTON_B)) {
    return true;
  }
  if (button == RETRO_DEVICE_ID_JOYPAD_B &&
      SDL_GameControllerGetButton(sdlController, SDL_CONTROLLER_BUTTON_A)) {
    return true;
  }
  if (button == RETRO_DEVICE_ID_JOYPAD_X &&
      SDL_GameControllerGetButton(sdlController, SDL_CONTROLLER_BUTTON_Y)) {
    return true;
  }
  if (button == RETRO_DEVICE_ID_JOYPAD_Y &&
      SDL_GameControllerGetButton(sdlController, SDL_CONTROLLER_BUTTON_X)) {
    return true;
  }
  if (button == RETRO_DEVICE_ID_JOYPAD_LEFT &&
      SDL_GameControllerGetButton(sdlController,
                                  SDL_CONTROLLER_BUTTON_DPAD_LEFT)) {
    return true;
  }
  if (button == RETRO_DEVICE_ID_JOYPAD_RIGHT &&
      SDL_GameControllerGetButton(sdlController,
                                  SDL_CONTROLLER_BUTTON_DPAD_RIGHT)) {
    return true;
  }
  if (button == RETRO_DEVICE_ID_JOYPAD_UP &&
      SDL_GameControllerGetButton(sdlController,
                                  SDL_CONTROLLER_BUTTON_DPAD_UP)) {
    return true;
  }
  if (button == RETRO_DEVICE_ID_JOYPAD_DOWN &&
      SDL_GameControllerGetButton(sdlController,
                                  SDL_CONTROLLER_BUTTON_DPAD_DOWN)) {
    return true;
  }
  if (button == RETRO_DEVICE_ID_JOYPAD_START &&
      SDL_GameControllerGetButton(sdlController, SDL_CONTROLLER_BUTTON_START)) {
    return true;
  }
  if (button == RETRO_DEVICE_ID_JOYPAD_SELECT &&
      SDL_GameControllerGetButton(sdlController, SDL_CONTROLLER_BUTTON_BACK)) {
    return true;
  }
  if (button == RETRO_DEVICE_ID_JOYPAD_L &&
      SDL_GameControllerGetButton(sdlController,
                                  SDL_CONTROLLER_BUTTON_LEFTSHOULDER)) {
    return true;
  }
  if (button == RETRO_DEVICE_ID_JOYPAD_R &&
      SDL_GameControllerGetButton(sdlController,
                                  SDL_CONTROLLER_BUTTON_RIGHTSHOULDER)) {
    return true;
  }
  if (button == RETRO_DEVICE_ID_JOYPAD_L3 &&
      SDL_GameControllerGetButton(sdlController,
                                  SDL_CONTROLLER_BUTTON_LEFTSTICK)) {
    return true;
  }
  if (button == RETRO_DEVICE_ID_JOYPAD_R3 &&
      SDL_GameControllerGetButton(sdlController,
                                  SDL_CONTROLLER_BUTTON_RIGHTSTICK)) {
    return true;
  }

  return false;
}

int16_t Gamepad::getLeftStickXPosition() {
  return SDL_GameControllerGetAxis(sdlController, SDL_CONTROLLER_AXIS_LEFTX);
}

int16_t Gamepad::getLeftStickYPosition() {
  return SDL_GameControllerGetAxis(sdlController, SDL_CONTROLLER_AXIS_LEFTY);
}

int16_t Gamepad::getRightStickXPosition() {
  return SDL_GameControllerGetAxis(sdlController, SDL_CONTROLLER_AXIS_RIGHTX);
}

int16_t Gamepad::getRightStickYPosition() {
  return SDL_GameControllerGetAxis(sdlController, SDL_CONTROLLER_AXIS_RIGHTY);
}

} // namespace libretro