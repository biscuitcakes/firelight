//
// Created by alexs on 11/9/2023.
//

#include "quick_menu.hpp"
#include "../context.hpp"
#include "menu_item.hpp"
#include "text.hpp"

#include <sstream>
#include <utility>

namespace FL::GUI {

QuickMenu::QuickMenu(Context *c) : context(c) {}

void FL::GUI::QuickMenu::addItem(MenuItem *menuItem) {
  menuItem->setParent(this);
  menuItem->setStyle(&childStyle);

  children.emplace_back(menuItem);
}

void QuickMenu::recalculateNavNeighbors() {
  Widget *last = nullptr;
  for (const auto &child : children) {
    child->setNeighborUp(last);

    if (last != nullptr) {
      last->setNeighborDown(child);
    }
    last = child;
  }
}

void FL::GUI::QuickMenu::paint(FL::GUI::WidgetPainter *painter,
                               FL::Math::BBox box) {
  FL::Math::BBox left(box.xPx, box.yPx, box.widthPx / 3, box.heightPx);
  FL::Math::BBox right(box.xPx + (box.widthPx / 3), box.yPx,
                       (box.widthPx / 3) * 2, box.heightPx);

  // Set up left side
  auto itemHeight = left.heightPx / children.size();

  auto cursor = 0;
  for (auto child : children) {
    FL::Math::BBox childBox(left.xPx, left.yPx + cursor, left.widthPx,
                            itemHeight);

    if (context->inFocusChain(child)) {
      painter->paintBackground(childBox, childStyle);
      if (child->getSubMenu() != nullptr) {
        child->getSubMenu()->paint(painter, right);
      }
    }

    child->paint(painter, childBox);

    cursor += itemHeight;
  }
}

Widget *QuickMenu::getFirstFocusable() {
  for (auto child : children) {
    if (child->focusable()) {
      auto addr = child->getFirstFocusable();
      return addr;
    }
  }

  return nullptr;
}

bool QuickMenu::focusable() {
  for (auto child : children) {
    if (child->focusable()) {
      return true;
    }
  }

  return false;
}
bool QuickMenu::canHaveFocus() { return false; }

bool QuickMenu::handleEvent(Event &event) { return false; }

} // namespace FL::GUI
