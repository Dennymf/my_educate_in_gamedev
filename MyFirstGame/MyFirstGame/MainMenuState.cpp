#include "MainMenuState.h"

void MainMenuState::initKeybinds()
{
	std::fstream file_keys("Config/gamestate_keybinds.ini");

	if (file_keys.is_open())
	{
		std::string key = "";
		std::string key2 = "";

		while (file_keys >> key >> key2)
		{
			this->keybinds[key] = this->supportedKeys->at(key2);
		}
	}

	file_keys.close();
}

MainMenuState::MainMenuState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys)
	: State(window, supportedKeys)
{
	this->initKeybinds();

	this->background.setSize(sf::Vector2f(window->getSize().x, window->getSize().y));
	this->background.setFillColor(sf::Color::Magenta);
}

MainMenuState::~MainMenuState()
{

}


void MainMenuState::endState()
{
	std::cout << "End game state\n";
}

void MainMenuState::updateInput(const float& dt)
{
	this->chekForQuit();
}

void MainMenuState::update(const float& dt)
{
	this->updateInput(dt);
}

void MainMenuState::render(sf::RenderTarget* target)
{
	if (!target)
	{
		target = this->window;
	}

	target->draw(this->background);
}