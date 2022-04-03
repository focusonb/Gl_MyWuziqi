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
#include <Windows.h>
#include <iostream>


#include "ShaderReader/FIleManager/FileManagerControler.h"
#include "ShaderReader/MyShader.h"
#include "myVertices.h"


#include "TextureManager/TextureManager.h"
#include "CallBack/callback.h"
#include "GlfwConfigure/GlfwConfigure.h"
#include "DrawBoard/glSquarePainter.h"
#include "DrawBoard/GlCirclePainter.h"
#include <thread>


GlCirclePainter* ptrChessWhitePainter = nullptr;
BoardLocation* ptrBoardLoc = nullptr;

using std::cout;
using std::endl;
int main()
{
	std::thread boardLoopRender([&]() {
		GlfwConfigure* myConfig = GlfwConfigure::getInstance();
		GLFWwindow* window = myConfig->getGlfWindowHandle();

		BoardLocation boardLoc(WINDOWS_WIDTH, WINDOWS_HEIGHT, 10, 10);
		int width = boardLoc.getWidth();
		BoardLocation::MapLoca mapLoca = boardLoc.getAllPoint();
		ptrBoardLoc = &boardLoc;

		GlCirclePainter chessWhitePainter(pair<int,int>(0,0), width, CorlorChess::black, WINDOWS_WIDTH, WINDOWS_HEIGHT);
		GlCirclePainter chessBlackPainter(pair<int,int>(300,300), width, CorlorChess::white, WINDOWS_WIDTH, WINDOWS_HEIGHT);
		ptrChessWhitePainter = &chessBlackPainter;

		GlSquarePainter square;
		for (auto it : mapLoca) {
			square.addOne(it.first, width);
		}
		while (!glfwWindowShouldClose(window))
		{
			Sleep(30);
			processInput(window);
			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			square.draw();
			chessWhitePainter.draw();
			chessBlackPainter.draw();

			glfwSwapBuffers(window);
			glfwPollEvents();
		}
		GlPainter::deleteVertexArrays();
		GlPainter::deleteBuffers();
		glfwTerminate();
	});
	boardLoopRender.join();
	return 0;
}