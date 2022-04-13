#ifndef _VECTOR2_HPP
#define _VECTOR2_HPP

/*
 * Includes for this file
 */
#include <cstdint>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cmath>

namespace Math
{

	/*
	 * 2D vector class
	 */
	class Vector2
	{
	public:

		Vector2();
		Vector2(double x, double y, double anim_time);


	public: // Public fields for this class
		double x, y;
		double anim_time;
	};
}
#endif#pragma once
