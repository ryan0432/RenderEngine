#pragma once
#include "Application.h"
class Application3D : public CORE::Application
{
public:
	Application3D();
	virtual ~Application3D();
	virtual bool Startup();
	virtual void Update();
	virtual void Render();
	virtual void Shutdown();
};

