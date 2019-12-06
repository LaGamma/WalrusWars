#ifndef _BotController_H_
#define _BotController_H_
#include "Controller.h"


class BotController : public Controller {

  public:
      BotController() = default;
      void update(sf::RenderWindow &window, GameLogic &logic, float dSec, int playerNum) override;
  private:

    struct Ray {
        sf::Vector2<double> dir;
        double dist;
        int obj;
    };
    void calculateRays(GameLogic &logic, int playerNum);
    void calculateForce(GameLogic &logic, int playerNum);

    std::list<Ray> rays;
    sf::Vector2f dir;

    float top_wall_y;
    float bottom_wall_y;
    float left_wall_x;
    float right_wall_x;
};





#endif
