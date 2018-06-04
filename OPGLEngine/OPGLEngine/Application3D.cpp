#include "Application3D.h"
#include <gl_core_4_4.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <Gizmos.h>
#include "Input.h"
#include "Camera_Free.h"

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
	m_camName = "myCam";
	m_fovy = glm::pi<float>() * 0.25f;
	m_aspectRatio = (float)GetWindowWidth() / (float)GetWindowHeight();
	m_left = -10.0f;
	m_right = 10.0f;
	m_bottom = -10.0f;
	m_top = 10.0f;
	m_nearClip = 0.1f;
	m_farClip = 1000.0f;
	m_lookAtFrom = vec3(2.0f, 2.0f, 10.0f);
	m_lookAtTo = vec3(0, 0, 0);
	m_camUpAxis = vec3(0, 1 ,0);

	myCam = new Camera_Free(m_camName, PERSP, m_fovy, m_aspectRatio,
		m_left, m_right, m_bottom, m_top, m_nearClip, m_farClip,
		m_lookAtFrom, m_lookAtTo, m_camUpAxis);

#pragma region oldCamInitialize

	//view = glm::lookAt(camPos, camViewPoint, camUpAxis);
	////initialize the projection range for Gizmos
	////projection = glm::perspective(glm::pi<float>() * 0.25f,
	////	(float)GetWindowWidth() / (float)GetWindowHeight(),
	////	0.1f, 1000.0f);

	//projection = glm::ortho(-50.0f, 50.0f,
	//						-30.0f, 30.0f,
	//						0.1f, 1000.0f);

	////camera's transform is the inverse of view space transform
	//camTransform = glm::inverse(view);
	////camera's translation speed
	//camTransSpd = 7.0f;

#pragma endregion

	//Set background colour
	SetBackgroundColour(0.3f, 0.3f, 0.3f, 1.0f);
	//Setup the Gimos's min/max drawing ability
	Gizmos::create(50000, 50000, 50000, 50000);

	return true;
}

void Application3D::Update()
{
	//Clear screen for rendering new frame
	ClearScreen();

	//Input Section
	CORE::Input* input = CORE::Input::getInstance();
	if (input->isKeyDown(CORE::INPUT_KEY_ESCAPE)) { SetRunning(false); }

	myCam->Update(GetDeltaTime());

	std::cout << "Pos X: " << myCam->getTransform()[3][0] << std::endl;
	std::cout << "Pos Y: " << myCam->getTransform()[3][1] << std::endl;
	std::cout << "Pos Z: " << myCam->getTransform()[3][2] << std::endl;
	system("cls");

#pragma region oldCamInput

	//auto&	rgtVec = camTransform[0];
	//auto	lftVec = camTransform[0] * -1.0f;
	//auto&	upVec = camTransform[1];
	//auto	dnVec = camTransform[1] * -1.0f;
	//auto&	fwardVec = camTransform[2];
	//auto	bwardVec = camTransform[2] * -1.0f;

	//if (input->isKeyDown(CORE::INPUT_KEY_A))
	//{
	//	camTransform[3] += lftVec * camTransSpd * GetDeltaTime();
	//}

	//if (input->isKeyDown(CORE::INPUT_KEY_D))
	//{
	//	camTransform[3] += rgtVec * camTransSpd * GetDeltaTime();
	//}

	//if (input->isKeyDown(CORE::INPUT_KEY_W))
	//{
	//	camTransform[3] += upVec * camTransSpd * GetDeltaTime();
	//}

	//if (input->isKeyDown(CORE::INPUT_KEY_S))
	//{
	//	camTransform[3] += dnVec * camTransSpd * GetDeltaTime();
	//}

	//static double startXpos;
	//static double startYPos;

	//if (input->isKeyDown(CORE::INPUT_KEY_LEFT_ALT))
	//{
	//	if (input->wasMouseButtonPressed(0))
	//	{
	//		glfwGetCursorPos(GetWindowPtr(), &startXpos, &startYPos);
	//	}
	//	else if (input->isMouseButtonDown(0))
	//	{
	//		double xpos, ypos;
	//		glfwGetCursorPos(GetWindowPtr(), &xpos, &ypos);

	//		double xOffset = xpos - startXpos;
	//		double yOffset = ypos - startYPos;

	//		startXpos = xpos;
	//		startYPos = ypos;

	//		std::cout << xOffset << " " << yOffset << std::endl;

	//		auto rotX = glm::angleAxis(0.1f * (float)xOffset * GetDeltaTime(), glm::vec3{ 0, 1, 0 });
	//		auto rotY = glm::angleAxis(0.1f * (float)yOffset * GetDeltaTime(), glm::vec3{ 1, 0, 0 });

	//		camTransform = camTransform * glm::mat4_cast(rotX * rotY);
	//	}
	//}

	////update the view by inversing camera transform
	//view = glm::inverse(camTransform);

#pragma endregion

}

void Application3D::Render()
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

	//assign draw area
	Gizmos::draw(myCam->Render());
}

void Application3D::Shutdown()
{
	Gizmos::destroy();
	delete myCam;
}
