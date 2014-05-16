#include <Block.hpp>
#include <defs.hpp>

namespace sv
{
    namespace ba
    {
        Block::Block(const sf::Vector2f pos, const sf::Color c)
        {
            shape.setSize({ BLOCK_W, BLOCK_H });
            shape.setOrigin({ BLOCK_W / 2.f, BLOCK_H / 2.f });
            shape.setPosition(pos);
            shape.setFillColor(c);
        }
    }
}