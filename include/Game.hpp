#ifndef SV_BA_GAME_HPP
#define SV_BA_GAME_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <algorithm>
#include <Block.hpp>
#include <Paddle.hpp>
#include <Ball.hpp>

namespace sv
{
    namespace ba
    {
        class Game
        {
            Ball ball;
            Paddle player;
            std::vector<Block> blocks;

            sf::RenderWindow window;

            public:
            Game();
            void run();
            void update();
            void render();
        };
    }
}
#endif