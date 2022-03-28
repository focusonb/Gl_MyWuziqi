//#include <wglew.h>
#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "opengl32.lib")
#include <glad/glad.h>
#include <glfw3.h>
#include <iostream>
#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//#include "WFileTextManager.h"
#include "FileManagerControler.h"
#include "MyShader.h"
#include "myVertices.h"


#include "TextureManager.h"
#include "callback.h"

const char* vertextShaderPath = "shader/vertextShader2.txt";
const char* vertextShaderPath2 = "shader/vertextShader_lighting_cube.txt";
const char* fragmentShaderPath = "shader/fragmentShader2.txt";
const char* fragmentShaderPath2 = "shader/fragmentShader_white_lighting.txt";
const char* MY_IMAGE_PATH_1 = "image/container.jpg";
const char* MY_IMAGE_PATH_2 = "image/awesomeface.png";
const int WINDOWS_HEIGHT = 900;
const int WINDOWS_WIDTH = 1200;
const int ViEW_HEIGHT = 900;
const int ViEW_WIDTH = 1200;


float deltaTime = 0.0f;	// Time between current frame and last frame
float lastFrame = 0.0f; // Time of last frame
float currentFrame;


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}


void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	const float cameraSpeed = 10.0f* deltaTime; // adjust accordingly
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		cameraPos += cameraSpeed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		cameraPos -= cameraSpeed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
}


