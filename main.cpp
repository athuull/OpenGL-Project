#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include </Users/Smitha/source/repos/OpenGL-Project/shader.h>
void processInput(GLFWwindow* window);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

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
	Shader ourShader("shaders/shader.vs", "shaders/shader.fs");

	float firstTriangle[] = {
		0.0f, 0.5f,0.0f,
		-0.5f , 0.0f,0.0f,
		0.5f , 0.0f,0.0f

	};
	float secondTriangle[] = { 0.0f, -0.5f,0.0f,
		-0.5f , 0.0f,0.0f,
		0.5f , 0.0f,0.0f };
		
	float aColor[] = { 1.0f,0.0f,0.0f,
					   0.0f,1.0f,0.0f,
					   0.0f,0.0f,1.0f
	};


	unsigned int VBOs[2], colorVBOs[2], VAOs[2];

	// Generate VAOs and VBOs
	glGenVertexArrays(2, VAOs);
	glGenBuffers(2, VBOs);
	glGenBuffers(2, colorVBOs);

	// First triangle
	glBindVertexArray(VAOs[0]);

	// Vertex data
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(firstTriangle), firstTriangle, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// Color data
	glBindBuffer(GL_ARRAY_BUFFER, colorVBOs[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(aColor), aColor, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);

	// Second triangle
	glBindVertexArray(VAOs[1]);

	// Vertex data
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(secondTriangle), secondTriangle, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// Color data
	glBindBuffer(GL_ARRAY_BUFFER, colorVBOs[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(aColor), aColor, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);


	

	

	
	while (!glfwWindowShouldClose(window)) {

		// Process Key Inputs
		processInput(window);

		// Render
		glClearColor(1.0f, 0.5f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		ourShader.use();
		glBindVertexArray(VAOs[0]);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		// then we draw the second triangle using the data from the second VAO
		glBindVertexArray(VAOs[1]);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		
        /*// Using uniforms to supply a dynamic value for green
		float timeValue = glfwGetTime();
		float greenValue = (sin(timeValue) / 2.0f + 0.5f); // returns a float value for green between 0.0f - 1.0f
		int vertexColorLocation = glGetUniformLocation(shaderProgram, "vertexColor"); // Self explanatory
		glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);  // 4f stands for 4 floats (vec4) */
		
		//Swaps Front and Back Buffers and handles events in the window
		glfwSwapBuffers(window);
		glfwPollEvents(); 
		glfwSetKeyCallback(window, key_callback);

	}

	glfwTerminate();
	return 0;
}

void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
	
}
// Code for toggling between wireframe mode and fill mode.
bool wireframeMode = false;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_W && action == GLFW_PRESS)
	{
		wireframeMode = !wireframeMode;
		glPolygonMode(GL_FRONT_AND_BACK, wireframeMode ? GL_LINE : GL_FILL);
	}
}