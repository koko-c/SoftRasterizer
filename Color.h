#ifndef COLOR_BY_CK
#define COLOR_BY_CK
#include "Math.h"
typedef unsigned char uint8_t;

namespace Math
{
	class Color
	{
	public:
		Color(float _r, float _g, float _b, float _a = 255) :
			r(static_cast<uint8_t>(_r)), 
			g(static_cast<uint8_t>(_g)),
			b(static_cast<uint8_t>(_b)),
			a(static_cast<uint8_t>(_a)) {}
		Color() :r(0), g(0), b(0), a(255) {}

		inline Color operator +(const Color& rhs)const
		{
			return Color(static_cast<float>(r + rhs.r), static_cast<float>( g + rhs.g), static_cast<float>(b + rhs.b));
		}
		inline void operator+=(const Color& rhs)
		{
			*this = *this + rhs;
		}
		inline Color operator*(float scalar)const
		{
			return Color(r * scalar, g * scalar, b * scalar, a * scalar);
		}
		inline Color operator/(float scalar)const
		{
			float divScalar = 1 / scalar;
			return *this * divScalar;
		}
	public:
		uint8_t b;
		uint8_t g;
		uint8_t r;
		uint8_t a;
	};
	inline Color operator*(float scalar, const Color& color)
	{
		return color * scalar;
	}
}
#endif // !COLOR_BY_CK