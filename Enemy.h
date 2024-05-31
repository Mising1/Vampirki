#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;
#include "Projectile.h"

class Enemy
{
public:
    float x;
    float y;
    float radius = 20;
    float speed = 0.03f;
    CircleShape enemy;

    Enemy(View view);
    void EnemyMove(Vector2f target); 
    bool Hit(Projectile& projectile);
    void EnemyDraw(RenderWindow& window);
    
};
