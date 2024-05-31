#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;
#include "Projectile.h"

class Enemy
{
private:
    Sprite enemy;
    Texture enemyTexture;
    RectangleShape enemyHitbox;
public:
    float x;
    float y;
    float radius = 58;
    float speed = 0.03f;

    Enemy(View view);
    void EnemyMove(Vector2f target); 
    bool Hit(Projectile& projectile);
    void EnemyDraw(RenderWindow& window);
    
};
