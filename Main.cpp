#include "SoftRasterizer.h"
#include<iostream>
#include "Print.h"
using namespace Math;
#undef main

int  main()
{
	SoftRasterizer app(600, 600);

	app.Run();

	system("pause");

	return 0;
}
