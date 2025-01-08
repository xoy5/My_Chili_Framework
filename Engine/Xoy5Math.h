/******************************************************************************************
 *	Xoy5Math.h																			  *
 *	Kacper Wojtkowski 23 December 2024 r.												      *
 *	(I spent whole day to learn trigonometry please respect it)                           *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 *****************************************************************************************/

#pragma once
#include <assert.h>
#include <math.h>
#include "Vec2.h"
#include "Rect.h"

namespace xoy5
{
	constexpr float PI = 3.1415927; 
	constexpr Vec2 GRAVITATION = Vec2(0.0f, 200.0f);

	inline float rtod(float radians)
	{
		return radians * (180.0f / PI);
	}

	inline float deg360(float degrees)
	{
		if (degrees >= 360.0f || degrees <= -360.0f) {
			degrees = std::fmod(degrees, 360.0f);
		}
		if (degrees < 0.0f) return 360.0f + degrees;
		else return degrees;
	}
}
