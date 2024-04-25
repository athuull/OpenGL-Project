#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

const char* vertexShaderSource =  "#version 330 core\n"
	"layout (location = 0) in vec3 aPos;\n"
	"void main()\n"
	"{\n"
	"   gl_Position = vec4(aPos.x,aPos.y,aPos.z,1.0);\n"
	"}\0";
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 1.0f, 0.2f, 1.0f);\n"
"}\n\0";
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

	// Vertex Shader
	 int success;
	 char infoLog[512];
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER); // Creates vertex Shader
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);  // Sets the Shader source
	glCompileShader(vertexShader);  // Compiles the Shader

   // Vertex Shader Error Checking/Handling

	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);   
	glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
	if (!success) {
		std::cout << infoLog << std::endl;
	}
     // Fragment Shader
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
	if (!success)
		std::cout << infoLog << std::endl;
	// Shader Program
	unsigned int shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	// Shader Program Error checking / handling
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
	if (!success)
		std::cout << infoLog << std::endl;

	float firstTriangle[] = {
		0.0f, 0.5f,0.0f,
		-0.5f , 0.0f,0.0f,
		0.5f , 0.0f,0.0f

	};
	float secondTriangle[] = { 0.0f, -0.5f,0.0f,
		-0.5f , 0.0f,0.0f,
		0.5f , 0.0f,0.0f };
		



	unsigned int VBOs[2], VAOs[2];
	glGenVertexArrays(2, VAOs);
	glGenBuffers(2, VBOs);
	glBindVertexArray(VAOs[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(firstTriangle), firstTriangle, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(VAOs[1]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(secondTriangle), secondTriangle, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);

	
	

	

	
	while (!glfwWindowShouldClose(window)) {

		// Process Key Inputs
		processInput(window);

		// Render
		glClearColor(1.0f, 0.5f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(shaderProgram);
		glBindVertexArray(VAOs[0]);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		// then we draw the second triangle using the data from the second VAO
		glBindVertexArray(VAOs[1]);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		


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