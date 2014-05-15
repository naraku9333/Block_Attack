#include <Game.hpp>
#include <algorithm>
#include <vector>
#include <cmath>

namespace sv
{
    namespace ba
    {
        Game::Game() : window{ { 800, 800 }, "Block Attack" },
            ball(),
            player()
        {
            std::srand(std::time(nullptr));
            static std::vector<sf::Color> colors
            {
                sf::Color::Red,
                sf::Color::Green,
                sf::Color::Blue,
                sf::Color::Yellow,
                sf::Color::Magenta,
                sf::Color::Cyan
            };

            for (int i = 0; i < 6; ++i)
            {
                float y = 110.f + 21 * i;
                for (int j = 0; j < 10; ++j)
                {
                    float x = 129.5f + 60 * j;
                    blocks.emplace_back(Block({ x, y }, /*colors[std::rand() % 6]*/colors[fmod(i + j, 6)]));
                }
            }
        }
        //run game
        void Game::run()
        {
            while (window.isOpen())
            {
                sf::Event event;
                while (window.pollEvent(event))//event loop
                {
                    switch (event.type)
                    {
                        case sf::Event::Closed:
                            window.close();
                            break;
                        case sf::Event::KeyPressed:
                            break;
                        case sf::Event::KeyReleased:
                            break;
                        default:
                            break;
                    }
                }
                update();
                render();
            }
        }

        //update objects
        void Game::update()
        {

        }

        //draw objects
        void Game::render()
        {
            window.clear();

            for (auto& b : blocks)
                window.draw(b);
            window.draw(ball);
            window.draw(player);

            window.display();
        }
    }
}
