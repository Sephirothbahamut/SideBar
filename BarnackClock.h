#pragma once

#include <SFML\Graphics.hpp>
#include "defines.h"

class BarnackClock : public sf::Drawable
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
		void step();
		BarnackClock(double x, double y, usi red, usi green, usi blue);
		~BarnackClock();
	};

