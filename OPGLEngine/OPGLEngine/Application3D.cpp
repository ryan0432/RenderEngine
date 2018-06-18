#include "Application3D.h"
#include <iostream>
#include <Gizmos.h>
#include <stdio.h>
#include "Input.h"
#include "imgui.h"
#include "Camera_Free.h"

using CORE::Gizmos;
using glm::vec3;
using glm::vec4;
using glm::mat3;
using glm::mat4;

Application3D::Application3D()
{
}


Application3D::~Application3D()
{
}

bool Application3D::Startup()
{
	//Setup Camera Spec
	m_camName = "My Cam";
	m_fovy = glm::pi<float>() * 0.25f;
	m_aspectRatio = (float)GetWindowWidth() / (float)GetWindowHeight();
	m_left = -10.0f;
	m_right = 10.0f;
	m_bottom = -10.0f;
	m_top = 10.0f;
	m_nearClip = 0.1f;
	m_farClip = 1000.0f;
	m_lookAtFrom = vec3(0.0f, 2.0f, 10.0f);
	m_lookAtTo = vec3(0, 0, 0);
	m_camUpAxis = vec3(0, 1 ,0);

	//Initialize Camera
	myCam = new Camera_Free(m_camName, PERSP, this ,m_fovy ,
		m_left, m_right, m_bottom, m_top, m_nearClip, m_farClip,
		m_lookAtFrom, m_lookAtTo, m_camUpAxis);

	//Initialize Shader
	//1. load vertex shader from file
	m_shader01.loadShader(CORE::eShaderStage::VERTEX, "../bin/shaders/simple.vert");
	m_shader02.loadShader(CORE::eShaderStage::VERTEX, "../bin/shaders/simple02.vert");
	m_bunnyShader.loadShader(CORE::eShaderStage::VERTEX, "../bin/shaders/bunny.vert");
	m_spearShader.loadShader(CORE::eShaderStage::VERTEX, "../bin/shaders/spear.vert");
	//2. load fragment shader from file
	m_shader01.loadShader(CORE::eShaderStage::FRAGMENT, "../bin/shaders/simple.frag");
	m_shader02.loadShader(CORE::eShaderStage::FRAGMENT, "../bin/shaders/simple02.frag");
	m_bunnyShader.loadShader(CORE::eShaderStage::FRAGMENT, "../bin/shaders/bunny.frag");
	m_spearShader.loadShader(CORE::eShaderStage::FRAGMENT, "../bin/shaders/spear.frag");
	//3. If fail to load shader files, prompt error message
	if (m_shader01.link() == false) { printf("Shader Error: %s\n", m_shader01.getLastError()); }
	if (m_shader02.link() == false) { printf("Shader Error: %s\n", m_shader02.getLastError()); }
	if (m_bunnyShader.link() == false) { printf("Shader Error: %s\n", m_bunnyShader.getLastError()); return false; }
	if (m_spearShader.link() == false) { printf("Shader Error: %s\n", m_spearShader.getLastError()); return false; }

	//4. If loading Obj file fails, prompt error message
	if (m_bunnyMesh.load("../bin/models/stanford/bunny.obj") == false) { printf("Loading Bunny Mesh Error!\n"); return false; }
	if (m_spearMesh.load("../bin/models/soulspear/soulspear.obj", true, true) == false) { printf("Loading Spear Mesh Error!\n"); return false; }

	//5. If loading Texture files fails, prompt error message
	if (m_spearDTexture.load("../bin/models/soulspear/soulspear_diffuse.tga") == false) { printf("Loading Spear Diffuse Texture Error!\n"); return false; }
	if (m_spearSTexture.load("../bin/models/soulspear/soulspear_specular.tga") == false) { printf("Loading Spear Specular Texture Error!\n"); return false; }
	if (m_gridTexture.load("../bin/models/stanford/UVgrid.jpg") == false) { printf("Loading UVgrid Texture Error!\n"); return false; }

	//Initialize mesh Quad
	m_mesh01.initialiseQuad();
	//Set mesh size
	m_mesh01Transform = {  5,  0,  0,  0,
						   0,  5,  0,  0,
						   0,  0,  5,  0,
						   0,  -1,  0,  1 };

	Mesh::Vertex vertices[12];

	vertices[0].position = { -0.5f, 0.5f, 0.5f, 1 };
	vertices[1].position = { 0.5f, 0.5f, 0.5f, 1 };
	vertices[2].position = { -0.5f, 0.5f, -0.5f, 1 };

	vertices[3].position = { -0.5f, 0.5f, -0.5f, 1 };
	vertices[4].position = { 0.5f, 0.5f, 0.5f, 1 };
	vertices[5].position = { 0.5f, 0.5f, -0.5f, 1 };

	vertices[6].position = { -0.5f, -0.5f, 0.5f, 1 };
	vertices[7].position = { 0.5f, -0.5f, 0.5f, 1 };
	vertices[8].position = { -0.5f, -0.5f, -0.5f, 1 };

	vertices[9].position = { -0.5f, -0.5f, -0.5f, 1 };
	vertices[10].position = { 0.5f, -0.5f, 0.5f, 1 };
	vertices[11].position = { 0.5f, -0.5f, -0.5f, 1 };

	// define 6 normals for 2 triangles
	vertices[0].normal = { 0, 1, 0, 0 };
	vertices[1].normal = { 0, 1, 0, 0 };
	vertices[2].normal = { 0, 1, 0, 0 };
	vertices[3].normal = { 0, 1, 0, 0 };
	vertices[4].normal = { 0, 1, 0, 0 };
	vertices[5].normal = { 0, 1, 0, 0 };
	vertices[6].normal = { 0, 1, 0, 0 };
	vertices[7].normal = { 0, 1, 0, 0 };
	vertices[8].normal = { 0, 1, 0, 0 };
	vertices[9].normal = { 0, 1, 0, 0 };
	vertices[10].normal = { 0, 1, 0, 0 };
	vertices[11].normal = { 0, 1, 0, 0 };

	m_mesh02.initialize(12, vertices);

	m_mesh02Transform = { 3,  0,  0,  0,
						  0,  3,  0,  0,
						  0,  0,  3,  0,
						  0,  0,  -4,  1 };

	//Initialize bunny transfrom
	m_bunnyTransform = { 0.3f,  0,  0,  0,
						 0,  0.3f,  0,  0,
						 0,  0,  0.3f,  0,
						-1.5f,  0,  0,  1 };

	//Initialize spear transfrom
	m_spearTransform = { 1,  0,  0,  0,
						 0,  1,  0,  0,
						 0,  0,  1,  0,
						 1.5f,  0,  0,  1 };
	

	//Setup Light and AmbientLight
	m_light01.position = { 1, 1, 1 };
	m_light01.diffuse = { 1, 1, 1 };
	m_light01.specular = { 1, 1, 1 };

	m_light02.position = { -1, -1, -1 };
	m_light02.diffuse = { 1, 1, 1 };
	m_light02.specular = { 1, 1, 1 };

	m_ambientLight01 = { 0.75f, 0.75f, 0.75f };

	//Select Imgui style
	ImGui::StyleColorsDark();

	//Set background colour
	SetBackgroundColour(0.3f, 0.3f, 0.3f, 1.0f);

	//Setup the Gimos's min/max drawing ability
	Gizmos::create(50000, 50000, 50000, 50000);

	return true;
}

