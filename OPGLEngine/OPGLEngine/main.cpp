#include <gl_core_4_4.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <iostream>
#include <Gizmos.h>

using aie::Gizmos;
using glm::vec3;
using glm::vec4;
using glm::mat3;
using glm::mat4;

int main()
{
	if (glfwInit() == false)
		return -1;

	// the rest of our code goes here!

	GLFWwindow* window = glfwCreateWindow(1280, 720, "My First Window.", nullptr, nullptr);

	if (window == nullptr)
	{
		glfwTerminate();
		return -2; //nagative number for error
	}

	glfwMakeContextCurrent(window);

	if (ogl_LoadFunctions() != ogl_LOAD_SUCCEEDED)
	{
		glfwDestroyWindow(window);
		glfwTerminate();
		return -3;
	}

	//Gizmos::create();

	mat4 view = glm::lookAt(vec3(10, 10, 10), vec3(0), vec3(0, 1, 0));
	mat4 projection = glm::perspective(glm::pi<float>() * 0.25f, 16 / 9.f, 0.1f, 1000.f);

	auto major = ogl_GetMajorVersion();
	auto minor = ogl_GetMinorVersion();
	std::cout << "GL: " << major << "." << minor << "\n";

	while (glfwWindowShouldClose(window) == false && glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS)
	{
		glClearColor(0.12f, 0.25f, 0.33f, 1.0f);
		glEnable(GL_DEPTH);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	//Do drawing
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}