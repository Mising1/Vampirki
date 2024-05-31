#include "Projectile.h"

Projectile::Projectile()
{
}

Projectile::Projectile(float posX, float posY, char direction)
{
    x = posX;
    y = posY;
    startedPosX = x;
    startedPosY = y;
    projectile.setRadius(5);
    projectile.setPosition(x, y);
    projectile.setFillColor(Color::Red);
    this->direction = direction;
}

void Projectile::Draw(RenderWindow& window)
{
    window.draw(projectile);
}

void Projectile::Update()
{
    Vector2f movement;
    switch (direction)
    {
    case 'w':
        movement.x = 0;
        movement.y -= speed;
        break;
    case 's':
        movement.x = 0;
        movement.y += speed;
        break;
    case 'a':
        movement.y = 0;
        movement.x -= speed;
        break;
    case 'd':
        movement.y = 0;
        movement.x += speed;
        break;
    default: break;
    }
    this->x = projectile.getPosition().x;
    this->y = projectile.getPosition().y;
    projectile.move(movement);
}

bool Projectile::CheckDistance()
{
    float distanceX = abs(startedPosX - x);
    float distanceY = abs(startedPosY - y);
    if (distanceX > distance || distanceY > distance)
        return true;
    return false;
}