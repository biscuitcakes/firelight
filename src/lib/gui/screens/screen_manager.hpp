//
// Created by alexs on 11/13/2023.
//

#ifndef FIRELIGHT_SCREEN_MANAGER_HPP
#define FIRELIGHT_SCREEN_MANAGER_HPP

#include "../widget_painter.hpp"
#include "../widgets/base/widget.hpp"
#include "screen.hpp"
#include <memory>
#include <stack>

namespace FL::GUI {

class ScreenManager {
private:
  std::stack<std::unique_ptr<Screen>> screenStack;
  //  std::shared_ptr<WidgetPainter> widgetPainter;

public:
  void pushScreen(std::unique_ptr<Screen> screen) {
    if (!screenStack.empty()) {
      screenStack.top()->exit(); // Call exit on the current screen
    }
    screenStack.push(std::move(screen));
    screenStack.top()->enter(); // Call enter on the new screen
  }

  void popScreen() {
    if (!screenStack.empty()) {
      screenStack.top()->exit();
      screenStack.pop();
      if (!screenStack.empty()) {
        screenStack.top()->enter(); // Resume the previous screen
      }
    }
  }

  void update(float deltaTime) {
    if (!screenStack.empty()) {
      screenStack.top()->update(deltaTime); // Update the current screen
    }
  }

  void render(const std::shared_ptr<WidgetPainter> &widgetPainter) {
    if (!screenStack.empty()) {
      screenStack.top()->render(widgetPainter); // Render the current screen
    }
  }

  // ... other methods as needed
};

} // namespace FL::GUI

#endif // FIRELIGHT_SCREEN_MANAGER_HPP
