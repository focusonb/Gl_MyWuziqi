#pragma once
#include "glSquarePainter.h"
#include "../ShaderReader/MyShader.h"

#include <memory>
using std::unique_ptr;

enum class CorlorChess { white,black};

class ShaderBuilder;

class GlCirclePainter : public GlPainter
{
public:
	GlCirclePainter(int widthWindow, int heightWindow, CorlorChess color = CorlorChess::white);
	GlCirclePainter(const PointGl& point, int width, CorlorChess color, int widthWindow, int heightWindow);
	void draw() const override;
	void setWindowSize(const int widthWindow, const int heightWindow);
	void setSize(const int& size) override {};
	void addOne(const PointGl& point, int width);
	~GlCirclePainter(){
		delete m_shaderManager;
	}
protected:
	bool configureShader(CorlorChess color);

private:
	GLuint VAO, VAO1, VBO, VBO1;
	unsigned int shaderProgram;
	unsigned int shaderProgramOutSquare;
	unsigned int texture1;
	int m_widthWindow;
	int m_heightWindow;

	list<GLuint> m_vao;
	list<GLuint> m_vao1;

	ShaderBuilder* m_shaderManager;
	unique_ptr<MyShader> m_myShader;
};