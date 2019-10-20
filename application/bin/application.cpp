#include <SFML/Graphics.hpp>
#include <GameLogic.h>
#include <CameraView.h>
#include <animation.h>
#include <iostream>


int main(int argc, char** argv)
{
  // create main window
  sf::RenderWindow App(sf::VideoMode(800,600,32), "Walrus Wars");
  // get window dimensions
  sf::Vector2u dim = App.getSize();
  //load in textures
  sf::Texture spriteMapP1;
  sf::Texture spriteMapP2;
  //sprite map must be in root dir
  spriteMapP1.loadFromFile("WWP1.png");
  spriteMapP2.loadFromFile("WWP1.png");

  CameraView view;
  GameLogic logic;
  Animation animation;

  animation.init(&spriteMapP1, sf::Vector2u(3,10), 0.3);
  view.init();

  //create clock
  sf::Clock clock;

  // start main loop
  while(App.isOpen())
  {

    // clear screen and fill with blue
    App.clear(sf::Color::Blue);
    App.clear(sf::Color::Green);
    App.clear(sf::Color::Yellow);
    App.clear(sf::Color::Red);


    sf::Time elapsed = clock.restart();
    float dSec = elapsed.asSeconds();

    // debug clock
    //std::cout << dSec << "\n";

    // process game input
    view.processInput(App, logic, dSec);
    // tick natural game logic
    logic.update(dSec);
    // draw window
    view.draw(App, logic, animation, spriteMapP1, spriteMapP2, dSec);

  }

  // Done.
  return 0;
}
