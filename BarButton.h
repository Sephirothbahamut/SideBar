#pragma once
#include <iostream>
#include <string>
#include "SbItem.h"


//string to wstring
#include <atlbase.h>
#include <atlconv.h>

class BarButton : public SbItem
	{
	private:
		std::vector<sf::IntRect> anim;
		sf::Sprite sprite;
		sf::Text text;
		usi current;
		int changing;
		std::string action;

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	public:
		BarButton(std::string text, std::string action, double x /*middle*/, double y /*top*/, sf::Texture& texture, sf::Font& font, sf::Color &color);
		~BarButton();

		void mouse_moved(sf::Vector2f mouse_pos);
		void mouse_moved(sf::Vector2f mouse_pos_previous, sf::Vector2f mouse_pos);
		void mouse_pressed(sf::Vector2f mouse_pos);
		void mouse_released(sf::Vector2f mouse_pos);

		void step();
	};

