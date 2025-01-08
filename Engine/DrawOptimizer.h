#pragma once
#include <math.h>

#include "Surface.h"
#include "Colors.h"

class DrawOptimizer 
{
public:
	DrawOptimizer(int width, int height) 
		:
		bs(width, height),
		s(width, height)
	{}

	void Reset()
	{
		bs.Reset();
		s.Reset();
	}

	void AddCircle(const Vei2& pos, float radius, const Color& c) 
	{
		const float radiusSqrt = std::pow(radius, 2);
		for (int y = -radius; y <= radius; y++) {
			for (int x = -radius; x <= radius; x++) {
				const Vei2 cur = Vei2{ x, y };
				const float curLengthSqrt = std::pow(cur.x, 2) + std::pow(cur.y, 2);
				if (curLengthSqrt <= radiusSqrt) {
					const Vei2 inSurface = pos + cur;
					if (!bs.GetPixel(inSurface.x, inSurface.y)) {
						bs.PutPixel(inSurface.x, inSurface.y, true);
						s.PutPixel(inSurface.x, inSurface.y, c);
					}
				}
			}
		}
	}

	const Surface& GetImage()
	{
		return s;
	}
private:
	BoolSurface bs;
	Surface s;
};