#include <SFML/Graphics.hpp>
#include <GameLogic.h>
#include <CameraView.h>
#include <iostream>
#include <memory>


int main(int argc, char** argv)
{
  // create main window
  sf::RenderWindow App(sf::VideoMode(WINDOW_WIDTH,WINDOW_HEIGHT,32), APP_TITLE);

  std::unique_ptr<CameraView> view = std::unique_ptr<CameraView>(new CameraView());
  std::unique_ptr<GameLogic> logic = std::unique_ptr<GameLogic>(new GameLogic());

  logic->init();
  view->init();

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
    view->processInput(App, *logic, dSec);
    // tick natural game logic
    logic->update(dSec);
    // draw window
    view->draw(App, *logic);

  }

  // Done.
  return 0;
}
