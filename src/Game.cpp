#include <Game.hpp>
#include <algorithm>
#include <vector>
#include <cmath>
#include <defs.hpp>
#include <cstdint>

namespace sv
{
    namespace ba
    {
        Game::Game() : window{ { SCREEN_W, SCREEN_H }, "Block Attack" },
            ball(),
            player()
        {
            background.loadFromFile("res/background.png");
            std::srand(static_cast<std::uint32_t>(std::time(nullptr)));
            static std::vector<sf::Color> colors
            {
                sf::Color::Red,
                sf::Color::Green,
                sf::Color::Blue,
                sf::Color::Yellow,
                sf::Color::Magenta,
                sf::Color::Cyan
            };

            //eventually I would like to load block configs from file,
            //probably xml or json and use boost to parse
            for (int i = 0; i < 6; ++i)//rows
            {
                float y = BLK_BUF + BLOCK_H / 2.f + (BLOCK_H + 1) * i;
                for (int j = 0; j < 10; ++j)//cols
                {
                    float x = BLK_BUF + BLOCK_W / 2.f + (BLOCK_W + 1) * j;
                    blocks.emplace_back(Block({ x, y }, /*colors[std::rand() % 6]*/colors[static_cast<std::uint32_t>(fmod(i + j, 6))]));
                }
            }
        }
        //run game
        void Game::run()
        {
            while (window.isOpen())
            {
                sf::Vector2f ply_vel{ 0, 0 }, ball_vel{ 0, 0 };

                sf::Event event;
                while (window.pollEvent(event))//event loop
                {
                    switch (event.type)
                    {
                        case sf::Event::Closed:
                            window.close();
                            break;
                        case sf::Event::KeyPressed:
                            if (event.key.code == sf::Keyboard::Left)
                            {
                                player.velocity.x = -0.2;
                            }
                            else if (event.key.code == sf::Keyboard::Right)
                            {
                                player.velocity.x = 0.2;
                            }
                            if (event.key.code == sf::Keyboard::Space)
                            {
                                if (ball.velocity == sf::Vector2f{})
                                {
                                    float rndx = (std::rand() % 4 - 2) / 10.f;
                                    float rndy = (std::rand() % 4 - 2) / -10.f;
                                    ball.velocity = sf::Vector2f{ rndx, rndy };
                                }
                            }
                            break;
                        case sf::Event::KeyReleased:
                            if (event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::Right)
                            {
                                player.velocity.x = 0.f;
                            }                            
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
            player.move();
            ball.move();
        }

        //draw objects
        void Game::render()
        {
            window.clear();
           // window.draw(sf::Sprite(background));

            for (auto& b : blocks)
                window.draw(b);

            window.draw(ball);
            window.draw(player);

            window.display();
        }
    }
}
