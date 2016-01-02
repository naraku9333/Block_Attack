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
			running(true),
            score(0),
            lives(3),
			ball_speed(BALL_SPEED),
            ball(),
            player(),
            lives_txt("", font),
			message("   GAME OVER!\nPlay Again? (Y/N)", font, 50)
        {
            window.setFramerateLimit(100);
            font.loadFromFile("res/Sansation.ttf");
            background.loadFromFile("res/background.png");
            lives_txt.setPosition(SCREEN_W - 120, 0);
			message.setPosition(SCREEN_W / 2 - message.getLocalBounds().width/2, SCREEN_H / 2 - message.getLocalBounds().height/2);
            std::srand(static_cast<std::uint32_t>(std::time(nullptr)));            

			fill_blocks();
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
                                    float rndx = (std::rand() % SCREEN_W - SCREEN_W / 2) / 100.f;
                                    ball.velocity = { rndx, -ball_speed };
                                }
                            }
							if (!running)
							{
								if (event.key.code == sf::Keyboard::Y)
								{
									running = true;
									blocks.clear();
									fill_blocks();
									lives = 3;
									score = 0;
								}
								if (event.key.code == sf::Keyboard::N) window.close();
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

				if (running)
				{
					update();
					render();
				}
				else
				{
					window.clear();
					window.draw(message);
					window.display();
				}
            }
        }

        //update objects
        void Game::update()
        {
            player.move();
			if (ball.move())
			{
				collision(ball, player);
				for (auto& b : blocks)
				{
					collision(ball, b);
				}
				blocks.erase(std::remove_if(blocks.begin(), blocks.end(), [](Block& b) { return b.is_hit; }), blocks.end());
				if (blocks.empty())//level is over
				{
					score += 1000;
					++lives;
					fill_blocks();
					ball_speed += 0.2f;
					ball = Ball();
					player = Paddle();
				}
			}
			else
			{
				--lives;
				if (lives == 0) running = false;
				int i = 0;
				(++i)++;
				ball = Ball();
				player = Paddle();
			}
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
            lives_txt.setString("Lives: " + std::to_string(lives));
            window.draw(lives_txt);
            window.draw(sf::Text("Score: " + std::to_string(score), font));
            window.display();
        }

        void Game::collision(Ball& ball, Paddle& other)
        {
            if (ball.collision(other) && ball.velocity != sf::Vector2f{})
            {                      
                float relXInt = other.shape.getPosition().x - ball.shape.getPosition().x;
                float norm = relXInt / (PADDLE_W / 2.f);
                float angle = norm * ( M_PI / 3.f);

                ball.velocity.x = ball_speed * std::sin(angle);
                ball.velocity.y = ball_speed * -std::cos(angle);
            }           
        }

        void Game::collision(Ball& b, Block& bl)
        {
            if (b.collision(bl))
            {
                bl.is_hit = true;
                score += bl.score;

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

		void Game::fill_blocks()
		{
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
					std::uint32_t index = static_cast<std::uint32_t>(fmod(i + j, 6));
					blocks.emplace_back(
						Block({ x, y }, colors[index], (index + 1) * 10)
						);
				}
			}
		}
    }
}
