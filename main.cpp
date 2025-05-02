#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include "Game.h"

int main()
{
    sf::RenderWindow app(sf::VideoMode(800, 600), "Car Racing");
    Game g;
    g.menu(app);
    return 0;
}
