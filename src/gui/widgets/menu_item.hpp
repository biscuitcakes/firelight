//
// Created by alexs on 11/11/2023.
//

#ifndef FIRELIGHT_MENU_ITEM_HPP
#define FIRELIGHT_MENU_ITEM_HPP

#include "base/widget.hpp"
#include <functional>
namespace FL::GUI {

class MenuItem : public Widget {
public:
  MenuItem(std::string text,
           std::function<void(MenuItem *item)> onSelectCallback);
  void paint(WidgetPainter *painter, FL::Math::BBox box) override;
  bool focusable() override;
  Widget *getFirstFocusable() override;
  bool handleEvent(Event &event) override;

  void setSubMenu(Widget *menu);
  Widget *getSubMenu();

private:
  std::string label;
  Widget *submenu = nullptr;
  std::function<void(MenuItem *item)> onSelect;
};

} // namespace FL::GUI

#endif // FIRELIGHT_MENU_ITEM_HPP
