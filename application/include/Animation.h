#ifndef _Animation_H_
#define _Animation_H_
#include <SFML/Graphics.hpp>
#include "Player.h"

class Animation {
public:
  Animation();
  void init(sf::Texture* texture, sf::Vector2u spriteCount, float switchTime);
  void updateWalrus(sf::Vector2f dir, Player::PlayerState state, float dSec);
  void updateFish(float dSec);
  void updateroundFire(float dSec);
  void updateWalrusSplash(float dSec);
  void updateWater(float dSec);


  sf::IntRect uvRect;

  //reset current sprite when player dies
  void setCurrentSprite(int x, int y);
  //needed to set beginning of attack animation
  void setCurrentSpriteX(int x);
  void setCurrentSpriteY(int y);
  int row = 0;
  bool flip = false;
private:
  sf::Vector2u spriteCount; //stores number of rows and columns of sprites
  sf::Vector2f currentSprite; //stores the row and column of current sprites
  float totalTime; //time since last change in sprite
  float switchTime; //time it takes before switching to new image
};

#endif
