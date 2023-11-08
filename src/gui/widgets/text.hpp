//
// Created by alexs on 11/6/2023.
//

#ifndef FIRELIGHT_TEXT_HPP
#define FIRELIGHT_TEXT_HPP

#include "base/new_widget.hpp"
#include <string>
namespace FL::GUI {

class Text : public NewWidget {
public:
  explicit Text(std::string text);

private:
  void paint(WidgetPainter *painter, FL::Math::BBox box) override;
  TextAlignment horiAlignment = CENTER;
  TextAlignment vertAlignment = CENTER;
  std::string text;
};

} // namespace FL::GUI

#endif // FIRELIGHT_TEXT_HPP
