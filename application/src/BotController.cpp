#include "BotController.h"
#include <iostream>
#include <cmath>

//for ai, generally move towards center if player near edge shortest path towards where player is headed or is depending on difficulty
// , if in close proximity to fish or closer to fish than player shortest path to fish.

BotController::BotController() {
  state = defensive;
};

void BotController::update(sf::RenderWindow &window, GameLogic &logic, float dSec, int playerNum) {

    sf::Vector2f self_pos = (playerNum == 1) ? logic.walrus1.getPos() : logic.walrus2.getPos();


    float bot_handicap = 2;  // higher number == slower bot

    /*// can probably simplify to 2 states
if(!opponent_dead && (state != defensive) && (opponent_vel.x>=30 || opponent_vel.y>=30)){
    state = defensive;
}
if(!opponent_dead && (state != aggressive) && (opponent_vel.x<30 || opponent_vel.y<30)){
    state = aggressive;
}
if(opponent_dead && (state != transition)){
    state = transition;
}*/


    calculateRays(logic, playerNum);

    for (auto r = rays.begin(); r != rays.end(); r++) {

        sf::Vertex line[] = {
                sf::Vertex(self_pos + sf::Vector2f((float)(*r).dir.x, (float)(*r).dir.y) * (float)(*r).dist),
                sf::Vertex(self_pos)
        };
        line[0].color = sf::Color::Red;
        line[1].color = sf::Color::Red;

        window.draw(line, 2, sf::Lines);
    }

    calculateForce(logic, playerNum);

    sf::Vertex line[] = {
            sf::Vertex(self_pos + dir),
            sf::Vertex(self_pos)
    };
    line[0].color = sf::Color::Green;
    line[1].color = sf::Color::Green;

    window.draw(line, 2, sf::Lines);

    (playerNum == 1) ? logic.walrus1.applyActiveForce(dir, dSec) : logic.walrus2.applyActiveForce(dir, dSec);

    // process events
    sf::Event Event;
    while (window.pollEvent(Event)) {
        switch (Event.type) {
            //window closed
            case sf::Event::Closed:
                window.close();
                break;
                //window out of focus
            case sf::Event::LostFocus:
                logic.togglePause();
                break;
            case sf::Event::GainedFocus:
                break;
            case sf::Event::KeyPressed:
                if (Event.key.code == sf::Keyboard::P) {
                    logic.togglePause();
                }
                break;
        }
    }
}


void BotController::calculateRays(GameLogic &logic, int playerNum) {
    bool opponent_dead = (playerNum == 1) ? logic.walrus2.isDead() : logic.walrus1.isDead();

    sf::Vector2<double> opponent_pos = (playerNum == 1) ? static_cast<sf::Vector2<double>>(logic.walrus2.getPos()) : static_cast<sf::Vector2<double>>(logic.walrus1.getPos());
    sf::Vector2<double> self_pos = (playerNum == 1) ? static_cast<sf::Vector2<double>>(logic.walrus1.getPos()) : static_cast<sf::Vector2<double>>(logic.walrus2.getPos());

    rays.clear();

    for (int i = 0; i < NUM_OF_RAYS_CAST; i++) {

        // calculate unit vector direction
        double angle = (360.0 / NUM_OF_RAYS_CAST) * i;
        sf::Vector2<double> unit_vec = sf::Vector2<double>(cos(angle*PI/180.0), sin(angle*PI/180.0));

        // project unit vector outwards until colliding with water
        sf::Vector2<double> projection = self_pos + (unit_vec / 10.0);
        while (logic.stage.getTileDura((int)(projection.x/ICE_BLOCKS_SIZE_Y), (int)(projection.y/ICE_BLOCKS_SIZE_Y), logic.getStageProgression()) > 0.4) {
            projection += (unit_vec / 10.0);
        }
        projection -= self_pos;

        // calculate length of projection
        double magnitude = sqrt(projection.x*projection.x + projection.y*projection.y);

        // create ray to water (1) and add to ray list
        Ray r {unit_vec, magnitude, 1};
        rays.push_back(r);

    }

    // calculate and add fish rays to list
    for (auto fish = logic.fish_list.begin(); fish != logic.fish_list.end(); fish++) {

        sf::Vector2<double> fish_pos = static_cast<sf::Vector2<double>>((*fish)->getPosition());
        sf::Vector2<double> posDiff = fish_pos - self_pos;
        double magnitude = sqrt((posDiff.x * posDiff.x) + (posDiff.y * posDiff.y));
        sf::Vector2<double> unit_vec = sf::Vector2<double>(posDiff.x / magnitude, posDiff.y / magnitude);

        // create ray to fish (2) and add to ray list
        Ray r {unit_vec, magnitude, 2};
        rays.push_back(r);
    }

    // calculate and add opponent ray to list
    if (!opponent_dead) {

        sf::Vector2<double> posDiff = opponent_pos - self_pos;
        double magnitude = sqrt((posDiff.x * posDiff.x) + (posDiff.y * posDiff.y));
        sf::Vector2<double> unit_vec = sf::Vector2<double>(posDiff.x / magnitude, posDiff.y / magnitude);

        // create ray to opponent (3) and add to ray list
        Ray r {unit_vec, magnitude, 3};
        rays.push_back(r);
    }
}

void BotController::calculateForce(GameLogic &logic, int playerNum) {
    sf::Vector2f opponent_vel = (playerNum == 1) ? logic.walrus2.getVel() : logic.walrus1.getVel();
    sf::Vector2f self_vel = (playerNum == 1) ? logic.walrus1.getVel() : logic.walrus2.getVel();

    sf::Vector2<double> pop_vec = sf::Vector2<double>(0,0);

    // provide the forces as functions of distance to calculate a population vector that guides movement
    for (auto r = rays.begin(); r != rays.end(); r++) {
        // which object type is it?
        switch ((*r).obj) {
            case 1: // water
                // repel from water direction
                pop_vec -= (*r).dir * ((50.0*pow(0.99, (*r).dist)) + 10.0);
                break;
            case 2: // fish
                // attract to fish direction
                pop_vec += (*r).dir * ((100.0*pow(0.99, (*r).dist)) + 10.0);
                break;
            case 3: // opponent

                sf::Vector2f opponent_force_component = sf::Vector2f(opponent_vel.x * -(*r).dir.x, opponent_vel.y * -(*r).dir.y);
                sf::Vector2f self_force_component = sf::Vector2f(self_vel.x * (*r).dir.x, self_vel.y * (*r).dir.y);

                sf::Vector2f force_diff_advantage = self_force_component - opponent_force_component;

                float magnitude = sqrt((force_diff_advantage.x * force_diff_advantage.x) + (force_diff_advantage.y * force_diff_advantage.y));

                if (force_diff_advantage.x > 30.0 || force_diff_advantage.y > 30.0) {
                    std::cout<<"advantage!"<<std::endl;
                    pop_vec += (*r).dir * ((100.0*pow(0.99, (*r).dist)) + 10.0);
                }

                else if (force_diff_advantage.x < -30.0 || force_diff_advantage.y < -30.0) {
                    std::cout<<"disadvantage, run!"<<std::endl;
                    pop_vec -= (*r).dir * ((100.0*pow(0.99, (*r).dist)) + 10.0);
                }

                break;
        }
    }


    double magnitude = sqrt((pop_vec.x * pop_vec.x) + (pop_vec.y * pop_vec.y));
    sf::Vector2<double> unit_vec = sf::Vector2<double>(pop_vec.x / magnitude, pop_vec.y / magnitude);
    // set target movement direction
    dir = sf::Vector2f(unit_vec.x, unit_vec.y);

}
