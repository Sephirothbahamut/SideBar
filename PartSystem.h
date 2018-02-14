#pragma once
#include <SFML\Graphics.hpp>
#include "defines.h"
#include "Particle.h"

class PartSystem
	{
	private:
		sf::Sprite sprite;
		float dir, dir_offset, speed, speed_offset, acc, acc_offset,
			size, size_offset, life, life_offset;
		usi gen_amount, gen_alarm, alarm;
		sf::FloatRect generator;

	public:
		std::vector<Particle> particles;
		PartSystem(sf::Sprite sprite,
			float dir, float dir_offset, float speed, float speed_offset,
			float acc, float acc_offset, float size, float size_offset,
			float life, float life_offset,
			usi gen_amount, usi gen_alarm, sf::FloatRect generator);
		PartSystem(sf::Sprite sprite,
			float dir, float dir_offset, float speed, float speed_offset,
			float size, float size_offset,
			float life, float life_offset,
			usi gen_amount, usi gen_alarm, sf::FloatRect generator);
		~PartSystem();
		void step();
		void draw(sf::RenderTarget& target);
	};

