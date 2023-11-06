//
// Created by alexs on 10/30/2023.
//

#ifndef BLUEMBER_WIDGET_HPP
#define BLUEMBER_WIDGET_HPP

#include "../../gfx/stuff.hpp"
#include "../open_gl_painter.hpp"
namespace FL::GUI {

class Widget {
public:
  Widget(int x, int y, int w, int h);
  virtual void render(OpenGLPainter *painter) = 0;
  bool canHaveFocus();
  Widget *getNeighborUp();
  Widget *getNeighborDown();
  Widget *getNeighborLeft();
  Widget *getNeighborRight();

  Widget *getParent();

protected:
  int x, y, w, h = 0;
  Widget *parent = nullptr;

  Widget *neighborUp = nullptr;
  Widget *neighborDown = nullptr;
  Widget *neighborLeft = nullptr;
  Widget *neighborRight = nullptr;
};

} // namespace FL::GUI

#endif // BLUEMBER_WIDGET_HPP
