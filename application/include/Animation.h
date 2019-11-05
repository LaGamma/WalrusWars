#ifndef _Animation_H_
#define _Animation_H_
#include <SFML/Graphics.hpp>

class Animation {
public:
  Animation();
  void updateMovement(sf::Vector2f dir, float dSec);
  void updateAttack(sf::Vector2f dir, float dSec);
  void updateSleep(float dSec);
  void init(sf::Texture* texture, sf::Vector2u spriteCount, float switchTime);

  sf::IntRect uvRect;

  //reset current sprite when player dies
  void setCurrentSprite(int x, int y);
  //needed to set begining of attack animation
  void setCurrentSpritex(int x);
  int row = 0;
  bool flip = 0;
private:
  sf::Vector2u spriteCount; //stores number of rows and columns of sprites
  sf::Vector2f currentSprite; //stores the row and column of current sprites
  float totalTime; //time since last change in sprite
  float switchTime; //time it takes before switching to new image
};

#endif