void Application3D::Update()
{
	//Input Section
	CORE::Input* input = CORE::Input::getInstance();
	if (input->isKeyDown(CORE::INPUT_KEY_ESCAPE)) { SetRunning(false); }

	ImGui::Begin("Control Panel", &mainWindowStart);
	ImGui::Text("Light 01 Position");
	ImGui::SliderFloat("Light01 X", &m_light01.position[0], 10.0f, -10.0f);
	ImGui::SliderFloat("Light01 Y", &m_light01.position[1], 10.0f, -10.0f);
	ImGui::SliderFloat("Light01 Z", &m_light01.position[2], 10.0f, -10.0f);
	ImGui::Text("Light 01 Diffuse Colour");
	ImGui::SliderFloat("Light01 Diffuse R", &m_light01.diffuse[0], 0.0f, 1.0f);
	ImGui::SliderFloat("Light01 Diffuse G", &m_light01.diffuse[1], 0.0f, 1.0f);
	ImGui::SliderFloat("Light01 Diffuse B", &m_light01.diffuse[2], 0.0f, 1.0f);
	ImGui::Text("Light 01 Specular Colour");
	ImGui::SliderFloat("Light01 Specular R", &m_light01.specular[0], 0.0f, 1.0f);
	ImGui::SliderFloat("Light01 Specular G", &m_light01.specular[1], 0.0f, 1.0f);
	ImGui::SliderFloat("Light01 Specular B", &m_light01.specular[2], 0.0f, 1.0f);

	ImGui::Text("Light 02 Position");
	ImGui::SliderFloat("Light02 X", &m_light02.position[0], 10.0f, -10.0f);
	ImGui::SliderFloat("Light02 Y", &m_light02.position[1], 10.0f, -10.0f);
	ImGui::SliderFloat("Light02 Z", &m_light02.position[2], 10.0f, -10.0f);
	ImGui::Text("Light 02 Diffuse Colour");
	ImGui::SliderFloat("Light02 Diffuse R", &m_light02.diffuse[0], 0.0f, 1.0f);
	ImGui::SliderFloat("Light02 Diffuse G", &m_light02.diffuse[1], 0.0f, 1.0f);
	ImGui::SliderFloat("Light02 Diffuse B", &m_light02.diffuse[2], 0.0f, 1.0f);
	ImGui::Text("Light 02 Specular Colour");
	ImGui::SliderFloat("Light02 Specular R", &m_light02.specular[0], 0.0f, 1.0f);
	ImGui::SliderFloat("Light02 Specular G", &m_light02.specular[1], 0.0f, 1.0f);
	ImGui::SliderFloat("Light02 Specular B", &m_light02.specular[2], 0.0f, 1.0f);
	ImGui::End();

	m_light01.direction = glm::normalize(m_light01.position);
	m_light02.direction = glm::normalize(m_light02.position);


	myCam->Update(GetDeltaTime(), this);

	std::cout << "Cam Name : " << myCam->getName() << std::endl;
	std::cout << "Cam Pos X: " << myCam->getTransform()[3][0] << std::endl;
	std::cout << "        Y: " << myCam->getTransform()[3][1] << std::endl;
	std::cout << "        Z: " << myCam->getTransform()[3][2] << std::endl;
	std::cout << "FPS: " << GetFPS() << std::endl;
	std::cout << "Elapsed Time: " << GetElapsedTime() << std::endl;
	system("cls");
}

