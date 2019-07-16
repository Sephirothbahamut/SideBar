#pragma once
#include <SFML\Graphics.hpp>
#include "defines.h"
#include "Particle.h"
#include <list>

class PartSystem
	{
	private:
		sf::Sprite sprite;
		float dir, dir_offset, speed, speed_offset, acc, acc_offset,
			size, size_offset;
		unsigned int life, life_offset;
		usi gen_amount, gen_alarm, alarm;
		sf::FloatRect generator;

	public:
		unsigned long int particles_max;
		std::list<Particle> particles;


		PartSystem(sf::Sprite sprite,
			float dir, float dir_offset, float speed, float speed_offset,
			float acc, float acc_offset, float size, float size_offset,
			unsigned int life, unsigned int life_offset,
			usi gen_amount, usi gen_alarm, sf::FloatRect generator);
		PartSystem(sf::Sprite sprite,
			float dir, float dir_offset, float speed, float speed_offset,
			float size, float size_offset,
			unsigned int life, unsigned int life_offset,
			usi gen_amount, usi gen_alarm, sf::FloatRect generator);
		~PartSystem();
		void step();
		void position_push(float x, float y, float force, float angle_min = 0, float angle_max = 360);
		void draw(sf::RenderTarget& target);
	};