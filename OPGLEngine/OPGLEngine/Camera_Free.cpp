#include "Camera_Free.h"
#include "Input.h"

Camera_Free::Camera_Free(std::string camName, CamType camType,
						 float fovY, float aspectRatio,
						 float left, float right, float bottom, float top,
						 float nearClip, float farClip,
						 vec3 lookAtFrom, vec3 lookAtTo, vec3 camUpAxis)
{
	setName(camName);
	setPosition(lookAtFrom);
	setCamType(camType);

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

	moveSpeed = 7.0f;
	rotationSpeed = 0.5f;
}

Camera_Free::~Camera_Free()
{
}

void Camera_Free::Update(float deltaTime)
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

	if (input->wasKeyPressed(CORE::INPUT_KEY_G))
	{
		switchCamType();
	}

	updateProjectionView();
}
