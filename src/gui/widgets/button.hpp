//
// Created by alexs on 11/9/2023.
//

#ifndef FIRELIGHT_BUTTON_HPP
#define FIRELIGHT_BUTTON_HPP

#include "base/widget.hpp"
#include <functional>
namespace FL::GUI {

class Button : public Widget {
public:
  Button(std::string text, std::function<void(Button *button)> onClickCallback);
  void paint(WidgetPainter *painter, FL::Math::BBox box) override;
  Widget *getFirstFocusable() override;
  bool focusable() override;
  bool handleEvent(Event &event) override;

private:
  std::string label;
  std::function<void(Button *button)> onClick;
};

} // namespace FL::GUI

#endif // FIRELIGHT_BUTTON_HPP
