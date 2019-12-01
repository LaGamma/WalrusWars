#include <SFML/Graphics.hpp>
#include <GameLogic.h>
#include <CameraView.h>
#include <iostream>


int main(int argc, char** argv)
{
  // create main window
  sf::RenderWindow App(sf::VideoMode(WINDOW_WIDTH,WINDOW_HEIGHT,32), APP_TITLE);

  CameraView view;
  GameLogic logic;

  logic.init();
  view.init();

  //create clock
  sf::Clock clock;

  // start main loop
  while(App.isOpen())
  {

    sf::Time elapsed = clock.restart();
    float dSec = elapsed.asSeconds();

    // debug clock
    //std::cout << dSec << "\n";

    // process game input
    view.processInput(App, logic, dSec);
    // tick natural game logic
    logic.update(dSec);
    // draw window
    view.draw(App, logic);

  }

  // Done.
  return 0;
}
