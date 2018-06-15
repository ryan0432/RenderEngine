#pragma once
#ifndef CAM_BASE_H
#define CAM_BASE_H

//------------------------------------------------------//
//														//
//	Name: Camera_Base.h									//
//														//
//	Desc: This is the base class of camera setups.		//
//														//
//------------------------------------------------------//

#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <string>
#include <map>

using glm::mat4;
using glm::vec3;
using glm::vec4;

enum CamType
{
	PERSP,
	ORTHO
};

namespace CORE
{
	class Application;
}

class Camera_Base
{
public:
	//Default constructor 
	Camera_Base();
	
	//Destructor, set virtual in case child class has it's own pointers to be deleted.
	virtual ~Camera_Base();
	
	//Update, needs all derived classes to be inherited.
	//This fuction will be called in App class.
	virtual void Update(float deltaTime, CORE::Application* app) = 0;

	//Set camera name
	inline void setName(std::string camName) { m_camName = camName; }

	//Set camera position
	void setPosition(vec3 pos);

	//Set camera [Projection Transform] to [Perspective].
	void setPerspective(float fovY, float aspectRatio, float nearClip, float farClip);
	
	//Set camera [Projection Transform] to [Orthography].
	void setOrthography(float left, float right, float bottom, float top,
						float nearClip, float farClip);

	//Set camera [View Transform]
	void setLookAt(vec3 lookAtFrom, vec3 lookAtTo, vec3 camUpAxis);

	//Set camera [World Transform]
	inline void setTransform(mat4 newCamTransform) { m_camTransform = newCamTransform; }

	//Returns camera name (std::string)
	inline std::string getName() { return m_camName; }

	//Returns camera position (vec3)
	vec3 getPosition();

	//Returns camera type (Enum CamType)
	inline CamType getCamType() { return m_camType; }

	//Returns camera [World Transform] (mat4)
	inline mat4 getTransform() { return m_camTransform; }

	//Returns camera [View Transform] (mat4)
	inline mat4 getViewTransform() { return m_viewTransform; }

	//Returns camera [Projection Transform] (mat4)
	inline mat4 getProjection() { return m_projectionTransform; }

	//Returns [Projection * View] transform (mat4)
	//p.s. (Projection * View * Model) = Render transform
	inline mat4 getProjectionView() { return m_projectionViewTransfrom; }

	//Returns [Projection * View] transform (mat4)
	//p.s. (Projection * View * Model) = Render transform
	inline mat4 Render() { return m_projectionViewTransfrom; }

	//Switch [Camera Type] between Orthography and Perspective
	void switchCamType();

	//Set all datas a [Perspective Camera] needs in a std::map
	void setPerspCamSpec(std::string name, float val) { m_perspSpec[name] = val; }

	//Set all datas a [Orthography Camera] needs in a std::map
	void setOrthoCamSpec(std::string name, float val) { m_orthoSpec[name] = val; }

	//---------------------------------------------------------//
	//Prevents users create an instance of pure virtual class  //
	Camera_Base(const Camera_Base&) = delete;				   //
	//Prevents users shallow copy							   //
	Camera_Base& operator=(const Camera_Base&) = delete;	   //
	//---------------------------------------------------------//
	
protected:
	//Updates [Projection * View] transform frame by frame
	inline void updateProjectionView()
	{
		//In Update(), [View Transfrom] changes along with [Projection Transform]
		//in its opposition
		m_viewTransform = glm::inverse(m_camTransform);

		//Calculation [Projection * View] transform for rendering
		m_projectionViewTransfrom = m_projectionTransform * m_viewTransform;
	}
	
	//Attention: This function only changes Enum, doesn't change the actual
	//projection type. [--Internal Use Only--]
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

