//
// Created by alexs on 11/9/2023.
//

#ifndef FIRELIGHT_QUICK_MENU_HPP
#define FIRELIGHT_QUICK_MENU_HPP

#include "base/widget.hpp"
#include "button.hpp"
namespace FL::GUI {

class QuickMenu : public Widget {
public:
  void addItem(std::string header);
  void paint(WidgetPainter *painter, FL::Math::BBox box) override;
  bool focusable() override;
  Widget *getFirstFocusable() override;
  void recalculateNavNeighbors() override;

private:
  int active = 0;

  struct Child {
    Button *header;
    std::vector<Widget *> children;
  };

  Style childStyle{.background = FILL_BACKGROUND,
                   .backgroundColor =
                       FL::Graphics::Color{.R = 1, .G = 1, .B = 1, .A = 1},
                   .horiAlignment = RIGHT,
                   .vertAlignment = CENTER};
  std::vector<Child> children;
};

} // namespace FL::GUI

#endif // FIRELIGHT_QUICK_MENU_HPP
