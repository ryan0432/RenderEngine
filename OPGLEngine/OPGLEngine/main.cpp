#include "Application3D.h"

int main()
{
	auto app = new Application3D();
	app->Run(1280, 720, "RenderDemo", false, "");
	delete app;
	return 0;
}