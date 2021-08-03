#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "State.h"
#include "GameOverMenu.h"

class GameState :
	public State
{
private:
	sf::Font font;
	Player* player;
	Fruit* fruit;
	GameOverMenu* overmenu;

	sf::Texture textureFruitsSheet;
	sf::Texture textureSheet;
	sf::Texture textureBackground;
	sf::RectangleShape background;
	bool lose;

	int SIZE = 60;
	sf::Vector2u line = window->getSize();
	int horizont = line.x / SIZE;
	int vertical = line.y / SIZE;
	bool flag;

	void initFonts();
	void initKeybinds();
	void initPlayer();
	void initTexture();
	void initFruit();
	void initBackground();
	void initGameOverMenu();

public:
	GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
	virtual ~GameState();

	void updateInput();
	void updatePlayerInput();
	void updateGameOverButton();
	void update(float& chrono, float& delay);
	void render(sf::RenderTarget& target);
	bool getFlag();
};

#endif