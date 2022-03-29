#pragma once
#include "BoardLocation.h"
#include <list>
#include <glad/glad.h>

using std::list;

//static float squareVertices[] = {
//	0.55f, -0.55f, 0.0f,  1.0f, 0.0f,	//right down
//	-0.55f, -0.55f, 0.0f,  0.0f, 0.0f,	//left down
//	-0.55f,  0.55f, 0.0f,  0.0f, 1.0f,	//left up
//	0.55f,  0.55f, 0.0f,  1.0f, 1.0f,	//right up
//	0.55f, -0.55f, 0.0f,  1.0f, 0.0f,	//right down
//	-0.55f,  0.55f, 0.0f,  0.0f, 1.0f,	//left up
//};

static float squareVertices[] = {
	1.0f, -1.0f, 0.0f,  1.0f, 0.0f,	//right down
	-1.0f, -1.0f, 0.0f,  0.0f, 0.0f,	//left down
	-1.0f, 1.0f, 0.0f,  0.0f, 1.0f,	//left up
	1.0f, 1.0f, 0.0f,  1.0f, 1.0f,	//right up
	1.0f, -1.0f, 0.0f,  1.0f, 0.0f,	//right down
	-1.0f, 1.0f, 0.0f,  0.0f, 1.0f,	//left up
};

static float outSquareVertices[] = {
		0.9f, -0.9f, -0.1f,  0.0f, 255.0f,0.0f,	//right down
	-0.9f, -0.9f, -0.1f,  0.0f, 255.0f,0.0f,	//left down
	-0.9f,  0.9f, -0.1f,  0.0f, 255.0f,0.0f,	//left up
	0.9f,  0.9f, -0.1f,  0.0f, 255.0f,0.0f,	//right up
	0.9f, -0.9f, -0.1f,  0.0f, 255.0f,0.0f,	//right down
	-0.9f,  0.9f, -0.1f,  0.0f, 255.0f,0.0f,	//left up
};

extern struct GLFWwindow;
class GlPainter {
public:
	virtual void draw() const = 0;
	virtual void setSize(const int& size) = 0;
	static void deleteVertexArrays() {
		for (auto it : vao) {
			glDeleteVertexArrays(1, &it);
		}
	};
	static void deleteBuffers() {
		for (auto it : vbo) {
			glDeleteBuffers(1, &it);
		}
	}
protected:
	static list<GLuint> vao;
	static list<GLuint> vbo;
};

class GlSquarePainter : public GlPainter
{
public:
	GlSquarePainter(const PointGl& point, float width);
	void draw() const override;
	void setSize(const int& size) override {};
	void addOne(const PointGl& point, float width);

private:
	GLuint VAO, VAO1, VBO, VBO1;
	unsigned int shaderProgram;
	unsigned int shaderProgramOutSquare;
	unsigned int texture1;
	list<GLuint> m_vao;
	list<GLuint> m_vao1;
};
