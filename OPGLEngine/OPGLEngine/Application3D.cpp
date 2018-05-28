#include "Application3D.h"
#include <gl_core_4_4.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <Gizmos.h>
#include "Input.h"

using CORE::Gizmos;
using glm::vec3;
using glm::vec4;
using glm::mat3;

Application3D::Application3D()
{
}


Application3D::~Application3D()
{
}

bool Application3D::Startup()
{
	//Set background colour
	SetBackgroundColour(0.3f, 0.3f, 0.3f, 1.0f);
	//Setup the Gimos's min/max drawing ability
	Gizmos::create(50000, 50000, 50000, 50000);
	//Setup the point for camera to look at
	view = glm::lookAt(vec3(10, 10, 10), vec3(0), vec3(0, 1, 0));

	return true;
}

void Application3D::Update()
{	
	//clear Gizmos buffer every frame
	Gizmos::clear();

	//setup Gizmos's default transform
	Gizmos::addTransform(glm::mat4(1));

	//setup white colour value
	vec4 white(1);

	//setup black colour value
	vec4 black(0, 0, 0, 1);

	//draw grid by margin of 1 on x and z axis
	for (int i = 0; i < 21; ++i)
	{
		Gizmos::addLine(vec3(-10 + i, 0, 10), vec3(-10 + i, 0, -10), i == 10 ? white : black);
		Gizmos::addLine(vec3(10, 0, -10 + i), vec3(-10, 0, -10 + i), i == 10 ? white : black);
	}

	//Input Section
	CORE::Input* input = CORE::Input::getInstance();
	if (input->isKeyDown(CORE::INPUT_KEY_ESCAPE)) { SetRunning(false); }
}

void Application3D::Render()
{
	//Clear screen for rendering new frame
	ClearScreen();
	//update the projection range for Gizmos
	projection = glm::perspective(glm::pi<float>() * 0.25f,
								  (float)GetWindowWidth() / (float)GetWindowHeight(),
								  0.1f, 1000.0f);

	//assign draw area
	Gizmos::draw(projection * view);
}

void Application3D::Shutdown()
{
	Gizmos::destroy();
}
