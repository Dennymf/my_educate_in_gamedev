#ifndef GAMEOVERMENU_H
#define GAMEOVERMENU_H

#include "Gui.h"

class GameOverMenu
{
private:
	sf::Font& font;
	sf::Text menuText;

	sf::RectangleShape background;
	sf::RectangleShape container;

	std::map<std::string, gui::Button*> buttons;

public:
	GameOverMenu(sf::RenderWindow& window, sf::Font& font);
	virtual ~GameOverMenu();

	//Accessor
	std::map<std::string, gui::Button*>& getAllButtons();

	//Func
	const bool& isButtonPressed(const std::string key);
	void addButton(const std::string key, float y, const std::string text);
	void update(const sf::Vector2f& mousePos);
	void render(sf::RenderTarget& target);
};

#endif