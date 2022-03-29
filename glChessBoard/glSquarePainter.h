#pragma once
#include "BoardLocation.h"

static float squareVertices[] = {
	0.55f, -0.55f, 0.0f,  1.0f, 0.0f,	//right down
	-0.55f, -0.55f, 0.0f,  0.0f, 0.0f,	//left down
	-0.55f,  0.55f, 0.0f,  0.0f, 1.0f,	//left up
	0.55f,  0.55f, 0.0f,  1.0f, 1.0f,	//right up
	0.55f, -0.55f, 0.0f,  1.0f, 0.0f,	//right down
	-0.55f,  0.55f, 0.0f,  0.0f, 1.0f,	//left up
};
static float outSquareVertices[] = {
		0.5f, -0.5f, -0.1f,  0.0f, 255.0f,0.0f,	//right down
	-0.5f, -0.5f, -0.1f,  0.0f, 255.0f,0.0f,	//left down
	-0.5f,  0.5f, -0.1f,  0.0f, 255.0f,0.0f,	//left up
	0.5f,  0.5f, -0.1f,  0.0f, 255.0f,0.0f,	//right up
	0.5f, -0.5f, -0.1f,  0.0f, 255.0f,0.0f,	//right down
	-0.5f,  0.5f, -0.1f,  0.0f, 255.0f,0.0f,	//left up
};

extern struct GLFWwindow;
class GlPainter
{
public:
	virtual void draw(const PointGl& point, GLFWwindow* window) const = 0;
	virtual void setSize(const GlSize& size) = 0;
};
class GlSquarePainter : public GlPainter
{
public:
	GlSquarePainter();
	void draw(const PointGl& point, GLFWwindow* window) const override;
	void setSize(const GlSize& size) override {};

private:
	unsigned int VAO, VAO1, VBO, VBO1;
	unsigned int shaderProgram;
	unsigned int shaderProgramOutSquare;
	unsigned int texture1;
};
