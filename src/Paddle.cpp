#include <Paddle.hpp>

namespace sv
{
    namespace ba
    {
        Paddle::Paddle()
        {            
            shape.setSize({ 90, 10 });
            shape.setOrigin({ 45.f, 5.f });
            shape.setPosition({ 400, 750 });
            shape.setFillColor({ 128, 128, 128 });
        }
    }
}
