#ifndef SV_BA_BLOCK_HPP
#define SV_BA_BLOCK_HPP

#include <SFML/Graphics.hpp>
#include <draw_obj.hpp>

namespace sv
{
    namespace ba
    {
        class Block : public draw_obj<sf::RectangleShape>
        {
            public:
            Block(const sf::Vector2f = { 0, 0 }, const sf::Color = sf::Color::Blue);
        };
    }
}
#endif
