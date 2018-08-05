#include <SFML/Graphics.hpp>
#include <random>
#include <vector>
#include <SFML/OpenGL.hpp>

class Box {
    public:
        Box(float x, float y,float z,float rad);
        void divide();
        void draw();
    private:
        float posX, posY, posZ, radius;
};