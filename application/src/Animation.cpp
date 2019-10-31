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
  currentSprite.x = 0;
  uvRect.width = texture->getSize().x / float(spriteCount.x);
  uvRect.height = texture->getSize().y / float(spriteCount.y);
}


void Animation::update(sf::Vector2f dir, float dSec) {
    totalTime += dSec;

    if (totalTime >= switchTime) {
        totalTime -= switchTime;
        currentSprite.x++;
        //make the animation loop through row
        if (currentSprite.x >= spriteCount.x) {
            currentSprite.x = 0;
        }
    }

    // this is the quickest way I could think of converting a unit vector into integers representing all of its component cases, may be a better solution
    int hash = dir.x * 17 + dir.y * 7;
    switch (hash) {
        case 17 + 7: //right down
            currentSprite.y = 4;
            uvRect.left = currentSprite.x * uvRect.width;
            uvRect.width = abs(uvRect.width);
            break;
        case 17 - 7: //right up
            currentSprite.y = 3;
            uvRect.left = (currentSprite.x + 1) * abs(uvRect.width);
            uvRect.width = -abs(uvRect.width);
            break;
        case -17 + 7: //left down
            currentSprite.y = 4;
            uvRect.left = (currentSprite.x + 1) * abs(uvRect.width);
            uvRect.width = -abs(uvRect.width);
            break;
        case -17 - 7: //left up
            currentSprite.y = 3;
            uvRect.left = currentSprite.x * uvRect.width;
            uvRect.width = abs(uvRect.width);
            break;
        case 17: //right
            currentSprite.y = 2;
            uvRect.left = (currentSprite.x + 1) * abs(uvRect.width);
            uvRect.width = -abs(uvRect.width);
            break;
        case 7: //down
            currentSprite.y = 0;
            uvRect.left = (currentSprite.x + 1) * abs(uvRect.width);
            uvRect.width = -abs(uvRect.width);
            break;
        case -17: //left
            currentSprite.y = 2;
            uvRect.left = currentSprite.x * uvRect.width;
            uvRect.width = abs(uvRect.width);
            break;
        case -7: //up
            currentSprite.y = 1;
            uvRect.left = currentSprite.x * uvRect.width;
            uvRect.width = abs(uvRect.width);
            break;
        case 0:
            break;
    }
    uvRect.top = currentSprite.y * uvRect.height;
}

void Animation::updateAttack(sf::Vector2f dir, float dSec){
    totalTime += dSec;

    if (totalTime >= switchTime) {
        totalTime -= switchTime;
        currentSprite.x++;
        //make the animation loop through row
        if (currentSprite.x >= spriteCount.x) {
            currentSprite.x = 0;
        }
    }

    // this is the quickest way I could think of converting a unit vector into integers representing all of its component cases, may be a better solution
    int hash = dir.x * 17 + dir.y * 7;
    switch (hash) {
        case 17 + 7: //right down
            currentSprite.y = 9;
            uvRect.left = (currentSprite.x + 1) * abs(uvRect.width);
            uvRect.width = -abs(uvRect.width);
            break;
        case 17 - 7: //right up
            currentSprite.y = 8;
            uvRect.left = (currentSprite.x + 1) * abs(uvRect.width);
            uvRect.width = -abs(uvRect.width);
            break;
        case -17 + 7: //left down
            currentSprite.y = 9;
            uvRect.left = currentSprite.x * uvRect.width;
            uvRect.width = abs(uvRect.width);
            break;
        case -17 - 7: //left up
            currentSprite.y = 8;
            uvRect.left = currentSprite.x * uvRect.width;
            uvRect.width = abs(uvRect.width);
            break;
        case 17: //right
            currentSprite.y = 7;
            uvRect.left = (currentSprite.x + 1) * abs(uvRect.width);
            uvRect.width = -abs(uvRect.width);
            break;
        case 7: //down
            currentSprite.y = 5;
            uvRect.left = (currentSprite.x + 1) * abs(uvRect.width);
            uvRect.width = -abs(uvRect.width);
            break;
        case -17: //left
            currentSprite.y = 7;
            uvRect.left = currentSprite.x * uvRect.width;
            uvRect.width = abs(uvRect.width);
            break;
        case -7: //up
            currentSprite.y = 6;
            uvRect.left = currentSprite.x * uvRect.width;
            uvRect.width = abs(uvRect.width);
            break;
        case 0:
            break;
    }
    uvRect.top = currentSprite.y * uvRect.height;
}

void Animation::setCurrentSprite(int x, int y){
    currentSprite.x = x;
    currentSprite.y = y;
}