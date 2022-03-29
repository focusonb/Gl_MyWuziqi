#include "glSquarePainter.h"
#include <glad/glad.h>
#include <glfw3.h>
#include "callback.h"

#include "MyShader.h"
#include "TextureManager.h"


static const char* vertextShaderPath = "shader/squareShader/vertextShaderSquareCenter.txt";
static const char* fragmentShaderPath = "shader/squareShader/fragmentShaderSquareCenter.txt";

static const char* vertextShaderPath2 = "shader/squareShader/vertextShaderSquare.txt";
static const char* fragmentShaderPath2 = "shader/squareShader/fragmentShaderSquare.txt";
static const char* texture = "texture1";
static const char* MY_IMAGE_PATH_1 = "image/background.jpg";


GlSquarePainter::GlSquarePainter()
{
	{//objects share one
		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);
		//VBO

		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(squareVertices), squareVertices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);

		//VAO

		glGenVertexArrays(1, &VAO1);
		glBindVertexArray(VAO1);
		//VBO

		glGenBuffers(1, &VBO1);
		glBindBuffer(GL_ARRAY_BUFFER, VBO1);
		glBufferData(GL_ARRAY_BUFFER, sizeof(outSquareVertices), outSquareVertices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
	}
	MyShader myShader(vertextShaderPath, fragmentShaderPath);

	MyShader myShader2(vertextShaderPath2, fragmentShaderPath2);

	//get shader program
	shaderProgram = myShader.getShaderProgram();
	shaderProgramOutSquare = myShader2.getShaderProgram();

	TextureManager textureManager;
	textureManager.setChannelType(GL_RGB);
	textureManager.loadImage(MY_IMAGE_PATH_1, texture1);

	// tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
	// -------------------------------------------------------------------------------------------
	// either set it manually like so:
	glUniform1i(glGetUniformLocation(shaderProgram, texture), 0);
	glEnable(GL_DEPTH_TEST);
}

void GlSquarePainter::draw(const PointGl & point, GLFWwindow* window) const
{
	if (shaderProgram == 0 || shaderProgramOutSquare == 0) {
		return ;
	}
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// bind textures on corresponding texture units
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);


		glBindVertexArray(VAO);
		glUseProgram(shaderProgram);
		glDrawArrays(GL_TRIANGLES, 0, 6);

		glBindVertexArray(VAO1);
		glUseProgram(shaderProgramOutSquare);
		glDrawArrays(GL_TRIANGLES, 0, 6);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glDeleteVertexArrays(1, &VAO);
	glDeleteVertexArrays(1, &VAO1);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &VBO1);
	glfwTerminate();
}
