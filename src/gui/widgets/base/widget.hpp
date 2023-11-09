//
// Created by alexs on 11/7/2023.
//

#ifndef FIRELIGHT_WIDGET_HPP
#define FIRELIGHT_WIDGET_HPP

#include "../../../math/bbox.hpp"
#include "../../widget_painter.hpp"
#include <vector>

namespace FL::GUI {

class Widget {
public:
  virtual void paint(WidgetPainter *painter, FL::Math::BBox box) = 0;

  virtual bool focusable();

  void setStyle(Style *style);

private:
  Style *style = nullptr;
};

} // namespace FL::GUI

#endif // FIRELIGHT_WIDGET_HPP
