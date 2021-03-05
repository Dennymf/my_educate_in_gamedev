#include "MainMenuState.h"

void MainMenuState::initVariables()
{

}

void MainMenuState::initBackground()
{
	this->background.setSize(sf::Vector2f(
		static_cast<float>(this->window->getSize().x),
		static_cast<float>(this->window->getSize().y)
	));

	if (!this->bgTexture.loadFromFile("Resources/Images/Background/bg1.png"))
	{
		throw("ERROR::MAINMENUSTATE::COULD NOT LOAD BACKGROUND");
	}
	this->background.setTexture(&this->bgTexture);
}

void MainMenuState::initFonts()
{
	if (!this->font.loadFromFile("Fonts/Loja.otf"))
	{
		throw("ERROR::MAINMENUSTATE::COULD NOT LOAD FONT");
	}
}

void MainMenuState::initKeybinds()
{
	std::fstream file_keys("Config/mainmenustate_keybinds.ini");

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

void MainMenuState::initButtons()
{
	float x = this->window->getSize().x / 2.f;
	float y = this->window->getSize().y / 4.f;
	float distance = this->window->getSize().y / 10.f;
	float width = 200.f;
	float height = 70.f;
	this->buttons["GAME_STATE"] =  new gui::Button(x - width / 2.f, y - height / 2.f, width, height,
		&this->font, "New Game", 50,
		sf::Color(250, 250, 250, 200), sf::Color(130, 130, 130, 255), sf::Color(80, 80, 80, 200),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));
	this->buttons["SETTING_STATE"] = new gui::Button(x - width / 2.f, y - height / 2.f + distance, width, height,
		&this->font, "Settings", 50,
		sf::Color(250, 250, 250, 200), sf::Color(130, 130, 130, 255), sf::Color(80, 80, 80, 200),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));
	this->buttons["EDITOR_STATE"] = new gui::Button(x - width / 2.f, y - height / 2.f + distance * 2.f, width, height,
		&this->font, "Editor", 50,
		sf::Color(250, 250, 250, 200), sf::Color(130, 130, 130, 255), sf::Color(80, 80, 80, 200),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));
	this->buttons["EXIT_STATE"] = new gui::Button(x - width / 2.f, y - height / 2.f + distance * 3.f, width, height,
		&this->font, "Quit", 50,
		sf::Color(250, 250, 250, 200), sf::Color(130, 130, 130, 255), sf::Color(80, 80, 80, 200),
		sf::Color(100, 100, 100, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));
}

MainMenuState::MainMenuState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
	: State(window, supportedKeys, states)
{
	this->initBackground();
	this->initVariables();
	this->initFonts();
	this->initKeybinds();
	this->initButtons();
}

MainMenuState::~MainMenuState()
{
	for (auto it = this->buttons.begin(); it != this->buttons.end(); it++)
	{
		delete it->second;
	}
}

void MainMenuState::updateInput(const float& dt)
{
	
}

void MainMenuState::updateButtons()
{
	for (auto &it : this->buttons)
	{
		it.second->update(this->mousePosView);
	}

	//New game
	if (this->buttons["GAME_STATE"]->isPressed())
	{
		this->states->push(new GameState(this->window, this->supportedKeys, this->states));
	}

	//Setting
	if (this->buttons["SETTING_STATE"]->isPressed())
	{
		this->states->push(new SettingState(this->window, this->supportedKeys, this->states));
	}
	
	//Editor
	if (this->buttons["EDITOR_STATE"]->isPressed())
	{
		this->states->push(new EditorState(this->window, this->supportedKeys, this->states));
	}

	//Quit
	if (this->buttons["EXIT_STATE"]->isPressed())
	{
		this->endState();
	}
}

void MainMenuState::update(const float& dt)
{
	this->updateMousePosition();
	this->updateInput(dt);
	this->updateButtons();
}

void MainMenuState::render(sf::RenderTarget* target)
{
	if (!target)
	{
		target = this->window;
	}

	target->draw(this->background);
	this->renderButtons(*target);

	//Remove later
	/*sf::Text mouseText;
	mouseText.setPosition(this->mousePosView.x, this->mousePosView.y - 50);
	mouseText.setFont(this->font);
	mouseText.setCharacterSize(12);
	std::stringstream ss;
	ss << this->mousePosView.x << " " << this->mousePosView.y;
	mouseText.setString(ss.str());

	target->draw(mouseText);*/
}

void MainMenuState::renderButtons(sf::RenderTarget& target)
{
	for (auto& it : this->buttons)
	{
		it.second->render(target);
	}
}
