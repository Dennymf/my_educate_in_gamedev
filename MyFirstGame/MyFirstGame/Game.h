#ifndef GAME_H
#define GAME_H

#include "MainMenuState.h"

class Game
{
private:

	//Variable

	sf::RenderWindow *window;
	sf::Event sf_event;

	sf::Clock dt_clock;
	float dt;

	std::stack<State*> states;

	std::map<std::string, int> supportedKeys;

	//Init 

	void initWindow();
	void initKeys();
	void initStates();

public:
	//Construction/destruction
	Game();
	virtual ~Game();

	//Function

	//Regular
	void endApplication();

	//Update
	void updateDT(); // Независимое движение от fps
	void updateEvents();
	void update();
	
	//Render
	void render();
	
	//Core
	void run();
};

#endif