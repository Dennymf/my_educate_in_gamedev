#include "Fruit.h"

Fruit::Fruit(int horiz, int  vert, Player* player, int SIZE, sf::Texture& textureFruitsSheet)
	: textureFruitsSheet(textureFruitsSheet)
{
	this->SIZE = SIZE;
	this->horiz = horiz;
	this->vert = vert;
	
	this->newFruit(player);
}


Fruit::~Fruit()
{
}

void Fruit::newFruit(Player* player)
{
	srand(time(NULL));
	bool flag = false;
	int new_x;
	int new_y;
	do
	{
		new_x = rand() % horiz;
		new_y = rand() % vert;
		if (!player->inSnake(new_x, new_y))
			flag = true;
	} while (!flag);

	this->fruit.x = new_x;
	this->fruit.y = new_y;
	srand(time(NULL));
	this->fruit.texture = rand() % 4;
}

bool Fruit::update(Player* player)
{
	if (player->inHead(this->fruit.x, this->fruit.y))
	{
		player->newLenght();
		this->newFruit(player);
		return true;
	}

	return false;
}

void Fruit::render(sf::RenderTarget& target)
{
	this->sprite.setTexture(this->textureFruitsSheet);
	switch (this->fruit.texture)
	{
	case 0:
		this->sprite.setTextureRect(sf::IntRect(0, 0, 60, 60));
		break;
	case 1:
		this->sprite.setTextureRect(sf::IntRect(60, 0, 60, 60));
		break;
	case 2:
		this->sprite.setTextureRect(sf::IntRect(0, 60, 60, 60));
		break;
	case 3:
		this->sprite.setTextureRect(sf::IntRect(60, 60, 60, 60));
		break;
	default:
		break;
	}
	sprite.setPosition(this->fruit.x * SIZE, this->fruit.y * SIZE);
	target.draw(sprite);
}

std::pair<int, int> Fruit::getCoor()
{
	return { fruit.x, fruit.y };
}