void Application3D::Render()
{
	//Clear screen for rendering new frame
	ClearScreen();

	//clear Gizmos buffer every frame
	Gizmos::clear();

	//setup Gizmos's default transform
	Gizmos::addTransform(glm::mat4(1));

	//setup white colour value
	vec4 white(1);

	//setup black colour value
	vec4 black(0, 0, 0, 1);

	//draw grid by margin of 1 on x and z axis
	for (int i = 0; i < 21; ++i)
	{
		Gizmos::addLine(vec3(-10 + i, 0, 10), vec3(-10 + i, 0, -10), i == 10 ? white : black);
		Gizmos::addLine(vec3(10, 0, -10 + i), vec3(-10, 0, -10 + i), i == 10 ? white : black);
	}

	Gizmos::addSphere((m_light01.position * -1.0f), 0.3f, 8, 8, vec4(m_light01.diffuse, 1));
	Gizmos::addSphere((m_light02.position * -1.0f), 0.3f, 8, 8, vec4(m_light02.diffuse, 1));

	m_shader01.bind();
	m_shader01.bindUniform("Ia", m_ambientLight01);
	m_shader01.bindUniform("Id", m_light01.diffuse);
	m_shader01.bindUniform("Is", m_light01.specular);
	m_shader01.bindUniform("Ka", mesh01Ka);
	m_shader01.bindUniform("Kd", mesh01Kd);
	m_shader01.bindUniform("Ks", mesh01Ks);
	m_shader01.bindUniform("ModelMatrix", m_mesh01Transform);
	m_shader01.bindUniform("LightDirection", m_light01.direction);
	m_shader01.bindUniform("cameraPosition", myCam->getPosition());
	auto pvmMesh01 = myCam->getProjectionView() * m_mesh01Transform;
	m_shader01.bindUniform("ProjectionViewModel", pvmMesh01);
	m_shader01.bindUniform("NormalMatrix",
						glm::inverseTranspose(mat3(m_mesh01Transform)));
	m_shader01.bindUniform("diffuseTexture", 0);
	m_gridTexture.bind(0);
	m_mesh01.draw();

	m_shader02.bind();
	m_shader02.bindUniform("Ia", m_ambientLight01);
	m_shader02.bindUniform("Id", m_light01.diffuse);
	m_shader02.bindUniform("Is", m_light01.specular);
	m_shader02.bindUniform("Ka", mesh02Ka);
	m_shader02.bindUniform("Kd", mesh02Kd);
	m_shader02.bindUniform("Ks", mesh02Ks);
	m_shader02.bindUniform("ModelMatrix", m_mesh02Transform);
	m_shader02.bindUniform("cameraPosition", myCam->getPosition());
	m_shader02.bindUniform("LightDirection", m_light01.direction);
	auto pvmMesh02 = myCam->getProjectionView() * m_mesh02Transform;
	m_shader02.bindUniform("ProjectionViewModel", pvmMesh02);
	m_shader02.bindUniform("NormalMatrix",
						glm::inverseTranspose(mat3(m_mesh02Transform)));
	m_mesh02.draw();

	m_bunnyShader.bind();
	m_bunnyShader.bindUniform("Ia", m_ambientLight01);
	m_bunnyShader.bindUniform("Id1", m_light01.diffuse);
	m_bunnyShader.bindUniform("Is1", m_light01.specular);
	m_bunnyShader.bindUniform("Id2", m_light02.diffuse);
	m_bunnyShader.bindUniform("Is2", m_light02.specular);
	m_bunnyShader.bindUniform("LightDirection01", m_light01.direction);
	m_bunnyShader.bindUniform("LightDirection02", m_light02.direction);
	m_bunnyShader.bindUniform("cameraPosition", myCam->getPosition());
	auto pvmBunnyMesh = myCam->getProjectionView() * m_bunnyTransform;
	m_bunnyShader.bindUniform("ProjectionViewModel", pvmBunnyMesh);
	m_bunnyShader.bindUniform("NormalMatrix",
						glm::inverseTranspose(mat3(m_bunnyTransform)));
	m_bunnyMesh.draw();

	m_spearShader.bind();
	m_spearShader.bindUniform("Ia", m_ambientLight01);
	m_spearShader.bindUniform("Id1", m_light01.diffuse);
	m_spearShader.bindUniform("Is1", m_light01.specular);
	m_spearShader.bindUniform("Id2", m_light02.diffuse);
	m_spearShader.bindUniform("Is2", m_light02.specular);
	m_spearShader.bindUniform("cameraPosition", myCam->getPosition());
	m_spearShader.bindUniform("LightDirection01", m_light01.direction);
	m_spearShader.bindUniform("LightDirection02", m_light02.direction);
	auto pvmSpearMesh = myCam->getProjectionView() * m_spearTransform;
	m_spearShader.bindUniform("ProjectionViewModel", pvmSpearMesh);
	m_spearShader.bindUniform("NormalMatrix",
						glm::inverseTranspose(mat3(m_spearTransform)));
	m_spearShader.bindUniform("diffuseTexture", 0);
	m_spearDTexture.bind(0);
	m_spearShader.bindUniform("specularTexture", 1);
	m_spearSTexture.bind(1);
	m_spearMesh.draw();

	//assign draw area
	Gizmos::draw(myCam->Render());
}

void Application3D::Shutdown()
{
	Gizmos::destroy();
	delete myCam;
}
