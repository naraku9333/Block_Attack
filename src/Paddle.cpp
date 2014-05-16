#include <Paddle.hpp>
#include <defs.hpp>

namespace sv
{
    namespace ba
    {
        Paddle::Paddle() : velocity{ 0, 0 }
        {            
            shape.setSize({ PADDLE_W, PADDLE_H });
            shape.setOrigin({ PADDLE_W / 2.f, PADDLE_H / 2.f });
            shape.setPosition({ SCREEN_W / 2.f, SCREEN_H - 50.f });
            shape.setFillColor({ 128, 128, 128 });
        }

        void Paddle::move()
        {
            float xPos = velocity.x + shape.getPosition().x;
            if ( xPos - PADDLE_W / 2 > 0.f && xPos + PADDLE_W / 2 < SCREEN_W )
                shape.move(velocity);
        }
    }
}
