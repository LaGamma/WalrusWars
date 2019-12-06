#ifndef _Animation_H_
#define _Animation_H_
#include <SFML/Graphics.hpp>
#include "Player.h"

class Animation {
public:
  Animation() = default;
  void init(sf::Texture* texture, sf::Vector2u spriteCount, float switchTime);
  void updateWalrus(sf::Vector2f dir, Player::PlayerState state, float dSec);
  void updateFish(float dSec);
  void updateRoundFire(float dSec);
  void updateWalrusSplash(float dSec);
  void updateWater(float dSec);
  //reset current sprite when player dies
  void setCurrentSprite(int x, int y);
  //set fish color
  void setCurrentSpriteY(int y);

  sf::IntRect uvRect;

private:
  sf::Vector2u spriteCount; //stores number of rows and columns of sprites
  sf::Vector2f currentSprite; //stores the row and column of current sprites
  float totalTime; //time since last change in sprite
  float switchTime; //time it takes before switching to new image
  int row = 0;
  bool flip = false;
};

#endif
