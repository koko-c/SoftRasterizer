#ifndef FRAMEBUFFER_BY_CK
#define FRAMEBUFFER_BY_CK
#include "ColorBuffer.h"
#include "ZBuffer.h"
#include <vector>
class FrameBuffer
{
public:
	FrameBuffer(Screen screen, UINT swapChainCount = 2)
	{
		mSwapChainCount = swapChainCount;
		mCurrentBackBufferIndex = 0;
		mScreen = screen;
		for (UINT i = 0; i < swapChainCount; ++i)
		{
			mColorBuffers.push_back(std::make_unique<ColorBuffer>(screen, Math::Color(0, 0, 0, 1)));
		}
		mZBuffer = std::make_unique<ZBuffer>(screen);
	}
	UINT GetCurentBackBufferIndex()
	{
		return mCurrentBackBufferIndex;
	}
	void SetCurentBackBufferColor(Math::Vec2 xy, Math::Color color)
	{
		mColorBuffers[mCurrentBackBufferIndex]->StoreColor(xy, color);
	}
	void GetCurrentBackBuffer(std::vector<Math::Color>& colors)
	{
		mColorBuffers[mCurrentBackBufferIndex]->GetColorBuffer(colors);
	}
	void SetDepthBuffer(Math::Vec2 xy, float depth)
	{
		mZBuffer->SetDepth(xy, depth);
	}
	void GetDepthBuffer(std::vector<float>& depthbuffer)
	{
		mZBuffer->GetDepthBuffer(depthbuffer);
	}
	float GetDepth(Math::Vec2 xy)
	{
		return mZBuffer->GetDepth(xy);
	}
	void Refrash()
	{
		mZBuffer->Refrash();
		mCurrentBackBufferIndex = (mCurrentBackBufferIndex + 1) % mSwapChainCount;
		mColorBuffers[mCurrentBackBufferIndex]->Refrash();
	}
private:
	std::vector<std::unique_ptr<ColorBuffer>> mColorBuffers;
	std::unique_ptr<ZBuffer> mZBuffer;
	UINT mCurrentBackBufferIndex;
	Screen mScreen;
	UINT mSwapChainCount;
};

#endif
