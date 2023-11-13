//
// Created by alexs on 11/12/2023.
//

#include "widget_factory.hpp"

namespace FL::GUI {

WidgetFactory::WidgetFactory(Context *context) : guiContext(context) {}

std::unique_ptr<Button> WidgetFactory::createButton(const std::string &label) {
  auto button = std::make_unique<Button>(label, nullptr);
  button->setId(getNextId());

  return button;
}
int WidgetFactory::getNextId() { return numWidgets++; }

} // namespace FL::GUI
