#ifndef SCREEN_BY_CK

#define SCREEN_BY_CK

struct Screen
{
	Screen():width(800),height(600) {}
	Screen(float _width, float _height) :width(_width), height(_height) {}
	float width;
	float height;
};
#endif // !SCREEN_BY_CK