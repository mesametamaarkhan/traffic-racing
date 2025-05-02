#ifndef NPC_H
#define NPC_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>

class NPC {
public:
	sf::Texture npcTex;
	sf::Sprite npcSprite;
	double xCor;
	double yCor;

	NPC(std::string pngPath, double x, double y) {
		xCor = x;
		yCor = y;
		npcTex.loadFromFile(pngPath);
		npcSprite.setTexture(npcTex);
		npcSprite.setPosition(xCor, yCor);
	}

	void move(double gameSpeed, double x, int& score) {
		if (this->yCor > 600)
		{
			this->yCor = 0;
			this->xCor = x;
			score++;
		}
		else {
			this->yCor += gameSpeed;
		}
		this->npcSprite.setPosition(xCor, yCor);
	}
};


#endif
