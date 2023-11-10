//
// Created by alexs on 11/9/2023.
//

#include "quick_menu.hpp"
#include "text.hpp"

#include <sstream>
#include <utility>

namespace FL::GUI {

void FL::GUI::QuickMenu::addItem(const std::string &header) {
  Child child;
  child.header = new Button(header, [&]() {
    printf("heyooooo i'm a kid again buddy you pressed a thing");
  });
  child.header->setParent(this);
  child.header->setStyle(&childStyle);
  child.children.emplace_back(new FL::GUI::Text("sub-content for " + header));

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
  FL::Math::BBox left(box.xPx, box.yPx, box.widthPx / 3, box.heightPx);
  FL::Math::BBox right(box.xPx + (box.widthPx / 3), box.yPx,
                       (box.widthPx / 3) * 2, box.heightPx);

  // Set up left side
  auto itemHeight = left.heightPx / children.size();

  auto cursor = 0;
  for (auto child : children) {
    FL::Math::BBox childBox(left.xPx, left.yPx + cursor, left.widthPx,
                            itemHeight);

    if (child.header->isFocused) {
      painter->paintBackground(childBox, childStyle);
      if (!child.children.empty()) {
        painter->paintBackground(
            right, Style{.background = FILL_BACKGROUND,
                         .backgroundColor = FL::Graphics::Color{.R = 1}});
        child.children.at(0)->paint(painter, right);
      }
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

bool QuickMenu::handleEvent(Event &event) { return false; }

} // namespace FL::GUI
