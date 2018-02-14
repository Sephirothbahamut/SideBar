#include "Particle.h"
#include <iostream>
#include <cmath>

Particle::Particle(const sf::Sprite &source, float x, float y, float dir, float speed, float acc, float size, float life) : sf::Sprite(source)
	{
	this->dir = dir;
	this->speed = speed;
	this->acc = acc;
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
	this->dead = false;
	this->alpha = getColor().a;
	}

Particle::Particle(const sf::Sprite &source) : sf::Sprite(source)
	{
	dead = false;
	}

Particle::~Particle()
	{}

void Particle::step()
	{
	move(speed_x, speed_y);
	if (alpha_dec)
		{//if has a lifespan
		if (getColor().a < alpha_dec)
			{
			dead = true;
			}
		else
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
	}

void Particle::push(float pdir, float pspeed)
	{
	this->speed_x += Maths::lengthdir_x(pspeed, pdir);
	this->speed_y += Maths::lengthdir_y(pspeed, pdir);
	this->dir = std::atan(speed_x / speed_y);
	this->acc_x = Maths::lengthdir_x(acc, dir);
	this->acc_y = Maths::lengthdir_y(acc, dir);
	}
