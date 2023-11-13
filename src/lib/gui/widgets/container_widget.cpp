//
// Created by alexs on 11/9/2023.
//

#include "container_widget.hpp"
#include <sstream>

namespace FL::GUI {

void ContainerWidget::paint(WidgetPainter *painter, FL::Math::Box box) {
  //  painter->paintRectangle(box);

  if (layoutManager) {
    layoutManager->layoutWidgets(*this);
  }

  for (auto &child : childWidgets) {
    child->paint(painter, child->box);
  }
}

bool ContainerWidget::focusable() {
  for (auto &child : childWidgets) {
    if (child->focusable()) {
      return true;
    }
  }

  return false;
}

bool ContainerWidget::handleEvent(Event &event) {
  if (event.type == Event::NAV_DOWN) {
    for (int i = 0; i < childWidgets.size(); ++i) {
      if (childWidgets.at(i)->isFocused && (i + 1) < childWidgets.size()) {
        childWidgets.at(i + 1)->isFocused = true;
        childWidgets.at(i)->isFocused = false;
        return true;
      }
    }
  } else if (event.type == Event::NAV_UP) {
    for (int i = 0; i < childWidgets.size(); ++i) {
      if (childWidgets.at(i)->isFocused && i > 0) {
        childWidgets.at(i - 1)->isFocused = true;
        childWidgets.at(i)->isFocused = false;
        return true;
      }
    }
  }

  return Widget::handleEvent(event);
}

Widget *ContainerWidget::getFirstFocusable() {
  for (auto &child : childWidgets) {
    if (child->focusable()) {
      auto addr = child->getFirstFocusable();
      return addr;
    }
  }

  return nullptr;
}

void ContainerWidget::addChild(std::unique_ptr<Widget> widget) {
  widget->setParent(this);
  // TODO TEMPORARY
  widget->setStyle(
      new FL::GUI::Style{.background = FILL_BACKGROUND,
                         .backgroundColor = FL::Graphics::Color{.B = 1},
                         .textColor = FL::Graphics::Color{.R = 1}});

  childWidgets.emplace_back(std::move(widget));
}
bool ContainerWidget::isContainer() const { return true; }

std::vector<std::unique_ptr<Widget>> &ContainerWidget::getChildren() {
  return childWidgets;
}

void ContainerWidget::setLayoutManager(std::unique_ptr<LayoutManager> manager) {
  layoutManager = std::move(manager);
}

std::unique_ptr<Widget> *ContainerWidget::getFocusedWidget() {
  for (auto &child : childWidgets) {
    if (child->isFocused) {
      return &child;
    }
  }

  return nullptr;
}

} // namespace FL::GUI