int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(WINDOWS_WIDTH, WINDOWS_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);//hide cursor
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);
	//load gl dynamic library
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	//index
	//unsigned int indices[] = {  // note that we start from 0!
	//1, 2, 3,   // first triangle
	//0, 1, 3,    // second triangle
	//};


	//VAO
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	//VBO
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	//glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	//glEnableVertexAttribArray(2);

	//EBO
	//unsigned int EBO;
	//glGenBuffers(1, &EBO);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//shaderProgram render cube
	MyShader myShader(vertextShaderPath, fragmentShaderPath);
	//render lignting cube
	MyShader myShaderLighting(vertextShaderPath2, fragmentShaderPath2);
	//MyShader myShader(vertextShaderPath, fragmentShaderPath);



	//get shader program
	unsigned int shaderProgram = myShader.getShaderProgram();
	unsigned int shaderLightingProgram = myShaderLighting.getShaderProgram();
	if (shaderProgram == 0 || shaderLightingProgram == 0) {
		return 0;
	}

	glm::vec3 cubePositions[] = {
	glm::vec3(0.0f,  0.0f,  0.0f),
	glm::vec3(2.0f,  5.0f, -15.0f),
	glm::vec3(-1.5f, -2.2f, -2.5f),
	glm::vec3(-3.8f, -2.0f, -12.3f),
	glm::vec3(2.4f, -0.4f, -3.5f),
	glm::vec3(-1.7f,  3.0f, -7.5f),
	glm::vec3(1.3f, -2.0f, -2.5f),
	glm::vec3(1.5f,  2.0f, -2.5f),
	glm::vec3(1.5f,  0.2f, -1.5f),
	glm::vec3(-1.3f,  1.0f, -1.5f)
	};

	glm::mat4 trans = glm::mat4(1.0f);
	trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0));

	glm::mat4 model = glm::mat4(1.0f);
	model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));

	//glm::mat4 view[10] = { glm::mat4(1.0f) };
	glm::mat4 view[10];
	for(int i = 0; i < 10; i++)
	{
		view[i] = glm::mat4(1.0f);
		view[i] = glm::translate(view[i], cubePositions[i]);
		view[i] = glm::translate(view[i], glm::vec3(1.0f, 0.0f, -1.5f));
		float angle = 20.0f * i;
		view[i] = glm::rotate(view[i], glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
	}

	glm::mat4 projection;
	projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 99.0f, 100.0f);

	glUseProgram(shaderProgram);
	int modelLoc = glGetUniformLocation(shaderProgram, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	int viewLoc = glGetUniformLocation(shaderProgram, "view");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view[0]));

	int projectionLoc = glGetUniformLocation(shaderProgram, "projection");
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

	unsigned int transformLoc = glGetUniformLocation(shaderProgram, "transform");
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));



	glUseProgram(shaderLightingProgram);

	glm::mat4 model2 = glm::scale(model, glm::vec3(0.5f));


	int modelLoc2 = glGetUniformLocation(shaderLightingProgram, "model");
	glUniformMatrix4fv(modelLoc2, 1, GL_FALSE, glm::value_ptr(model));

	int viewLoc2 = glGetUniformLocation(shaderLightingProgram, "view");
	glUniformMatrix4fv(viewLoc2, 1, GL_FALSE, glm::value_ptr(view[0]));

	int projectionLoc2 = glGetUniformLocation(shaderLightingProgram, "projection");
	glUniformMatrix4fv(projectionLoc2, 1, GL_FALSE, glm::value_ptr(projection));

	unsigned int transformLoc2 = glGetUniformLocation(shaderLightingProgram, "transform");
	glUniformMatrix4fv(transformLoc2, 1, GL_FALSE, glm::value_ptr(trans));



	glViewport(0, 0, ViEW_WIDTH, ViEW_HEIGHT);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);


	// texture


	unsigned int texture1, texture2;
	TextureManager textureManager;
	textureManager.setChannelType(GL_RGB);
	textureManager.loadImage(MY_IMAGE_PATH_1, texture1);
	textureManager.setChannelType(GL_RGBA);
	textureManager.loadImage(MY_IMAGE_PATH_2, texture2);


	// tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
	// -------------------------------------------------------------------------------------------
	// either set it manually like so:
	glUniform1i(glGetUniformLocation(shaderProgram, "texture1"), 0);
	// or set it via the texture class
	glUniform1i(glGetUniformLocation(shaderProgram, "texture2"), 1);



	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);

	float radiuStep = 0.0f;

	while (!glfwWindowShouldClose(window))
	{
		currentFrame = static_cast<float>(glfwGetTime());
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		processInput(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		//glClear(GL_COLOR_BUFFER_BIT);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// bind textures on corresponding texture units
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);

	
		glm::mat4 view_look;
		view_look = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
		
		projection = glm::perspective(glm::radians(fov), (float)WINDOWS_WIDTH / (float)WINDOWS_HEIGHT, 0.5f, 100.0f);
		model2 = glm::translate(model2, glm::vec3(-0.0001f, 0.0, 0.0));

		glBindVertexArray(VAO);
		glUseProgram(shaderLightingProgram);
		int viewLoc3 = glGetUniformLocation(shaderLightingProgram, "view3");
		glUniformMatrix4fv(viewLoc3, 1, GL_FALSE, glm::value_ptr(view_look));
		glUniformMatrix4fv(projectionLoc2, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(modelLoc2, 1, GL_FALSE, glm::value_ptr(model2));

		//for (int i = 1; i < 10; i++) {
		//	glUniformMatrix4fv(viewLoc2, 1, GL_FALSE, glm::value_ptr(view[i]));
		//	glDrawArrays(GL_TRIANGLES, 0, 36);
		//}
		glUniformMatrix4fv(viewLoc2, 1, GL_FALSE, glm::value_ptr(view[0]));
		glDrawArrays(GL_TRIANGLES, 0, 36);
		//..........................................................................
		glUseProgram(shaderProgram);
		//glDrawElements(GL_TRIANGLES,36, GL_UNSIGNED_INT, 0);
		int viewLoc3_1 = glGetUniformLocation(shaderProgram, "view3");
		glUniformMatrix4fv(viewLoc3_1, 1, GL_FALSE, glm::value_ptr(view_look));
		

		glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));
		
		//for (int i = 1; i < 10; i++) {
		//	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view[i]));
		//	glDrawArrays(GL_TRIANGLES, 0, 36);
		//}
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view[0]));
		glDrawArrays(GL_TRIANGLES, 0, 36);



		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	//glDeleteBuffers(1, &EBO);
	glfwTerminate();
	return 0;
}