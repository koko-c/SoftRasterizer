#ifndef VERTEX_BY_CK
#define VERTEX_BY_CK
#include "Vector.h"
#include "Color.h"
struct VertexIn
{
	VertexIn() :posL(Math::Vec3(0, 0, 0)), normalL(Math::Vec3(1, 0, 0)), color(Math::Color(255, 0, 0, 255)), uv(Math::Vec2(0, 0)) {}
	VertexIn(Math::Vec3 pos, Math::Vec3 normal, Math::Color _color, Math::Vec2 _uv) :posL(pos), normalL(normal), color(_color), uv(_uv) {}
	Math::Vec3 posL;
	Math::Vec3 normalL;
	Math::Color color;
	Math::Vec2 uv;
};
struct VertexOut
{
	Math::Vec4 posH;
	Math::Vec3 posL;
	Math::Vec3 posW;
	Math::Vec3 posV;
	Math::Vec3 normalW;
	Math::Color color;
	Math::Vec2 uv;

	Math::Vec2 screenPos;

	//”√”⁄≤Â÷µ
	VertexOut operator+(const VertexOut& rhs)
	{
		VertexOut v;
		v.posH = posH + rhs.posH;
		v.posL = posL + rhs.posL;
		v.posW = posW + rhs.posW;
		v.posV = posV + rhs.posV;
		v.normalW = normalW + rhs.normalW;
		v.color = color + rhs.color;
		v.uv = uv + rhs.uv;
		v.screenPos = screenPos + rhs.screenPos;
		
		return v;
	}

	VertexOut operator*(float scalar)const
	{
		VertexOut v;
		v.posH = posH * scalar;
		v.posL = posL * scalar;
		v.posW = posW * scalar;
		v.posV = posV * scalar;
		v.normalW = normalW * scalar;
		v.color = color * scalar;
		v.uv = uv * scalar;
		v.screenPos = screenPos * scalar;

		return v;
	}
	VertexOut operator/(float scalar)const
	{
		VertexOut v;
		v.posH = posH / scalar;
		v.posL = posL / scalar;
		v.posW = posW / scalar;
		v.posV = posV / scalar;
		v.normalW = normalW / scalar;
		v.color = color / scalar;
		v.uv = uv / scalar;
		v.screenPos = screenPos / scalar;

		return v;
	}
};
inline VertexOut operator*(float scalar, const VertexOut& v)
{
	return v * scalar;
}
using Fragment = VertexOut;
#endif // !VERTEX_BY_CK
