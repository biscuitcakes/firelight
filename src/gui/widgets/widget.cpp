//
// Created by alexs on 10/30/2023.
//

#include "widget.hpp"
#include "../../gfx/stuff.hpp"
#include <cstdio>

namespace FL::GUI {
Widget::Widget(int xPos, int yPos, int width, int height) {
  x = xPos;
  y = yPos;
  w = width;
  h = height;
}
bool Widget::canHaveFocus() { return true; }

Widget *Widget::getNeighborUp() { return neighborUp; }
Widget *Widget::getNeighborDown() { return neighborDown; }
Widget *Widget::getNeighborLeft() { return neighborLeft; }
Widget *Widget::getNeighborRight() { return neighborRight; }
Widget *Widget::getParent() { return parent; }
} // namespace FL::GUI
