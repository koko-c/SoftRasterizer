#ifndef SOFT_RASTERIZER_BY_CK
#define SOFT_RASTERIZER_BY_CK
#include "RenderPipeline.h"

class SoftRasterizer :public RenderPipeline
{
public:
	SoftRasterizer(float screenWidth, float screenHeight) :RenderPipeline(Screen(screenWidth, screenHeight)) {}

	virtual void VertexShader(const std::vector<VertexIn>& input, const Math::Matrix4& toWorld, std::vector<VertexOut>& output)override;
	virtual void PixelShader(std::vector<Fragment>& input)override;
	virtual void Initial()override;
public:
	Math::Matrix4 view;
	Math::Matrix4 proj;
};

#endif // !SOFT_RASTERIZER_BY_CK
