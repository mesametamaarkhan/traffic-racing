#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>

class Player {
public:
	sf::Texture playerTex;
	sf::Sprite playerSprite;
	const int racerHeight;
	const int racerWidth;
	int xCor;
	int yCor;

	Player(std:: string pngPath, int x, int y) : racerHeight(70), racerWidth(40) {
		xCor = x / 2;
		yCor = y - racerHeight;
		if (!playerTex.loadFromFile(pngPath)) {
			std::cout << "Error loading player png!!" << std::endl;
			exit;
		}
		playerSprite.setTexture(playerTex);
		playerSprite.setPosition(xCor, yCor);
	}

	void move(char direction, int leftBorder, int rightBorder, int screenHeight) {
		
		if (direction == 'u') {
			if (yCor > 0) {
				yCor -= 10;
			}
		}
		
		if (direction == 'd') {
			if (yCor < screenHeight - racerHeight) {
				yCor += 10;
			}
		}
		
		if (direction == 'l') {
			if (xCor > leftBorder) {
				xCor -= 10;
			}
		}
		
		if (direction == 'r') {
			if (xCor < rightBorder) {
				xCor += 10;
			}
		}

		playerSprite.setPosition(xCor, yCor);
	}
};


#endif