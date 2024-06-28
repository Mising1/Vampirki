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
    
    float y = 50;
    float speedPlayer = 0.05f;

    Player();
    void PlayerInit(vector<Enemy>& enemies);
    void UpdateProjectiles(vector<Enemy>& enemies);
    void PlayerMove();
    bool Hit(Projectile& projectile);
    void PlayerAttack(float elapsed, Clock& c);
    void PlayerDraw(RenderWindow& window, View& view);
};
