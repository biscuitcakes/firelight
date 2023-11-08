//
// Created by alexs on 11/6/2023.
//

#include "text.hpp"

#include <utility>

namespace FL::GUI {

Text::Text(std::string text) { text = std::move(text); }

void Text::paint(WidgetPainter *painter, FL::Math::BBox box) {
  painter->paintText(text, box, FL::GUI::Style{});
}

} // namespace FL::GUI
