#include "Button.h"


Button::Button(float x, float y, float width, float height,
	sf::Font* font, std::string text, unsigned characher_size,
	sf::Color idle_text_color, sf::Color hover_text_color, sf::Color active_text_color,
	sf::Color idle_color, sf::Color hover_color, sf::Color active_color)
{
	this->buttonState = BTN_IDLE;

	this->shape.setPosition(sf::Vector2f(x, y));
	this->shape.setSize(sf::Vector2f(width, height));

	this->shape.setFillColor(idle_color);
	this->font = font;
	this->text.setFont(*this->font);
	this->text.setString(text);
	this->text.setFillColor(idle_text_color);
	this->text.setCharacterSize(characher_size);
	std::string temp = this->text.getString();
	float xx = this->text.getGlobalBounds().width;
	std::cout << xx << std::endl;
	this->text.setPosition(
		this->shape.getPosition().x + this->shape.getSize().x / 2.f - this->text.getGlobalBounds().width / 2.f,
		this->shape.getPosition().y + this->shape.getGlobalBounds().height / 2.f - this->text.getGlobalBounds().height / 2.f
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

Button::~Button()
{

}

const bool Button::isPressed() const
{
	if (this->buttonState == BTN_ACTIVE)
	{
		return true;
	}
	return false;
}

void Button::update(const sf::Vector2f& mousePos)
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

void Button::render(sf::RenderTarget& target)
{
	target.draw(this->shape);
	target.draw(this->text);
}
