//Special thanks:
//https://www.youtube.com/watch?v=k9LDF016_1A

//Getting started tutorial
//https://learnopengl.com/#!Getting-started/Hello-Window

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

//rendering engine headers
#include "IdCounters.h"
#include "CubeDemo.h"
#include "PBRSpheres.h"
#include "Renderer.h"


void processInput(GLFWwindow *window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

// settings
unsigned int SCR_WIDTH = 800;
unsigned int SCR_HEIGHT = 600;

//camera
float oldMouseX = 0.0;
float oldMouseY = 0.0;
float mouseX = 0.0;
float mouseY = 0.0;
float scrollY = 0.0;

bool updateViewport = true;
bool updateMouse = false;
bool updateScroll = false;
bool leftPressed = false;
bool firstMouse = true;

int main()
{
	// glfw: initialize and configure
	// ------------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

														 // glfw window creation
														 // --------------------
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwSetScrollCallback(window, scroll_callback);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	
	//create the demo
	CubeDemo demo;
	//demo.createScene();
	Scene* scene = demo.getScene();

	//create the renderer
	Renderer renderer(scene);

	// render loop
	// -----------
	while (!glfwWindowShouldClose(window))
	{
		// input
		// -----
		processInput(window);

		// render
		// ------
		
		
		if (updateViewport) {
			renderer.setViewport(SCR_WIDTH, SCR_HEIGHT);
			updateViewport = false;
		}
		if (updateMouse) {
			Camera& camera = renderer.getCamera();
			if (leftPressed) camera.ProcessMouseMovement(mouseX - oldMouseX, mouseY - oldMouseY);
			updateMouse = false;
		}
		if (updateScroll) {
			Camera& camera = renderer.getCamera();
			camera.ProcessMouseScroll(scrollY);
			updateScroll = false;
		}
		renderer.render();

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	renderer.deleteScene();

	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glfwTerminate();
	return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);

	SCR_WIDTH = width;
	SCR_HEIGHT = height;

	updateViewport = true;
}

void getMouseOnCircle(float &iPageX, float &iPageY) {
	iPageX = (iPageX - 0.5f*(float)SCR_WIDTH) / (0.5f*(float)SCR_WIDTH);
	iPageY = (SCR_HEIGHT - 2.0f*iPageY) / ((float)SCR_WIDTH);
}
// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (!leftPressed) return;
	if (firstMouse) {
		oldMouseX = 0.0f;
		oldMouseY = 0.0f;
		mouseX = (float)xpos;
		mouseY = (float)ypos;
		getMouseOnCircle(mouseX, mouseY);
		firstMouse = false;
		return;
	}
	oldMouseX = mouseX;
	oldMouseY = mouseY;
	mouseX = (float)xpos;
	mouseY = (float)ypos;
	getMouseOnCircle(mouseX, mouseY);
	updateMouse = true;
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	scrollY = (float)yoffset;
	updateScroll = true;
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
		leftPressed = true;
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
		leftPressed = false;
		firstMouse = true;
		updateMouse = false;
	}
}