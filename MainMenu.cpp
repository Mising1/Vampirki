#include "MainMenu.h"
#include <iostream>
using namespace sf;

MainMenu::MainMenu(int wX, int wY)
{
    if (!font.loadFromFile("./murderFont2.otf"))
    {
        std::cout << "Nie udalo sie wczytac czcionki" << std::endl;
    }
    menu[0].setString("Graj");
    menu[0].setStyle(Text::Underlined);
    menu[1].setString("Opcje");
    menu[2].setString("Wyjscie");
    for (int i = 0; i < 3; i++)
    {
        menu[i].setFont(font);
        menu[i].setCharacterSize(60);
        menu[i].setFillColor(Color::White);
        menu[i].setPosition((wX / 2) - 60, 100+i * wY / 3);
    }
}

void MainMenu::draw(RenderWindow& window)
{
    for (int i = 0; i < 3; i++)
    {
        window.draw(menu[i]);
    }
}

void MainMenu::MoveDown()
{
    for (int i = 0; i < 3; i++)
    {
        if (menu[i].getStyle() == Text::Underlined)
        {
            menu[i].setStyle(Text::Regular);
            if ((i + 1) == 3)
            {
                menu[0].setStyle(Text::Underlined);
                break;
            }
            menu[i + 1].setStyle(Text::Underlined);
            break;
        }
    }
}

void MainMenu::MoveUp()
{
    for (int i = 0; i < 3; i++)
    {
        if (menu[i].getStyle() == Text::Underlined)
        {
            menu[i].setStyle(Text::Regular);
            if ((i - 1) == -1)
            {
                menu[2].setStyle(Text::Underlined);
                break;
            }
            menu[i - 1].setStyle(Text::Underlined);
            break;
        }
    }
}

void MainMenu::Button(Keyboard::Key key)
{
    if (key == Keyboard::Up)
    {
        MoveUp();
    }
    if (key == Keyboard::Down)
    {
        MoveDown();
    }
}