#pragma once
#include <stdlib.h>
#include <cmath>
#define M_PI 3.141592653589793238L 

class Maths
	{
	public:
		Maths();
		~Maths();

		static double random_range(double min, double max);
		static float random_range(float min, float max);
		static float random_range(unsigned int min, unsigned int max);

		static double lengthdir_x(double length, double angle);
		static double lengthdir_y(double length, double angle);
	};

