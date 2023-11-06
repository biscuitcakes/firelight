//
// Created by alexs on 10/30/2023.
//

#include "context.hpp"

namespace FL::GUI {
void Context::handleSdlEvent(SDL_Event *event) {}
Rect Context::getWorkArea() { return workArea; }
void Context::setWorkArea(Rect area) {
  workArea = area;
  painter->viewportWidth = area.w;
  painter->viewportHeight = area.h;
}

void Context::render() {
  for (auto t : thingies) {
    t->render(painter.get());
  }
}

Context::Context(Point size) {
  workArea.x = 0;
  workArea.y = 0;
  workArea.w = size.x;
  workArea.h = size.y;

  painter = std::make_unique<OpenGLPainter>(size.x, size.y);
}

void Context::addThingy(Widget *thingy) { thingies.emplace_back(thingy); }
void Context::focus(Widget *target) {
  focusChain.clear();
  if (target->canHaveFocus()) {
    // TODO: Set target state
  }

  focusChain.emplace_back(target);

  auto parent = target->getParent();
  while (parent != nullptr) {
    focusChain.emplace_back(parent);
    parent = parent->getParent();
  }
}
} // namespace FL::GUI
