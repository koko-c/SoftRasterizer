#ifndef TRIANGLE_BY_CK
#define TRIANGELE_BY_CK
#include "BoundingBox.h"
#include "Vertex.h"
struct Triangle
{
	VertexOut vertex[3];
	AABB2D boundingBox;
};

#endif
