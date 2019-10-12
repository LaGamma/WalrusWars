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

  // create major update classes
  //Controller player1;
  //Controller player2;
  CameraView camera;
  GameLogic logic;

  //create clock
  sf::Clock clock;

  // start main loop
  while(App.isOpen())
  {
    // process events
    sf::Event Event;
    while(App.pollEvent(Event))
    {
      // Exit
      if(Event.type == sf::Event::Closed)
        App.close();
    }

    // clear screen and fill with blue
    App.clear(sf::Color::Blue);
    App.clear(sf::Color::Green);
    App.clear(sf::Color::Yellow);


    sf::Time elapsed = clock.restart();
    float dSec = elapsed.asSeconds() * 2000;

    // debug clock
    std::cout << dSec << "\n";

    // process user/bot input
    //player1.update(dSec);
    //player2.update(dSec);
    // tick natural game logic
    logic.update(dSec);
    // draw window in cameraView
    camera.draw(App);

    // display
    App.display();
  }

  // Done.
  return 0;
}