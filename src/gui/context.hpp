//
// Created by alexs on 10/30/2023.
//

#ifndef BLUEMBER_CONTEXT_HPP
#define BLUEMBER_CONTEXT_HPP

#include "SDL2/SDL.h"
#include "open_gl_painter.hpp"
#include "point.hpp"
#include "rect.hpp"
#include "widgets/widget.hpp"
#include <memory>
#include <string>
#include <vector>

using std::string;
using std::vector;

namespace FL::GUI {

class Context {
public:
  explicit Context(Point size);
  void handleSdlEvent(SDL_Event *event);
  Rect getWorkArea();
  void setWorkArea(Rect area);
  void addThingy(Widget *thing);
  void focus(Widget *target);

  void render();

private:
  std::unique_ptr<OpenGLPainter> painter;

  vector<Widget *> thingies;
  Rect workArea{};
  vector<Widget *> widgets;
  vector<Widget *> focusChain;
};

} // namespace FL::GUI

#endif // BLUEMBER_CONTEXT_HPP
