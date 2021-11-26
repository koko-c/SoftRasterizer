#ifndef Z_BUFFER_BY_CK
#define Z_BUFFER_BY_CK
#include "Screen.h"
#include <vector>
#include <windows.h>
#include "Math.h"
#include <memory>
struct ZBuffer
{
	ZBuffer(Screen screen)
	{
		mScreen = screen;
		mZBuffer.resize(static_cast<unsigned int>(screen.height * screen.width), static_cast<float>(-INT_MAX));
	}
	void SetDepth(Math::Vec2 xy, float depth)
	{
		mZBuffer[at(xy)] = depth;
	}
	void GetDepthBuffer(std::vector<float>& depthbuffer)
	{
		depthbuffer.insert(depthbuffer.end(), mZBuffer.begin(), mZBuffer.end());
	}
	float GetDepth(Math::Vec2 xy)
	{
		return mZBuffer[at(xy)];
	}
	void Refrash()
	{
		mZBuffer.clear();
		mZBuffer.resize(static_cast<unsigned int>(mScreen.height * mScreen.width), static_cast<float>(-INT_MAX));
	}
private:
	int at(Math::Vec2 xy)
	{
		if (xy.x<0 || xy.x>(mScreen.width - 1) || xy.y<0 || xy.y>(mScreen.height - 1))
		{
			MessageBox(0, L"超出深度缓冲区域", 0, 0);
			exit(0);
		}
		return static_cast<int>((mScreen.height - xy.y - 1) * mScreen.height + (mScreen.width - 1 - xy.x));
	}
private:
	Screen mScreen;
	std::vector<float> mZBuffer;
};
#endif
