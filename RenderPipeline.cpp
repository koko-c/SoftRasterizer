#include "RenderPipeline.h"
#include<iostream>
RenderPipeline::RenderPipeline(Screen screen, UINT swapChainCount)
{
	mScreen = screen;
	mpFrameBuffer = std::make_unique<FrameBuffer>(screen, swapChainCount);
	mDispaly = std::make_unique<Display>(screen);
	mRenderItems = std::make_unique<std::vector<RenderItem>>();
	mIsSetRenderItems = false;
}

std::vector<Triangle>RenderPipeline::ScreenMap(const std::vector<VertexOut>& vertices, const std::vector<UINT>& indices)
{
	std::vector<Triangle> triangles;
	for (UINT i = 0; i < indices.size(); i += 3)
	{
		Triangle triangle;
		for (int index = 0; index < 3; ++index)
		{
			triangle.vertex[index] = vertices[indices[i + index]];
			auto posH = triangle.vertex[index].posH;
			//透视除法
			posH /= posH.w;
			triangle.vertex[index].posH = posH;
			//映射到屏幕
			triangle.vertex[index].screenPos = Math::Vec2(posH.x * mScreen.width / 2 + mScreen.width / 2,
				posH.y * (-mScreen.height) / 2 + mScreen.height / 2);
		}
		triangles.push_back(triangle);
	}
	return triangles;
}

void RenderPipeline::TriangleSetup(std::vector<Triangle>& triangles)
{
	for (UINT i = 0; i < triangles.size(); ++i)
	{
		float minX = Math::Min(
			triangles[i].vertex[0].screenPos.x,
			triangles[i].vertex[1].screenPos.x,
			triangles[i].vertex[2].screenPos.x);
		float minY = Math::Min(
			triangles[i].vertex[0].screenPos.y,
			triangles[i].vertex[1].screenPos.y,
			triangles[i].vertex[2].screenPos.y);
		float maxX = Math::Max(
			triangles[i].vertex[0].screenPos.x,
			triangles[i].vertex[1].screenPos.x,
			triangles[i].vertex[2].screenPos.x);
		float maxY = Math::Max(
			triangles[i].vertex[0].screenPos.y,
			triangles[i].vertex[1].screenPos.y,
			triangles[i].vertex[2].screenPos.y);
		minX = Math::clamp(minX, 0, mScreen.width - 1);
		minY = Math::clamp(minY, 0, mScreen.height - 1);
		maxX = Math::clamp(maxX, 0, mScreen.width - 1);
		maxY = Math::clamp(maxY, 0, mScreen.height - 1);

		triangles[i].boundingBox.min = Math::Vec2(minX, minY);
		triangles[i].boundingBox.max = Math::Vec2(maxX, maxY);
	}
}

void RenderPipeline::TriangleTraverse(const std::vector<Triangle>& triangles, std::vector<Fragment>& fragments)
{
	//检测每一个三角形覆盖了多少像素点,并且通过插值输出这些像素点
	for (UINT i = 0; i < triangles.size(); ++i)
	{
		Triangle triangle = triangles[i];
		Math::Vec2 triangleScreenPos[] = { triangle.vertex[0].screenPos + 0.5,triangle.vertex[1].screenPos + 0.5,triangle.vertex[2].screenPos + 0.5 };
		for (auto m = static_cast<UINT> (triangle.boundingBox.min.y); m <= triangle.boundingBox.max.y; ++m)
		{
			for (auto n = static_cast<UINT> (triangle.boundingBox.min.x); n <= triangle.boundingBox.max.x; ++n)
			{
				auto p = Math::Vec2(static_cast<float>(m), static_cast<float>(n)) + 0.5;
				if (Math::isInTheTriangle(p, triangleScreenPos))//这里并没有使用任何反走样的技术
				{
					//利用公式法求出重心坐标
					auto a = triangleScreenPos[0];
					auto b = triangleScreenPos[1];
					auto c = triangleScreenPos[2];

					float alpha = (-(p.x - b.x) * (c.y - b.y) + (p.y - b.y) * (c.x - b.x)) / (-(a.x - b.x) * (c.y - b.y) + (a.y - b.y) * (c.x - b.x));
					float beta = (-(p.x - c.x) * (a.y - c.y) + (p.y - c.y) * (a.x - c.x)) / (-(b.x - c.x) * (a.y - c.y) + (b.y - c.y) * (a.x - c.x));
					float gama = 1 - alpha - beta;

					//透视矫正
					auto Za = triangle.vertex[0].posV.z;
					auto Zb = triangle.vertex[1].posV.z;
					auto Zc = triangle.vertex[2].posV.z;

					auto Zt = 1 / (alpha / Za + beta / Zb + gama / Zc);

					Fragment frag = Zt * (alpha * triangle.vertex[0] / Za + beta * triangle.vertex[1] / Zb + gama * triangle.vertex[2] / Zc);
					frag.screenPos = p - 0.5;//屏幕坐标别拿去插值!!!!!!
					fragments.push_back(frag);
				}
			}
		}
	}
}

