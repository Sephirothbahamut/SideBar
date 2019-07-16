#pragma once

#include "SbItem.h"

class BarnackClock : public SbItem
	{
	sf::Sprite clock;
	sf::Sprite mins;
	sf::Sprite hous;
	sf::Sprite secs;

	sf::Sprite analog_field;
	sf::Sprite day_field;

	sf::Text analog;
	sf::Text day;

	sf::Texture texture;
	sf::Font font;


	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	public:
		void mouse_moved(sf::Vector2f mouse_pos);
		void mouse_moved(sf::Vector2f mouse_pos_previous, sf::Vector2f mouse_pos);
		void mouse_pressed(sf::Vector2f mouse_pos);
		void mouse_released(sf::Vector2f mouse_pos);
		void step();
		BarnackClock(double x /*middle*/, double y /*top*/, usi red, usi green, usi blue);
		~BarnackClock();
	};

