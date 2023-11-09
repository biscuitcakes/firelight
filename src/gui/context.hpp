//
// Created by alexs on 10/30/2023.
//

#ifndef FIRELIGHT_CONTEXT_HPP
#define FIRELIGHT_CONTEXT_HPP

#include "../math/bbox.hpp"
#include "SDL2/SDL.h"
#include "widgets/base/widget.hpp"
#include <memory>
#include <string>
#include <vector>

using std::string;
using std::vector;

namespace FL::GUI {

class Context {
public:
  explicit Context(FL::Math::BBox workArea, FL::Graphics::Driver *driver);
  void handleSdlEvent(SDL_Event *event);
  void setWorkArea(FL::Math::BBox area);

  void addWidget(Widget *widget);

  void render();

private:
  FL::Math::BBox workArea;
  std::unique_ptr<WidgetPainter> widgetPainter;

  Widget *focusTarget = nullptr;

  vector<Widget *> widgets;
};

} // namespace FL::GUI

#endif // FIRELIGHT_CONTEXT_HPP
