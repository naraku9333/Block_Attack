#include <Block.hpp>
#include <defs.hpp>

namespace sv
{
    namespace ba
    {
        Block::Block(const sf::Vector2f pos, const sf::Color c) : is_hit(false)
        {
            shape.setSize({ BLOCK_W, BLOCK_H });
            shape.setOrigin({ BLOCK_W / 2.f, BLOCK_H / 2.f });
            shape.setPosition(pos);
            shape.setOutlineColor(c + sf::Color{100, 100, 100});
            shape.setOutlineThickness(-0.5f);
            shape.setFillColor(c);
        }
    }
}
