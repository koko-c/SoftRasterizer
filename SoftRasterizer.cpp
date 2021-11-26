#include "SoftRasterizer.h"

void SoftRasterizer::VertexShader(const std::vector<VertexIn>& input, const Math::Matrix4& toWorld, std::vector<VertexOut>& output)
{
	for (UINT i = 0; i < input.size(); ++i)
	{
		VertexOut v;
		v.posL = input[i].posL;
		v.posW = (const_cast<Math::Matrix4&>(toWorld) * input[i].posL.toVec4(1)).toVec3();
		v.posV = (view * v.posW.toVec4(1)).toVec3();
		v.posH = proj * v.posV.toVec4(1);
		v.color = input[i].color;
		v.normalW = const_cast<Math::Matrix4&>(toWorld) * input[i].normalL.toVec4(0);
		v.uv = input[i].uv;

		output.push_back(v);
	}
}
void SoftRasterizer::PixelShader(std::vector<Fragment>& fragments)
{
	//这里只是渲染一个三角形,并且颜色已经给出,就不再做处理
}
void SoftRasterizer::Initial()
{
	view = Math::GetViewMatrix(Math::Vec3(0, 0, 5), Math::Vec3(0, 0, 0), Math::Vec3(0, 1, 0));
	proj = Math::GetPerspectiveProjMatrix(Math::toRadians(90), AspectRation(), -1.0f, -1000.0f);

	RenderItem triangle;

	std::vector<VertexIn> vertices;
	vertices.push_back(VertexIn(Math::Vec3(-3, -3, 0), Math::Vec3(0, 0, 0), Math::Color(255, 0, 0, 255), Math::Vec2(0, 0)));
	vertices.push_back(VertexIn(Math::Vec3(+3, -3, 0), Math::Vec3(0, 0, 0), Math::Color(0, 255, 0, 255), Math::Vec2(0, 0)));
	vertices.push_back(VertexIn(Math::Vec3(+0, +3, 0), Math::Vec3(0, 0, 0), Math::Color(0, 0, 255, 255), Math::Vec2(0, 0)));

	triangle.SetVertices(vertices);

	std::vector<UINT> indices;
	indices.push_back(0);
	indices.push_back(1);
	indices.push_back(2);
	triangle.SetIndices(indices);

	triangle.SetWorld(Math::Matrix4::indentity());

	std::vector<RenderItem> renderItems;
	renderItems.push_back(triangle);
	SetRenderItems(renderItems);

}