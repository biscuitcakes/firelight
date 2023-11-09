//
// Created by alexs on 10/30/2023.
//

#include "context.hpp"

namespace FL::GUI {

void Context::handleSdlEvent(SDL_Event *event) {
  switch (event->type) {
  case SDL_CONTROLLERBUTTONDOWN:
    printf("button down\n");
    break;
  case SDL_CONTROLLERBUTTONUP:
    printf("button up\n");
    break;
  }
}

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

void Context::addWidget(Widget *widget) {
  if (focusTarget == nullptr) {
    if (widget->focusable()) {
      printf("Found focus target\n");
      focusTarget = widget;
    }
  }
  
  widgets.emplace_back(widget);
}

} // namespace FL::GUI
