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
			//͸�ӳ���
			posH /= posH.w;
			triangle.vertex[index].posH = posH;
			//ӳ�䵽��Ļ
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
	//���ÿһ�������θ����˶������ص�,����ͨ����ֵ�����Щ���ص�
	for (UINT i = 0; i < triangles.size(); ++i)
	{
		Triangle triangle = triangles[i];
		Math::Vec2 triangleScreenPos[] = { triangle.vertex[0].screenPos + 0.5,triangle.vertex[1].screenPos + 0.5,triangle.vertex[2].screenPos + 0.5 };
		for (auto m = static_cast<UINT> (triangle.boundingBox.min.y); m <= triangle.boundingBox.max.y; ++m)
		{
			for (auto n = static_cast<UINT> (triangle.boundingBox.min.x); n <= triangle.boundingBox.max.x; ++n)
			{
				auto p = Math::Vec2(static_cast<float>(m), static_cast<float>(n)) + 0.5;
				if (Math::isInTheTriangle(p, triangleScreenPos))//���ﲢû��ʹ���κη������ļ���
				{
					//���ù�ʽ�������������
					auto a = triangleScreenPos[0];
					auto b = triangleScreenPos[1];
					auto c = triangleScreenPos[2];

					float alpha = (-(p.x - b.x) * (c.y - b.y) + (p.y - b.y) * (c.x - b.x)) / (-(a.x - b.x) * (c.y - b.y) + (a.y - b.y) * (c.x - b.x));
					float beta = (-(p.x - c.x) * (a.y - c.y) + (p.y - c.y) * (a.x - c.x)) / (-(b.x - c.x) * (a.y - c.y) + (b.y - c.y) * (a.x - c.x));
					float gama = 1 - alpha - beta;

					//͸�ӽ���
					auto Za = triangle.vertex[0].posV.z;
					auto Zb = triangle.vertex[1].posV.z;
					auto Zc = triangle.vertex[2].posV.z;

					auto Zt = 1 / (alpha / Za + beta / Zb + gama / Zc);

					Fragment frag = Zt * (alpha * triangle.vertex[0] / Za + beta * triangle.vertex[1] / Zb + gama * triangle.vertex[2] / Zc);
					frag.screenPos = p - 0.5;//��Ļ�������ȥ��ֵ!!!!!!
					fragments.push_back(frag);
				}
			}
		}
	}
}

void RenderPipeline::Merge(const std::vector<Fragment>& pixels)
{
	//��Ȳ���
	for (UINT i = 0; i < pixels.size(); ++i)
	{
		Math::Vec2 screenPos = pixels[i].screenPos;
		//ע����������ʹ�õ�����������ϵ,�������ֵȫΪ����,Խ������������ֵԽ��
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
	//������ɫ��:���������model transform->view transform->perspective transform,ͬʱҲ�ѷ��ߴӾֲ�����ϵת��������������ϵ
	std::vector<VertexOut> vsOutput;
	VertexShader(renderItem.GetVertices(), renderItem.GetWorld(), vsOutput);

	//��Ļӳ��:���Ƚ�����͸�ӳ���,���������βü��ռ�任����NDC�ռ�,Ȼ���ٴ�NDC�ռ�任������Ļ�ռ�
	std::vector<Triangle> triangles;
	triangles = ScreenMap(vsOutput, renderItem.GetIndices());

	//��դ���׶�:
		//��Ҫ��Ϊ�����׶� 
			//1.����������:�����դ��һ������������Ҫ������,��߽�����,�������Ǽ��������ӿڷ�Χ�ڵ������ε�AABB��Χ��
			//2.�����α���:ʹ��ɨ�跨���㱻�����θ��ǵ����ص�,Ȼ���λ���������ڲ������ص�ʹ�����������͸�ӽ��������в�ֵ����

	TriangleSetup(triangles);
	std::vector<Fragment> fragments;
	TriangleTraverse(triangles, fragments);

	//������ɫ��:�����ؼ�����ɫ

	PixelShader(fragments);

	//�ϲ�:�ѻ����˵���ɫ��backbuffer�е���ɫ���кϲ�,��Ȳ��Է�������һ�׶�
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
		MessageBox(0, L"û��������Ⱦ��", 0, 0);
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