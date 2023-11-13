//
// Created by alexs on 11/13/2023.
//

#include "screen.hpp"

namespace FL::GUI {

Screen::Screen(std::unique_ptr<ContainerWidget> container)
    : mainContainer(std::move(container)) {}

void Screen::enter() {}
void Screen::exit() {}
void Screen::update(float deltaTime) {}
void Screen::render(const std::shared_ptr<WidgetPainter> &painter) {
  mainContainer->paint(painter.get(), FL::Math::Box(0, 0, 1280, 720));
}

void Screen::addWidget(std::unique_ptr<Widget> widget) {
  mainContainer->addChild(std::move(widget));
}

} // namespace FL::GUI