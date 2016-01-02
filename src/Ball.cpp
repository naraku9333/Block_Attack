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
            shape.setPosition({ SCREEN_W / 2, BALL_STRT });
            shape.setFillColor({ 0, 178, 238 });
        }

        bool Ball::move()
        {
            float xPos = velocity.x + shape.getPosition().x;
            float yPos = velocity.y + shape.getPosition().y;

            if (xPos - BALL_RAD <= 0.f || xPos + BALL_RAD >= SCREEN_W)
                velocity.x *= -1;
            if (yPos - BALL_RAD <= 0.f) 
                velocity.y *= -1;
			if (yPos + BALL_RAD >= SCREEN_H)
				return false;

            shape.move(velocity);
			return true;
        }
    }
}
