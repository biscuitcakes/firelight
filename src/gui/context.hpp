//
// Created by alexs on 10/30/2023.
//

#ifndef FIRELIGHT_CONTEXT_HPP
#define FIRELIGHT_CONTEXT_HPP

#include "../math/bbox.hpp"
#include "SDL2/SDL.h"
#include "open_gl_painter.hpp"
#include "widgets/base/new_widget.hpp"
#include <memory>
#include <string>
#include <vector>

using std::string;
using std::vector;

namespace FL::GUI {

class Context {
public:
  explicit Context(FL::Math::BBox size);
  void handleSdlEvent(SDL_Event *event);
  void setWorkArea(FL::Math::BBox area);

  void addWidget(NewWidget *widget);

  void drawText(const std::string &text, FL::Math::BBox bbox);

  void render();

private:
  std::unique_ptr<OpenGLPainter> painter;

  vector<NewWidget *> newWidgets;
};

} // namespace FL::GUI

#endif // FIRELIGHT_CONTEXT_HPP
