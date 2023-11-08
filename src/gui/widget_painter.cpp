//
// Created by alexs on 11/7/2023.
//

#include "widget_painter.hpp"
#include "../graphics/driver.hpp"

namespace FL::GUI {

WidgetPainter::WidgetPainter(FL::Graphics::Driver *driver)
    : gfxDriver(driver) {}

void WidgetPainter::paintText(const std::string &text, FL::Math::BBox box,
                              Style style) {}
} // namespace FL::GUI
