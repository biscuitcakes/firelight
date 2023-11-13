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
    case SDL_CONTROLLER_BUTTON_B:
      guiEvent.type = Event::NAV_BACK_PUSHED;
      break;
    default:
      return;
    }
    break;
  default:
    return;
  }

  if (focusTarget != nullptr) {
    focusTarget->handleEvent(guiEvent);
  }
}

void Context::setWorkArea(FL::Math::Box area) { workArea = area; }

void Context::render() {
  ImGui::Begin("Widgets");

  for (auto widget : widgets) {
    widget->paint(widgetPainter.get(), workArea);
  }

  ImGui::End();

  //  ImGui::Begin("Widgets");
  //
  //  ImGui::Text("Number of widgets in chain: %d", focusChain.size());
  //
  //  if (ImGui::TreeNode("Focus Chain")) {
  //    for (auto f : focusChain) {
  //      std::ostringstream address;
  //      address << (void const *)f;
  //      std::string name = address.str();
  //
  //      if (ImGui::TreeNode(name.c_str())) {
  //        ImGui::TreePop();
  //      }
  //    }
  //    ImGui::TreePop();
  //  }
  //
  //  ImGui::End();
}

Context::Context(FL::Math::Box workArea, FL::Graphics::Driver *driver)
    : workArea(workArea) {
  widgetPainter = std::make_unique<WidgetPainter>(driver);
}

void Context::addWidget(Widget *widget) {
  if (focusTarget == nullptr) {
    auto target = widget->getFirstFocusable();
    if (target != nullptr) {
      setFocusTarget(target);
    }
  }

  widgets.emplace_back(widget);
}
void Context::setFocusTarget(Widget *widget) {
  if (widget == nullptr) {
    return;
  }

  auto target = widget->getFirstFocusable();
  if (target == nullptr || target == focusTarget) {
    // TODO: error
    return;
  }

  if (focusTarget != nullptr) {
    focusTarget->isFocused = false;
  }

  focusTarget = target;
  focusTarget->isFocused = true;
}

} // namespace FL::GUI
