#include <SFML/Graphics.hpp>
#include <random>
#include <vector>
#include <SFML/OpenGL.hpp>
#include <string>

class Box {
    public:
        Box(float x, float y,float z,float siz);
        std::vector<Box> divide();
        void draw();
        std::string toString();
    private:
        float posX, posY, posZ, size;
};