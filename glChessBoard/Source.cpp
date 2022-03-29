//#include <wglew.h>
#ifdef _DEBUG
#pragma comment(lib, "glfw3d.lib")
#else
#pragma comment(lib, "glfw3.lib")
#endif
#pragma comment(lib, "opengl32.lib")
#include <glad/glad.h>
#include <glfw3.h>
#include <iostream>
#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//#include "WFileTextManager.h"
#include "ShaderReader/FIleManager/FileManagerControler.h"
#include "ShaderReader/MyShader.h"
#include "myVertices.h"


#include "TextureManager/TextureManager.h"
#include "CallBack/callback.h"
#include "GlfwConfigure/GlfwConfigure.h"
#include "DrawBoard/glSquarePainter.h"


int main()
{
	GlfwConfigure* myConfig = GlfwConfigure::getInstance();
	GLFWwindow* window = myConfig->getGlfWindowHandle();

	GlSquarePainter square(pair<int,int>(0.000,0.000),800.000);

	while (!glfwWindowShouldClose(window))
	{
		processInput(window);
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		square.draw();


		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	GlPainter::deleteVertexArrays();
	GlPainter::deleteBuffers();
	glfwTerminate();
	return 0;
}