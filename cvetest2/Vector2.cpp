#include "vector2.hpp"
#include <cstdint>
#include <algorithm>
#include <iostream>
#include <iomanip>



namespace Math
{

	Vector2::Vector2()
	{
	
		x = 0, y = 0, anim_time = 0;
	}

	Vector2::Vector2(double init_x, double init_y, double anim_time)
	{
		anim_time = anim_time;
		x = init_x, y = init_y;
	}

}