#include "Enemy.h"

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
