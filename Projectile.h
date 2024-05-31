#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

class Projectile
{
private:
    char direction;
    float startedPosX;
    float startedPosY;
    float distance = 400;
    float speed = 0.2f;

public:
    CircleShape projectile;
    float x;
    float y;
    Projectile();
    Projectile(float posX, float posY, char direction);
    void Draw(RenderWindow& window);
    void Update();
    bool CheckDistance();
};
