#pragma once
#include <stdlib.h>
#include <cmath>
#define M_PI 3.141592653589793238L 

namespace Maths
	{
	double random_range(double min, double max);
	float random_range(float min, float max);
	float random_range(unsigned int min, unsigned int max);

	double lengthdir_x(double length, double angle);
	double lengthdir_y(double length, double angle);
	};

