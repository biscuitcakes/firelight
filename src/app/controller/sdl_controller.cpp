//
// Created by alexs on 12/5/2023.
//

#include "sdl_controller.hpp"

namespace FL::Input {
SDLGamepad::SDLGamepad(SDL_GameController *controller)
    : sdlController(controller) {
  auto joystick = SDL_GameControllerGetJoystick(controller);
  auto guid = SDL_JoystickGetGUID(joystick);

  int numAxes = SDL_CONTROLLER_AXIS_MAX;
  int numButtons = SDL_CONTROLLER_BUTTON_MAX;

  printf("Available controller inputs:\n");

  for (int axis = 0; axis < numAxes; ++axis) {
    SDL_GameControllerButtonBind bind = SDL_GameControllerGetBindForAxis(
        controller, (SDL_GameControllerAxis)axis);
    if (bind.bindType == SDL_CONTROLLER_BINDTYPE_AXIS) {
      printf("Axis %d: %s\n", axis,
             SDL_GameControllerGetStringForAxis((SDL_GameControllerAxis)axis));
    }
  }

  for (int button = 0; button < numButtons; ++button) {
    SDL_GameControllerButtonBind bind = SDL_GameControllerGetBindForButton(
        controller, (SDL_GameControllerButton)button);
    if (bind.bindType == SDL_CONTROLLER_BINDTYPE_BUTTON) {
      printf("Button %d: %s\n", button,
             SDL_GameControllerGetStringForButton(
                 (SDL_GameControllerButton)button));
    }
  }

  auto vendor = SDL_GameControllerGetVendor(controller);
  auto product = SDL_GameControllerGetProduct(controller);

  if (vendor == 1406 && product == 8217) {
    printf("Got NSO N64 controller\n");
  }
  //  for (auto i = 0; i < SDL_GameControllerNumMappings(); ++i) {
  //    auto s = SDL_GameControllerMappingForIndex(i);
  //    printf("%s\n", s);
  //    SDL_free(s);
  //  }

  char buf[33];
  SDL_GUIDToString(guid, buf, 33);
  printf("GUID: %s\n", buf);

  printf("name: %s\n", SDL_GameControllerName(controller));
  printf("type: %u\n", SDL_GameControllerGetType(controller));

  printf("serial: %s\n", SDL_GameControllerGetSerial(controller));
  printf("vendor: %u\n", SDL_GameControllerGetVendor(controller));
  printf("product: %u\n", SDL_GameControllerGetProduct(controller));
  printf("product version: %u\n",
         SDL_GameControllerGetProductVersion(controller));
}
} // namespace FL::Input
