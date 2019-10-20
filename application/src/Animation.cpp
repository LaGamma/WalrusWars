#include "animation.h"
#include <SFML/Graphics.hpp>
#include <iostream>

Animation::Animation(sf::Texture* texture, sf::Vector2u spriteCount, float switchTime)
{
  this->spriteCount = spriteCount;
  this->switchTime = switchTime;
  totalTime = 0;
  currentSprite.x = 0;

  uvRect.width = texture->getSize().x / float(spriteCount.x);
  uvRect.height = texture->getSize().y / float(spriteCount.y);
}
void Animation::update(int row, float dSec)
{
  currentSprite.y = row;
  totalTime += dSec;

  if (totalTime >= switchTime)
  {
    totalTime -= switchTime;
    currentSprite.x++;

    //make the animation loop through row
    if (currentSprite.x >= spriteCount.x)
    {
        currentSprite.x = 0;
    }
  }

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
  {
    currentSprite.y = 2;
    uvRect.left = currentSprite.x * uvRect.width;
    uvRect.width = abs(uvRect.width);
  }

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
  {
    currentSprite.y = 2;
    uvRect.left = (currentSprite.x+1) * abs(uvRect.width);
    uvRect.width = -abs(uvRect.width);

  }

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
  {
    currentSprite.y = 1;
    uvRect.left = currentSprite.x * uvRect.width;
    uvRect.width = abs(uvRect.width);
  }

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
  {
    currentSprite.y = 0;
    uvRect.left = (currentSprite.x + 1) * abs(uvRect.width);
    uvRect.width = -abs(uvRect.width);
  }
  uvRect.top = currentSprite.y * uvRect.height;
  }
int Animation::getSpriteRow()
{
  return currentSprite.y;
}
