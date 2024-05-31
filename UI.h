#pragma once

#include <SFML/Graphics.hpp>

#include "Player.h"
using namespace sf;
class UI:public Player
{
private:
    RectangleShape hpBar;
    RectangleShape hpBarBackground;
    RectangleShape gunReloadBar;
    Font font;
    Text text;
    RectangleShape gunReloadBackground;
    Player& player;
public:
    UI(Player& player);
    void HPBar();
    void Level();
    void GunReload();
    void Draw(RenderWindow& window, View view, float elapsed);
};
