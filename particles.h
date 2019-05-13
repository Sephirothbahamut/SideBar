#pragma once
#include <SFML\Graphics.hpp>
#include "defines.h"
#include "Maths.h"
#include <random>

#include <list>
#include <vector>

namespace particle
	{
	class system;

	class generator
		{
		friend class system;
		public:
			enum type { line, rectangle, circle };
			enum distribution { linear, gaussian, /*inverse_gaussian*/ };

		private:
			system * s;
			float x1, y1, x2, y2;
			unsigned int amount;
			type t; distribution d;

			//randomizer
			std::default_random_engine rand_gen;

			float random_range_linear(float a, float b);
			float random_range_gaussian(float a, float b);
			//float random_range_inverse_gaussian(float a, float b);

			float (generator::*random_range)(float a, float b);

			//generators
			void generate_line();
			void generate_rectangle();
			void generate_circle();
			void (generator::*generate_)();

			void step();

		public:
			//setup
			generator(float center_x, float center_y, float radius, unsigned int amount, distribution d);
			generator(float x1, float y1, float x2, float y2, unsigned int amount, type t, distribution d);

			//run time
			void generate(unsigned int amount);
		};

	class system : public sf::Drawable
		{
		private:

			class particle : public sf::Sprite
				{
				friend class system;
				private:
					unsigned int life;
					float dir, speed, acc, speed_x, speed_y, acc_x, acc_y, alpha, alpha_dec;
				public:
					particle(const sf::Sprite &source, float x, float y, float dir, float speed, float acc, float size, float life);
					bool step();
					void push(float dir, float speed);
				};

			std::list<particle> particles;
			generator g;
			sf::Sprite s;

			float dir, dir_offset, speed, speed_offset, acc, acc_offset,
				size, size_offset;
			unsigned int life, life_offset;
			usi gen_amount, gen_alarm, alarm;
			unsigned long int particles_max;

		public:
			//setup
			system(sf::Sprite s, generator g,
				float dir, float dir_offset, float speed, float speed_offset,
				float acc, float acc_offset, float size, float size_offset,
				unsigned int life, unsigned int life_offset,
				usi gen_amount, usi gen_alarm);

			//run time
			virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
			void step();
			void generate(float x, float y);
			void push(float center_x, float center_y, float force);
			void pull(float center_x, float center_y, float force);
		};


	};

