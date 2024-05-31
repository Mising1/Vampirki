#include "Player.h"

#include <iostream>
#include "Projectile.h"

class Enemy;

Player::Player()
{
    tail.setRadius(radius);
    tail.setFillColor(Color::Green);
    tail.setPosition(x, y);
    gun.setSize(Vector2f(width, height));
    gun.setFillColor(Color::White);
    gun.setPosition(x + radius, y + radius);
}

void Player::PlayerMove()
{
    Vector2f movementPlayer;

    if (Keyboard::isKeyPressed(Keyboard::W))
    {
        movementPlayer.y -= speedPlayer;
        direction = 'w';
    }
    if (Keyboard::isKeyPressed(Keyboard::S))
    {
        movementPlayer.y += speedPlayer;
        direction = 's';
    }
    if (Keyboard::isKeyPressed(Keyboard::A))
    {
        movementPlayer.x -= speedPlayer;
        direction = 'a';
    }
    if (Keyboard::isKeyPressed(Keyboard::D))
    {
        movementPlayer.x += speedPlayer;
        direction = 'd';
    }

    if (Keyboard::isKeyPressed(Keyboard::Up))
    {
        gun.setRotation(-90);
        direction = 'w';
    }
    if (Keyboard::isKeyPressed(Keyboard::Down))
    {
        gun.setRotation(90);
        direction = 's';
    }
    if (Keyboard::isKeyPressed(Keyboard::Left))
    {
        gun.setRotation(180);
        direction = 'a';
    }
    if (Keyboard::isKeyPressed(Keyboard::Right))
    {
        gun.setRotation(0);
        direction = 'd';
    }
    tail.move(movementPlayer);
    gun.move(movementPlayer);
}

void Player::PlayerAttack(float elapsed, Clock& c)
{
    if ((Keyboard::isKeyPressed(Keyboard::Up) || Keyboard::isKeyPressed(Keyboard::Down) ||
        Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::Left)) && elapsed > attackSpeed)
    {
        float projectileX = gun.getPosition().x;
        float projectileY = gun.getPosition().y;
        switch (direction)
        {
        case 'w':
            projectileX += 7;
            break;
        case 's':
            projectileX -= 12;
            break;
        case 'a':
            projectileY -= 12;
            break;
        case 'd':
            projectileY += 7;
            break;
        default: break;
        }
        Projectile projectile(projectileX, projectileY, direction);
        listProjectile.push_back(projectile);
        c.restart();
    }
}

void Player::PlayerDraw(RenderWindow& window, View& view)
{
    for (int i = 0; i < listProjectile.size(); i++)
    {
        if (listProjectile[i].CheckDistance())
        {
            listProjectile.erase(listProjectile.begin() + i);
            i--;
            continue;
        }
        listProjectile[i].Update();
        listProjectile[i].Draw(window);
    }

    window.draw(gun);
    view.setCenter(tail.getPosition().x + 25, tail.getPosition().y + 25);
    window.draw(tail);
}

void Player::UpdateProjectiles(vector<Enemy>& enemies)
{
    for (int i = 0; i < listProjectile.size(); i++)
    {
        if (listProjectile[i].CheckDistance())
        {
            listProjectile.erase(listProjectile.begin() + i);
            i--;
            continue;
        }

        for (int j = 0; j < enemies.size(); j++)
        {
            if (enemies[j].Hit(listProjectile[i]))
            {
                level++;
                listProjectile.erase(listProjectile.begin() + i);
                enemies.erase(enemies.begin() + j);
                i--;
                break;
            }
        }

        if (i < listProjectile.size())
        {
            listProjectile[i].Update();
        }
    }
}
