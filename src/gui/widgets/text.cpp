//
// Created by alexs on 11/6/2023.
//

#include "text.hpp"

#include <utility>

namespace FL::GUI {
Text::Text(std::string text, int x, int y, int w, int h) : Widget(x, y, w, h) {
  this->text = std::move(text);
}
void Text::render(OpenGLPainter *painter) { painter->drawText(text, x, y); }
} // namespace FL::GUI
