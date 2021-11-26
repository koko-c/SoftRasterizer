#ifndef RENDERITEM_BY_CK
#define RENDERITEM_BY_CK
#include "Math.h"
#include "Vertex.h"
#include<string>
#include <vector>

class RenderItem
{
public:
	RenderItem()
	{
		mWorld = Math::Matrix4::indentity();
		mVertices.clear();
		mIndices.clear();
	}
	RenderItem(std::string name, const std::vector<VertexIn>& vertices, const std::vector<UINT>& indices, Math::Matrix4 world)
	{
		mName = name;
		SetVertices(vertices);
		SetIndices(indices);
		SetWorld(world);
	}
	Math::Matrix4 GetWorld()const
	{
		return mWorld;
	}
	void SetWorld(const Math::Matrix4& world)
	{
		mWorld = world;
	}
	void SetVertices(const std::vector<VertexIn>& vertices)
	{
		mVertices.insert(mVertices.end(), vertices.begin(), vertices.end());
	}
	std::vector<VertexIn>& GetVertices()
	{
		return mVertices;
	}
	void SetIndices(const std::vector<UINT>& indices)
	{
		mIndices.insert(mIndices.end(), indices.begin(), indices.end());
	}
	std::vector<UINT>& GetIndices()
	{
		return mIndices;
	}
public:
	std::string mName;
private:
	Math::Matrix4 mWorld;
	std::vector<VertexIn> mVertices;
	std::vector<UINT> mIndices;
};
#endif
