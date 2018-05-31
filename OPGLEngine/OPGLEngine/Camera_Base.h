#pragma once
#ifndef CAM_BASE_H
#define CAM_BASE_H

#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <string>

enum CamType
{
	ORTHO,
	PERSP
};

using glm::mat4;
using glm::vec3;

class Camera_Base
{
public:
	Camera_Base(std::string camName, vec3 camPos,
				float fovY, float aspectRatio,
				float nearClip, float farClip,
				vec3 lookAtFrom, vec3 lookAtTo, vec3 camUpAxis);

	virtual ~Camera_Base();
	virtual void Update() = 0;
	inline void setName(std::string camName) { m_camName = camName; }
	void setPosition(vec3 pos);
	void setPerspective(float fovY, float aspectRatio, float nearClip, float farClip);
	void setOrthography();
	void setLookAt(vec3 lookAtFrom, vec3 lookAtTo, vec3 camUpAxis);
	inline void setTransform(mat4 newCamTransform) { m_camTransform = newCamTransform; }
	inline std::string getName() { return m_camName; }
	inline mat4 getTransform() { return m_camTransform; }
	inline mat4 getViewTransform() { return m_viewTransform; }
	inline mat4 getProjection() { return m_projectionTransform; }
	inline mat4 getProjectionView() { return m_projectionViewTransfrom; }
	inline mat4 render() { return m_projectionViewTransfrom; }

protected:
	inline void updateProjectionView()
	{
		m_viewTransform = glm::inverse(m_camTransform);
		m_projectionViewTransfrom = m_viewTransform * m_projectionTransform;
	}
	
private:
	std::string m_camName;
	mat4 m_camTransform;
	mat4 m_viewTransform;
	mat4 m_projectionTransform;
	mat4 m_projectionViewTransfrom;
};

#endif

