#pragma once
#include <SFML/Graphics.hpp>

#include "Enemy.h"
#include "Projectile.h"

using namespace sf;
using namespace std;

class Player
{
private:
    vector<Projectile> listProjectile;
    char direction = 'r';
    Sprite bow;
    vector<Enemy> enemies;
    Texture playerTextureR;
    Texture playerTextureL;
    Texture bowTexture;

public:
    Sprite playerSprite;
    float x = 50;
    int level = 1;
    float health = 100;
    float attackSpeed = 0.6f;
    float width = 40;
    float height = 20;
    float y = 50;
    float radius = 25;
    float speedPlayer = 0.05f;

    Player();
    void UpdateProjectiles(vector<Enemy>& enemies);
    void PlayerMove();
    void PlayerAttack(float elapsed, Clock& c);
    void PlayerDraw(RenderWindow& window, View& view);
};
