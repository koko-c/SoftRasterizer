#ifndef MATRIX_BY_CK
#define MATRIX_BY_CK
#include "Vector.h"
namespace Math
{
	class Matrix4;
	class Matrix3
	{
	public:
		Matrix3(Vec3 v0, Vec3 v1, Vec3 v2)/* 列对列,不是列对行 */
		{
			m_data[0] = Vec3(v0.x, v1.x, v2.x);
			m_data[1] = Vec3(v0.y, v1.y, v2.y);
			m_data[2] = Vec3(v0.z, v1.z, v2.z);
		}
		Matrix3()
		{
			m_data[0] = Vec3(0);
			m_data[1] = Vec3(0);
			m_data[2] = Vec3(0);
		}
		Matrix3(Matrix4& m4);
		static Matrix3 indentity()
		{
			Vec3 v0(1, 0, 0);
			Vec3 v1(0, 1, 0);
			Vec3 v2(0, 0, 1);

			return Matrix3(v0, v1, v2);
		}
		inline Vec3 v0()
		{
			return Vec3(m_data[0][0], m_data[1][0], m_data[2][0]);
		}
		inline Vec3 v1()
		{
			return Vec3(m_data[0][1], m_data[1][1], m_data[2][1]);
		}
		inline Vec3 v2()
		{
			return Vec3(m_data[0][2], m_data[1][2], m_data[2][2]);
		}
		inline void v0(const Vec3& v)
		{
			m_data[0].x = v.x;
			m_data[1].x = v.y;
			m_data[2].x = v.z;
		}
		inline void v1(const Vec3& v)
		{
			m_data[0].y = v.x;
			m_data[1].y = v.y;
			m_data[2].y = v.z;
		}
		inline void v2(const Vec3& v)
		{
			m_data[0].z = v.x;
			m_data[1].z = v.y;
			m_data[2].z = v.z;
		}
		inline Vec3& operator[](int i)
		{
			return m_data[i];
		}
		inline Matrix3 operator+(Matrix3& rhs)
		{
			return Matrix3(this->v0() + rhs.v0(), this->v1() + rhs.v1(), this->v2() + rhs.v2());
		}
		inline void operator+=(Matrix3& rhs)
		{
			*this = *this + rhs;
		}
		inline Matrix3 operator-(Matrix3& rhs)
		{
			return Matrix3(this->v0() - rhs.v0(), this->v1() - rhs.v1(), this->v2() - rhs.v2());
		}
		inline void operator-=(Matrix3& rhs)
		{
			*this = *this - rhs;
		}
		inline Matrix3 operator*(Matrix3& rhs)
		{
			Vec3 v0((*this)[0] * rhs.v0(), (*this)[1] * rhs.v0(), (*this)[2] * rhs.v0());
			Vec3 v1((*this)[0] * rhs.v1(), (*this)[1] * rhs.v1(), (*this)[2] * rhs.v1());
			Vec3 v2((*this)[0] * rhs.v2(), (*this)[1] * rhs.v2(), (*this)[2] * rhs.v2());

			return Matrix3(v0, v1, v2);
		}
		inline Matrix3 operator*(float scalar)
		{
			return Matrix3(this->v0() * scalar, this->v1() * scalar, this->v2() * scalar);
		}
		inline Matrix3 operator/(float scalar)
		{
			float divScalar = 1 / scalar;
			return Matrix3(this->v0() * divScalar, this->v1() * divScalar, this->v2() * divScalar);
		}
		inline void operator/=(float scalar)
		{
			*this = *this / scalar;
		}
		inline float trace()
		{
			return m_data[0][0] + m_data[1][1] + m_data[2][2];
		}
		inline Vec3 operator*(const Vec3& rhs)
		{
			return Vec3((*this)[0]* rhs, (*this)[1] * rhs, (*this)[2]* rhs);
		}
		inline Matrix4 toMatrix4();
	public:
		Vec3 m_data[3];
	};

	class Matrix4
	{
	public:

