#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <ctime>
#include <fstream>
#include <stack>
#include <random>
#include <vector>

#include "SFML\Graphics.hpp"
#include "SFML\Window.hpp"
#include "SFML\System.hpp"
#include "SFML\Audio.hpp"

class Player
{
	struct Snake {
		int x;
		int y;
	};
private:
	int SIZE;
	int direction;
	int horizont;
	int vertical;
	std::vector<Snake> snake;
	sf::Texture& textureSheet;
	sf::Sprite sprite;
	bool lose;

	void initVariables();
public:
	Player(float horizont, float vertical, int SIZE, sf::Texture& textureSheet);
	virtual ~Player();

	void update();
	void updateSnake();
	void changeDirection(int dir);
	void move();
	void render(sf::RenderTarget& target);
	void newLenght();
	bool inSnake(int x, int y);
	bool inHead(int x, int y);
	void checkLose();
	bool getLose();
};

#endif