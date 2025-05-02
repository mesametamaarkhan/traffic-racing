#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include "Player.h"
#include "npc.h"

class Game {
public:
	const double SCREEN_WIDTH;
	const double SCREEN_HEIGHT;
	const int borderLeft;
	const int borderRight;
    static bool firstRandGen;
    Player* p;
    NPC* npc1;
    NPC* npc2;
    NPC* npc3;
    NPC* npc4;
    sf::Texture backgroundTex;
    sf::Texture gameover;
    sf::Texture menuTex;
    sf::Texture htpTex;
    sf::Sprite background;
    sf::Sprite background1;
    sf::Sprite menuBG;
    sf::Sprite htpBG;
    sf::Sprite Gameover;
	std::string stringscore;
    sf::SoundBuffer gameSoundBuffer;
    sf::SoundBuffer gameOver;
    sf::Sound GameSound;
    sf::Sound GameOver;
    sf::Font myfont;
    sf::Text text;
	int score;
	double gameSpeed;
	
	Game() : SCREEN_WIDTH(800), SCREEN_HEIGHT(600), borderLeft(140), borderRight(660) {
		stringscore = "";
		score = 0;
		gameSpeed = 0.3;
        p = new Player("img/player.png", SCREEN_WIDTH, SCREEN_HEIGHT);
        npc1 = new NPC("img/npc1.png", getRandomNumber(borderLeft, borderRight), 0);
        npc2 = new NPC("img/npc2.png", getRandomNumber(borderLeft, borderRight), -100);
        npc3 = new NPC("img/npc3.png", getRandomNumber(borderLeft, borderRight), -200);
        npc4 = new NPC("img/npc4.png", getRandomNumber(borderLeft, borderRight), -300);
        backgroundTex.loadFromFile("img/background.png");
        background.setTexture(backgroundTex);
        background1.setTexture(backgroundTex);
        menuTex.loadFromFile("img/menu.png");
        menuBG.setTexture(menuTex);
        htpTex.loadFromFile("img/htp.png");
        htpBG.setTexture(htpTex);
        gameover.loadFromFile("img/over.png");
        Gameover.setTexture(gameover);
        gameSoundBuffer.loadFromFile("sound/game.wav");
        GameSound.setBuffer(gameSoundBuffer);
        gameOver.loadFromFile("sound/crash.wav");
        GameOver.setBuffer(gameOver);
        myfont.loadFromFile("font/xirod.ttf");
        text.setCharacterSize(15);
        text.setFont(myfont);
        text.setString("SCORE:0");
        text.setPosition(5, 0);
	}

