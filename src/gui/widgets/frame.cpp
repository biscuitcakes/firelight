//
// Created by alexs on 11/9/2023.
//

#include "frame.hpp"

namespace FL::GUI {

void Frame::paint(WidgetPainter *painter, FL::Math::BBox box) {
  //  painter->paintRectangle(box);

  for (auto child : children) {
    child.widget->paint(painter, child.box);
  }
}

bool Frame::focusable() {
  for (auto child : children) {
    if (child.widget->focusable()) {
      return true;
    }
  }

  return false;
}

void Frame::addChild(Widget *widget, FL::Math::BBox box) {
  Child child;
  child.widget = widget;
  child.box = box;

  children.emplace_back(child);
}

} // namespace FL::GUI
