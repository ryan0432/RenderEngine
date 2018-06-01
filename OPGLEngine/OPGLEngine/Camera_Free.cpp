#include "Camera_Free.h"

Camera_Free::Camera_Free(std::string camName, vec3 camPos, CamType camType,
						 float fovY, float aspectRatio,
						 float nearClip, float farClip,
						 vec3 lookAtFrom, vec3 lookAtTo, vec3 camUpAxis)
{
	setName(camName);
	setPosition(camPos);
	setPerspective(fovY, aspectRatio, nearClip, farClip);
	setLookAt(lookAtFrom, lookAtTo, camUpAxis);
	setTransform(glm::inverse(getViewTransform()));
	setCamType(PERSP);
}

Camera_Free::Camera_Free(std::string camName, vec3 camPos, CamType camType,
						 float left, float right, float bottom, float top,
						 float nearClip, float farClip,
						 vec3 lookAtFrom, vec3 lookAtTo, vec3 camUpAxis)
{
	setName(camName);
	setPosition(camPos);
	setOrthography(left, right, bottom, top, nearClip, farClip);
	setLookAt(lookAtFrom, lookAtTo, camUpAxis);
	setTransform(glm::inverse(getViewTransform()));
	setCamType(ORTHO);
}

Camera_Free::~Camera_Free()
{
}

void Camera_Free::Update()
{
	updateProjectionView();
}
