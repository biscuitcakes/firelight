//
// Created by alexs on 11/12/2023.
//

#ifndef FIRELIGHT_WIDGET_FACTORY_HPP
#define FIRELIGHT_WIDGET_FACTORY_HPP

#include "context.hpp"
#include "widgets/button.hpp"
#include <memory>

namespace FL::GUI {

class WidgetFactory {
public:
  explicit WidgetFactory(Context *context);
  std::unique_ptr<Button> createButton(const std::string &label);

private:
  int numWidgets = 0;
  int getNextId();
  Context *guiContext;
};

} // namespace FL::GUI

#endif // FIRELIGHT_WIDGET_FACTORY_HPP
