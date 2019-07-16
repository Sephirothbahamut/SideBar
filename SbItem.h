#pragma once

#include <SFML\Graphics.hpp>
#include "settings.h"
#include "defines.h"
class SbItem : public sf::Drawable
	{
	public:
		sf::IntRect collision;
		Settings::sidebar_element::TYPE type;
		virtual void mouse_moved(sf::Vector2f mouse_pos) = 0;
		virtual void mouse_moved(sf::Vector2f mouse_pos_previous, sf::Vector2f mouse_pos) = 0;
		virtual void mouse_pressed(sf::Vector2f mouse_pos) = 0;
		virtual void mouse_released(sf::Vector2f mouse_pos) = 0;

		virtual void step() = 0;
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;

		SbItem(Settings::sidebar_element::TYPE type);
		~SbItem();
	};

