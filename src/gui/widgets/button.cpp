//
// Created by alexs on 11/9/2023.
//

#include "button.hpp"

#include <sstream>
#include <utility>

namespace FL::GUI {

void Button::paint(WidgetPainter *painter, FL::Math::BBox box) {
  painter->paintText(label, box, *style);
  // draw rectangle
}
bool Button::focusable() { return true; }
Widget *Button::getFirstFocusable() { return this; }

Button::Button(std::string text) : label(std::move(text)) {}

} // namespace FL::GUI
