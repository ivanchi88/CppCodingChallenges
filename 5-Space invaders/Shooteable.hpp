#pragma once
#include <SFML/Graphics.hpp>

class Shooteable {
    public:
        virtual sf::Rect<float> getHitbox () = 0;
        virtual void kill() = 0;
        virtual bool getIsRunning() = 0;
};