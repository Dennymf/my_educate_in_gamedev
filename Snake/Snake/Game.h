#ifndef GAME_H
#define GAME_H

#include "GameState.h"

class Game
{
private:
	sf::RenderWindow* window;
	sf::Event sf_event;
	std::vector<sf::VideoMode> viedoModes;
	sf::ContextSettings windowSettings;
	bool fullscreen;

	sf::Clock dt_clock;
	float dt;

	std::stack<State*> states;

	std::map<std::string, int> supportedKeys;

	sf::Clock clock;
	float chrono = 0;
	float delay = 0.2;

	void initWindow();
	void initKeys();
	void initStates();

public:
	Game();
	virtual ~Game();

	void endApplication();

	void updateDT(); // Независимое движение от fps
	void updateEvents();
	void update();
	void render();

	void run();
};

#endif