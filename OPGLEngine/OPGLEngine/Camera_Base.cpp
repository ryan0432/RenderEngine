#include "Camera_Base.h"
#include "Application.h"

Camera_Base::Camera_Base()
{
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
	m_camType = PERSP;
	m_perspSpec["fovY"] = fovY;
	m_perspSpec["aspectRatio"] = aspectRatio;
	m_perspSpec["nearClip"] = nearClip;
	m_perspSpec["farClip"] = farClip;
}

void Camera_Base::setOrthography(float left, float right, float bottom, float top,
								 float nearClip, float farClip)
{
	m_projectionTransform = glm::ortho(left, right, bottom, top, nearClip, farClip);
	m_camType = ORTHO;
	m_orthoSpec["left"] = left;
	m_orthoSpec["right"] = right;
	m_orthoSpec["bottom"] = bottom;
	m_orthoSpec["top"] = top;
	m_orthoSpec["nearClip"] = nearClip;
	m_orthoSpec["farClip"] = farClip;
}

void Camera_Base::setLookAt(vec3 lookAtFrom, vec3 lookAtTo, vec3 camUpAxis)
{
	m_viewTransform = glm::lookAt(lookAtFrom, lookAtTo, camUpAxis);
}

void Camera_Base::switchCamType()
{
	switch (m_camType)
	{
		case PERSP:
		{
			setOrthography( m_orthoSpec["left"],
							m_orthoSpec["right"],
							m_orthoSpec["bottom"],
							m_orthoSpec["top"],
							m_orthoSpec["nearClip"],
							m_orthoSpec["farClip"] );
			break;
		}

		case ORTHO:
		{
			setPerspective( m_perspSpec["fovY"],
							m_perspSpec["aspectRatio"],
							m_perspSpec["nearClip"],
							m_perspSpec["farClip"] );
			break;
		}
	}
}



