#include <Game.hpp>
#include <algorithm>
#include <vector>
#include <cmath>
#include <defs.hpp>
#include <cstdint>
#include <iostream>

namespace sv
{
    namespace ba
    {
        Game::Game() : window{ { SCREEN_W, SCREEN_H }, "Block Attack" },
            ball(),
            player()
        {
            window.setFramerateLimit(100);
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
                    blocks.emplace_back(
                        Block({ x, y }, colors[static_cast<std::uint32_t>(fmod(i + j, 6))])
                        );
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
                            if (event.key.code == sf::Keyboard::Left)
                            {
                                player.velocity.x = -5;
                            }
                            else if (event.key.code == sf::Keyboard::Right)
                            {
                                player.velocity.x = 5;
                            }
                            if (event.key.code == sf::Keyboard::Space)
                            {
                                if (ball.velocity == sf::Vector2f{})
                                {
                                    //float rndx = (std::rand() % SCREEN_W - SCREEN_W / 2) / 100.f;
                                    ball.velocity = { BALL_SPEED, -BALL_SPEED };
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
            collision(ball, player);
            for (auto& b : blocks)
            {
                collision(ball, b);
            }
            blocks.erase(std::remove_if(blocks.begin(), blocks.end(), [](Block& b){ return b.is_hit; }), blocks.end());
        }

        //draw objects
        void Game::render()
        {
            window.clear();
            window.draw(sf::Sprite(background));

            for (auto& b : blocks)
                window.draw(b);

            window.draw(ball);
            window.draw(player);

            window.display();
        }

        void Game::collision(Ball& ball, Paddle& other)
        {
            if (ball.collision(other) && ball.velocity != sf::Vector2f{})
            {                      
                float relXInt = other.shape.getPosition().x - ball.shape.getPosition().x;
                float norm = relXInt / (PADDLE_W / 2.f);
                float angle = norm * (5.f * M_PI / 12.f);

                ball.velocity.x = BALL_SPEED * std::sin(angle);
                ball.velocity.y = BALL_SPEED * -std::cos(angle);
            }           
        }

        void Game::collision(Ball& b, Block& bl)
        {
            if (b.collision(bl))
            {
                bl.is_hit = true;

                auto ballpos = b.shape.getPosition();
                auto blockpos = bl.shape.getPosition();

                if (ballpos.y > blockpos.y - BLOCK_H / 2.f && ballpos.y < blockpos.y + BLOCK_H / 2.f)//block hit from side
                {
                    b.velocity.x *= -1;
                }
                else
                {
                    b.velocity.y *= -1;
                }                
            }
        }
    }
}