    void menu(sf::RenderWindow& window) {
        GameSound.play();
        GameSound.setLoop(1);
        while (window.isOpen())
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();
                if (event.type == sf::Event::KeyPressed)
                {
                    if (event.key.code == sf::Keyboard::P)
                    {
                        GameSound.stop();
                        this->run(window);
                    }
                    if (event.key.code == sf::Keyboard::H)
                    {
                        GameSound.stop();
                        this->howToPlay(window);
                    }
                    if (event.key.code == sf::Keyboard::Q)
                    {
                        window.close();
                    }
                }

            }
            window.clear();
            window.draw(menuBG);
            window.display();
        }
    }

    void howToPlay(sf::RenderWindow& window) {
        GameSound.play();
        GameSound.setLoop(1);
        while (window.isOpen())
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();
                if (event.type == sf::Event::KeyPressed)
                {
                    if (event.key.code == sf::Keyboard::P)
                    {
                        GameSound.stop();
                        this->run(window);
                    }
                    if (event.key.code == sf::Keyboard::Q)
                    {
                        window.close();
                    }
                }

            }
            window.clear();
            window.draw(htpBG);
            window.display();
        }
    }

	void run(sf::RenderWindow& window) {
        sf::Texture gameover;

        double BackgroundY1 = 0;
        double BackgroundY2 = -600;

        GameSound.play();
        GameSound.setLoop(true);

        //GAME LOOP
        while (window.isOpen())
        {
            //initialize and count score
            stringscore = "SCORE:" + std::to_string(score);
            text.setString(stringscore);

            //background scrolling 
            background.setPosition(0, BackgroundY1);
            background1.setPosition(0, BackgroundY2);
            if (BackgroundY2 > 0)
            {
                BackgroundY1 = 0;
                BackgroundY2 = BackgroundY1 - 500;
            }
            BackgroundY1 += 0.1;
            BackgroundY2 += 0.1;

            //NPC movement handling here
            npc1->move(gameSpeed, getRandomNumber(borderLeft, borderRight), score);
            npc2->move(gameSpeed, getRandomNumber(borderLeft, borderRight), score);
            npc3->move(gameSpeed, getRandomNumber(borderLeft, borderRight), score);
            npc4->move(gameSpeed, getRandomNumber(borderLeft, borderRight), score);

            //handling player movement through keyboard input
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();
                if (event.type == sf::Event::KeyPressed)
                {
                    if (event.key.code == sf::Keyboard::Left)
                    {
                        p->move('l', borderLeft, borderRight, SCREEN_HEIGHT);
                    }
                    if (event.key.code == sf::Keyboard::Right)
                    {
                        p->move('r', borderLeft, borderRight, SCREEN_HEIGHT);
                    }
                    if (event.key.code == sf::Keyboard::Up)
                    {
                        p->move('u', borderLeft, borderRight, SCREEN_HEIGHT);
                    }
                    if (event.key.code == sf::Keyboard::Down)
                    {
                        p->move('d', borderLeft, borderRight, SCREEN_HEIGHT);
                    }
                }
            }

            //this function defined below checks for accidents (gameover condition)
            checkCollision(window);

            //game level
            if (score > 10 && score < 20) {
                gameSpeed = 0.4;
            }

            if (score > 20 && score < 30) {
                gameSpeed = 0.5;
            }

            if (score > 30) {
                gameSpeed = 0.6;
            }

            //this function draws everything on screen
            drawEverything(window);
        }   
	}
    
    void drawEverything(sf::RenderWindow& window) {
        window.clear();
        window.draw(background);
        window.draw(background1);
        window.draw(p->playerSprite);
        window.draw(npc1->npcSprite);
        window.draw(npc2->npcSprite);
        window.draw(npc3->npcSprite);
        window.draw(npc4->npcSprite);
        window.draw(text);
        window.display();
    }

    void checkCollision(sf::RenderWindow& window) {
        if (p->playerSprite.getGlobalBounds().intersects(npc1->npcSprite.getGlobalBounds())) {
            GameSound.stop();
            gameOverFunction(window);
        }

        if (p->playerSprite.getGlobalBounds().intersects(npc2->npcSprite.getGlobalBounds())) {
            GameSound.stop();
            gameOverFunction(window);
        }

        if (p->playerSprite.getGlobalBounds().intersects(npc3->npcSprite.getGlobalBounds())) {
            GameSound.stop();
            gameOverFunction(window);
        }

        if (p->playerSprite.getGlobalBounds().intersects(npc4->npcSprite.getGlobalBounds())) {
            GameSound.stop();
            gameOverFunction(window);
        }
    }

    void gameOverFunction(sf::RenderWindow& window) {
        GameOver.play();
        while (window.isOpen())
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();
            }
            stringscore = "YOUR SCORE:" + std::to_string(score);
            sf::Text text(stringscore, myfont, 30);
            text.setPosition(210, 450);
            window.clear();
            window.draw(Gameover);
            window.draw(text);
            window.display();
        }
    }

	int getRandomNumber(int x, int y) {
		if (firstRandGen) {
			srand(time(NULL));
			firstRandGen = false;
		}

        int result = x + rand() % ((y + 1) - x);
        result = (result / 10) * 10;
        return result;
	} 
};

bool Game::firstRandGen = true;



#endif