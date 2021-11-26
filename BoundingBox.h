#ifndef BOUNDING_BOX_BY_CK
#define BOUNDING_BOX_BY_CK
#include "Vector.h"
struct AABB2D
{
	Math::Vec2 min;
	Math::Vec2 max;
};
struct AABB3D
{
	Math::Vec3 min;
	Math::Vec3 max;
};

#endif
