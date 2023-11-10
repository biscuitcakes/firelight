//
// Created by alexs on 11/7/2023.
//

#include "widget.hpp"

namespace FL::GUI {

void Widget::setStyle(Style *widgetStyle) { style = widgetStyle; }

void Widget::setParent(Widget *newParent) { parent = newParent; }
Widget *Widget::getParent() const { return parent; }
Widget *Widget::getNeighborRight() { return neighborRight; }
Widget *Widget::getNeighborLeft() { return neighborLeft; }
Widget *Widget::getNeighborDown() { return neighborDown; }
Widget *Widget::getNeighborUp() { return neighborUp; }

void Widget::recalculateNavNeighbors() {
  // Intentional no-op for default implementation
}

void Widget::setNeighborUp(Widget *neighbor) { neighborUp = neighbor; }
void Widget::setNeighborDown(Widget *neighbor) { neighborDown = neighbor; }
void Widget::setNeighborLeft(Widget *neighbor) { neighborLeft = neighbor; }
void Widget::setNeighborRight(Widget *neighbor) { neighborRight = neighbor; }

} // namespace FL::GUI
