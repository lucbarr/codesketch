#include <SFML/Window.hpp>

#include "externs.h"
#include "text.h"
#include "shell.h"
#include "sketch.h"

namespace codesketch {

sf::ContextSettings settings;
sf::RenderWindow window;

int windowWidth = 640, windowHeight = 480;

int mouseX, mouseY;
u8 mouseState;

int frameCount;

fs::path binPath;

void init(int argc, char** argv) {
  binPath = fs::canonical((fs::current_path() / argv[0])).remove_filename();

  // Initialize settings
  //settings.antialiasingLevel = 8;

  // Initialize Window
  window.create(
    sf::VideoMode(windowWidth, windowHeight),
    "CodeSketch",
    sf::Style::Titlebar | sf::Style::Close,
    settings
  );

  window.setFramerateLimit(60);

  // Initialize text
  textInit();
}

void run() {
  window.clear();
  shellAddHistory("Type help for help!");

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();

      // Print screen
      if (event.type == sf::Event::KeyPressed and event.key.code == sf::Keyboard::F12) {
        // Create screenshots folder if not created yet
        fs::path folderpath = binPath / "../screenshots/";
        if (!fs::exists(folderpath) or !fs::is_directory(folderpath))
          fs::create_directory(folderpath);

        std::string filename = "codesketch";
        // Choose the name of the sketch if running
        if (sketchIsRunning())
          filename = sketchPath.stem().string();
        filename += "-";

        // Find the first unused filename
        int cnt = 0;
        while (fs::exists(folderpath / (filename + std::to_string(cnt) + ".png")))
          cnt++;

        filename += std::to_string(cnt);
        filename += ".png";

        fs::path filepath = folderpath / filename;
        if (window.capture().saveToFile(filepath.string()))
          printf("Successfully saved screenshot: %s\n", filename.c_str());
      }

      if (sketchIsRunning()) {
        if (event.type == sf::Event::KeyPressed and event.key.code == sf::Keyboard::Escape) {
          sketchClose();
        }
      } else {
        if (event.type == sf::Event::KeyPressed) {
          if (event.key.code == sf::Keyboard::BackSpace) {
            shellBackspace();
          } else if (event.key.code == sf::Keyboard::Return) {
            shellParseInput();
          } else if (event.key.code == sf::Keyboard::L and event.key.control) {
            shellClearHistory();
          } else if (event.key.code == sf::Keyboard::D and event.key.control) {
            window.close();
          }
        } else if (event.type == sf::Event::TextEntered) {
          shellAddInput(event.text.unicode);
        }
      }
    }

    // Mouse
    auto mouse = sf::Mouse::getPosition(window);
    mouseX = mouse.x;
    mouseY = mouse.y;
    mouseState = 0;
    for (int i = sf::Mouse::Left; i < sf::Mouse::ButtonCount; ++i)
      if (sf::Mouse::isButtonPressed(sf::Mouse::Button(i)))
        mouseState |= (1<<i);

    if (sketchIsRunning()) {
      // If sketch is running, I/O the sketch
      sketchRun();
    } else {
      // If sketch is not running, show the shell
      window.clear();
      shellDraw();
    }

    window.display();
  }
}

}

int main(int argc, char** argv) {
  codesketch::init(argc, argv);
  codesketch::run();
}
