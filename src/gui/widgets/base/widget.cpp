//
// Created by alexs on 11/7/2023.
//

#include "widget.hpp"

namespace FL::GUI {

void Widget::setStyle(Style *widgetStyle) { style = widgetStyle; }

bool Widget::focusable() { return false; }

} // namespace FL::GUI
