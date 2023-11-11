//
// Created by alexs on 11/11/2023.
//

#include "menu_item.hpp"

#include <utility>

namespace FL::GUI {

void MenuItem::paint(WidgetPainter *painter, FL::Math::BBox box) {
  painter->paintText(label, box, *style);
}

bool MenuItem::focusable() { return true; }

Widget *MenuItem::getFirstFocusable() { return this; }

bool MenuItem::handleEvent(Event &event) {
  if (event.type == Event::NAV_SELECT_PUSHED) {
    if (onSelect) {
      onSelect(this);
      return true;
    }
  }
  return false;
}

MenuItem::MenuItem(std::string text,
                   std::function<void(MenuItem *item)> onSelectCallback)
    : label(std::move(text)), onSelect(std::move(onSelectCallback)) {}

Widget *MenuItem::getSubMenu() { return submenu; }

void MenuItem::setSubMenu(Widget *menu) {
  submenu = menu;
  submenu->setParent(this);
}

} // namespace FL::GUI
