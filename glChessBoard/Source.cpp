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
#include "FileManagerControler.h"
#include "MyShader.h"
#include "myVertices.h"


#include "TextureManager.h"
#include "callback.h"
#include "GlfwConfigure.h"
#include "glSquarePainter.h"

const int WINDOWS_HEIGHT = 900;
const int WINDOWS_WIDTH = 1200;
const int ViEW_HEIGHT = 900;
const int ViEW_WIDTH = 1200;

int main()
{
	GlfwConfigure* myConfig = GlfwConfigure::getInstance();
	GLFWwindow* window = myConfig->getGlfWindowHandle();

	GlSquarePainter square;

	square.draw(spgl::PointGl(1.0f, 1.0f), window);
	return 0;
}