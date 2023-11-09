//
// Created by alexs on 11/9/2023.
//

#include "button.hpp"

#include <utility>

namespace FL::GUI {

void Button::paint(WidgetPainter *painter, FL::Math::BBox box) {
  painter->paintText(label, box, Style{});
  // draw rectangle
}

bool Button::focusable() { return true; }

Button::Button(std::string text) : label(std::move(text)) {}

} // namespace FL::GUI
