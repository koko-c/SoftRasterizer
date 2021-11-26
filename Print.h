#ifndef PRINT_BY_CK
#define PRINT_BY_CK
#include "Math.h"
using namespace Math;
#include<iostream>
using std::cout;
using std::endl;

std::ostream& operator<<(std::ostream& out, Color c)
{
	cout << "color: " << endl << " r = " << c.r << " g = " << c.g << " b = " << c.b << " a = " << c.a << endl;
	return out;
}

std::ostream& operator<<(std::ostream& out, Vec3 v)
{
	cout << "Vec3: " << endl << "x = " << v.x << " y = " << v.y << " z = " << v.z << endl;
	return out;
}

std::ostream& operator<<(std::ostream& out, Vec4 v)
{
	cout << "Vec4:" << endl << "x = " << v.x << " y = " << v.y << " z = " << v.z << " w =" << v.w << endl;
	return out;

}

std::ostream& operator<<(std::ostream& out, Matrix3 m)
{
	cout << "Matrix3:" << endl;
	cout << m[0][0] << " " << m[0][1] << " " << m[0][2] << endl;
	cout << m[1][0] << " " << m[1][1] << " " << m[1][2] << endl;
	cout << m[2][0] << " " << m[2][1] << " " << m[2][2] << endl;
	return out;
}
std::ostream& operator<<(std::ostream& out, Matrix4 m)
{
	cout << "Matrix4:" << endl;
	cout << m[0][0] << " " << m[0][1] << " " << m[0][2] << " " << m[0][3] << endl;
	cout << m[1][0] << " " << m[1][1] << " " << m[1][2] << " " << m[1][3] << endl;
	cout << m[2][0] << " " << m[2][1] << " " << m[2][2] << " " << m[2][3] << endl;
	cout << m[3][0] << " " << m[3][1] << " " << m[3][2] << " " << m[3][3] << endl;
	return out;
}
std::ostream& operator<<(std::ostream& out, Vec2 v)
{
	cout << "Vec2: " << endl << "x = " << v.x << " y= " << v.y << endl;
	return out;
}

#endif // !PRINT_BY_CK


