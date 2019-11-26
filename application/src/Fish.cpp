#include <iostream>
#include "Fish.h"

Fish::Fish(sf::Vector2f pos, sf::Vector2f init_target) {
    spawn(pos, init_target);
}

void Fish::spawn(sf::Vector2f position, sf::Vector2f init_target) {
    pos = position;

    int rand_color = rand() % 10;
    if (rand_color < 5)
        color = 0;
    else
        color = 1;

    // roll dice to set threshold
    flop_trigger_timer = rand() % 4 + 2;
    // start in flopping pos
    target_flop = init_target;
    flop_progress_timer = 1.0f;

}

void Fish::flop(float dSec) {

    // check if we're still below the current threshold
    if (flop_time_accumulator <= flop_trigger_timer) {
        flop_time_accumulator += dSec;
    } else {
        flop_time_accumulator -= flop_trigger_timer;
        target_flop = sf::Vector2f(rand() % 80 - 40, rand() % 80 - 40);
        flop_progress_timer = 1.0f;
        // re-roll dice and set threshold
        flop_trigger_timer = rand() % 3 + 1;
    }

    // move fish to the target
    if (flop_progress_timer > 0) {
        pos += target_flop * dSec;
        flop_progress_timer -= dSec;
    } else {
        flop_progress_timer = 0;
    }
}

sf::Vector2f Fish::getPosition() {
    return pos;
}

unsigned int Fish::getColor() {
    return color;
}