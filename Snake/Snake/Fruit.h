#ifndef FRUIT_H
#define FRUIT_H

#include "Player.h"

class Fruit
{
private:
	struct fruit {
		int x;
		int y;
		int texture;
	} fruit;

	int SIZE;
	int horiz;
	int vert;
	sf::Texture& textureFruitsSheet;
	sf::Sprite sprite;

public:
	Fruit(int horiz, int vert, Player* player, int SIZE, sf::Texture& textureFruitsSheet);
	virtual ~Fruit();

	void newFruit(Player* player);
	bool update(Player* player);
	void render(sf::RenderTarget& target);
	std::pair<int, int> getCoor();
};

#endif