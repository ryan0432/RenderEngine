#pragma once
#include "Application.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>

using glm::mat4;

class Application3D : public CORE::Application
{
public:
	Application3D();
	virtual ~Application3D();
	virtual bool Startup();
	virtual void Update();
	virtual void Render();
	virtual void Shutdown();

private:
	//setup the viewpoint
	mat4 view;
	//setup the projection range for Gizmos
	mat4 projection;
};

