#pragma once
#include <glad/glad.h>
#include <list>
#include <vector>

#include "BoardLocation.h"
#include "GlPainter.h"
#include "../ShaderReader/MyShader.h"


#include <memory>
using std::unique_ptr;

using std::list;
using std::vector;
class ShaderBuilder;

//static float squareVertices[] = {
//	0.55f, -0.55f, 0.0f,  1.0f, 0.0f,	//right down
//	-0.55f, -0.55f, 0.0f,  0.0f, 0.0f,	//left down
//	-0.55f,  0.55f, 0.0f,  0.0f, 1.0f,	//left up
//	0.55f,  0.55f, 0.0f,  1.0f, 1.0f,	//right up
//	0.55f, -0.55f, 0.0f,  1.0f, 0.0f,	//right down
//	-0.55f,  0.55f, 0.0f,  0.0f, 1.0f,	//left up
//};


extern struct GLFWwindow;

class GlSquarePainter : public GlPainter
{
public:
	GlSquarePainter();
	GlSquarePainter(const PointGl& point, int width);
	void draw() const override;
	void setSize(const int& size) override {};
	void addOne(const PointGl& point, int width);
	~GlSquarePainter() {
		delete m_shaderManager;
		delete m_shaderManager2;
	}
protected:
	bool configureShader();

private:
	GLuint VAO, VAO1, VBO, VBO1;
	unsigned int shaderProgram;
	unsigned int shaderProgramOutSquare;
	unsigned int texture1;
	list<GLuint> m_vao;
	list<GLuint> m_vao1;

	ShaderBuilder* m_shaderManager;
	unique_ptr<MyShader> m_myShader;

	ShaderBuilder* m_shaderManager2;
	unique_ptr<MyShader> m_myShader2;
};
