#pragma once
#ifndef CAM_BASE_H
#define CAM_BASE_H

#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <string>
#include <map>

using glm::mat4;
using glm::vec3;

enum CamType
{
	PERSP,
	ORTHO
};

class Camera_Base
{
public:
	Camera_Base();
	virtual ~Camera_Base();
	virtual void Update() = 0;
	inline void setName(std::string camName) { m_camName = camName; }
	void setPosition(vec3 pos);
	void setPerspective(float fovY, float aspectRatio, float nearClip, float farClip);
	void setOrthography(float left, float right, float bottom, float top,
						float nearClip, float farClip);
	void setLookAt(vec3 lookAtFrom, vec3 lookAtTo, vec3 camUpAxis);
	inline void setTransform(mat4 newCamTransform) { m_camTransform = newCamTransform; }
	inline std::string getName() { return m_camName; }
	inline CamType getCamType() { return m_camType; }
	inline mat4 getTransform() { return m_camTransform; }
	inline mat4 getViewTransform() { return m_viewTransform; }
	inline mat4 getProjection() { return m_projectionTransform; }
	inline mat4 getProjectionView() { return m_projectionViewTransfrom; }
	inline mat4 render() { return m_projectionViewTransfrom; }

	void switchCamType();
	void setPerspCamSpec(std::string name, float val) { m_perspSpec[name] = val; }
	void setOrthoCamSpec(std::string name, float val) { m_orthoSpec[name] = val; }

	Camera_Base(const Camera_Base&) = delete;
	Camera_Base& operator=(const Camera_Base&) = delete;
	

protected:
	inline void updateProjectionView()
	{
		m_viewTransform = glm::inverse(m_camTransform);
		m_projectionViewTransfrom = m_viewTransform * m_projectionTransform;
	}
	
	inline void setCamType(CamType camType) { m_camType = camType; }

private:
	std::string m_camName;
	CamType m_camType;
	mat4 m_camTransform;
	mat4 m_viewTransform;
	mat4 m_projectionTransform;
	mat4 m_projectionViewTransfrom;
	std::map<std::string, float> m_perspSpec;
	std::map<std::string, float> m_orthoSpec;
};

#endif

