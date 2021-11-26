#ifndef MATH_BY_CK
#define MATH_BY_CK
#include "Color.h"
#include "Vector.h"
#include "Matrix.h"
#include <cmath>

const float pi = static_cast<float>(3.1415926);

namespace Math
{
	inline float toRadians(float degree)
	{
		return degree / static_cast<float>(180.0) * pi;
	}
	inline float dot(const Vec2& v1, const Vec2& v2)
	{
		return v1.x * v2.x + v1.y * v2.y;
	}
	inline float dot(const Vec3& v1, const Vec3& v2)
	{
		return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
	}
	inline float dot(const Vec4& v1, const Vec4& v2)
	{
		return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w;
	}
	inline float length_square(const Vec3& v)
	{
		return dot(v, v);
	}
	inline float length_square(const Vec2& v)
	{
		return dot(v, v);
	}
	inline float length(const Vec3& v)
	{
		return sqrtf(length_square(v));
	}

	inline float length(const Vec2 v)
	{
		return sqrtf(length_square(v));
	}
	inline Vec3 normalize(const Vec3& v)
	{
		return const_cast<Vec3&>(v) / length(v);
	}
	inline Vec3 cross(const Vec3& v1, const Vec3& v2)
	{
		return Vec3(
			v1.y * v2.z - v1.z * v2.y,
			v1.z * v2.x - v1.x * v2.z,
			v1.x * v2.y - v1.y * v2.x
		);
	}
	inline Matrix4 transpose(Matrix4& m)
	{
		return Matrix4(m[0], m[1], m[2], m[3]);
	}
	inline Matrix3 transpose(Matrix3& m)
	{
		return Matrix3(m[0], m[1], m[2]);
	}

	inline  float clamp(float value, float min, float max)
	{
		if (min > max)
		{
			MessageBox(0, L"ERROR:clamp输入错误", 0, 0);
			exit(0);
		}
		value = value < max ? value : max;
		value = value > min ? value : min;
		return value;
	}
	inline float lerp(float value1, float value2, float t)
	{
		t = clamp(t, 0.0f, 1.0f);
		return (value2 - value1) * t + value1;
	}
	inline float Max(float a, float b, float c)
	{
		return max(max(a, b), c);
	}
	inline float Max(float a, float b)
	{
		return max(a, b);
	}
	inline float Min(float a, float b, float c)
	{
		return min(min(a, b), c);
	}

	inline float Min(float a, float b)
	{
		return min(a, b);
	}
	inline bool isInTheTriangle(Vec2 point, Vec2 triangles[])
	{
		Math::Vec3 a = Math::Vec3(triangles[0].x, triangles[0].y, 0);
		Math::Vec3 b = Math::Vec3(triangles[1].x, triangles[1].y, 0);
		Math::Vec3 c = Math::Vec3(triangles[2].x, triangles[2].y, 0);

		Math::Vec3 p = Math::Vec3(point.x, point.y, 0);

		Math::Vec3 cp = p - c;
		Math::Vec3 ca = a - c;
		Math::Vec3 ap = p - a;
		Math::Vec3 ab = b - a;
		Math::Vec3 bp = p - b;
		Math::Vec3 bc = c - b;

		return (cross(ca, cp).z >= 0 && cross(ab, ap).z >= 0 && cross(bc, bp).z >= 0) ||
			(cross(ca, cp).z <= 0 && cross(ab, ap).z <= 0 && cross(bc, bp).z <= 0);
	}
	inline Matrix4 GetOrthogonalProjMatrix(float l, float r, float t, float b, float n, float f)/*x,y,z都映射到了[-1,1]*/
	{
		return Matrix4(
			Vec4(2 / (r - l), 0, 0, 0),
			Vec4(0, 2 / (t - b), 0, 0),
			Vec4(0, 0, 2 / (f - n), 0),
			Vec4(-(r + l) / (r - l), -(t + b) / (t - b), -(f + n) / (f - n), 1)
		);
	}
	inline Matrix4 GetPerspectiveProjMatrix(float fovRadians, float aspectRatio, float n, float f)
		/* rtr4的所示的透视投影矩阵会把近平面投影到-1,而远平面投影到1,所以我们把第四行取负,来更改这种取反 */
	{
		float t = tanf(fovRadians / 2) * abs(n);
		float b = -t;
		float r = aspectRatio * t;
		float l = -r;

		return Matrix4(
			Vec4(2 * n / (r - l), 0, 0, 0),
			Vec4(0, 2 * n / (t - b), 0, 0),
			Vec4(-(r + l) / (r - l), -(t + b) / (t - b), (f + n) / (f - n), -1),//把原本的+1取负变成-1
			Vec4(0, 0, -2 * f * n / (f - n), 0));
	}
	inline Matrix4 GetViewMatrix(const Vec3& eye, const Vec3& target, const Vec3& up)
	{
		Vec3 viewUp = normalize(up);
		Vec3 zAxis = -(target - eye);//看向的是-Z轴
		zAxis /= length(zAxis);

		Vec3 xAxis = cross(viewUp, zAxis);
		Vec3 yAxis = cross(zAxis, xAxis);
		return Matrix4(
			xAxis.toVec4(0),
			yAxis.toVec4(0),
			zAxis.toVec4(0),
			(-eye).toVec4(1));
	}
}

#endif