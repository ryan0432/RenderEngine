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
using glm::mat4;

Application3D::Application3D()
{
}


Application3D::~Application3D()
{
}

bool Application3D::Startup()
{
	//Setup the point for camera to look at
	camPos = vec3(0, 10, 10);
	camViewPoint = vec3(0, 0, 0);
	camUpAxis = vec3(0, 1 ,0);
	view = glm::lookAt(camPos, camViewPoint, camUpAxis);
	//camera's transform is the inverse of view space transform
	camTransform = glm::inverse(view);
	//camera's translation speed
	camTransSpd = 7.0f;

	//Set background colour
	SetBackgroundColour(0.3f, 0.3f, 0.3f, 1.0f);
	//Setup the Gimos's min/max drawing ability
	Gizmos::create(50000, 50000, 50000, 50000);

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

	auto&	rgtVec = camTransform[0];
	vec4	lftVec = camTransform[0] * -1.0f;
	auto&	upVec = camTransform[1];
	vec4	dnVec = camTransform[1] * -1.0f;
	auto&	fwardVec = camTransform[2];
	vec4	bwardVec = camTransform[2] * -1.0f;
	
	if (input->isKeyDown(CORE::INPUT_KEY_A))
	{
		camTransform[3] += lftVec * camTransSpd * GetDeltaTime();
	}
	if (input->isKeyDown(CORE::INPUT_KEY_D))
	{
		camTransform[3] += rgtVec * camTransSpd * GetDeltaTime();
	}


	if (input->isKeyDown(CORE::INPUT_KEY_W))
	{
		camTransform[3] += upVec * camTransSpd * GetDeltaTime();
	}
	if (input->isKeyDown(CORE::INPUT_KEY_S))
	{
		camTransform[3] += dnVec * camTransSpd * GetDeltaTime();
	}

	static double startXpos;
	static double startYPos;

	if (input->isKeyDown(CORE::INPUT_KEY_LEFT_ALT))
	{
		if (input->wasMouseButtonPressed(0))
		{
			glfwGetCursorPos(GetWindowPtr(), &startXpos, &startYPos);
		}
		else if(input->isMouseButtonDown(0))
		{
			double xpos, ypos;
			glfwGetCursorPos(GetWindowPtr(), &xpos, &ypos);

			double xOffset = xpos - startXpos;
			double yOffset = ypos - startYPos;

			startXpos = xpos;
			startYPos = ypos;

			std::cout << xOffset << " " << yOffset << std::endl;

			auto rotX = glm::angleAxis(0.1f * (float)xOffset * GetDeltaTime(), glm::vec3{ 0, 1, 0 });
			auto rotY = glm::angleAxis(0.1f * (float)yOffset * GetDeltaTime(), glm::vec3{ 1, 0, 0 });

			camTransform = camTransform * glm::mat4_cast(rotX * rotY);
		}
	}

	view = glm::inverse(camTransform);
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
