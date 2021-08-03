#ifndef STATE_H
#define STATE_H

#include "Fruit.h"

class State
{
private:

protected:
	std::stack<State*>* states;
	sf::RenderWindow* window;
	std::map<std::string, int>* supportedKeys;
	std::map<std::string, int> keybinds;
	bool quit;
	bool paused;
	float keytime;
	float keytimeMax;
	bool newdelay;

	sf::Vector2i mousePosScreen;
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;
	//Resources
	std::map<std::string, sf::Texture> texture;

	//Functions
	virtual void initKeybinds() = 0;

public:
	State(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
	virtual ~State();

	const bool& getQuit() const;
	const bool& getKeytime();
	void endState();
	void pauseState();
	void unpauseState();

	virtual bool newDelay();
	virtual void updateMousePosition();
	virtual void updateKeytime();
	virtual void updateInput() = 0;
	virtual bool getFlag() = 0;
	virtual void update(float& chrono, float& delay) = 0;
	virtual void render(sf::RenderTarget& target) = 0;
};

#endif
