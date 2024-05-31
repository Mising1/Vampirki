#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

class MainMenu
{
private:
    Text menu[4];
    Font font;
    void MoveUp();
    void MoveDown();

public:
    MainMenu(int wX, int wY);
    void draw(RenderWindow& window);
    void Button(Keyboard::Key key);
};
