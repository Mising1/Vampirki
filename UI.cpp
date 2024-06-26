﻿#include "UI.h"

#include <iostream>

UI::UI(Player& player)
    : player(player)
{
    HPBar();
    GunReload();
    Level();
}

void UI::HPBar()
{
    hpBar.setFillColor(Color::Red);
    hpBarBackground.setSize(Vector2f(100, 20));
    hpBarBackground.setOutlineThickness(2);
    hpBarBackground.setFillColor(Color::Transparent);
    hpBarBackground.setOutlineColor(Color::White);
}

void UI::GunReload()
{
    gunReloadBar.setFillColor(Color::Green);
    gunReloadBackground.setSize(Vector2f(100, 20));
    gunReloadBackground.setOutlineThickness(2);
    gunReloadBackground.setFillColor(Color::Transparent);
}

void UI::Level()
{
    font.loadFromFile("./font/lakes.ttf");
    text.setFont(font);
    text.setString("Level: " + to_string(player.level));
    text.setCharacterSize(24);
    text.setFillColor(Color::White);
}

void UI::Draw(RenderWindow& window, View view, float elapsed)
{
    float reloadPercentage = elapsed / player.attackSpeed * 100;
    if (reloadPercentage > 100)
    {
        gunReloadBar.setSize(Vector2f(100, 20));
    }
    else
    {
        gunReloadBar.setSize(Vector2f(reloadPercentage, 20));
    }

    hpBar.setPosition(view.getCenter().x - 780, view.getCenter().y - 425);
    gunReloadBar.setPosition(view.getCenter().x - 780, view.getCenter().y - 395);
    hpBar.setSize(Vector2f(player.health, 20));
    hpBarBackground.setPosition(view.getCenter().x - 780, view.getCenter().y - 425);
    gunReloadBackground.setPosition(view.getCenter().x - 780, view.getCenter().y - 395);
    text.setString("Level: " + to_string(player.level));
    text.setPosition(view.getCenter().x + 650, view.getCenter().y - 425);


    window.draw(hpBarBackground);
    window.draw(hpBar);
    window.draw(text);
    window.draw(gunReloadBackground);
    window.draw(gunReloadBar);
}
