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

	GlSquarePainter square;
	square.draw(spgl::PointGl(1.0f, 1.0f), window);


	return 0;
}