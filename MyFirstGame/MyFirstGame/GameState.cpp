#include "GameState.h"

void GameState::initKeybinds()
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

void GameState::initTextures()
{
	sf::Texture temp;
	temp.loadFromFile("Resources/Images/Sprites/Player/player.png");
	this->texture["PLAYER_IDLE"] = temp;
}

void GameState::initPlayers()
{
	this->player = new Player(0, 0, &this->texture["PLAYER_IDLE"]);
}

GameState::GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
	: State(window, supportedKeys, states)
{
	this->initKeybinds();
	this->initTextures();
	this->initPlayers();
}

GameState::~GameState()
{
	delete this->player;
}

void GameState::updateInput(const float& dt)
{
	//Update player input
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_LEFT"))))
	{
		this->player->move(dt, -1.f, 0.f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_RIGHT"))))
	{
		this->player->move(dt, 1.f, 0.f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_UP"))))
	{
		this->player->move(dt, 0.f, -1.f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_DOWN"))))
	{
		this->player->move(dt, 0.f, 1.f);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))))
	{
		this->endState();
	}
}

void GameState::update(const float& dt)
{
	this->updateMousePosition();
	this->updateInput(dt);

	this->player->update(dt);
}

void GameState::render(sf::RenderTarget* target )
{
	if (!target)
	{
		target = this->window;
	}
	this->player->render(target);
}
