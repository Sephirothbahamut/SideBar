/*
#pragma once
#include <SFML\Graphics.hpp>
#include "defines.h"
#include "Maths.h"

class OldParticle : public sf::Sprite
	{
	private:
		float dir, speed, acc, speed_x, speed_y, acc_x, acc_y, alpha, alpha_dec;
	public:
		bool dead;
		OldParticle(const sf::Sprite &source);
		OldParticle(const sf::Sprite &source, float x, float y, float dir, float speed, float acc, float size, float life);
		~OldParticle();
		void step();
		void push(float dir, float speed);
	};
*/