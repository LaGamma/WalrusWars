#include "Animation.h"
#include <SFML/Graphics.hpp>
#include <iostream>

Animation::Animation()
{
}

void Animation::init(sf::Texture* texture, sf::Vector2u sprite_count, float switch_time)
{
  spriteCount = sprite_count;
  switchTime = switch_time;
  totalTime = 0;
  currentSpriteP1.x = 0;
  currentSpriteP2.x = 0;
  uvRectP2.width = texture->getSize().x / float(spriteCount.x);
  uvRectP2.height = texture->getSize().y / float(spriteCount.y);
  uvRectP1.width = texture->getSize().x / float(spriteCount.x);
  uvRectP1.height = texture->getSize().y / float(spriteCount.y);
}


void Animation::update(float dSec)
{
  totalTime += dSec;

  if (totalTime >= switchTime)
  {
    totalTime -= switchTime;
    currentSpriteP1.x++;
    currentSpriteP2.x++;
    //make the animation loop through row
    if (currentSpriteP1.x >= spriteCount.x)
    {
        currentSpriteP1.x = 0;
    }
    if (currentSpriteP2.x >= spriteCount.x)
    {
        currentSpriteP2.x = 0;
    }
  }

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
  {
    currentSpriteP2.y = 2;
    uvRectP2.left = currentSpriteP2.x * uvRectP2.width;
    uvRectP2.width = abs(uvRectP2.width);
  }

  else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
  {
    currentSpriteP2.y = 2;
    uvRectP2.left = (currentSpriteP2.x+1) * abs(uvRectP2.width);
    uvRectP2.width = -abs(uvRectP2.width);
  }

  else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
  {
    currentSpriteP2.y = 1;
    uvRectP2.left = currentSpriteP2.x * uvRectP2.width;
    uvRectP2.width = abs(uvRectP2.width);
  }

  else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
  {
    currentSpriteP2.y = 0;
    uvRectP2.left = (currentSpriteP2.x + 1) * abs(uvRectP2.width);
    uvRectP2.width = -abs(uvRectP2.width);
  }

  else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
  {
    currentSpriteP1.y = 2;
    uvRectP1.left = currentSpriteP1.x * uvRectP1.width;
    uvRectP1.width = abs(uvRectP1.width);
  }

  else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
  {
    currentSpriteP1.y = 2;
    uvRectP1.left = (currentSpriteP1.x+1) * abs(uvRectP1.width);
    uvRectP1.width = -abs(uvRectP1.width);
  }

  else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
  {
    currentSpriteP1.y = 1;
    uvRectP1.left = currentSpriteP1.x * uvRectP1.width;
    uvRectP1.width = abs(uvRectP1.width);
  }

  else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
  {
    currentSpriteP1.y = 0;
    uvRectP1.left = (currentSpriteP1.x + 1) * abs(uvRectP1.width);
    uvRectP1.width = -abs(uvRectP1.width);
  }
  uvRectP2.top = currentSpriteP2.y * uvRectP2.height;
  uvRectP1.top = currentSpriteP1.y * uvRectP1.height;
  }
