//
// Created by alexs on 11/14/2023.
//

#ifndef FIRELIGHT_SCREEN_THING_HPP
#define FIRELIGHT_SCREEN_THING_HPP

#include "../lib/gui/screens/screen.hpp"
#include "../lib/gui/screens/screen_manager.hpp"
#include "../lib/gui/vertical_box_layout_manager.hpp"
#include "../lib/gui/widget_factory.hpp"
#include "controller/controller_manager.hpp"
#include "game_screen.hpp"
#include "library/entry.hpp"
#include <memory>
namespace FL::GUI {

class ScreenThing {
private:
  std::unordered_map<std::string, std::unique_ptr<Screen>> screenCache;
  ScreenManager *screenManager;
  WidgetFactory *widgetFactory;
  ControllerManager *controllerManager;

public:
  ScreenThing(ScreenManager *manager, WidgetFactory *factory);

  std::unique_ptr<Screen> getInitialScreen() {
    //    return std::move(screenCache["home"]);
    return std::move(screenCache["home"]);
  }

  void buildHomeScreen(const std::vector<FL::Library::Entry> &entries) {
    auto container = std::make_unique<ContainerWidget>();
    container->box.xPx = 0;
    container->box.yPx = 0;
    container->box.widthPx = 1280;
    container->box.heightPx = 720;

    container->setLayoutManager(
        std::make_unique<VerticalBoxLayoutManager>(30, 10));

    auto screen = std::make_unique<Screen>(std::move(container));

    for (const auto &e : entries) {
      auto button = widgetFactory->createButton(e.gameName);

      button->onPressed.connect([e, this](Button *button) {
        auto container = std::make_unique<ContainerWidget>();
        container->box.xPx = 0;
        container->box.yPx = 0;
        container->box.widthPx = 1280;
        container->box.heightPx = 720;

        container->setLayoutManager(
            std::make_unique<VerticalBoxLayoutManager>(30, 10));

        auto screen = std::make_unique<GameScreen>(std::move(container),
                                                   controllerManager,
                                                   e.romPath.generic_string());

        this->screenManager->pushScreen(std::move(screen));
      });

      screen->addWidget(std::move(button));
    }

    //    screen->addWidget(widgetFactory->createButton("Paper Mario"));
    //    screen->addWidget(widgetFactory->createButton("Pokemon Red Version"));
    //    screen->addWidget(widgetFactory->createButton("Pokemon Yellow
    //    Version")); screen->addWidget(widgetFactory->createButton("Super Mario
    //    World"));

    screenCache.emplace("home", std::move(screen));
  }

  void buildGameScreen(FL::ControllerManager *manager) {
    this->controllerManager = manager;
    //
    //
    //
    //    screenCache.emplace("game", std::move(screen));
  }
};

} // namespace FL::GUI

#endif // FIRELIGHT_SCREEN_THING_HPP
