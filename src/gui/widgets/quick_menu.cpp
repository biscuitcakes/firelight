//
// Created by alexs on 11/9/2023.
//

#include "quick_menu.hpp"

#include <sstream>
#include <utility>

namespace FL::GUI {

void FL::GUI::QuickMenu::addItem(std::string header) {
  Child child;
  child.header = new Button(std::move(header));
  child.header->setParent(this);
  child.header->setStyle(&childStyle);

  children.emplace_back(child);
}
void QuickMenu::recalculateNavNeighbors() {
  Widget *last = nullptr;
  for (const auto &child : children) {
    child.header->setNeighborUp(last);

    if (last != nullptr) {
      last->setNeighborDown(child.header);
    }
    last = child.header;
  }
}

void FL::GUI::QuickMenu::paint(FL::GUI::WidgetPainter *painter,
                               FL::Math::BBox box) {
  auto itemHeight = box.heightPx / children.size();

  auto cursor = 0;
  for (auto child : children) {
    FL::Math::BBox childBox(box.xPx, box.yPx + cursor, box.widthPx, itemHeight);

    if (child.header->isFocused) {
      painter->paintBackground(childBox, childStyle);
    }

    child.header->paint(painter, childBox);

    cursor += itemHeight;
  }
}

Widget *QuickMenu::getFirstFocusable() {
  for (auto child : children) {
    if (child.header->focusable()) {
      auto addr = child.header->getFirstFocusable();
      return addr;
    }
  }

  return nullptr;
}

bool QuickMenu::focusable() {
  for (auto child : children) {
    if (child.header->focusable()) {
      return true;
    }
  }

  return false;
}

} // namespace FL::GUI
