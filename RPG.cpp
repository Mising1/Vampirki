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
    Clock c;
    Clock c2;

    bool isMenu = true;
    float elapsed, elapsed2;
    
    while (window.isOpen())
    {
        audioSongs.Update();
        elapsed = c.getElapsedTime().asSeconds();
        elapsed2 = c2.getElapsedTime().asSeconds();


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
                    isMenu = true;
            }
        }
        window.clear();
        if (isMenu)
            mainMenu.draw(window);
        else
        {
            player.UpdateProjectiles(enemy1);
            

            for (auto& enemy : enemy1)
            {
                enemy.EnemyMove(player.tail.getPosition());
                enemy.EnemyDraw(window);
            }
            window.setView(view);
            player.PlayerMove();
            player.PlayerDraw(window, view);
            player.PlayerAttack(elapsed, c);

            if (elapsed2 >= 2)
            {
                enemy1.push_back(Enemy(view));
                c2.restart();
            }
            ui.Draw(window, view, elapsed);
        }
        window.display();
    }
}
