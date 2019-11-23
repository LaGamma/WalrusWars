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

void Animation::updateWalrus(sf::Vector2f dir, Player::PlayerState state, float dSec) {
    switch(state) {
        case Player::idle:
            setCurrentSprite(0,0);
            break;
        case Player::resting:
            totalTime += dSec;
            currentSprite.y = 10;

            if (totalTime >= switchTime * 2) {
                totalTime -= switchTime * 2;
                currentSprite.x++;
                //make the animation loop through row
                if (currentSprite.x >= spriteCount.x) {
                    currentSprite.x = 0;
                }
            }
            break;
        case Player::raising_tusks:
            totalTime += dSec;
            currentSprite.y = row + 5;

            if (totalTime >= switchTime) {
                totalTime -= switchTime;
                currentSprite.x++;
                if (currentSprite.x >= spriteCount.x) {
                    currentSprite.x = 0;
                }
                if (currentSprite.x == 2) {
                    currentSprite.x = 1;
                }
            }
            break;
        case Player::attacking:
            totalTime += dSec;
            currentSprite.y = row + 5;

            if (totalTime >= switchTime) {
                totalTime -= switchTime;
                currentSprite.x--;
                if (currentSprite.x <= 0) {
                    currentSprite.x = spriteCount.x - 1;
                }
                if (currentSprite.x == 1) {
                    currentSprite.x = 2;
                }
            }
            break;
        case Player::running:
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
                    row = 4;
                    flip = 1;
                    break;
                case 17 - 7: //right up
                    currentSprite.y = 3;
                    row = 3;
                    flip = 1;
                    break;
                case -17 + 7: //left down
                    currentSprite.y = 4;
                    row = 4;
                    flip = 0;
                    break;
                case -17 - 7: //left up
                    currentSprite.y = 3;
                    row = 3;
                    flip = 0;
                    break;
                case 17: //right
                    currentSprite.y = 2;
                    row = 2;
                    flip = 1;
                    break;
                case 7: //down
                    currentSprite.y = 0;
                    row = 0;
                    flip = 0;
                    break;
                case -17: //left
                    currentSprite.y = 2;
                    row = 2;
                    flip = 0;
                    break;
                case -7: //up
                    currentSprite.y = 1;
                    row = 1;
                    flip = 0;
                    break;
                case 0:
                    break;
            }
            break;
    }
    // flip sprite is needed
    if (flip) {
        uvRect.left = (currentSprite.x + 1) * abs(uvRect.width);
        uvRect.width = -abs(uvRect.width);
    } else {
        uvRect.left = currentSprite.x * uvRect.width;
        uvRect.width = abs(uvRect.width);
    }
    uvRect.top = currentSprite.y * uvRect.height;
}

void Animation::updateFish(float dSec) {
    totalTime += dSec;
    //currentSprite.y = 1;

    if (totalTime >= switchTime) {
        totalTime -= switchTime;
        currentSprite.x++;
        //make the animation loop through row
        if (currentSprite.x >= spriteCount.x) {
            currentSprite.x = 0;
        }
    }
    //update uv rect
    uvRect.top = currentSprite.y * uvRect.height;
    uvRect.left = currentSprite.x * uvRect.width;
    uvRect.width = abs(uvRect.width);
}


void Animation::setCurrentSprite(int x, int y){
    currentSprite.x = x;
    currentSprite.y = y;
    uvRect.top = currentSprite.y * uvRect.height;
    uvRect.left = currentSprite.x * uvRect.width;
    uvRect.width = abs(uvRect.width);
    row = y;
}
void Animation::setCurrentSpriteX(int x){
    currentSprite.x = x;
}

void Animation::setCurrentSpriteY(int y) {
    currentSprite.y = y;
}
