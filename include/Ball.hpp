#ifndef SV_BA_BALL_HPP
#define SV_BA_BALL_HPP

#include <SFML/Graphics.hpp>
#include <draw_obj.hpp>

namespace sv
{
    namespace ba
    {
        class Ball : public draw_obj<sf::CircleShape>
        {
            public:
            sf::Vector2f velocity;

            Ball();

            void move();
        };
    }
}
#endif
