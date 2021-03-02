#include "AnimationComponent.h"

AnimationComponent::AnimationComponent(sf::Sprite& sprite, sf::Texture& texture_sheet)
	: sprite(sprite), textureSheet(texture_sheet)
{

}

AnimationComponent::~AnimationComponent()
{
	for (auto &iter : this->animations)
	{
		delete iter.second;
	}
}

void AnimationComponent::addAnimation(const std::string key, float animation_timer,
	int start_frame_x, int start_frame_y, int frames_x, int frames_y,
	int widht, int height)
{
	this->animations[key] = new Animation(this->sprite, this->textureSheet, animation_timer,
		start_frame_x, start_frame_y, frames_x, frames_y,
		widht, height);
}

void AnimationComponent::play(const std::string key, const float& dt)
{
	this->animations[key]->play(dt);
}
