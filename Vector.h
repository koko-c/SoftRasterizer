#ifndef VECTOR_BY_CK
#define VECTOR_BY_CK
#include<windows.h>
namespace Math
{
	class Vec4;

	class Vec2
	{
	public:
		Vec2(float _x, float _y) :x(_x), y(_y) {}
		Vec2() :x(0), y(0) {}

		inline Vec2 operator+(const Vec2& rhs)const { return Vec2(x + rhs.x, y + rhs.y); }
		inline void  operator+=(const Vec2& rhs) { *this = *this + rhs; }
		inline Vec2 operator-(const Vec2& rhs)const { return Vec2(x - rhs.x, y - rhs.y); }
		inline Vec2 operator-()const { return Vec2(-x, -y); }
		inline void  operator-=(const Vec2& rhs) { *this = *this - rhs; }
		inline float operator*(const Vec2& rhs)const { return x*rhs.x+y*rhs.y; }
		inline Vec2 operator*(float scalar)const { return Vec2(x * scalar, y * scalar); }
		inline void operator*=(float scalar) { *this = *this * scalar; }
		inline Vec2 operator/(float scalar)const { return Vec2(x / scalar, y / scalar); }
		inline void operator/=(float scalar) { *this = *this / scalar; }
		inline Vec2 operator+(float scalar)const { return Vec2(scalar + x, scalar + y); }
		inline void  operator+=(float scalar) { *this = *this + scalar; }
		inline Vec2 operator-(float scalar)const { return Vec2(x - scalar, y - scalar); }
		inline void operator-=(float scalar) { *this = *this - scalar; }
	public:
		float x;
		float y;
	};

	inline Vec2 operator*(float scalar,const Vec2& v) { return v * scalar; }
	inline Vec2 operator+(float scalar,const Vec2& v) { return v + scalar; }
	inline Vec2 operator-(float scalar,const Vec2& v) { return -v + scalar; }

	class Vec3
	{
	public:
		Vec3(float _x, float _y, float _z) :x(_x), y(_y), z(_z) {}
		Vec3() : x(0), y(0), z(0) {}
		Vec3(float scalar) : x(scalar), y(scalar), z(scalar) {}
		Vec3(const Vec4& v);

		inline Vec3 operator+(const Vec3& rhs)const
		{
			return Vec3(x + rhs.x, y + rhs.y, z + rhs.z);
		}
		inline Vec3 operator-(const Vec3& rhs)const
		{
			return Vec3(x - rhs.x, y - rhs.y, z - rhs.z);
		}
		inline Vec3 operator-()const
		{
			return Vec3(-x, -y, -z);
		}
		inline void operator+=(const Vec3& rhs)
		{
			*this = *this + rhs;
		}
		inline void operator-=(const Vec3& rhs)
		{
			*this = *this - rhs;
		}
		inline float operator*(const Vec3& rhs)const
		{
			return x * rhs.x + y * rhs.y + z * rhs.z;
		}
		
		inline void operator*=(float scalar)
		{
			*this = *this * scalar;
		}
		inline Vec3 operator*(float scalar)const
		{
			return Vec3(scalar * x, scalar * y, scalar * z);
		}
		inline Vec3 operator/(float scalar)const
		{
			float divScalar = 1 / scalar;
			return Vec3(x * divScalar, y * divScalar, z * divScalar);
		}
		inline void operator/=(float scalar)
		{
			*this = *this / scalar;
		}
		inline float& operator[](int i)
		{
			switch (i)
			{
			case 0:
				return x;
			case 1:
				return y;
			case 2:
				return z;
			default:
				MessageBox(0, L"Vec3³¬³öË÷Òý·¶Î§", 0, 0);
				exit(0);
			}
		}
		inline Vec4 toVec4(float _w)const;
	public:
		float x;
		float y;
		float z;
	};

	class Vec4
	{
	public:
		Vec4(float _x, float _y, float _z, float _w = 1) :x(_x), y(_y), z(_z), w(_w) {}
		Vec4() :x(0), y(0), z(0), w(0) {}
		Vec4(const Vec3& vec3, float _w)
		{
			x = vec3.x;
			y = vec3.y;
			z = vec3.z;
			w = _w;
		}

		inline Vec3 toVec3()
		{
			return Vec3(x, y, z);
		}
		inline float& operator[](int i)
		{
			switch (i)
			{
			case 0:
				return x;
			case 1:
				return y;
			case 2:
				return z;
			case 3:
				return w;
			default:
				MessageBox(0, L"Vec4³¬³öË÷Òý·¶Î§", 0, 0);
				exit(0);
			}
		}
		
		Vec4 operator/(float scalar)const
		{
			return Vec4(x / scalar, y / scalar, z / scalar, w / scalar);
		}
		void operator/=(float scalar)
		{
			*this = *this / scalar;
		}
		Vec4 operator+(const Vec4& rhs)const
		{
			return Vec4(x + rhs.x, y + rhs.y, z + rhs.z, w + rhs.w);
		}
		void operator+=(const Vec4& rhs)
		{
			*this = *this + rhs;
		}
		Vec4 operator-(const Vec4& rhs)const
		{
			return Vec4(x - rhs.x, y - rhs.y, z - rhs.z, w - rhs.w);
		}
		void operator-=(const Vec4& rhs)
		{
			*this = *this - rhs;
		}
		Vec4 operator*(float scalar)const
		{
			return Vec4(x * scalar, y * scalar, z * scalar, w * scalar);
		}
		void operator*=(float scalar)
		{
			*this = *this * scalar;
		}
		float operator*(const Vec4& v)const
		{
			return x * v.x + y * v.y + z * v.z + w * v.w;
		}
	public:
		float x;
		float y;
		float z;
		float w;
	};
	inline Vec3 operator*(float scalar, const Vec3& rhs)
	{
		return rhs * scalar;
	}

	inline Vec3::Vec3(const Vec4& v) :x(v.x), y(v.y), z(v.z) {}

	inline Vec4 Vec3::toVec4(float _w)const
	{
		return Vec4(*this, _w);
	}
	inline Vec4 operator*(float scalar, const Vec4& v)
	{
		return v * scalar;
	}
}
#endif // !VECTOR