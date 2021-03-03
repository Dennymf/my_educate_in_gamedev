#ifndef BUTTON_H
#define BUTTON_H

#include <iostream>
#include <ctime>
#include <fstream>
#include <sstream>

#include "SFML\Graphics.hpp"
#include "SFML\Window.hpp"
#include "SFML\System.hpp"
#include "SFML\Audio.hpp"

enum button_states{BTN_IDLE = 0, BTN_HOVER, BTN_ACTIVE};
class Button
{
private:
	short unsigned buttonState;

	bool pressed;
	bool hover;

	sf::RectangleShape shape;
	sf::Font* font;
	sf::Text text;

	sf::Color idleTextColor;
	sf::Color hoverTextColor;
	sf::Color activeTextColor;

	sf::Color idleColor;
	sf::Color hoverColor;
	sf::Color activeColor;

public:
	Button(float x, float y, float width, float height,
		sf::Font* font, std::string text, unsigned characher_size,
		sf::Color idle_text_color, sf::Color hover_text_color, sf::Color active_text_color,
		sf::Color idle_color, sf::Color hover_color, sf::Color active_color);
	~Button();

	const bool isPressed() const;

	//Fuction
	void update(const sf::Vector2f mousePos);
	void render(sf::RenderTarget& target);
};

#endif