#include "Application.h"
#include "gl_core_4_4.h"
#include "imgui_glfw3.h"
#include "Input.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <chrono>
#include <iostream>

namespace CORE
{
	Application::~Application()
	{
	}

	int Application::Run(int width, int height,
						  const char* title,
						  bool isFullscreen,
						  std::string configPath)
	{
		auto success = InitializeWindow(width, height, title, isFullscreen);
		if (!success)
		{
			std::cout << "Window is failed to initialize." << std::endl;
			system("cls");
			return -1;
		}

		if (!Startup())
		{
			TerminateWindow();
			return -2;
		}

		GameLoop();
		Shutdown();
		TerminateWindow();
		return 0;
	}

	bool Application::InitializeWindow(int width, int height,
		const char * title, bool isFullscreen)
	{
		if(glfwInit() == GL_FALSE)
			return false;

		GLFWwindow* window = glfwCreateWindow(width, height, title,
			isFullscreen ? glfwGetPrimaryMonitor() : nullptr, nullptr);

		if (window == nullptr)
		{
			glfwTerminate();
			return false;
		} 

		glfwMakeContextCurrent(window);

		if (ogl_LoadFunctions() == ogl_LOAD_FAILED)
		{
			glfwDestroyWindow(window);
			glfwTerminate();
			return false;
		}

		m_window		= window;
		m_windowWidth	= width;
		m_windowHeight	= height;
		m_isFullscreen	= isFullscreen;

		m_applicationStartTime = std::chrono::high_resolution_clock::now();
		m_prevFrameTime = m_applicationStartTime;

		glfwSetWindowSizeCallback(m_window, 
									[](GLFWwindow*, int w, int h)
										{
											glViewport(0, 0,w, h); 
										}
								  );

		glClearColor(0, 0, 0, 1);

		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		// start input manager
		Input::create();

		ImGui_Init(m_window, true);

		return true;

	}

	bool const Application::IsWindowClosed()
	{
		return glfwWindowShouldClose(m_window) == GL_TRUE;
	}

	void Application::GameLoop()
	{
		while (GetRunning())
		{
			auto now = std::chrono::high_resolution_clock::now();
			auto timeTaken = now - m_prevFrameTime;
			m_deltaTime = std::chrono::duration<float>(timeTaken).count();
			m_prevFrameTime = now;

			auto elapsedTime = now - m_applicationStartTime;
			m_elapsedTime = std::chrono::duration<float>(elapsedTime).count();

			CORE::Input::getInstance()->clearStatus();

			Update();
			Render();
			ImGui::Render();
			glfwPollEvents();
		}
	}

	void Application::TerminateWindow()
	{
		CORE::Input::destroy();
		CORE::ImGui_Shutdown();
		glfwDestroyWindow(m_window);
		glfwTerminate();
	}

	void Application::ClearScreen()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	}

	void Application::SetBackgroundColour(float r, float g, float b, float a)
	{
		glClearColor(r, g, b, a);
	}
	void Application::SetShowCursor(bool visible)
	{
		ShowCursor(visible);
	}

	void Application::SetVSync(bool enabled)
	{
		glfwSwapInterval(enabled ? 1 : 0);
	}
}
