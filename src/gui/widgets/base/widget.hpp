//
// Created by alexs on 11/7/2023.
//

#ifndef FIRELIGHT_WIDGET_HPP
#define FIRELIGHT_WIDGET_HPP

#include "../../../math/bbox.hpp"
#include "../../events/event.hpp"
#include "../../widget_painter.hpp"
#include <unordered_map>
#include <vector>

namespace FL::GUI {

class Widget {
public:
  virtual void paint(WidgetPainter *painter, FL::Math::BBox box) = 0;
  virtual bool focusable() = 0;

  virtual Widget *getFirstFocusable() = 0;

  virtual bool canHaveFocus();

  void setStyle(Style *style);
  void setParent(Widget *newParent);
  Widget *getParent() const;
  virtual bool handleEvent(FL::GUI::Event &event) = 0;

  void setNeighborUp(Widget *neighbor);
  void setNeighborDown(Widget *neighbor);
  void setNeighborLeft(Widget *neighbor);
  void setNeighborRight(Widget *neighbor);

  Widget *getNeighborUp();
  Widget *getNeighborDown();
  Widget *getNeighborLeft();
  Widget *getNeighborRight();

  virtual void recalculateNavNeighbors();

  bool isFocused = false;

protected:
  Widget *neighborUp = nullptr;
  Widget *neighborDown = nullptr;
  Widget *neighborLeft = nullptr;
  Widget *neighborRight = nullptr;

  Widget *parent = nullptr;
  Style *style = nullptr;
};

} // namespace FL::GUI

#endif // FIRELIGHT_WIDGET_HPP
