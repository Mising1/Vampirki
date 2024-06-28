#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;
#include "Projectile.h"

class Enemy
{
private:
    Sprite enemy;
    Texture enemyTexture;
    RectangleShape enemyHitbox;

public:
    vector<Projectile> enemylistProjectile;
    float x;
    float y;
    float attackSpeed = 1.5f;
    float radius = 58;
    float speed = 0.03f;

    Enemy(View view);
    void EnemyMove(Vector2f target); 
    bool Hit(Projectile& projectile);
    void EnemyDraw(RenderWindow& window);
    void EnemyShoot(float elapsed, Clock& c);
    
};
