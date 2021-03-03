#include "MovementComponent.h"

MovementComponent::MovementComponent(sf::Sprite& sprite, float maxVelocity,
	float acceleration, float deceleration)
	: sprite(sprite), maxVelocity(maxVelocity), acceleration(acceleration), deceleration(deceleration)
{
	this->maxVelocity = maxVelocity;
}

MovementComponent::~MovementComponent()
{
}

const float MovementComponent::getMaxVelocity() const
{
	return this->maxVelocity;
}

const sf::Vector2f& MovementComponent::getVelocity() const
{
	return this->velocity;
}

const bool MovementComponent::getState(const short unsigned state) const
{
	switch (state)
	{
	case IDLE:
		return this->velocity.x == 0.f && this->velocity.y == 0.f ? true : false;
		break;

	case MOVING:
		return this->velocity.x != 0.f || this->velocity.y != 0.f ? true : false;
		break;

	case MOVING_LEFT:
		return this->velocity.x < 0.f ? true : false;
		break;

	case MOVING_RIGHT:
		return this->velocity.x > 0.f ? true : false;
		break;

	case MOVING_UP:
		return this->velocity.y < 0.f ? true : false;
		break;

	case MOVING_DOWN:
		return this->velocity.y > 0.f ? true : false;
		break;
	}

	return false;
}


void MovementComponent::move(const float dir_x, const float dir_y, const float& dt)
{
	//Acceleration
	this->velocity.x += this->acceleration * dir_x;
	
	this->velocity.y += this->acceleration * dir_y;
}

void MovementComponent::update(const float& dt)
{
	//Decelaration 
	if (this->velocity.x != 0.f)
	{
		if (abs(this->velocity.x) > abs(this->maxVelocity))
		{
			this->velocity.x = dirVelocity(this->velocity.x) * this->maxVelocity;
		}
		this->velocity.x -= dirVelocity(this->velocity.x) * deceleration;
		if (this->velocity.x * dirVelocity(this->velocity.x) < 0.f)
		{
			this->velocity.x = 0.f;
		}
	}

	if (this->velocity.y != 0.f)
	{
		if (abs(this->velocity.y) > abs(this->maxVelocity))
		{
			this->velocity.y = dirVelocity(this->velocity.y) * this->maxVelocity;
		}
		this->velocity.y -= dirVelocity(this->velocity.y) * deceleration;
		if (this->velocity.y * dirVelocity(this->velocity.y) < 0.f)
		{
			this->velocity.y = 0.f;
		}
	}

	//Final move
	this->sprite.move(this->velocity * dt);
}

int MovementComponent::dirVelocity(float velocity)
{
	if (velocity > 0.f)
	{
		return 1;
	}
	else if (velocity < 0.f)
	{
		return -1;
	}
}
