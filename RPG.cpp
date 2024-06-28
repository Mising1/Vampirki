#include <SFML/Graphics.hpp>

#include "AudioSongs.h"
#include "Enemy.h"
#include "Player.h"
#include "MainMenu.h"
#include "UI.h"
using namespace sf;
#include <iostream>

int main(int argc, char* argv[])
{
    vector<string> songPaths = {"./audio/NeonAbyss.mp3", "./audio/FutureFrenzy.mp3"};
    AudioSongs audioSongs(songPaths);

    const int width = 1600;
    const int height = 900;
    vector<Enemy> enemy1;
    RenderWindow window(VideoMode(width, height), "RPG");
    MainMenu mainMenu(width, height);
    View view(Vector2f(0.0f, 0.0f), Vector2f(width, height));
    Player player;
    UI ui(player);
    Clock player_clock;
    Clock spawnClock;
    Clock enemy_clock;

    bool isMenu = true;
    float player_attacks, spawn_rate, enemy_elapsed;

    while (window.isOpen())
    {
        audioSongs.Update();
        player_attacks = player_clock.getElapsedTime().asSeconds();
        spawn_rate = spawnClock.getElapsedTime().asSeconds();
        enemy_elapsed = enemy_clock.getElapsedTime().asSeconds();

        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
            if (event.type == Event::KeyPressed)
            {
                if (isMenu)
                {
                    mainMenu.Button(event.key.code);
                    if (event.key.code == Keyboard::Enter)
                        isMenu = false;
                }
                if (event.key.code == Keyboard::Escape)
                {
                    isMenu = true;
                    player.PlayerInit(enemy1);
                }
            }
        }
        if (player.health <= 0)
        {
            isMenu = true;
            player.PlayerInit(enemy1);
        }
        window.clear();
        if (isMenu)
        {
            window.setView(window.getDefaultView());
            mainMenu.draw(window);
        }
        else
        {
            window.setView(view);
            player.UpdateProjectiles(enemy1);

            for (auto& enemy : enemy1)
            {
                enemy.EnemyMove(player.playerSprite.getPosition());
                enemy.EnemyDraw(window);
                enemy.EnemyShoot(enemy_elapsed, enemy_clock);
            }
            player.PlayerMove();
            player.PlayerDraw(window, view);
            player.PlayerAttack(player_attacks, player_clock);

            if (spawn_rate >= 1)
            {
                enemy1.push_back(Enemy(view));
                spawnClock.restart();
            }
            ui.Draw(window, view, player_attacks);
        }
        window.display();
    }
}