		Matrix4(Vec4 v0, Vec4 v1, Vec4 v2, Vec4 v3)/* 列对列,不是列对行 */
		{
			m_data[0] = Vec4(v0.x, v1.x, v2.x, v3.x);
			m_data[1] = Vec4(v0.y, v1.y, v2.y, v3.y);
			m_data[2] = Vec4(v0.z, v1.z, v2.z, v3.z);
			m_data[3] = Vec4(v0.w, v1.w, v2.w, v3.w);
		}
		Matrix4(Matrix3&& m3)
		{
			this->v0(Vec4(m3.v0(), 0));
			this->v1(Vec4(m3.v1(), 0));
			this->v2(Vec4(m3.v2(), 0));
			this->v3(Vec4(Vec3(0), 1));
		}
		Matrix4(Matrix3& m3)
		{
			this->v0(Vec4(m3.v0(), 0));
			this->v1(Vec4(m3.v1(), 0));
			this->v2(Vec4(m3.v2(), 0));
			this->v3(Vec4(Vec3(0), 1));
		}
		Matrix4()
		{
			m_data[0] = Vec3(0).toVec4(0);
			m_data[1] = Vec3(0).toVec4(0);
			m_data[2] = Vec3(0).toVec4(0);
			m_data[3] = Vec3(0).toVec4(0);
		}

		static Matrix4 indentity()
		{
			return Matrix4(Matrix3::indentity());
		}

		inline Vec4 v0()
		{
			return Vec4(m_data[0][0], m_data[1][0], m_data[2][0], m_data[3][0]);
		}
		inline Vec4 v1()
		{
			return Vec4(m_data[0][1], m_data[1][1], m_data[2][1], m_data[3][1]);
		}
		inline Vec4 v2()
		{
			return Vec4(m_data[0][2], m_data[1][2], m_data[2][2], m_data[3][2]);
		}
		inline Vec4 v3()
		{
			return Vec4(m_data[0][3], m_data[1][3], m_data[2][3], m_data[3][3]);
		}
		inline void v0(const Vec4& v)
		{
			m_data[0].x = v.x;
			m_data[1].x = v.y;
			m_data[2].x = v.z;
			m_data[3].x = v.w;
		}
		inline void v1(const Vec4& v)
		{
			m_data[0].y = v.x;
			m_data[1].y = v.y;
			m_data[2].y = v.z;
			m_data[3].y = v.w;
		}
		inline void v2(const Vec4& v)
		{
			m_data[0].z = v.x;
			m_data[1].z = v.y;
			m_data[2].z = v.z;
			m_data[3].z = v.w;
		}
		inline void v3(const Vec4& v)
		{
			m_data[0].w = v.x;
			m_data[1].w = v.y;
			m_data[2].w = v.z;
			m_data[3].w = v.w;
		}
		inline Vec4& operator[](int i)
		{
			return m_data[i];
		}
		inline float trace()
		{
			return m_data[0][0] + m_data[1][1] + m_data[2][2] + m_data[3][3];
		}
		inline Matrix3 toMatrix3()
		{
			return Matrix3(*this);
		}
		inline Matrix4 operator*(Matrix4& rhs)
		{
			Vec4 v0((*this)[0] * rhs.v0(), (*this)[1] * rhs.v0(), (*this)[2] * rhs.v0(), (*this)[3] * rhs.v0());
			Vec4 v1((*this)[0] * rhs.v1(), (*this)[1] * rhs.v1(), (*this)[2] * rhs.v1(), (*this)[3] * rhs.v1());
			Vec4 v2((*this)[0] * rhs.v2(), (*this)[1] * rhs.v2(), (*this)[2] * rhs.v2(), (*this)[3] * rhs.v2());
			Vec4 v3((*this)[0] * rhs.v3(), (*this)[1] * rhs.v3(), (*this)[2] * rhs.v3(), (*this)[3] * rhs.v3());

			return Matrix4(v0, v1, v2, v3);
		}
		inline Vec4 operator*(const Vec4& v)
		{
			return Vec4((*this)[0] * v, (*this)[1] * v, (*this)[2] * v, (*this)[3] * v);
		}
	public:
		Vec4 m_data[4];
	};

	inline Matrix3 operator*(float scalar, Matrix3& rhs)
	{
		return rhs * scalar;
	}
	inline Matrix4 Matrix3::toMatrix4()
	{
		return Matrix4(*this);
	}
	inline Matrix3::Matrix3(Matrix4& m4)
	{
		this->v0(m4.v0());
		this->v1(m4.v1());
		this->v2(m4.v2());
	}
}

#endif