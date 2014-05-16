#ifndef SV_DRAW_OBJ_HPP
#define SV_DRAW_OBJ_HPP

#include <SFML/Graphics.hpp>
#include <memory>

namespace sv
{
    namespace ba
    {
        template <class T>
        class draw_obj : public sf::Drawable
        {
            protected:
            T shape;

            public:
            draw_obj() 
            {

            }

            //void set_position(const sf::Vector2f pos) { shape.setPosition(pos); }

            void draw(sf::RenderTarget& target, sf::RenderStates state) const
            {
                target.draw(shape);
            }

            virtual ~draw_obj()
            {

            }
        };
    }
}
#endif