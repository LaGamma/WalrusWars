#include "BotController.h"
#include <iostream>
#include <cmath>

BotController::BotController() {
  state = fighting;
};

void BotController::update(sf::RenderWindow &window, GameLogic &logic, float dSec, int playerNum) {

    sf::Vector2f self_pos = (playerNum == 1) ? logic.walrus1->getPos() : logic.walrus2->getPos();
    bool opponent_dead = (playerNum == 1) ? logic.walrus2->isDead() : logic.walrus1->isDead();

    if(!opponent_dead) {
        state = fighting;
        // reset repel walls
        top_wall_y = -50;
        bottom_wall_y = WINDOW_HEIGHT+50;
        left_wall_x = -50;
        right_wall_x = WINDOW_WIDTH+50;
    } else {
        state = exiting;
        
        // adapt repel walls to player position
        if (self_pos.y < top_wall_y) {
            top_wall_y = self_pos.y - 150.0f;
        }
        if (self_pos.y > bottom_wall_y) {
            bottom_wall_y = self_pos.y + 150.0f;
        }
        if (self_pos.x < left_wall_x) {
            left_wall_x = self_pos.x - 150.0f;
        }
        if (self_pos.x > right_wall_x) {
            right_wall_x = self_pos.x + 150.0f;
        }
        // enclose repel walls
        if (bottom_wall_y > 17*WINDOW_HEIGHT/30+ICE_BLOCKS_HEIGHT) {
            bottom_wall_y -= dSec*120;
        }
        if (top_wall_y < 13*WINDOW_HEIGHT/30+ICE_BLOCKS_HEIGHT) {
            top_wall_y += dSec*120;
        }
        if (playerNum == 1 && right_wall_x > 0) {
            right_wall_x -= dSec*120;
        } else if (playerNum == 2 && left_wall_x < WINDOW_WIDTH) {
            left_wall_x += dSec*120;
        }

    }

    // draw repel border
    sf::Vertex line[] = {
            sf::Vertex(sf::Vector2f(left_wall_x, bottom_wall_y)),
            sf::Vertex(sf::Vector2f(right_wall_x,bottom_wall_y)),
            sf::Vertex(sf::Vector2f(right_wall_x, top_wall_y)),
            sf::Vertex(sf::Vector2f(left_wall_x, top_wall_y)),
            sf::Vertex(sf::Vector2f(left_wall_x,bottom_wall_y))
    };
    for(int i = 0; i < 5; i++) {
        line[i].color = sf::Color::Black;
    }
    window.draw(line, 5, sf::LinesStrip);

    
    calculateRays(logic, playerNum);

    // draw rays
    for (auto r = rays.begin(); r != rays.end(); r++) {
        sf::Vertex line[] = {
                sf::Vertex(self_pos + sf::Vector2f((float)(*r).dir.x, (float)(*r).dir.y) * (float)(*r).dist),
                sf::Vertex(self_pos)
        };
        line[0].color = sf::Color::Blue;
        line[1].color = sf::Color::Blue;

        window.draw(line, 2, sf::Lines);
    }

    
    calculateForce(logic, playerNum);

    // draw direction line
    sf::Vertex direction_line[] = {
            sf::Vertex(self_pos + dir),
            sf::Vertex(self_pos)
    };
    direction_line[0].color = sf::Color::Red;
    direction_line[1].color = sf::Color::Red;
    window.draw(direction_line, 2, sf::Lines);


    double angst_magnitude = sqrt((dir.x * dir.x) + (dir.y * dir.y));
    
    //sf::Vector2<double> unit_vec = sf::Vector2<double>(dir.x / angst_magnitude, dir.y / angst_magnitude);
    //dir = sf::Vector2f(unit_vec.x *(angst_magnitude/200.0), unit_vec.y *(angst_magnitude/200.0));
    
    if (angst_magnitude > 30 && state == fighting) {
        // set target movement direction
        sf::Vector2<double> unit_vec = sf::Vector2<double>(dir.x / angst_magnitude, dir.y / angst_magnitude);
        dir = sf::Vector2f(unit_vec.x, unit_vec.y);
    } else if (angst_magnitude > 60) {
        // set target movement direction
        sf::Vector2<double> unit_vec = sf::Vector2<double>(dir.x / angst_magnitude, dir.y / angst_magnitude);
        dir = sf::Vector2f(unit_vec.x, unit_vec.y);
    } else {
        //slow down?
        //std::cout<<"low angst: "<<angst_magnitude<<std::endl;
        sf::Vector2<double> unit_vec = sf::Vector2<double>(dir.x / angst_magnitude, dir.y / angst_magnitude);
        dir = sf::Vector2f(unit_vec.x / 4, unit_vec.y / 4);
    }

    // apply movement force
    (playerNum == 1) ? logic.walrus1->applyActiveForce(dir, dSec) : logic.walrus2->applyActiveForce(dir, dSec);

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

    sf::Vector2<double> opponent_pos = (playerNum == 1) ? static_cast<sf::Vector2<double>>(logic.walrus2->getPos()) : static_cast<sf::Vector2<double>>(logic.walrus1->getPos());
    sf::Vector2<double> self_pos = (playerNum == 1) ? static_cast<sf::Vector2<double>>(logic.walrus1->getPos()) : static_cast<sf::Vector2<double>>(logic.walrus2->getPos());

    rays.clear();

    for (int i = 0; i < NUM_OF_RAYS_CAST; i++) {

        // calculate unit vector direction
        double angle = (360.0 / NUM_OF_RAYS_CAST) * i;
        sf::Vector2<double> unit_vec = sf::Vector2<double>(cos(angle*PI/180.0), sin(angle*PI/180.0));

        // project unit vector outwards until colliding with water
        sf::Vector2<double> projection = self_pos + (unit_vec / 10.0);

        if (state == fighting) {
            while (logic.stage->getTileDura((int)(projection.x/ICE_BLOCKS_SIZE_Y), (int)(projection.y/ICE_BLOCKS_SIZE_Y), logic.getStageProgression()) > 0.4) {
                projection += (unit_vec / 10.0);
            }
            projection -= self_pos;
            // calculate length of projection
            double magnitude = sqrt(projection.x*projection.x + projection.y*projection.y);
            // create ray to water (1) and add to ray list
            Ray r {unit_vec, magnitude, 1};
            rays.push_back(r);

        } else {
            while (logic.stage->getTileDura((int)(projection.x/ICE_BLOCKS_SIZE_Y), (int)(projection.y/ICE_BLOCKS_SIZE_Y), logic.getStageProgression()) > 0.4 && projection.x > left_wall_x && projection.x < right_wall_x && projection.y > top_wall_y && projection.y < bottom_wall_y) {
                projection += (unit_vec / 10.0);
            }
            if (logic.stage->getTileDura((int)(projection.x/ICE_BLOCKS_SIZE_Y), (int)(projection.y/ICE_BLOCKS_SIZE_Y), logic.getStageProgression()) > 0.4) {
                projection -= self_pos;
                double magnitude = sqrt(projection.x*projection.x + projection.y*projection.y);
                // create ray to water (1) and add to ray list
                Ray r {unit_vec, magnitude, 1};
                rays.push_back(r);
            } else {
                projection -= self_pos;
                double magnitude = sqrt(projection.x*projection.x + projection.y*projection.y);
                // create ray to repel border (4) and add to ray list
                Ray r {unit_vec, magnitude, 4};
                rays.push_back(r);
            }

        }
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
    if (state == fighting) {
        sf::Vector2<double> posDiff = opponent_pos - self_pos;
        double magnitude = sqrt((posDiff.x * posDiff.x) + (posDiff.y * posDiff.y));
        sf::Vector2<double> unit_vec = sf::Vector2<double>(posDiff.x / magnitude, posDiff.y / magnitude);

        // create ray to opponent (3) and add to ray list
        Ray r {unit_vec, magnitude, 3};
        rays.push_back(r);
    } else {
        sf::Vector2<double> posDiff = opponent_pos - self_pos;
        double magnitude = sqrt((posDiff.x * posDiff.x) + (posDiff.y * posDiff.y));
        sf::Vector2<double> unit_vec = sf::Vector2<double>(posDiff.x / magnitude, posDiff.y / magnitude);

        // create ray to opponent (3) and add to ray list
        Ray r {unit_vec, magnitude, 4};
        rays.push_back(r);
    }
}

void BotController::calculateForce(GameLogic &logic, int playerNum) {

    sf::Vector2f opponent_vel = (playerNum == 1) ? logic.walrus2->getVel() : logic.walrus1->getVel();
    sf::Vector2f self_vel = (playerNum == 1) ? logic.walrus1->getVel() : logic.walrus2->getVel();

    sf::Vector2<double> pop_vec = sf::Vector2<double>(0,0);

    sf::Vector2f opponent_force_component;
    sf::Vector2f self_force_component;
    sf::Vector2f force_diff_advantage;

    // provide the forces as functions of distance to calculate a population vector that guides movement
    for (auto r = rays.begin(); r != rays.end(); r++) {
        // which object type is it?
        switch ((*r).obj) {
            case 1: // water
                // repel from water direction
                pop_vec -= (*r).dir * ((100.0*pow(0.99, (*r).dist)) + 10.0);
                break;
            case 2: // fish
                // attract to fish direction
                pop_vec += (*r).dir * ((100.0*pow(0.97, (*r).dist)) + 10.0);
                break;
            case 3: // opponent
                opponent_force_component = sf::Vector2f(opponent_vel.x * -(*r).dir.x, opponent_vel.y * -(*r).dir.y);
                self_force_component = sf::Vector2f(self_vel.x * (*r).dir.x, self_vel.y * (*r).dir.y);
                force_diff_advantage = self_force_component - opponent_force_component;

                if (force_diff_advantage.x > 30.0 || force_diff_advantage.y > 30.0) {
                    //std::cout<<"advantage, attack!"<<std::endl;
                    pop_vec += (*r).dir * ((100.0*pow(0.99, (*r).dist)) + 10.0);
                }

                else if (force_diff_advantage.x < -30.0 || force_diff_advantage.y < -30.0) {
                    //std::cout<<"disadvantage, run!"<<std::endl;
                    pop_vec -= (*r).dir * ((100.0*pow(0.99, (*r).dist)) + 10.0);
                }
                break;
            case 4: // repel border
                // repel strongly
                pop_vec -= (*r).dir * ((200.0*pow(0.99, (*r).dist)) + 10.0);
                break;
        }
    }

    dir = sf::Vector2f(pop_vec.x, pop_vec.y);

}
