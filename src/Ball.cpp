#include <Ball.hpp>

namespace sv
{
    namespace ba
    {
        Ball::Ball()
        {
            shape.setRadius(7.f);
            shape.setOrigin({ 7.f, 7.f });
            shape.setPosition({ 400, 738 });
            shape.setFillColor({ 0, 178, 238 });
        }
    }
}
