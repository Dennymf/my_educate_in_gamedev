#include "GameState.h"

void GameState::initFonts()
{
	if (!this->font.loadFromFile("Fonts/Loja.otf"))
	{
		throw("ERROR::GAMESTATE::COULD NOT LOAD FONT");
	}
}

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

void GameState::initPlayer()
{
	this->player = new Player(horizont, vertical, SIZE, textureSheet);
}

void GameState::initTexture()
{
	if (!this->textureFruitsSheet.loadFromFile("Resources/Images/Sprites/fruits.png"));
	{
		//throw "ERROR::GAME_STATE::COULD_NOT_LOAD_FRUIT_TEXTURE";
	}
	if (!this->textureSheet.loadFromFile("Resources/Images/Sprites/snake.png"));
	{
		//throw "ERROR::GAME_STATE::COULD_NOT_LOAD_SNAKE_TEXTURE";
	}
}

void GameState::initFruit()
{
	this->fruit = new Fruit(horizont, vertical, player, SIZE, textureFruitsSheet);
}

void GameState::initBackground()
{
	this->background.setSize(sf::Vector2f(
		static_cast<float>(this->window->getSize().x),
		static_cast<float>(this->window->getSize().y)
	));

	if (!this->textureBackground.loadFromFile("Resources/Images/Background/bg1.jpg"))
	{
		throw("ERROR::GAMESTATE::COULD NOT LOAD BACKGROUND");
	}
	this->background.setTexture(&this->textureBackground);
}

void GameState::initGameOverMenu()
{
	this->overmenu = new GameOverMenu(*this->window, this->font);
	this->overmenu->addButton("NEW GAME", 540.f, "New game");
}

GameState::GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
	: State(window, supportedKeys, states)
{
	this->newdelay = true;
	this->initFonts();
	this->initKeybinds();
	this->initTexture();
	this->initBackground();
	this->initPlayer();
	this->initFruit();
	this->initGameOverMenu();
}

GameState::~GameState()
{
}

void GameState::updateInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))))
	{
		this->window->close();
	}

}

void GameState::updatePlayerInput()
{
	//Update player input
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_LEFT"))))
	{
		this->player->changeDirection(0);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_RIGHT"))))
	{
		this->player->changeDirection(1);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_UP"))))
	{
		this->player->changeDirection(3);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_DOWN"))))
	{
		this->player->changeDirection(4);
	}
}

void GameState::updateGameOverButton()
{
	if (this->overmenu->isButtonPressed("NEW GAME"))
	{
		this->states->pop();
		this->states->push(new GameState(this->window, this->supportedKeys, this->states));
	}
}

void GameState::update(float& chrono, float& delay)
{
	this->newdelay = false;
	this->updateMousePosition();
	this->updateKeytime();
	this->updateInput();
	if (!this->player->getLose()) {
		this->updatePlayerInput();
		this->flag = false;
		if (chrono > delay)
		{
			this->player->update();
			if (this->fruit->update(player))
			{
				this->flag = true;
			}
		}
	} 
	else
	{
		this->overmenu->update(this->mousePosView);
		this->updateGameOverButton();
	}
}

void GameState::render(sf::RenderTarget& target)
{
	window->draw(this->background);
	fruit->render(target);
	player->render(target);
	if (this->player->getLose())
	{
		this->overmenu->render(target);
	}
}

bool GameState::getFlag()
{
	return this->flag;
}
