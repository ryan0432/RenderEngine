#pragma once
#include "Application.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "Mesh.h"
#include "OBJMesh.h"
#include "Shader.h"
#include "Texture.h"

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

protected:
	struct Light
	{
		vec3 direction;
		vec3 diffuse;
		vec3 specular;
	};

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

	Mesh m_mesh01;
	CORE::ShaderProgram m_shader01;
	CORE::Texture m_gridTexture;
	mat4 m_mesh01Transform;

	Mesh m_mesh02;
	CORE::ShaderProgram m_shader02;
	mat4 m_mesh02Transform;
	//vec3 Ka = { 1,1,0 };
	//vec3 Kd = { 0,1,0 };
	//vec3 Ks = { 0,1,1 };


	CORE::OBJMesh m_bunnyMesh;
	CORE::ShaderProgram m_bunnyShader;
	mat4 m_bunnyTransform;

	CORE::OBJMesh m_spearMesh;
	CORE::ShaderProgram m_spearShader;
	CORE::Texture m_spearDTexture;
	CORE::Texture m_spearSTexture;
	mat4 m_spearTransform;

	Light m_light01;
	vec3 m_ambientLight01;
};