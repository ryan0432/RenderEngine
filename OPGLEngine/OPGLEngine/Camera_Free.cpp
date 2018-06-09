#define GLM_ENABLE_EXPERIMENTAL
#include "Camera_Free.h"
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/transform.hpp>
#include <GLFW/glfw3.h>
#include "Application.h"
#include "Input.h"

Camera_Free::Camera_Free(std::string camName, CamType camType, CORE::Application* app,
						 float fovY, 
						 float left, float right, float bottom, float top,
						 float nearClip, float farClip,
						 vec3 lookAtFrom, vec3 lookAtTo, vec3 camUpAxis)
{
	setName(camName);
	setPosition(lookAtFrom);
	setCamType(camType);
	float aspectRatio = (float)app->GetWindowWidth() / (float)app->GetWindowHeight();

	switch (camType)
	{
		case PERSP:
		{
			setPerspective(fovY, aspectRatio, nearClip, farClip);
			setOrthoCamSpec("left", left);
			setOrthoCamSpec("right", right);
			setOrthoCamSpec("bottom", bottom);
			setOrthoCamSpec("top", top);
			setOrthoCamSpec("nearClip", nearClip);
			setOrthoCamSpec("farClip", farClip);
			break;
		}

		case ORTHO:
		{
			setOrthography(left, right, bottom, top, nearClip, farClip);
			setPerspCamSpec("fovY", fovY);
			setPerspCamSpec("aspectRatio", aspectRatio);
			setPerspCamSpec("nearClip", nearClip);
			setPerspCamSpec("farClip", farClip);
			break;
		}
	}
	
	setLookAt(lookAtFrom, lookAtTo, camUpAxis);
	setTransform(glm::inverse(getViewTransform()));

	moveSpeed = 4.0f;
	rotationSpeed = 0.3f;
}

Camera_Free::~Camera_Free()
{
}

void Camera_Free::Update(float deltaTime, CORE::Application* app)
{
	CORE::Input* input = CORE::Input::getInstance();

	auto&	rgtVec = getTransform()[0];
	auto	lftVec = getTransform()[0] * -1.0f;
	auto&	upVec = getTransform()[1];
	auto	dnVec = getTransform()[1] * -1.0f;
	auto&	bwardVec = getTransform()[2];
	auto	fwardVec = getTransform()[2] * -1.0f;

	if (input->isKeyDown(CORE::INPUT_KEY_A))
	{
		setPosition(getTransform()[3] += lftVec * moveSpeed * deltaTime);
	}

	if (input->isKeyDown(CORE::INPUT_KEY_D))
	{
		setPosition(getTransform()[3] += rgtVec * moveSpeed * deltaTime);
	}

	if (input->isKeyDown(CORE::INPUT_KEY_W))
	{
		setPosition(getTransform()[3] += upVec * moveSpeed * deltaTime);
	}

	if (input->isKeyDown(CORE::INPUT_KEY_S))
	{
		setPosition(getTransform()[3] += dnVec * moveSpeed * deltaTime);
	}

	if (input->isKeyDown(CORE::INPUT_KEY_Q))
	{
		setPosition(getTransform()[3] += bwardVec * moveSpeed * deltaTime);
	}

	if (input->isKeyDown(CORE::INPUT_KEY_E))
	{
		setPosition(getTransform()[3] += fwardVec * moveSpeed * deltaTime);
	}

	if (input->wasKeyPressed(CORE::INPUT_KEY_Z))
	{
		switchCamType();
	}

	if (input->isKeyDown(CORE::INPUT_KEY_F))
	{
		glm::quat rot(-getTransform()[1] * deltaTime * rotationSpeed);
		setTransform(glm::mat4_cast(rot) * getTransform());
	}

	if (input->isKeyDown(CORE::INPUT_KEY_H))
	{
		glm::quat rot(getTransform()[1] * deltaTime * rotationSpeed);
		setTransform(glm::mat4_cast(rot) * getTransform());
	}

	if (input->isKeyDown(CORE::INPUT_KEY_T))
	{
		glm::quat rot(-getTransform()[0] * deltaTime * rotationSpeed);
		setTransform(glm::mat4_cast(rot) * getTransform());
	}

	if (input->isKeyDown(CORE::INPUT_KEY_G))
	{
		glm::quat rot(getTransform()[0] * deltaTime * rotationSpeed);
		setTransform(glm::mat4_cast(rot) * getTransform());
	}

	if (input->isKeyDown(CORE::INPUT_KEY_R))
	{
		glm::quat rot(-getTransform()[2] * deltaTime * rotationSpeed);
		setTransform(glm::mat4_cast(rot) * getTransform());
	}

	if (input->isKeyDown(CORE::INPUT_KEY_Y))
	{
		glm::quat rot(getTransform()[2] * deltaTime * rotationSpeed);
		setTransform(glm::mat4_cast(rot) * getTransform());
	}

	if (input->isKeyDown(CORE::INPUT_KEY_LEFT_ALT) || input->isKeyDown(CORE::INPUT_KEY_RIGHT_ALT))
	{
		static double startRotPosX;
		static double startRotPosY;
		static double startMovPosX;
		static double startMovPosY;
		static double startZomPosX;
		static double startZomPosY;

		if (input->wasMouseButtonPressed(0))
		{
			glfwGetCursorPos(app->GetWindowPtr(), &startRotPosX, &startRotPosY);
		}
		else if (input->isMouseButtonDown(0))
		{
			double newPosX;
			double newPosY;

			glfwGetCursorPos(app->GetWindowPtr(), &newPosX, &newPosY);

			double offsetX = newPosX - startRotPosX;
			double offsetY = newPosY - startRotPosY;

			startRotPosX = newPosX;
			startRotPosY = newPosY;

			
			glm::quat rot1(-(float)offsetX * getTransform()[1] * deltaTime * 0.03f);
			glm::quat rot0(-(float)offsetY * getTransform()[0] * deltaTime * 0.03f);

			setTransform(glm::mat4_cast(rot1) * getTransform());
			setTransform(glm::mat4_cast(rot0) * getTransform());

			setTransform(mat4(1) * getTransform());
		}

		if (input->wasMouseButtonPressed(2))
		{
			glfwGetCursorPos(app->GetWindowPtr(), &startMovPosX, &startMovPosY);
		}
		else if (input->isMouseButtonDown(2))
		{
			double newPosX;
			double newPosY;

			glfwGetCursorPos(app->GetWindowPtr(), &newPosX, &newPosY);

			double offsetX = newPosX - startMovPosX;
			double offsetY = newPosY - startMovPosY;

			startMovPosX = newPosX;
			startMovPosY = newPosY;

			setPosition(getTransform()[3] -= (float)offsetX * rgtVec * 0.15f * deltaTime);
			setPosition(getTransform()[3] -= (float)offsetY * dnVec * 0.15f * deltaTime);
		}

		if (input->wasMouseButtonPressed(1))
		{
			glfwGetCursorPos(app->GetWindowPtr(), &startZomPosX, &startZomPosY);
		}
		else if (input->isMouseButtonDown(1))
		{
			double newPosX;
			double newPosY;

			glfwGetCursorPos(app->GetWindowPtr(), &newPosX, &newPosY);

			double offsetX = newPosX - startZomPosX;
			double offsetY = newPosY - startZomPosY;

			startZomPosX = newPosX;
			startZomPosY = newPosY;

			setPosition(getTransform()[3] -= (float)offsetX * bwardVec * 0.15f * deltaTime);
			setPosition(getTransform()[3] -= (float)offsetY * fwardVec * 0.15f * deltaTime);
		}
	}

	updateProjectionView();
}
