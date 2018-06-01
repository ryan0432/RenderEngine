#include "Camera_Base.h"
#include "Application.h"

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

void Camera_Base::setOrthography(float left, float right, float bottom, float top, float nearClip, float farClip)
{
	m_projectionTransform = glm::ortho(left, right, bottom, top, nearClip, farClip);
}

void Camera_Base::setLookAt(vec3 lookAtFrom, vec3 lookAtTo, vec3 camUpAxis)
{
	m_viewTransform = glm::lookAt(lookAtFrom, lookAtTo, camUpAxis);
}

void Camera_Base::switchCamType()
{
	if (m_camType == ORTHO)
	{
		//int width = CORE::Applicaion::GetWindowWidth();
		setCamType(PERSP);
	}
	else if (m_camType == PERSP)
	{
		setCamType(ORTHO);
	}
}



