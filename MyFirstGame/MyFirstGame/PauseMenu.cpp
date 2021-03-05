#include "PauseMenu.h"

PauseMenu::PauseMenu(sf::RenderWindow& window, sf::Font& font)
	: font(font)
{
	this->background.setSize(sf::Vector2f(static_cast<float>(window.getSize().x),
		static_cast<float>(window.getSize().y)));
	this->background.setFillColor(sf::Color(20, 20, 20, 100));

	this->container.setSize(sf::Vector2f(static_cast<float>(window.getSize().x) / 3.f,
		static_cast<float>(window.getSize().y) / 3.f));
	this->container.setFillColor(sf::Color(20, 20, 20, 200));
	this->container.setPosition(static_cast<float>(window.getSize().x) / 3.f,
		static_cast<float>(window.getSize().y) / 4.f);

	this->menuText.setFont(font);
	this->menuText.setFillColor(sf::Color(255, 255, 255, 200));
	this->menuText.setCharacterSize(50);
	this->menuText.setString("PAUSED");
	this->menuText.setPosition(
		this->container.getPosition().x + this->container.getSize().x / 2.f - this->menuText.getGlobalBounds().width / 2.f,
		this->container.getPosition().y + 10.f
	);
}

PauseMenu::~PauseMenu()
{
	for (auto it = this->buttons.begin(); it != this->buttons.end(); it++)
	{
		delete it->second;
	}
}

std::map<std::string, gui::Button*>& PauseMenu::getAllButtons()
{
	return this->buttons;
}

const bool& PauseMenu::isButtonPressed(const std::string key)
{
	return this->buttons[key]->isPressed();
}

void PauseMenu::addButton(const std::string key, float y, const std::string text)
{
	float width = 200.f;
	float height = 70.f;
	float x = this->container.getPosition().x + this->container.getSize().x / 2.f - width / 2.f;
	this->buttons[key] = new gui::Button(x, y, width, height,
		&this->font, text, 50,
		sf::Color(250, 250, 250, 200), sf::Color(130, 130, 130, 255), sf::Color(80, 80, 80, 200),
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));
}

void PauseMenu::update(const sf::Vector2f& mousePos)
{
	for (auto &it : buttons)
	{
		it.second->update(mousePos);
	}
}

void PauseMenu::render(sf::RenderTarget& target)
{
	target.draw(this->background);
	target.draw(this->container);

	for (auto &it : this->buttons)
	{
		it.second->render(target);
	}

	target.draw(this->menuText);
}