void RenderPipeline::Merge(const std::vector<Fragment>& pixels)
{
	//深度测试
	for (UINT i = 0; i < pixels.size(); ++i)
	{
		Math::Vec2 screenPos = pixels[i].screenPos;
		//注意由于我们使用的是右手坐标系,所以深度值全为负数,越靠近相机的深度值越大
		if (pixels[i].posH.z > mpFrameBuffer->GetDepth(screenPos))
		{
			mpFrameBuffer->SetDepthBuffer(screenPos, pixels[i].posH.z);
			mpFrameBuffer->SetCurentBackBufferColor(screenPos, pixels[i].color);
		}
	}
}

void RenderPipeline::DrawIndex(RenderItem& renderItem)
{
	mpFrameBuffer->Refrash();
	//顶点着色器:依次完成了model transform->view transform->perspective transform,同时也把法线从局部坐标系转换到了世界坐标系
	std::vector<VertexOut> vsOutput;
	VertexShader(renderItem.GetVertices(), renderItem.GetWorld(), vsOutput);

	//屏幕映射:首先进行了透视除法,把物体从齐次裁剪空间变换到了NDC空间,然后再从NDC空间变换到了屏幕空间
	std::vector<Triangle> triangles;
	triangles = ScreenMap(vsOutput, renderItem.GetIndices());

	//光栅化阶段:
		//主要分为两个阶段 
			//1.三角形设置:计算光栅化一个三角形所需要的条件,如边界条件,这里我们计算了在视口范围内的三角形的AABB包围盒
			//2.三角形遍历:使用扫描法计算被三角形覆盖的像素点,然后对位于三角形内部的像素点使用重心坐标和透视矫正来进行插值计算

	TriangleSetup(triangles);
	std::vector<Fragment> fragments;
	TriangleTraverse(triangles, fragments);

	//像素着色器:逐像素计算颜色

	PixelShader(fragments);

	//合并:把绘制了的颜色与backbuffer中的颜色进行合并,深度测试发生在这一阶段
	Merge(fragments);

}

void RenderPipeline::DisplayImage()
{
	std::vector<Math::Color> colors;

	mpFrameBuffer->GetCurrentBackBuffer(colors);

	mDispaly->Present(colors);
}

void RenderPipeline::SetRenderItems(const std::vector<RenderItem>& renderItems)
{
	mRenderItems->insert(mRenderItems->end(), renderItems.begin(), renderItems.end());
	mIsSetRenderItems = true;
}

void RenderPipeline::Run()
{
	Initial();
	if (mIsSetRenderItems == false)
	{
		MessageBox(0, L"没有设置渲染项", 0, 0);
		exit(0);
	}

	/*while (true)
	{
		for (UINT i = 0; i < mRenderItems->size(); ++i)
		{
			DrawIndex(mRenderItems->at(i));
		}
		DisplayImage();
	}*/
	for (UINT i = 0; i < mRenderItems->size(); ++i)
	{
		DrawIndex(mRenderItems->at(i));
	}
	DisplayImage();
}

float RenderPipeline::AspectRation()
{
	return mScreen.width / mScreen.height;
}