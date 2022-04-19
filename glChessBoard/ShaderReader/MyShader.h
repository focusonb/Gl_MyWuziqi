#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "FIleManager/FileManagerControler.h"
class FileManagerControler;
class MyShader
{
public:
	MyShader(const char* vertex, const char* fragment);
	~MyShader() { 
		delete m_vertexShaderSource;
		delete m_fragmentShaderSource;
	};

	bool configure();

	void setModelMatrix(const glm::mat4& mat);
	void setViewMatrix(const glm::mat4& mat);
	void setProjectionMatrix(const glm::mat4& mat);
	void setUniformVec3(const glm::vec3& vec, const char* uniform);
	void setUniformFloat1(const float& value, const char* uniform);
	void setUniformInt1(const int& value, const char* uniform);
	int getUniformId(const char*	uniformName) const;
	unsigned int getShaderProgram() const;
protected:
	bool loadShader(const char* source, int shaderType, GLuint* shader);

private:
	unsigned int m_shaderProgram;
	char* m_vertexShaderSource;
	char* m_fragmentShaderSource;
	int m_modelLoc;
	int m_viewLoc;
	int m_projectionLoc;
};
