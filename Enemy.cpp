#include "Enemy.h"
#include <iostream>
using namespace std;

Enemy::Enemy(View view)
{
    enemyTexture.loadFromFile("./graphics/orc.png");
    this->x = rand() % int(view.getSize().x - (-view.getSize().x)) + (-view.getSize().x);
    this->y = rand() % int(view.getSize().y - (-view.getSize().y)) + (-view.getSize().y);
    enemy.scale(0.5f, 0.5f);
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
    for (int i = 0; i < enemylistProjectile.size(); i++)
    {
        enemylistProjectile[i].Update();
        enemylistProjectile[i].Draw(window);
    }
    enemy.setTexture(enemyTexture);
    window.draw(enemy);
}

bool Enemy::Hit(Projectile& projectile)
{
    if (projectile.x >= x + 5 && projectile.x <= x + enemy.getGlobalBounds().width - 10 &&
        projectile.y >= y && projectile.y <= y + enemy.getGlobalBounds().height)
    {
        return true;
    }
    return false;
}

void Enemy::EnemyShoot()
{
    elapsedAttack = clock.getElapsedTime().asSeconds();
    if (elapsedAttack > attackSpeed)
    {
        char dir[4] = {'w', 's', 'a', 'd'};
        char direction = dir[rand() % 4];
        float projectileX = x + 25;
        float projectileY = y + 25;
        
        Projectile projectile(projectileX, projectileY, direction);
        enemylistProjectile.push_back(projectile);
        clock.restart();
    }
}