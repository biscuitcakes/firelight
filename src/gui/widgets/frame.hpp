//
// Created by alexs on 11/9/2023.
//

#ifndef FIRELIGHT_FRAME_HPP
#define FIRELIGHT_FRAME_HPP

#include "base/widget.hpp"
namespace FL::GUI {

class Frame : public Widget {
public:
  void paint(WidgetPainter *painter, FL::Math::BBox box) override;
  void addChild(Widget *widget, FL::Math::BBox box);
  bool focusable() override;
  Widget *getFirstFocusable() override;
  bool handleEvent(Event &event) override;

private:
  struct Child {
    Widget *widget = nullptr;
    FL::Math::BBox box;
  };

  std::vector<Child> children;
};

} // namespace FL::GUI

#endif // FIRELIGHT_FRAME_HPP
