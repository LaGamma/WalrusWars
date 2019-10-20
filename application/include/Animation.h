#ifndef _Animation_H_
#define _Animation_H_
#include <SFML/Graphics.hpp>

class Animation {
public:
  Animation();
  void update(float dSec);
  void init(sf::Texture* texture, sf::Vector2u spriteCount, float switchTime);

  sf::IntRect uvRectP2;
  sf::IntRect uvRectP1;

private:
  sf::Vector2u spriteCount; //stores number of rows and columns of sprites
  sf::Vector2u currentSpriteP1; //stores the row and column of current sprites
  sf::Vector2u currentSpriteP2;
  float totalTime; //time since last change in sprite
  float switchTime; //time it takes before switching to new image
};

#endif
