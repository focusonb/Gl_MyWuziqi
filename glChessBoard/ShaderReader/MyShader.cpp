#include "MyShader.h"
#include <string.h>
#include <iostream>
#include "FIleManager/WFIleTextManager.h"


MyShader::MyShader(const char* vertex, const char* fragment)
{
	size_t vertexLength = strlen(vertex) + 1;
	m_vertexShaderSource = new char[vertexLength];
	strcpy_s(m_vertexShaderSource, vertexLength, vertex);
	size_t fragmentLength = strlen(fragment) + 1;
	m_fragmentShaderSource = new char[strlen(fragment) + 1];
	strcpy_s(m_fragmentShaderSource, fragmentLength, fragment);
}
bool MyShader::configure()
{
	GLuint vertexShader;
	GLuint fragmentShader;
	if (loadShader(m_vertexShaderSource, GL_VERTEX_SHADER, &vertexShader) == false)
		return false;
	if (loadShader(m_fragmentShaderSource, GL_FRAGMENT_SHADER, &fragmentShader) == false)
		return false;

	if (vertexShader == 0 || fragmentShader == 0) {
		std::cout << "load shader failed" << std::endl;
		m_shaderProgram = 0;
		return false;
	}
	//link shader
	if (m_shaderProgram == 0)
		m_shaderProgram = glCreateProgram();
	glAttachShader(m_shaderProgram, vertexShader);
	glAttachShader(m_shaderProgram, fragmentShader);
	glLinkProgram(m_shaderProgram);
	int success;
	char infoLog[512];
	glGetProgramiv(m_shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(m_shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADERPROGRAM::FAILED\n" << infoLog << std::endl;
		return false;
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	return true;
}
int MyShader::getUniformId(const char * uniformName) const
{
	return glGetUniformLocation(m_shaderProgram, uniformName);
}

unsigned int MyShader::getShaderProgram() const
{
	return m_shaderProgram;
}

bool MyShader::loadShader(const char * source, int shaderType, GLuint* shader)
{
	//const char *shaderSource = m_ptr_controler->outPut();
	//if (shaderSource == nullptr)
	//{
	//	std::cout << "ERROR::GET_SHADERSOURCE_FAILED\n" << std::endl;
	//	return 0;
	//}
	*shader = glCreateShader(shaderType);
	glShaderSource(*shader, 1, &source, NULL);
	glCompileShader(*shader);
	//check shader compilation
	int  success;
	char infoLog[512];
	glGetShaderiv(*shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(*shader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
		return false;
	}
	return true;
}

void MyShader::setModelMatrix(const glm::mat4& mat)
{
	m_modelLoc = glGetUniformLocation(m_shaderProgram, "model");
	glUniformMatrix4fv(m_modelLoc, 1, GL_FALSE, glm::value_ptr(mat));
}

void MyShader::setViewMatrix(const glm::mat4& mat)
{
	m_viewLoc = glGetUniformLocation(m_shaderProgram, "view");
	glUniformMatrix4fv(m_viewLoc, 1, GL_FALSE, glm::value_ptr(mat));
}

void MyShader::setProjectionMatrix(const glm::mat4& mat)
{
	m_projectionLoc = glGetUniformLocation(m_shaderProgram, "projection");
	glUniformMatrix4fv(m_projectionLoc, 1, GL_FALSE, glm::value_ptr(mat));
}

void MyShader::setUniformVec3(const glm::vec3 & vec, const char * uniform)
{
	int uniformId = glGetUniformLocation(m_shaderProgram, uniform);
	glUniform3fv(uniformId, 1, &vec[0]);
}

void MyShader::setUniformFloat1(const float & value, const char * uniform)
{
	int uniformId = glGetUniformLocation(m_shaderProgram, uniform);
	glUniform1fv(uniformId, 1, &value);
}

void MyShader::setUniformInt1(const int & value, const char * uniform)
{
	glUniform1i(glGetUniformLocation(m_shaderProgram, uniform), value);
}
