#include "Player.h"

void Player::initVariables()
{
	snake.clear();
	Snake head = { horizont / 2, vertical / 2 };
	this->lose = false;
	snake.push_back(head);
	direction = 0;
	snake.push_back(snake[0]);
	snake.push_back(snake[0]);
}

Player::Player(float horizont, float vertical, int SIZE, sf::Texture& textureSheet)
	: textureSheet(textureSheet)
{
	this->SIZE = SIZE;
	this->horizont = horizont;
	this->vertical = vertical;
	this->initVariables();
}

Player::~Player()
{
}

void Player::update()
{
	this->updateSnake();
	this->move();
	this->checkLose();
}

void Player::updateSnake()
{
	for (int i = this->snake.size() - 1; i > 0; --i)
	{
		snake[i].x = snake[i - 1].x;
		snake[i].y = snake[i - 1].y;
	}

}

void Player::changeDirection(int dir)
{
	if (abs(this->direction - dir) != 1)
	{
		this->direction = dir;
	}
}

void Player::move()
{
	switch (this->direction)
	{
	case 0:
		snake[0].x -= 1;
		break;
	case 1:
		snake[0].x += 1;
		break;
	case 3:
		snake[0].y -= 1;
		break;
	case 4:
		snake[0].y += 1;
		break;
	default:
		break;
	}

	if (snake[0].x < 0 || snake[0].x >= horizont || snake[0].y < 0 || snake[0].y >= vertical)
	{
		this->lose = true;
	}
}

void Player::render(sf::RenderTarget& target)
{
	for (int i = 0; i < snake.size(); i++)
	{
		this->sprite.setTexture(this->textureSheet);
		if (i == 0)
		{
			int x = snake[0].x - snake[1].x;
			int y = snake[0].y - snake[1].y;
			if (x == 0 && y == 1)
			{
				this->sprite.setTextureRect(sf::IntRect(240, 60, 60, 60));
			}
			else if (x == 0 && y == -1)
			{
				this->sprite.setTextureRect(sf::IntRect(180, 0, 60, 60));
			}
			else if (x == 1 && y == 0)
			{
				this->sprite.setTextureRect(sf::IntRect(240, 0, 60, 60));
			}
			else if (x == -1 && y == 0)
			{
				this->sprite.setTextureRect(sf::IntRect(180, 60, 60, 60));
			}
		}
		else if (i == snake.size() - 1 ||
			i == snake.size() - 2 && snake[snake.size() - 2].x == snake[snake.size() - 1].x
			&& snake[snake.size() - 2].y == snake[snake.size() - 1].y)
		{
			int x = snake[i].x - snake[i - 1].x;
			int y = snake[i].y - snake[i - 1].y;
			if (x == 1)
			{
				this->sprite.setTextureRect(sf::IntRect(180, 180, 60, 60));
			}
			else if (x == -1)
			{
				this->sprite.setTextureRect(sf::IntRect(240, 120, 60, 60));
			}
			else if (y == 1)
			{
				this->sprite.setTextureRect(sf::IntRect(180, 120, 60, 60));
			}
			else if (y == -1)
			{
				this->sprite.setTextureRect(sf::IntRect(240, 180, 60, 60));
			}
		}
		else 
		{
			int x = snake[i].x - snake[i - 1].x;
			int y = snake[i].y - snake[i - 1].y;
			int x1 = snake[i + 1].x - snake[i].x;
			int y1 = snake[i + 1].y - snake[i].y;
			if (x == 1 && x1 == 1 || x == -1 && x1 == -1)
			{
				this->sprite.setTextureRect(sf::IntRect(60, 0, 60, 60));
			}
			else if (y == 1 && y1 == 1 || y == -1 && y1 == -1)
			{
				this->sprite.setTextureRect(sf::IntRect(120, 60, 60, 60));
			}
			else if (x == 0 && x1 == 1 && y == 1 && y1 == 0 ||
				x == -1 && x1 == 0 && y == 0 && y1 == -1)
			{
				this->sprite.setTextureRect(sf::IntRect(0, 60, 60, 60));
			}
			else if (x == 1 && x1 == 0 && y == 0 && y1 == -1 ||
				x == 0 && x1 == -1 && y == 1 && y1 == 0)
			{
				this->sprite.setTextureRect(sf::IntRect(120, 120, 60, 60));
			}
			else if (x == 0 && x1 == 1 && y == -1 && y1 == 0 ||
				x == -1 && x1 == 0 && y == 0 && y1 == 1)
			{
				this->sprite.setTextureRect(sf::IntRect(0, 0, 60, 60));
			}
			else if (x == 0 && x1 == -1 && y == -1 && y1 == 0 ||
				x == 1 && x1 == 0 && y == 0 && y1 == 1)
			{
				this->sprite.setTextureRect(sf::IntRect(120, 0, 60, 60));
			}
		}
		sprite.setPosition(snake[i].x * SIZE, snake[i].y * SIZE);
		target.draw(sprite);
	}
}

void Player::newLenght()
{
	this->snake.push_back(snake[snake.size() - 1]);
}

bool Player::inSnake(int x, int y)
{
	for (int i = 0; i < this->snake.size(); i++)
	{
		if (x == this->snake[i].x && y == this->snake[i].y)
			return true;
	}

	return false;
}

bool Player::inHead(int x, int y)
{
	return x == this->snake[0].x && y == this->snake[0].y;
}

void Player::checkLose()
{
	if (snake.size() > 3)
	{
		for (int i = 1; i < this->snake.size(); i++)
		{
			if (snake[0].x == snake[i].x && snake[0].y == snake[i].y)
			{
				this->lose = true;
				break;
			}
		}
	}
}

bool Player::getLose()
{
	return this->lose;
}
