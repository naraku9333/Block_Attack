#ifndef SV_BA_PADDLE_HPP
#define SV_BA_PADDLE_HPP

#include <SFML/Graphics.hpp>
#include <draw_obj.hpp>

namespace sv
{
    namespace ba
    {
        class Paddle : public draw_obj<sf::RectangleShape>
        {
            public:

            sf::Vector2f velocity;

            Paddle();

            void move();
        };
    }
}
#endif
