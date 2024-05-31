#include "Enemy.h"

#include <iostream>
using namespace std;
Enemy::Enemy(View view)
{
    enemy.setRadius(radius);
    enemy.setFillColor(Color::Red);
    this->x = rand() % int(view.getSize().x - (-view.getSize().x)) + (-view.getSize().x);
    this->y = rand() % int(view.getSize().y - (-view.getSize().y)) + (-view.getSize().y);
    enemy.setPosition(x, y);
}

void Enemy::EnemyMove(Vector2f target)
{
    Vector2f direction = target - enemy.getPosition();

    float length = sqrt((direction.x * direction.x) + (direction.y * direction.y));
    Vector2f normalizedDirection = direction / length;

    Vector2f velocity = normalizedDirection * speed;

    this->x = enemy.getPosition().x;
    this->y = enemy.getPosition().y;
    enemy.move(velocity);
}


void Enemy::EnemyDraw(RenderWindow& window)
{
    window.draw(enemy);
}

bool Enemy::Hit(Projectile& projectile)
{
    float distance = sqrt(pow(projectile.x - x, 2) + pow(projectile.y - y, 2));
    if (distance < radius + projectile.projectile.getRadius())
    {
        return true;
    }
    return false;
}
