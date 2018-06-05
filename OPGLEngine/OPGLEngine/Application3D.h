#pragma once
#include "Application.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>

using glm::mat4;
using glm::vec3;

class Camera_Free;

class Application3D : public CORE::Application
{
public:
	Application3D();
	virtual ~Application3D();
	virtual bool Startup();
	virtual void Update();
	virtual void Render();
	virtual void Shutdown();

private:
	std::string m_camName;
	float m_fovy;
	float m_aspectRatio;
	float m_left;
	float m_right;
	float m_bottom;
	float m_top;
	float m_nearClip;
	float m_farClip;
	vec3 m_lookAtFrom;
	vec3 m_lookAtTo;
	vec3 m_camUpAxis;

	Camera_Free* myCam;

};

