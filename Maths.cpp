#include "Maths.h"
#include <iostream>

namespace Maths
	{double random_range(double min, double max)
		{
		return((max - min) * ((double)rand() / (double)RAND_MAX) + min);
		}
	float random_range(float min, float max)
		{
		return((max - min) * ((float)rand() / (float)RAND_MAX) + min);
		}

	float random_range(unsigned int min, unsigned int max)
		{
		return((max - min) * ((unsigned int)rand() / (unsigned int)RAND_MAX) + min);
		}

	double lengthdir_x(double length, double angle)
		{
		return length * cos(angle * M_PI / 180);
		}
	double lengthdir_y(double length, double angle)
		{
		return length * sin(angle * M_PI / 180);
		}
	}