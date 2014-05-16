#include <Ball.hpp>
#include <defs.hpp>

namespace sv
{
    namespace ba
    {
        Ball::Ball() : velocity{ 0, 0 }
        {
            shape.setRadius(BALL_RAD);
            shape.setOrigin({ BALL_RAD, BALL_RAD });
            shape.setPosition({ 400, 738 });
            shape.setFillColor({ 0, 178, 238 });
        }

        void Ball::move()
        {
            float xPos = velocity.x + shape.getPosition().x;
            float yPos = velocity.y + shape.getPosition().y;

            if (xPos - BALL_RAD <= 0.f || xPos + BALL_RAD >= SCREEN_W)
                velocity.x *= -1;
            if (yPos - BALL_RAD <= 0.f || yPos + BALL_RAD >= SCREEN_H)
                velocity.y *= -1;

            shape.move(velocity);
        }
    }
}
