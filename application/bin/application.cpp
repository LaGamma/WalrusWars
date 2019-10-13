#include <SFML/Graphics.hpp>
#include <GameLogic.h>
#include <CameraView.h>
#include <iostream>


int main(int argc, char** argv)
{
  // create main window
  sf::RenderWindow App(sf::VideoMode(800,600,32), "Walrus Wars");
  // get window dimensions
  sf::Vector2u dim = App.getSize();

  CameraView view;
  GameLogic logic;
  view.init(logic);

  //create clock
  sf::Clock clock;

  // start main loop
  while(App.isOpen())
  {

    // clear screen and fill with blue
    App.clear(sf::Color::Blue);
    App.clear(sf::Color::Green);
    App.clear(sf::Color::Yellow);


    sf::Time elapsed = clock.restart();
    float dSec = elapsed.asSeconds() * 2000;

    // debug clock
    //std::cout << dSec << "\n";

    // process game input
    view.processInput(App, dSec);
    // tick natural game logic
    logic.update(dSec);
    // draw window
    view.draw(App);

  }

  // Done.
  return 0;
}
