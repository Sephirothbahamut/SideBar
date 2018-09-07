#include "Maths.h"
#include <iostream>


Maths::Maths()
	{}


Maths::~Maths()
	{}

double Maths::random_range(double min, double max)
	{
	return((max - min) * ((double)rand() / (double)RAND_MAX) + min);
	}
float Maths::random_range(float min, float max)
	{
	return((max - min) * ((float)rand() / (float)RAND_MAX) + min);
	}

float Maths::random_range(unsigned int min, unsigned int max)
	{
	return((max - min) * ((unsigned int)rand() / (unsigned int)RAND_MAX) + min);
	}

double Maths::lengthdir_x(double length, double angle)
	{
	return length * cos(angle * M_PI / 180);
	}
double Maths::lengthdir_y(double length, double angle)
	{
	return length * sin(angle * M_PI / 180);
	}
