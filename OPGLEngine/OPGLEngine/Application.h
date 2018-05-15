#pragma once
#ifndef APPLICATION_H
#define APPLICATION_H
#include <chrono>
#include <string>

// Forward declared structure for access to GLFW window.
struct GLFWwindow;

// Engine Code Name: CORE
namespace CORE
{
	// Application is a pure-virtual base class that inclues all the basic functionalities.
	// Clients derive their own applications from this class.
	class Application
	{
	public:
		// Default Constructor, when a class is created,
		// set current window to null pointer, not game over, fps = 0;
		Application() : m_window(nullptr), m_isRunning(true), m_fps(0) {};
		virtual ~Application();

		// Run() sets the title of the game, width, height, fullscreen mode on/off.
		// It creates a window based on these settings also calls Update() and Draw()
		// repeatedly. It calls Startup() at the beginning of the application, if it
		// succeeds it then starts the  game loop.
		// It ends with Shutdown() if m_gameOver is true. 
		int Run( int width, int height, const char* title, bool isFullscreen, std::string configPath = "");
		
		/// The following functions must be implemented by derived class. -----------//
		// Starup() allows clients to do custom initialization.						 //
		virtual bool Startup()	= 0;												 //
		// Update() updates customed contents based on deltaTime.					 //
		virtual void Update()	= 0;												 //
		// Shutdown() allows clients to clean up created pointers.					 //
		virtual void Shutdown() = 0;												 //
		// Render() allows clients to draw objects with a renderer they brought in.	 //
		virtual void Render() = 0;													 //
		///--------------------------------------------------------------------------//
		
		// Clears the screen to begin drawing a frame
		void ClearScreen();

		// Wipes the screen clear to begin a frame of drawing
		void SetBackgroundColour(float r, float g, float b, float a);

		// Show/Hide os cursor
		void SetShowCursor(bool visible);
		
		// Enable/Disable V-Sync
		void SetVSync(bool enabled);

		inline bool GetRunning() const { return m_isRunning; }
		inline void SetRunning(bool val) { m_isRunning = val; }

		inline float GetDeltaTime() const { return m_deltaTime; }
		inline bool GetFullscreen() const { return m_isFullscreen; }

		// Accesses ti the GLFW window
		inline GLFWwindow* const GetWindowPtr() { return m_window; }

		// Check if current window has been closed
		bool const IsWindowClosed();

		// Returns the width of current window.
		inline unsigned int GetWindowWidth() const { return m_windowWidth; }

		// Returns the height of current window.
		inline unsigned int GetWindowHeight() const { return m_windowHeight; }

		// Returns app running time.
		inline float GetElapsedTime() const { return m_elapsedTime; }

		// Returns current FPS that the app is running at
		inline unsigned int GetFPS() const { return m_fps; }


	protected:
		virtual bool InitializeWindow(int width, int hight, const char * title,
									  bool isFullscreen);

		virtual void GameLoop();
		virtual void TerminateWindow();

	private:
		GLFWwindow*		m_window;
		unsigned int	m_windowWidth	= 1280;
		unsigned int	m_windowHeight	= 720;
		bool			m_isFullscreen	= false;
		bool			m_isRunning		= false;

		float			m_deltaTime = 0.0f;
		float			m_elapsedTime = 0.0f;
		unsigned int	m_fps = 0;

		std::chrono::high_resolution_clock::time_point m_applicationStartTime;
		std::chrono::high_resolution_clock::time_point m_prevFrameTime;
	};
}

#endif

