//
// Created by alexs on 11/9/2023.
//

#ifndef FIRELIGHT_BUTTON_HPP
#define FIRELIGHT_BUTTON_HPP

#include "base/widget.hpp"
namespace FL::GUI {

class Button : public Widget {
public:
  explicit Button(std::string text);
  void paint(WidgetPainter *painter, FL::Math::BBox box) override;
  bool focusable() override;

private:
  std::string label;
};

} // namespace FL::GUI

#endif // FIRELIGHT_BUTTON_HPP
