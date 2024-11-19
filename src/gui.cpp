#include "gui.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <chrono>
#include <thread>

#include "hitmap.hpp"
#include "tube.hpp"

Gui::Gui(Tube *tube, int fps, Vector<int> winsize, std::string winname)
    : tube_(tube),
      fps_(fps),
      window_(sf::VideoMode(winsize.x, winsize.y), winname) {
  auto *hitmap = new Hitmap(&window_, {0, 0}, winsize, tube);
  widgets_.push_back(hitmap);
}

Gui::~Gui() {
  for (auto *widget : widgets_) {
    delete widget;
  }
}

void Gui::Run() {
  std::chrono::duration<double> delay(1 / static_cast<double>(fps_));

  while (window_.isOpen()) {
    auto start_time = std::chrono::system_clock::now();

    sf::Event event;
    while (window_.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window_.close();
      }
    }

    tube_->NewFrame(1 / static_cast<double>(fps_));

    window_.clear();

    for (auto *widget : widgets_) {
      widget->Render();
    }

    window_.display();

    if (std::chrono::system_clock::now() - start_time < delay) {
      std::this_thread::sleep_for(delay + std::chrono::system_clock::now() -
                                  start_time);
    }
  }
}
