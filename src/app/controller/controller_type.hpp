//
// Created by alexs on 12/5/2023.
//

#ifndef FIRELIGHT_CONTROLLER_TYPE_HPP
#define FIRELIGHT_CONTROLLER_TYPE_HPP

namespace FL::Input {

enum ControllerType {
  NSO_N64,
};

static ControllerType getByThingy() { return NSO_N64; }

} // namespace FL::Input

#endif // FIRELIGHT_CONTROLLER_TYPE_HPP
