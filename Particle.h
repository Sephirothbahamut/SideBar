#pragma once
#include <SFML\Graphics.hpp>
#include "defines.h"
#include "Maths.h"

class Particle : public sf::Sprite
	{
	private:
		float dir, speed, acc, speed_x, speed_y, acc_x, acc_y, alpha, alpha_dec;
	public:
		bool dead;
		Particle(const sf::Sprite &source);
		Particle(const sf::Sprite &source, float x, float y, float dir, float speed, float acc, float size, float life);
		~Particle();
		void step();
		void push(float dir, float speed);
	};

