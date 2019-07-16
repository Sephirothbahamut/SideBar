/*
#include "OldPartSystem.h"
#include <iostream>
#include "OldPartSystem.h"

OldPartSystem::OldPartSystem(sf::Sprite sprite, float dir, float dir_offset, float speed, float speed_offset, float acc, float acc_offset, float size, float size_offset, float life, float life_offset, usi gen_amount, usi gen_alarm, sf::FloatRect generator)
	{
	this->sprite = sprite;
	this->sprite.setOrigin(sprite.getGlobalBounds().width / 2, sprite.getGlobalBounds().height / 2);
	this->dir = dir;
	this->dir_offset = dir_offset;
	this->speed = speed;
	this->speed_offset = speed_offset;
	this->acc = acc;
	this->acc_offset = acc_offset;
	this->size = size;
	this->size_offset = size_offset;
	this->life = life;
	this->life_offset = life_offset;
	this->gen_amount = gen_amount;
	this->gen_alarm = gen_alarm;
	this->generator = generator;
	this->alarm = 0;
	}

OldPartSystem::OldPartSystem(sf::Sprite sprite, float dir, float dir_offset, float speed, float speed_offset, float size, float size_offset, float life, float life_offset, usi gen_amount, usi gen_alarm, sf::FloatRect generator)
	{
	this->sprite = sprite;
	this->sprite.setOrigin(sprite.getGlobalBounds().width / 2, sprite.getGlobalBounds().height / 2);
	this->dir = dir;
	this->dir_offset = dir_offset;
	this->speed = speed;
	this->speed_offset = speed_offset;
	this->acc = 0;
	this->acc_offset = 0;
	this->size = size;
	this->size_offset = size_offset;
	this->life = life;
	this->life_offset = life_offset;
	this->gen_amount = gen_amount;
	this->gen_alarm = gen_alarm;
	this->generator = generator;
	this->alarm = 0;
	}

OldPartSystem::~OldPartSystem()
	{
	}

void OldPartSystem::step()
	{
	alarm++;
	if (alarm == gen_alarm)
		{
		alarm = 0;
		for (size_t i = 0; i < gen_amount; i++)
			{
			float p_x = Maths::random_range(generator.left, generator.left + generator.width);
			float p_y = Maths::random_range(generator.top, generator.top + generator.height);
			float p_dir = Maths::random_range(dir - dir_offset, dir + dir_offset);
			float p_life = Maths::random_range(life - life_offset, life + life_offset);
			float p_speed = Maths::random_range(speed - speed_offset, speed + speed_offset);
			float p_acc = Maths::random_range(acc - acc_offset, acc + acc_offset);
			float p_size = Maths::random_range(size - size_offset, size + size_offset);
			Particle part = Particle(sprite, p_x, p_y, p_dir, p_speed, p_acc, p_size, p_life);
			particles.push_back(part);
			}
		}
	size_t i = 0;
	while (i<particles.size())
		{
		Particle particle = particles[i];
		if (particle.dead)
			{//if must be deleted
			particles.erase(particles.begin() + i);
			}
		else
			{//if must be updated
			particles[i].step();
			i++;
			}
		}
	}

void OldPartSystem::draw(sf::RenderTarget & target)
	{
	for (size_t i = 0; i < particles.size(); i++)
		{
		target.draw(particles[i]);
		}
	}
*/