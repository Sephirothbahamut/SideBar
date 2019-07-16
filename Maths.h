#pragma once
#include <stdlib.h>
#include <cmath>
#define M_PI 3.141592653589793238L 

namespace Maths
	{
	double random_range(double min, double max);
	float random_range(float min, float max);
	float random_range(unsigned int min, unsigned int max);

	template <typename t>
	t lengthdir_x(t length, t angle)
		{
		return length * cos(angle * M_PI / 180);
		}
	template <typename t>
	t lengthdir_y(t length, t angle)
		{
		return length * sin(angle * M_PI / 180);
		}
	template<typename t>
	t point_dist(t x1, t y1, t x2, t y2)
		{
		t dist_x = x2 - x1;
		t dist_y = y2 - y1;
		return sqrt((dist_x * dist_x) + (dist_y * dist_y));
		}
	template<typename t>
	t point_angle(t x1, t y1, t x2, t y2)
		{
		return atan2(x2 - x1, y2 - y1) * 180 / M_PI;
		}
	};
