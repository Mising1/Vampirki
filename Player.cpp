#include "Player.h"

#include <iostream>
#include "Projectile.h"

class Enemy;

Player::Player()
{
    playerTextureR.loadFromFile("./graphics/ziomekR.png");
    playerTextureL.loadFromFile("./graphics/ziomekL.png");
    bowTexture.loadFromFile("./graphics/lukRem.png");
    playerSprite.scale(0.5f, 0.5f);
    playerSprite.setTexture(playerTextureR);
    bow.setScale(0.5f, 0.5f);
    playerSprite.setPosition(x, y);
    bow.setPosition(playerSprite.getPosition().x + 45, playerSprite.getPosition().y + 25);
}

void Player::PlayerInit(vector<Enemy> &enemies)
{
    
    level = 1;
    health = 100;
    attackSpeed = 0.6f;
    speedPlayer = 0.05f;
    
    listProjectile.clear();
    
    for(int i = 0; i < enemies.size(); i++)
    {
        enemies[i].enemylistProjectile.clear();
    }
    enemies.clear();
}

void Player::PlayerMove()
{
    Vector2f movementPlayer;

    if (Keyboard::isKeyPressed(Keyboard::W))
    {
        movementPlayer.y -= speedPlayer;
        
    }
    if (Keyboard::isKeyPressed(Keyboard::S))
    {
        movementPlayer.y += speedPlayer;
    }
    // if(Keyboard::isKeyPressed(Keyboard::Space))
    // {
    //     cout<<direction<<endl;
    // }
    if (Keyboard::isKeyPressed(Keyboard::A))
    {
        bow.setRotation(180);
        movementPlayer.x -= speedPlayer;
        direction = 'a';
    }
    if (Keyboard::isKeyPressed(Keyboard::D))
    {
        movementPlayer.x += speedPlayer;
        bow.setRotation(0);
        direction = 'd';
    }
    if (Keyboard::isKeyPressed(Keyboard::Up))
    {
        bow.setRotation(-90);
        if(direction != 'w')
            direction = 'w';
    }
    if (Keyboard::isKeyPressed(Keyboard::Down))
    {
        bow.setRotation(90);
        if(direction != 's')
            direction = 's';
    }
    if (Keyboard::isKeyPressed(Keyboard::Left))
    {
        bow.setRotation(180);
        if(direction != 'a')
            direction = 'a';
    }
    if (Keyboard::isKeyPressed(Keyboard::Right))
    {
        bow.setRotation(0);
        if(direction != 'd')
            direction = 'd';
    }
    playerSprite.move(movementPlayer);
    bow.move(movementPlayer);
}

void Player::PlayerAttack(float elapsed, Clock& c)
{
    if ((Keyboard::isKeyPressed(Keyboard::Up) || Keyboard::isKeyPressed(Keyboard::Down) ||
        Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::Left)) && elapsed > attackSpeed)
    {
        float projectileX = bow.getPosition().x;
        float projectileY = bow.getPosition().y;
        switch (direction)
        {
        case 'w':
            projectileX += 18;
            break;
        case 's':
            projectileX -= 25;
            break;
        case 'a':
            projectileY -= 25;
            break;
        case 'd':
            projectileY += 18;
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
    if (direction == 'w') //up arrow
    {
        if (playerSprite.getTexture() == &playerTextureR)
        {
            bow.setPosition(playerSprite.getPosition().x + 28, playerSprite.getPosition().y + 50);
        }
        else
        {
            bow.setPosition(playerSprite.getPosition().x-12, playerSprite.getPosition().y + 50);
            
        }
        
    }
    if (direction == 's') //down arrow
    {
        if (playerSprite.getTexture() == &playerTextureR)
        {
        bow.setPosition(playerSprite.getPosition().x + 70, playerSprite.getPosition().y + 40);
        }
        else
        {
            bow.setPosition(playerSprite.getPosition().x+28, playerSprite.getPosition().y + 40);

        }
        
    }
    if (direction == 'a') //left arrow
    {
        playerSprite.setTexture(playerTextureL);
        bow.setPosition(playerSprite.getPosition().x + 12, playerSprite.getPosition().y + 65);
    }
    if (direction == 'd') //right arrow
    {
        bow.setPosition(playerSprite.getPosition().x + 45, playerSprite.getPosition().y + 25);
        playerSprite.setTexture(playerTextureR);
    }
    
    bow.setTexture(bowTexture);
    window.draw(playerSprite);
    window.draw(bow);
    view.setCenter(playerSprite.getPosition().x + 25, playerSprite.getPosition().y + 25);
}

bool Player::Hit(Projectile& projectile)
{
    if (projectile.x >= playerSprite.getPosition().x + 5 && projectile.x <= playerSprite.getPosition().x + playerSprite.getGlobalBounds().width &&
        projectile.y >= playerSprite.getPosition().y && projectile.y <= playerSprite.getPosition().y + playerSprite.getGlobalBounds().height)
    {
        return true;
    }
    return false;
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
    for(int i = 0; i < enemies.size(); i++)
    {
        for(int j = 0; j < enemies[i].enemylistProjectile.size(); j++)
        {
            if(enemies[i].enemylistProjectile[j].CheckDistance())
            {
                enemies[i].enemylistProjectile.erase(enemies[i].enemylistProjectile.begin() + j);
                j--;
                continue;
            }
            if(Hit(enemies[i].enemylistProjectile[j]))
            {
                health-=10;
                enemies[i].enemylistProjectile.erase(enemies[i].enemylistProjectile.begin() + j);
                j--;
            }
            if(j < enemies[i].enemylistProjectile.size())
            {
                enemies[i].enemylistProjectile[j].Update();
            }
        }
    }
}