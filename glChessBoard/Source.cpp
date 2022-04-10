//#include <wglew.h>
#ifdef _DEBUG
#pragma comment(lib, "glfw3d.lib")
#else
#pragma comment(lib, "glfw3.lib")
#endif
#pragma comment(lib, "opengl32.lib")
#include "Socket/socketManager.h"
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
#include "Rule/WuziqiRule.h"
#include "Rule/ChessMapData.h"
#include "CallBack/mouse_click_callback.h"
#include "CallBack/PosMessage.h"
#include "ThirdParty/event/szevent.h"
#include "eventHandle/ruleHandle.h"


#include <thread>
namespace sh {
	BoardLocation* ptrBoardLoc;
	GlCirclePainter* ptrChessWhitePainter;
	GlCirclePainter* ptrChessBlackPainter;
	int chessCorlor;

	PlayChessHandle playChessHandle;
}
sz::event<PosMessage::MessageUnit> ruleEvnet;
sz::event<GLFWwindow *, double, double> drawChessEvent;

using std::cout;
using std::endl;
int main()
{
	//PlayRule<ChessMapData> chessRule;
	ChessMapData chessMapData;
	sh::playChessHandle.setMapData(&chessMapData);

	ruleEvnet.add(ruleHandle);
	drawChessEvent.add(handlePos);

	SocketManager socketConnection;
	std::thread socketThread(&SocketManager::buidConnection, &socketConnection
		, AF_INET, 0x7f000001, "8198");

	std::thread boardLoopRender([&]() {
		GlfwConfigure* myConfig = GlfwConfigure::getInstance();
		GLFWwindow* window = myConfig->getGlfWindowHandle();

		BoardLocation boardLoc(WINDOWS_WIDTH, WINDOWS_HEIGHT, 10, 10);
		int width = boardLoc.getWidth();
		BoardLocation::MapLoca mapLoca = boardLoc.getAllPoint();

		sh::playChessHandle.setBoardLocation(&boardLoc);
		sh::ptrBoardLoc = &boardLoc;

		GlCirclePainter chessWhitePainter(WINDOWS_WIDTH, WINDOWS_HEIGHT);
		GlCirclePainter chessBlackPainter(WINDOWS_WIDTH, WINDOWS_HEIGHT, CorlorChess::black);

		sh::playChessHandle.setWhitePainter(&chessWhitePainter);
		sh::playChessHandle.setBlackPainter(&chessBlackPainter);
		sh::ptrChessWhitePainter = &chessWhitePainter;
		sh::ptrChessBlackPainter = &chessBlackPainter;

		sh::chessCorlor = 2;//black chess;

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
	socketConnection.close();
	socketThread.join();
	return 0;
}