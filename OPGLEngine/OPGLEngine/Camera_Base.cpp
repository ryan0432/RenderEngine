#include "Camera_Base.h"

Camera_Base::Camera_Base(std::string camName, vec3 camPos,
						 float fovY, float aspectRatio,
						 float nearClip, float farClip,
						 vec3 lookAtFrom, vec3 lookAtTo, vec3 camUpAxis)
{
	setName(camName);
	setPosition(camPos);
	setPerspective(fovY, aspectRatio, nearClip, farClip);
	setLookAt(lookAtFrom, lookAtTo, camUpAxis);
	setTransform(glm::inverse(m_viewTransform));
}

Camera_Base::~Camera_Base()
{
}

void Camera_Base::setPosition(vec3 pos)
{
	m_camTransform[3][0] = (float)pos.x;
	m_camTransform[3][1] = (float)pos.y;
	m_camTransform[3][2] = (float)pos.z;
}

void Camera_Base::setPerspective(float fovY, float aspectRatio, float nearClip, float farClip)
{
	m_projectionTransform = glm::perspective(fovY, aspectRatio, nearClip, farClip);
}

void Camera_Base::setLookAt(vec3 lookAtFrom, vec3 lookAtTo, vec3 camUpAxis)
{
	m_viewTransform = glm::lookAt(lookAtFrom, lookAtTo, camUpAxis);
}



