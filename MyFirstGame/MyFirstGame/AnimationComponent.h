#ifndef ANIMINATIONCOMPONENT_H
#define ANIMINATIONCOMPONENT_H

#include <iostream>
#include <string>
#include <map>

#include "SFML\Graphics.hpp"
#include "SFML\Window.hpp"
#include "SFML\System.hpp"
#include "SFML\Audio.hpp"
#include "SFML\Network.hpp"

class AnimationComponent
{
private:
	class Animation
	{
	public:
		//Variables
		sf::Sprite& sprite;
		sf::Texture& textureSheet;
		float animationTimer;
		float timer;
		int widht, height;
		sf::IntRect startRect, currentRect, endRect;

		Animation(sf::Sprite& sprite, sf::Texture& texture_sheet, float animation_timer,
				int start_frame_x, int start_frame_y, int frames_x, int frames_y,
				int widht, int height)
			: sprite(sprite), textureSheet(texture_sheet), animationTimer(animation_timer),
			widht(widht), height(height)
		{
			this->timer = 0.f;
			this->startRect = sf::IntRect(start_frame_x * widht, start_frame_y * height, widht, height);
			this->currentRect = this->startRect;
			this->endRect = sf::IntRect(frames_x * widht, frames_y * height, widht, height);
			
			this->sprite.setTexture(this->textureSheet, true);
			this->sprite.setTextureRect(this->startRect);
		}

		//Func
		void play(const float& dt)
		{
			this->timer += 100.f * dt;
			if (this->timer >= this->animationTimer)
			{
				this->timer = 0.f;

				if (this->currentRect != this->endRect)
				{
					this->currentRect.left += this->widht;
				}
				else
				{
					this->currentRect = this->startRect;
				}

				this->sprite.setTextureRect(this->currentRect);
			}
		}

		void reset()
		{
			this->timer = 0.f;
			this->currentRect = this->startRect;
		}
	};

	sf::Sprite& sprite;
	sf::Texture& textureSheet;
	std::map<std::string, Animation*> animations;

public:
	AnimationComponent(sf::Sprite& sprite, sf::Texture& texture_sheet);
	virtual ~AnimationComponent();

	void addAnimation(const std::string key, float animation_timer,
		int start_frame_x, int start_frame_y, int frames_x, int frames_y,
		int widht, int height);

	void play(const std::string key, const float& dt);
};

#endif