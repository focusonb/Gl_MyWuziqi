#include "glSquarePainter.h"
#include <glad/glad.h>
#include <glfw3.h>
#include "../CallBack/callback.h"

#include "../ShaderReader/MyShader.h"
#include "../TextureManager/TextureManager.h"
#include "../GlfwConfigure//GlfwConfigure.h"


const char* vertextShaderPath = "shader/squareShader/vertextShaderSquareCenter.txt";
const char* fragmentShaderPath = "shader/squareShader/fragmentShaderSquareCenter.txt";

const char* vertextShaderPath2 = "shader/squareShader/vertextShaderSquare.txt";
const char* fragmentShaderPath2 = "shader/squareShader/fragmentShaderSquare.txt";
const char* texture = "texture1";
const char* MY_IMAGE_PATH_1 = "image/background.jpg";

list<GLuint> GlPainter:: vao;
list<GLuint> GlPainter:: vbo;

GlSquarePainter::GlSquarePainter(const PointGl& point, float width)
{
	addOne(point, width);
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

void GlSquarePainter::draw() const
{
	if (shaderProgram == 0 || shaderProgramOutSquare == 0) {
		return ;
	}
	// bind textures on corresponding texture units
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture1);

	glUseProgram(shaderProgram);
	for (auto it : m_vao) {
		glBindVertexArray(it);
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}

	glUseProgram(shaderProgramOutSquare);
	for (auto it : m_vao1) {
		glBindVertexArray(it);
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}
	glDrawArrays(GL_TRIANGLES, 0, 6);
}

void GlSquarePainter::addOne(const PointGl& point, float width)
{
	float k = WINDOWS_WIDTH / width;//shrink times
	float offsetX = (2.000 * point.first / WINDOWS_WIDTH) - 1.000 + (1.000 / k);//offset in x direction
	float offsetY = (2.000 * point.second / WINDOWS_HEIGHT) - 1.000 + (1.000 / k);//offset in y direction

	float tmp;
	for (int i = 0; i < 6; ++i) {
		for (int j = 0; j < 2; ++j) {
			switch (j) {
			case 0: {
				tmp = squareVertices[i * 5 + j];
				squareVertices[i * 5 + j] = tmp / k + offsetX;
				tmp = outSquareVertices[i * 6 + j];
				outSquareVertices[i * 6 + j] = tmp / k + offsetX;
				break;
			}
			case 1: {
				tmp = squareVertices[i * 5 + j];
				squareVertices[i * 5 + j] = tmp / k + offsetY;
				tmp = outSquareVertices[i * 6 + j];
				outSquareVertices[i * 6 + j] = tmp / k + offsetY;
				break;
			}
			}
		}
	}
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

	m_vao.push_back(VAO);
	GlPainter::vao.push_back(VAO);
	GlPainter::vao.push_back(VBO);

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
	m_vao1.push_back(VAO1);
	GlPainter::vao.push_back(VAO1);
	GlPainter::vao.push_back(VBO1);

}
