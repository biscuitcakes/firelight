//
// Created by alexs on 10/30/2023.
//

#ifndef FIRELIGHT_STYLE_HPP
#define FIRELIGHT_STYLE_HPP

#include "../graphics/color.hpp"
namespace FL::GUI {

enum TextAlignment { NONE, CENTER, RIGHT };

struct Style {
  bool hasBackgroundColor = false;
  FL::Graphics::Color backgroundColor{1.0, 1.0, 1.0, 1.0};
  TextAlignment horiTextAlignment = NONE;
  TextAlignment vertTextAlignment = NONE;
  int innerPaddingPx = 0;
};

} // namespace FL::GUI

#endif // FIRELIGHT_STYLE_HPP
