//
// Created by alexs on 10/30/2023.
//

#include "context.hpp"

namespace FL::GUI {
void Context::handleSdlEvent(SDL_Event *event) {}
void Context::setWorkArea(FL::Math::BBox area) {
  painter->viewportWidth = area.widthPx;
  painter->viewportHeight = area.heightPx;
}

void Context::render() {
  // for each widget
  // get the style
  // check for positioning first
  // - anchors
  // - padding
  // - margin
  // - border
  // - size restrictions?

  //  for (auto t : thingies) {
  //    renderWidget(t, t->x, t->y, t->w, t->h);
  //  }

  FL::Math::BBox box(0, 0, 1280, 720);

  for (auto widget : newWidgets) {
    widget->paint(painter.get(), box);
  }
}

Context::Context(FL::Math::BBox size) {
  painter = std::make_unique<OpenGLPainter>(size.widthPx, size.heightPx);
}

void Context::drawText(const std::string &text, FL::Math::BBox bbox) {
  painter->drawText(text, bbox.xPx, bbox.yPx);
}
void Context::addWidget(NewWidget *widget) { newWidgets.emplace_back(widget); }

} // namespace FL::GUI
