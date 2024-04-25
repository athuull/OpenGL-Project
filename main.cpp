#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

void processInput(GLFWwindow* window);
int main() {
	// Initialises GLFW
	glfwInit();

	// Configure GLFW Version and Profile
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Creates the window
	GLFWwindow *window = glfwCreateWindow(800, 600, "OpenGL Project", NULL, NULL);
    
	// Error handling for window creation
	if (window == NULL) {
		std::cout << "Failed to create the Window" << std::endl;
		glfwTerminate();
		return -1;
	}

	// Makes the window the current context
	glfwMakeContextCurrent(window);

	// Loads Glad to manage OpenGL function pointers
	gladLoadGL();
	while (!glfwWindowShouldClose(window)) {

		// Process Key Inputs
		processInput(window);

		// Render
		glClearColor(1.0f, 0.5f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//Swaps Front and Back Buffers and handles events in the window
		glfwSwapBuffers(window);
		glfwPollEvents(); 
	
	}

	glfwTerminate();
	return 0;
}

void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
		glfwSetWindowShouldClose(window, true);
	}
}