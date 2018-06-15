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
	//Set [Projection Transform] to glm::perspective()
	m_projectionTransform = glm::perspective(fovY, aspectRatio, nearClip, farClip);
	//Set camera type enum
	m_camType = PERSP;
	//store perspective projection specs in a std::map
	m_perspSpec["fovY"] = fovY;
	m_perspSpec["aspectRatio"] = aspectRatio;
	m_perspSpec["nearClip"] = nearClip;
	m_perspSpec["farClip"] = farClip;
}

void Camera_Base::setOrthography(float left, float right, float bottom, float top,
								 float nearClip, float farClip)
{
	//Set [Projection Transform] to glm::ortho()
	m_projectionTransform = glm::ortho(left, right, bottom, top, nearClip, farClip);
	//Set camera type enum
	m_camType = ORTHO;
	//Store orthography projection specs in a std::map
	m_orthoSpec["left"] = left;
	m_orthoSpec["right"] = right;
	m_orthoSpec["bottom"] = bottom;
	m_orthoSpec["top"] = top;
	m_orthoSpec["nearClip"] = nearClip;
	m_orthoSpec["farClip"] = farClip;
}

void Camera_Base::setLookAt(vec3 lookAtFrom, vec3 lookAtTo, vec3 camUpAxis)
{
	//Set View Transform with glm::lookAt()
	m_viewTransform = glm::lookAt(lookAtFrom, lookAtTo, camUpAxis);
}

vec3 Camera_Base::getPosition()
{
	vec3 pos = {m_camTransform[3][0],
				m_camTransform[3][1],
				m_camTransform[3][2]};
	return pos;
}

void Camera_Base::switchCamType()
{
	//Switch based on current camera type
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



