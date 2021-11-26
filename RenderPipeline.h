#ifndef RENDER_PIPELINE_BY_CK
#define RENDER_PIPELINE_BY_CK
#include "Color.h"
#include "Screen.h"
#include "ZBuffer.h"
#include <memory>
#include "Math.h"
#include "Vertex.h"
#include "FrameBuffer.h"
#include "RenderItems.h"
#include "BoundingBox.h"
#include "Triangle.h"
#include "Display.h"
class RenderPipeline
{
public:
	RenderPipeline(Screen screen, UINT swapChainCount = 2);

	virtual void VertexShader(const std::vector<VertexIn>& input, const Math::Matrix4& toWorld, std::vector<VertexOut>& output) = 0;//可编程

	virtual void PixelShader(std::vector<Fragment>& input) = 0;//可编程

	virtual void Initial() = 0;

	void SetRenderItems(const std::vector<RenderItem>& renderItems);

	void Run();

	float AspectRation();

private:

	void DrawIndex(RenderItem& renderItem);

	std::vector<Triangle> ScreenMap(const std::vector<VertexOut>& vertices, const std::vector<UINT>& indices);//包含透视除法和屏幕映射

	/*光栅化阶段*/
	void TriangleSetup(std::vector<Triangle>& triangles);

	void TriangleTraverse(const std::vector<Triangle>& triangles, std::vector<Fragment>& fragments);//找出位于三角形内部的所有像素并进行插值

	void Merge(const std::vector<Fragment>& pixels);//合并颜色,执行深度测试

	void DisplayImage();

private:

	Screen mScreen;//我们的屏幕从左上角开始,一个点对应一个像素
	std::unique_ptr<FrameBuffer> mpFrameBuffer;
	std::unique_ptr<Display> mDispaly;
	std::unique_ptr<std::vector<RenderItem>> mRenderItems;
	bool mIsSetRenderItems;
};

#endif
