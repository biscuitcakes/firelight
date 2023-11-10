//
// Created by alexs on 11/6/2023.
//

#include "text.hpp"

#include <utility>

namespace FL::GUI {

Text::Text(std::string text) { myText = std::move(text); }

void Text::paint(WidgetPainter *painter, FL::Math::BBox box) {
  painter->paintText(myText, box, FL::GUI::Style{});
}
bool Text::focusable() { return false; }
Widget *Text::getFirstFocusable() { return nullptr; }

} // namespace FL::GUI
