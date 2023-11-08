//
// Created by alexs on 10/30/2023.
//

#include "context.hpp"

namespace FL::GUI {
void Context::handleSdlEvent(SDL_Event *event) {}
void Context::setWorkArea(FL::Math::BBox area) { workArea = area; }

void Context::render() {
  for (auto widget : widgets) {
    widget->paint(widgetPainter.get(), workArea);
  }
}

Context::Context(FL::Math::BBox workArea, FL::Graphics::Driver *driver)
    : workArea(workArea) {
  widgetPainter = std::make_unique<WidgetPainter>(driver);
}

void Context::addWidget(Widget *widget) { widgets.emplace_back(widget); }

} // namespace FL::GUI
