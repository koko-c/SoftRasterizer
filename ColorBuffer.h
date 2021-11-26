#ifndef COLOR_BUFFER_BY_CK
#define COLOR_BUFFER_BY_CK
#include "Screen.h"
#include<memory>
#include "Color.h"
#include <vector>
#include "Math.h"
class ColorBuffer
{
public:
	ColorBuffer(Screen screen, Math::Color backgroundColor)
	{
		mScreen = screen;
		mBackgroundColor = backgroundColor;
		mColorBuffer.resize(static_cast<unsigned int>(mScreen.width * mScreen.height), backgroundColor);
	}
	void StoreColor(Math::Vec2 xy, Math::Color color)
	{
		mColorBuffer[at(xy)] = color;
	}
	void GetColorBuffer(std::vector<Math::Color>& colors)
	{
		colors.insert(colors.end(), mColorBuffer.begin(), mColorBuffer.end());
	}
	void Refrash()
	{
		mColorBuffer.clear();
		mColorBuffer.resize(static_cast<unsigned int>(mScreen.width * mScreen.height), mBackgroundColor);
	}
private:
	int at(Math::Vec2 xy)
	{
		if (xy.x<0 || xy.x>(mScreen.width - 1) || xy.y<0 || xy.y>(mScreen.height - 1))
		{
			MessageBox(0, L"超出颜色缓冲区域", 0, 0);
			exit(0);
		}
		return  static_cast<int>((mScreen.height - xy.y - 1) * mScreen.height + (mScreen.width - 1 - xy.x));//弄得这么复杂是为了让图像上下颠倒回去
	}
private:
	Screen mScreen;
	std::vector<Math::Color> mColorBuffer;
	Math::Color mBackgroundColor;
};

#endif // !FRAME_BUFFER_BY_CK
