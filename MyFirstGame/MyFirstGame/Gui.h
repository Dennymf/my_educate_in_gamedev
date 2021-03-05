#ifndef GUI_H
#define GUI_H

#include <iostream>
#include <ctime>
#include <fstream>
#include <sstream>
#include <vector>

#include "SFML\Graphics.hpp"
#include "SFML\Window.hpp"
#include "SFML\System.hpp"
#include "SFML\Audio.hpp"

enum button_states{BTN_IDLE = 0, BTN_HOVER, BTN_ACTIVE};

namespace gui
{
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

		//Accessor
		const bool isPressed() const;
		const std::string getText() const;
		
		//Modif
		void setText(const std::string text);

		//Fuction
		void update(const sf::Vector2f& mousePos);
		void render(sf::RenderTarget& target);
	};

	class DropDownList
	{
	private:
		float keytime;
		float keytimeMax;
		sf::Font& font;
		gui::Button* activeElement;
		std::vector<gui::Button*> list;
		bool showList;

	public:
		DropDownList(float x, float y, float width, float height,
			sf::Font& font, std::string list[], unsigned numberOfElements, const unsigned default_index = 0);
		virtual ~DropDownList();

		const bool getKeytime();
		void updateKeytime(const float& dt);
		void update(const sf::Vector2f& mousePos, const float& dt);
		void render(sf::RenderTarget& target);
	};
}
#endif