#include "particles.h"
#include <iostream>
namespace particle
	{
	float generator::random_range_linear(float a, float b) { return Maths::random_range(a, b); }
	float generator::random_range_gaussian(float a, float b)
		{
		std::normal_distribution<float> rand_distr(a, b);
		return rand_distr(rand_gen);
		}

	void generator::generate_line()
		{
		float dx = x2 - x1;
		float dy = y2 - y1;
		float length = sqrt(dx*dx + dy * dy);
		float dist = (this->*random_range)(0, length);

		float x = x1 + ((dist / length)*(x2 - x1));
		float y = y1 + ((dist / length)*(y2 - y1));
		
		s->generate(x, y);
		}
	void generator::generate_rectangle()
		{
		float x = (this->*random_range)(x1, x2);
		float y = (this->*random_range)(y1, y2);
		s->generate(x, y);
		}
	void generator::generate_circle()
		{
		float dist = (this->*random_range)(0, x2);//x2 is radius
		float angle = (this->*random_range)(0, 360);

		float x = Maths::lengthdir_x(dist, angle);
		float y = Maths::lengthdir_y(dist, angle);
		s->generate(x, y);
		}

	void generator::step() { generate(amount); }


	generator::generator(float center_x, float center_y, float radius, unsigned int amount, distribution d)
		: t(circle), x1(center_x), y1(center_y), x2(radius), amount(amount), d(d)
		{
		generate_ = &generator::generate_circle;
		switch (d)
			{
			case linear: random_range = &generator::random_range_linear; break;
			case gaussian: random_range = &generator::random_range_gaussian; break;
			}
		}
	generator::generator(float x1, float y1, float x2, float y2, unsigned int amount, type t, distribution d)
		: x1(x1), y1(y1), x2(x2), y2(y2), amount(amount), t(t), d(d)
		{
		switch (t)
			{
			case line: generate_ = &generator::generate_line; break;
			case rectangle: generate_ = &generator::generate_rectangle; break;
			case circle: generate_ = &generator::generate_circle; break;
			}
		switch (d)
			{
			case linear: random_range = &generator::random_range_linear; break;
			case gaussian: random_range = &generator::random_range_gaussian; break;
			}
		}

	void generator::generate(unsigned int amount)
		{
		for (unsigned int i = 0; i < amount; i++) { (this->*generate_)(); }
		}

	system::particle::particle(const sf::Sprite & source, float x, float y, float dir, float speed, float acc, float size, float life)
		: sf::Sprite(source), dir(dir), speed(speed), acc(acc), life(life)
		{
		setPosition(x, y);
		this->speed_x = Maths::lengthdir_x(speed, dir);
		this->speed_y = Maths::lengthdir_y(speed, dir);
		this->acc_x = Maths::lengthdir_x(acc, dir);
		this->acc_y = Maths::lengthdir_y(acc, dir);

		if (life > 0)
			{
			this->alpha_dec = ((getColor().a) / (life));
			}
		else
			{
			this->alpha_dec = 0;
			}
		this->setScale(size, size);
		this->alpha = getColor().a;
		}

	bool system::particle::step()
		{
		move(speed_x, speed_y);
		if (alpha_dec)
			{//if has a lifespan
			if (getColor().a >= alpha_dec)
				{
				alpha -= alpha_dec;
				setColor(sf::Color(getColor().r, getColor().g, getColor().b, alpha));
				}
			}
		if (acc)
			{
			this->speed_x -= acc_x;
			this->speed_y -= acc_y;
			}
		if (life)
			{
			life--;
			return(false);
			}
		return(true);
		}

	void system::particle::push(float pdir, float pspeed)
		{
		this->speed_x += Maths::lengthdir_x(pspeed, pdir);
		this->speed_y += Maths::lengthdir_y(pspeed, pdir);
		this->dir = std::atan(speed_x / speed_y);
		this->acc_x = Maths::lengthdir_x(acc, dir);
		this->acc_y = Maths::lengthdir_y(acc, dir);
		}
	
	system::system(sf::Sprite s, generator g, float dir, float dir_offset, float speed, float speed_offset, float acc, float acc_offset, float size, float size_offset, unsigned int life, unsigned int life_offset, usi gen_amount, usi gen_alarm)
		: s(s), g(g), dir(dir), dir_offset(dir_offset), speed(speed), speed_offset(speed_offset), acc(acc), acc_offset(acc_offset)
		, size(size), size_offset(size_offset), life(life), life_offset(life_offset), gen_amount(gen_amount), gen_alarm(gen_alarm)
		{
		this->g.s = this;
		}

	void system::draw(sf::RenderTarget & target, sf::RenderStates states) const
		{
		for (auto p : particles) { target.draw(p, states); }
		}

	void system::step()
		{

		/*alarm++;
		if (alarm == gen_alarm)
			{
			alarm = 0;
			for (size_t i = 0; i < gen_amount; i++)
				{
				//generate particles
				}
			}*/

		std::list<particle>::iterator it = particles.begin();
		while (it != particles.end())
			{
			auto p = *it;
			if (p.step()) { it = particles.erase(it); }
			else { it++; }
			}
		g.step();
		}

	void system::generate(float x, float y)
		{
		float p_dir = Maths::random_range(dir - dir_offset, dir + dir_offset);
		float p_life = Maths::random_range(life - life_offset, life + life_offset);
		float p_speed = Maths::random_range(speed - speed_offset, speed + speed_offset);
		float p_acc = Maths::random_range(acc - acc_offset, acc + acc_offset);
		float p_size = Maths::random_range(size - size_offset, size + size_offset);
		particles.push_back(particle(s, x, y, p_dir, p_speed, p_acc, p_size, p_life));
		}

	}


