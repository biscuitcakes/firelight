//
// Created by alexs on 11/9/2023.
//

#ifndef FIRELIGHT_QUICK_MENU_HPP
#define FIRELIGHT_QUICK_MENU_HPP

#include "base/widget.hpp"
#include "button.hpp"
#include "menu_item.hpp"
namespace FL::GUI {

class Context;

class QuickMenu : public Widget {
public:
  explicit QuickMenu(Context *c);
  bool handleEvent(Event &event) override;
  void addItem(MenuItem *menuItem);
  void paint(WidgetPainter *painter, FL::Math::BBox box) override;
  bool focusable() override;
  Widget *getFirstFocusable() override;
  void recalculateNavNeighbors() override;
  bool canHaveFocus() override;

private:
  int divider = 0;
  //  FL::Math::BBox leftSide;
  //  FL::Math::BBox RightSide;

  Context *context;

  Style childStyle{
      .background = FILL_BACKGROUND,
      .backgroundColor = FL::Graphics::Color{.R = 1, .G = 1, .B = 1, .A = 1},
      .horiAlignment = RIGHT,
      .vertAlignment = CENTER,
      .textColor = FL::Graphics::Color{.R = .5, .G = 0, .B = .5, .A = 1}};
  std::vector<MenuItem *> children;
};

} // namespace FL::GUI

#endif // FIRELIGHT_QUICK_MENU_HPP
