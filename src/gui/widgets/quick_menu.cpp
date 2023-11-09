//
// Created by alexs on 11/9/2023.
//

#include "quick_menu.hpp"

#include <utility>

namespace FL::GUI {

void FL::GUI::QuickMenu::addItem(std::string header) {
  Child child;
  child.header = new Button(std::move(header));

  children.emplace_back(child);
}

void FL::GUI::QuickMenu::paint(FL::GUI::WidgetPainter *painter,
                               FL::Math::BBox box) {
  auto itemHeight = box.heightPx / children.size();

  auto cursor = 0;
  for (int i = 0; i < children.size(); ++i) {
    auto child = children.at(i);
    FL::Math::BBox childBox(box.xPx, box.yPx + cursor, box.widthPx, itemHeight);

    if (active == i) {
      painter->paintBackground(childBox, childStyle);
    }

    child.header->paint(painter, childBox);

    cursor += itemHeight;
  }
}

bool QuickMenu::focusable() { return !children.empty(); }

} // namespace FL::GUI
