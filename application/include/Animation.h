#ifndef _Animation_H_
#define _Animation_H_

#include <SFML/Graphics.hpp>

class Animation
{
public:
<<<<<<< HEAD
  animation(sf::Texture* texture, sf::Vector2u spriteCount, float switchTime);
  void Update(int row, float dSec);
  int getSpriteRow();

public:
  sf::IntRect uvRect;

private:
  sf::Vector2u spriteCount; //stores number of rows and columns of sprites
  sf::Vector2u currentSprite; //stores the row and column of current sprites

  float totalTime; //time since last change in sprite
  float switchTime; //time it takes before switching to new image
=======
  Animation();
  void Update();
>>>>>>> 7ef964d01003f9424ee4906d4b481106b9016621
};

#endif
