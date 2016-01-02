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
			bool running;
            int score, lives;
			float ball_speed;

            Ball ball;
            Paddle player;
            std::vector<Block> blocks;
            
            sf::Font font;
            sf::Text lives_txt;
			sf::Text message;
            sf::Texture background;
            sf::RenderWindow window;

			void fill_blocks();
            void collision(Ball&, Paddle&);
            void collision(Ball&, Block&);

            public:
            Game();
            void run();
            void update();
            void render();
        };
    }
}
#endif
