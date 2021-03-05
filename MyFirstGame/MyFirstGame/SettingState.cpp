#include "SettingState.h"

void SettingState::initVariables()
{

}

void SettingState::initBackground()
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

void SettingState::initFonts()
{
	if (!this->font.loadFromFile("Fonts/Loja.otf"))
	{
		throw("ERROR::MAINMENUSTATE::COULD NOT LOAD FONT");
	}
}

void SettingState::initKeybinds()
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

void SettingState::initGui()
{
	float x = this->window->getSize().x / 2.f;
	float y = this->window->getSize().y / 4.f;
	float distance = this->window->getSize().y / 10.f;
	float width = 200.f;
	float height = 70.f;
	this->buttons["EXIT_STATE"] = new gui::Button(x - width / 2.f, y - height / 2.f + distance * 4.f, width, height,
		&this->font, "Back", 50,
		sf::Color(250, 250, 250, 200), sf::Color(130, 130, 130, 255), sf::Color(80, 80, 80, 200),
		sf::Color(100, 100, 100, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

	std::string li[] = { "1920x1080", "1280x1024", "800x600" };
	this->dropDownLists["RESOLUTION"] = new gui::DropDownList(
		x - width / 2.f, y, width, 40, font, li, 3
	);
}


SettingState::SettingState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
	: State(window, supportedKeys, states)
{
	this->initBackground();
	this->initVariables();
	this->initFonts();
	this->initKeybinds();
	this->initGui();
}

SettingState::~SettingState()
{
	for (auto it = this->buttons.begin(); it != this->buttons.end(); it++)
	{
		delete it->second;
	}

	for (auto it = this->dropDownLists.begin(); it != this->dropDownLists.end(); it++)
	{
		delete it->second;
	}
}

void SettingState::updateInput(const float& dt)
{

}

void SettingState::updateGui(const float& dt)
{
	for (auto& it : this->buttons)
	{
		it.second->update(this->mousePosView);
	}

	//Quit
	if (this->buttons["EXIT_STATE"]->isPressed())
	{
		this->endState();
	}
	for (auto& it : this->dropDownLists)
	{
		it.second->update(this->mousePosView, dt);
	}

}

void SettingState::update(const float& dt)
{
	this->updateMousePosition();
	this->updateInput(dt);
	this->updateGui(dt);
}

void SettingState::render(sf::RenderTarget* target)
{
	if (!target)
	{
		target = this->window;
	}

	target->draw(this->background);
	this->renderGui(*target);
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

void SettingState::renderGui(sf::RenderTarget& target)
{
	for (auto& it : this->buttons)
	{
		it.second->render(target);
	}

	for (auto& it : this->dropDownLists)
	{
		it.second->render(target);
	}
}
