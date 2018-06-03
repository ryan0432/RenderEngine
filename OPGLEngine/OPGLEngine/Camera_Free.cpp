#include "Camera_Free.h"
#include "Input.h"

Camera_Free::Camera_Free(std::string camName, vec3 camPos, CamType camType,
						 float fovY, float aspectRatio,
						 float left, float right, float bottom, float top,
						 float nearClip, float farClip,
						 vec3 lookAtFrom, vec3 lookAtTo, vec3 camUpAxis)
{
	setName(camName);
	setPosition(camPos);
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
}

Camera_Free::~Camera_Free()
{
}

void Camera_Free::Update()
{
	CORE::Input* input = CORE::Input::getInstance();

	auto&	rgtVec = getTransform()[0];
	auto	lftVec = getTransform()[0] * -1.0f;
	auto&	upVec = getTransform()[1];
	auto	dnVec = getTransform()[1] * -1.0f;
	auto&	fwardVec = getTransform()[2];
	auto	bwardVec = getTransform()[2] * -1.0f;


	updateProjectionView();
}
