//
// Created by alexs on 11/9/2023.
//

#include "frame.hpp"
#include <sstream>

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

bool Frame::handleEvent(Event &event) {
  for (auto child : children) {
    if (child.widget->handleEvent(event)) {
      return true;
    }
  }

  return false;
}

Widget *Frame::getFirstFocusable() {
  for (auto child : children) {
    if (child.widget->focusable()) {
      auto addr = child.widget->getFirstFocusable();
      return addr;
    }
  }

  return nullptr;
}

void Frame::addChild(Widget *widget, FL::Math::BBox box) {
  Child child;
  child.widget = widget;
  child.widget->setParent(this);
  child.box = box;

  children.emplace_back(child);
}

} // namespace FL::GUI
