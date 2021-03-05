#include "Gui.h"


gui::Button::Button(float x, float y, float width, float height,
	sf::Font* font, std::string text, unsigned characher_size,
	sf::Color idle_text_color, sf::Color hover_text_color, sf::Color active_text_color,
	sf::Color idle_color, sf::Color hover_color, sf::Color active_color)
{
	this->pressed = false;
	this->hover = false;
	this->buttonState = BTN_IDLE;

	this->shape.setPosition(sf::Vector2f(x, y));
	this->shape.setSize(sf::Vector2f(width, height));

	this->shape.setFillColor(idle_color);
	this->font = font;
	this->text.setFont(*this->font);
	this->text.setString(text);
	this->text.setFillColor(idle_text_color);
	this->text.setCharacterSize(characher_size);
	this->text.setPosition(
		this->shape.getPosition().x + this->shape.getSize().x / 2.f - this->text.getGlobalBounds().width / 2.f,
		this->shape.getPosition().y + this->shape.getSize().y / 2.f - this->text.getGlobalBounds().height / 2.f
	);

	this->idleTextColor = idle_text_color;
	this->hoverTextColor = hover_text_color;
	this->activeTextColor = active_text_color;
	this->text.setOutlineThickness(3.f);
	this->text.setOutlineColor(sf::Color(20, 20, 20, 255));
	this->shape.setOutlineThickness(2.f);
	this->shape.setOutlineColor(sf::Color(200, 200, 200, 200));

	this->idleColor = idle_color;
	this->hoverColor = hover_color;
	this->activeColor = active_color;
}

gui::Button::~Button()
{

}

const bool gui::Button::isPressed() const
{
	if (this->buttonState == BTN_ACTIVE)
	{
		return true;
	}
	return false;
}

const std::string gui::Button::getText() const
{
	return this->text.getString();
}

void gui::Button::setText(const std::string text)
{
	this->text.setString(text);
}

void gui::Button::update(const sf::Vector2f& mousePos)
{
	this->buttonState = BTN_IDLE;

	if (this->shape.getGlobalBounds().contains(mousePos))
	{
		this->buttonState = BTN_HOVER;
	
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			this->buttonState = BTN_ACTIVE;
		}
	}

	switch (this->buttonState)
	{
	case BTN_IDLE:
		this->shape.setFillColor(this->idleColor);
		this->text.setFillColor(this->idleTextColor);
		break;
	case BTN_HOVER:
		this->shape.setFillColor(this->hoverColor);
		this->text.setFillColor(this->hoverTextColor);
		break;
	case BTN_ACTIVE:
		this->shape.setFillColor(this->activeColor);
		this->text.setFillColor(this->activeTextColor);
		break;
	default:
		this->shape.setFillColor(sf::Color::Red);
		this->text.setFillColor(sf::Color::Blue);
		break;
	}
}

void gui::Button::render(sf::RenderTarget& target)
{
	target.draw(this->shape);
	target.draw(this->text);
}

gui::DropDownList::DropDownList(float x, float y, float width, float height,
	sf::Font& font, std::string list[], unsigned numberOfElements, const unsigned default_index)
	: font(font), showList(false), keytimeMax(10.f), keytime(0.f)
{
	//unsigned numberOfElements = sizeof(list) / sizeof(std::string);


	this->activeElement = new gui::Button(
		x, y, width, height,
		&this->font, list[default_index], 20,
		sf::Color(250, 250, 250, 150), sf::Color(250, 250, 250, 250), sf::Color(80, 80, 80, 200),
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 200), sf::Color(20, 20, 20, 200)
	);

	for (size_t i = 0; i < numberOfElements; i++)
	{
		this->list.push_back(
			new gui::Button(
				x, y + ((i + 1) * height), width, height,
				&this->font, list[i], 20,
				sf::Color(250, 250, 250, 150), sf::Color(250, 250, 250, 250), sf::Color(80, 80, 80, 200),
				sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 200), sf::Color(20, 20, 20, 200)
			)
		);
	}
}

gui::DropDownList::~DropDownList()
{
	delete this->activeElement;
	
	for (auto *&it : this->list)
	{
		delete it;
	}
}

const bool gui::DropDownList::getKeytime()
{
	if (this->keytime >= this->keytimeMax)
	{
		this->keytime = 0.f;
		return true;
	}

	return false;
}

void gui::DropDownList::updateKeytime(const float& dt)
{
	if (this->keytime < this->keytimeMax)
	{
		this->keytime += 30.f * dt;
	}
}

void gui::DropDownList::update(const sf::Vector2f& mousePos, const float& dt)
{
	this->updateKeytime(dt);
	this->activeElement->update(mousePos);

	if (this->activeElement->isPressed() && this->getKeytime())
	{
		this->showList = !this->showList;
	}
	if (this->showList) {
		for (auto& i : this->list)
		{
			i->update(mousePos);

			if (i->isPressed() && this->getKeytime())
			{
				this->showList = false;
				this->activeElement->setText(i->getText());
			}
		}
	}
}

void gui::DropDownList::render(sf::RenderTarget& target)
{
	this->activeElement->render(target);

	if (this->showList) {
		for (auto& i : this->list)
		{
			i->render(target);
		}
	}
}
