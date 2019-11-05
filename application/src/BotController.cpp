#include "BotController.h"

BotController::BotController() {

};

void BotController::update(sf::RenderWindow &window, GameLogic &logic, float dSec, int playerNum, Animation &anim) {


    float bot_handicap = 1.0;  // higher number == slower bot

    sf::Vector2f dir = sf::Vector2f(0,0);
    sf::Vector2f w1_pos = logic.walrus1.getPos();
    sf::Vector2f w2_pos = logic.walrus2.getPos();

    if (playerNum == 1) {
        //process input for player 1
        if (w1_pos.y > w2_pos.y) {
            dir.y -= 1;
        } else if (w1_pos.y < w2_pos.y) {
            dir.y += 1;
        }
        if (w1_pos.x > w2_pos.x) {
            dir.x -= 1;
        } else if (w1_pos.x < w2_pos.x) {
            dir.x += 1;
        }

        logic.walrus1.applyActiveForce(dir, dSec/bot_handicap);

    } else {
        //process input for player 2
        if (w2_pos.y > w1_pos.y) {
            dir.y -= 1;
        } else if (w2_pos.y < w1_pos.y) {
            dir.y += 1;
        }
        if (w2_pos.x > w1_pos.x) {
            dir.x -= 1;
        } else if (w2_pos.x < w1_pos.x) {
            dir.x += 1;
        }
        logic.walrus2.applyActiveForce(dir, dSec/bot_handicap);

    }
    anim.updateMovement(dir, dSec/bot_handicap);

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
};
