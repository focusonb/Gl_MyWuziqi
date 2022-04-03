#include "GlCirclePainter.h"
#include <glad/glad.h>
#include <glfw3.h>
#include "../CallBack/callback.h"

#include "../ShaderReader/MyShader.h"
#include "../TextureManager/TextureManager.h"
#include "../GlfwConfigure//GlfwConfigure.h"

#include <iostream>
using std::cout;
using std::endl;


static const char* vertextShaderPath = "shader/squareShader/vertextShaderSquareCenter.txt";
static const char* fragmentShaderPath = "shader/squareShader/fragmentShaderSquareCenter.txt";

static const char* texture = "texture1";
static const char* MY_IMAGE_PATH_1 = "image/whiteChess.jpg";
static const char* MY_IMAGE_PATH_2 = "image/blackChess.jpg";

static const int verticesNum = 270;
static const double circleVertices[verticesNum] = {
1, 0, -0.3, 2, 0.939692,
0.939692, 0.34202, -0.3, 1.87939, 0,
0, 0, -0.3, 0, 0.939692,
0.939692, 0.34202, -0.3, 1.87939, 0.766044,
0.766044, 0.642788, -0.3, 1.53209, 0,
0, 0, -0.3, 0, 0.766044,
0.766044, 0.642788, -0.3, 1.53209, 0.5,
0.5, 0.866026, -0.3, 1, 0,
0, 0, -0.3, 0, 0.5,
0.5, 0.866026, -0.3, 1, 0.173648,
0.173648, 0.984808, -0.3, 0.347296, 0,
0, 0, -0.3, 0, 0.173648,
0.173648, 0.984808, -0.3, 0.347296, -0.173648,
-0.173648, 0.984808, -0.3, -0.347296, 0,
0, 0, -0.3, 0, -0.173648,
-0.173648, 0.984808, -0.3, -0.347296, -0.5,
-0.5, 0.866026, -0.3, -1, 0,
0, 0, -0.3, 0, -0.5,
-0.5, 0.866026, -0.3, -1, -0.766044,
-0.766044, 0.642788, -0.3, -1.53209, 0,
0, 0, -0.3, 0, -0.766044,
-0.766044, 0.642788, -0.3, -1.53209, -0.939692,
-0.939692, 0.34202, -0.3, -1.87939, 0,
0, 0, -0.3, 0, -0.939692,
-0.939692, 0.34202, -0.3, -1.87939, -1,
-1, 5.35898e-08, -0.3, -2, 0,
0, 0, -0.3, 0, -1,
-1, 5.35898e-08, -0.3, -2, -0.939692,
-0.939692, -0.34202, -0.3, -1.87939, 0,
0, 0, -0.3, 0, -0.939692,
-0.939692, -0.34202, -0.3, -1.87939, -0.766044,
-0.766044, -0.642788, -0.3, -1.53209, 0,
0, 0, -0.3, 0, -0.766044,
-0.766044, -0.642788, -0.3, -1.53209, -0.5,
-0.5, -0.866026, -0.3, -1, 0,
0, 0, -0.3, 0, -0.5,
-0.5, -0.866026, -0.3, -1, -0.173648,
-0.173648, -0.984808, -0.3, -0.347296, 0,
0, 0, -0.3, 0, -0.173648,
-0.173648, -0.984808, -0.3, -0.347296, 0.173648,
0.173648, -0.984808, -0.3, 0.347296, 0,
0, 0, -0.3, 0, 0.173648,
0.173648, -0.984808, -0.3, 0.347296, 0.5,
0.5, -0.866026, -0.3, 1, 0,
0, 0, -0.3, 0, 0.5,
0.5, -0.866026, -0.3, 1, 0.766044,
0.766044, -0.642788, -0.3, 1.53209, 0,
0, 0, -0.3, 0, 0.766044,
0.766044, -0.642788, -0.3, 1.53209, 0.939692,
0.939692, -0.34202, -0.3, 1.87939, 0,
0, 0, -0.3, 0, 0.939692,
0.939692, -0.34202, -0.3, 1.87939, 1,
1, 0, -0.3, 2, 0,
0, 0, -0.3, 0, 4,
};




GlCirclePainter::GlCirclePainter(const PointGl& point, int width, CorlorChess color, int widthWindow, int heightWindow)
	:m_widthWindow(widthWindow), m_heightWindow(heightWindow)
{
	addOne(point, width);
	if (configureShader(color) == false) {
		cout << "configureShader failed" << endl;
	};

}

void GlCirclePainter::draw() const
{
	// bind textures on corresponding texture units
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture1);

	glUseProgram(shaderProgram);
	for (auto it : m_vao) {
		glBindVertexArray(it);
		glDrawArrays(GL_TRIANGLES, 0, verticesNum);
	}

}

void GlCirclePainter::setWindowSize(int widthWindow, int heightWindow)
{
	m_widthWindow = widthWindow;
	m_heightWindow = heightWindow;
}

void GlCirclePainter::addOne(const PointGl& point, int width)
{
	float k = static_cast<float>(width) / static_cast<float>(m_widthWindow);
	float offsetX = -1 + 2.0*static_cast<float>(point.first)/ static_cast<float>(m_widthWindow);
	float offsetY = 1 - 2.0*static_cast<float>(point.second) / static_cast<float>(m_heightWindow);


	volatile float tmp;
	int index;
	static float tmpVertices[verticesNum] = { 0 };
	for (int i = 0; i < (verticesNum / 5); ++i) {
		for (int j = 0; j < 5; ++j) {
			index = i * 5 + j;
			tmpVertices[index] = static_cast<float>(circleVertices[index]);
		}
	}

	for (int i = 0; i < (verticesNum/5); ++i) {
		for (int j = 0; j < 2; ++j) {
			switch (j) {
			case 0: {
				tmp = tmpVertices[i * 5 + j];
				tmpVertices[i * 5 + j] = tmp*k + offsetX;
				break;
			}
			case 1: {
				tmp = tmpVertices[i * 5 + j];
				tmpVertices[i * 5 + j] = tmp*k + offsetY;
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
	//glBufferData(GL_ARRAY_BUFFER, sizeof(circleVertices), circleVertices, GL_STATIC_DRAW);
	glBufferData(GL_ARRAY_BUFFER, sizeof(tmpVertices), tmpVertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	m_vao.push_back(VAO);
	GlPainter::vao.push_back(VAO);
	GlPainter::vao.push_back(VBO);
}

bool GlCirclePainter::configureShader(CorlorChess color)
{
	MyShader myShader(vertextShaderPath, fragmentShaderPath);

	//get shader program
	shaderProgram = myShader.getShaderProgram();

	TextureManager textureManager;
	textureManager.setChannelType(GL_RGB);
	switch (color) {
		case CorlorChess::white: {
			textureManager.loadImage(MY_IMAGE_PATH_1, texture1);
			break;
		}
		case CorlorChess::black: {
			textureManager.loadImage(MY_IMAGE_PATH_2, texture1);
			break;
		}
	}

	// tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
	// -------------------------------------------------------------------------------------------
	// either set it manually like so:
	glUniform1i(glGetUniformLocation(shaderProgram, texture), 0);
	glEnable(GL_DEPTH_TEST);
	if (shaderProgram == 0) {
		return false;
	}
	return true;
}
