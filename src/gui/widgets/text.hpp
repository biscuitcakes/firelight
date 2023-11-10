//
// Created by alexs on 11/6/2023.
//

#ifndef FIRELIGHT_TEXT_HPP
#define FIRELIGHT_TEXT_HPP

#include "base/widget.hpp"
#include <string>
namespace FL::GUI {

class Text : public Widget {
public:
  explicit Text(std::string text);
  bool focusable() override;
  Widget *getFirstFocusable() override;
  bool handleEvent(Event &event) override;

private:
  void paint(WidgetPainter *painter, FL::Math::BBox box) override;
  std::string myText;
};

} // namespace FL::GUI

#endif // FIRELIGHT_TEXT_HPP
