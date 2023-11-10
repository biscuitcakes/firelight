//
// Created by alexs on 10/30/2023.
//

#include "context.hpp"
#include "events/event.hpp"
#include "imgui_impl_opengl3.h"
#include <sstream>

namespace FL::GUI {

void Context::handleSdlEvent(SDL_Event *event) {
  FL::GUI::Event guiEvent{};

  switch (event->type) {
  case SDL_CONTROLLERBUTTONDOWN:
    switch (event->cbutton.button) {
    case SDL_CONTROLLER_BUTTON_DPAD_DOWN:
      guiEvent.type = Event::NAV_DOWN;
      break;
    case SDL_CONTROLLER_BUTTON_DPAD_UP:
      guiEvent.type = Event::NAV_UP;
      break;
    case SDL_CONTROLLER_BUTTON_A:
      guiEvent.type = Event::NAV_SELECT_PUSHED;
      break;
    }
    break;
  default:
    return;
  }

  Widget *next = focusTarget;

  while (next != nullptr) {
    if (guiEvent.type == Event::NAV_UP) {
      auto up = next->getNeighborUp();
      if (up != nullptr) {
        next->isFocused = false;
        setFocusTarget(up);
        return;
      }
    } else if (guiEvent.type == Event::NAV_DOWN) {
      auto down = next->getNeighborDown();
      if (down != nullptr) {
        next->isFocused = false;
        setFocusTarget(down);
        return;
      }
    } else if (guiEvent.type == Event::NAV_SELECT_PUSHED) {
      if (focusTarget != nullptr) {
        if (focusTarget->handleEvent(guiEvent)) {
          return;
        }
      }
    }

    next = next->getParent();
  }
}

void Context::setWorkArea(FL::Math::BBox area) { workArea = area; }

void Context::render() {
  for (auto widget : widgets) {
    widget->paint(widgetPainter.get(), workArea);
  }

  ImGui::Begin("Widgets");

  ImGui::Text("Number of widgets in chain: %d", focusChain.size());

  if (ImGui::TreeNode("Focus Chain")) {
    for (auto f : focusChain) {
      std::ostringstream address;
      address << (void const *)f;
      std::string name = address.str();

      if (ImGui::TreeNode(name.c_str())) {
        ImGui::TreePop();
      }
    }
    ImGui::TreePop();
  }

  ImGui::End();
}

Context::Context(FL::Math::BBox workArea, FL::Graphics::Driver *driver)
    : workArea(workArea) {
  widgetPainter = std::make_unique<WidgetPainter>(driver);
}

void Context::addWidget(Widget *widget) {
  if (focusTarget == nullptr) {
    auto target = widget->getFirstFocusable();
    if (target != nullptr) {
      setFocusTarget(target);
      focusTarget = target;
    }
  }

  widgets.emplace_back(widget);
}
void Context::setFocusTarget(Widget *widget) {
  if (!widget->focusable()) {
    // TODO: error
    return;
  }

  focusChain.clear();
  Widget *next = widget;

  while (next != nullptr) {
    focusChain.push_back(next);
    next = next->getParent();
  }

  focusTarget = widget;
  focusTarget->isFocused = true;
}

} // namespace FL::GUI
