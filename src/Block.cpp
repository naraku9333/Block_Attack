#include <Block.hpp>

namespace sv
{
    namespace ba
    {
        Block::Block(const sf::Vector2f pos, const sf::Color c)
        {
            shape.setSize({ 59.f, 20.f });
            shape.setOrigin({ 29.5f, 10.f });
            shape.setPosition(pos);
            shape.setFillColor(c);
        }
    }
}