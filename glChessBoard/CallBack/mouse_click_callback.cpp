#include "mouse_click_callback.h"
#include "../DrawBoard/BoardLocation.h"
#include "../DrawBoard/GlCirclePainter.h"


#include <glfw3.h>
#include <iostream>
using std::cout;
using std::endl;


void mouseClick_callback(GLFWwindow * window, int button, int xposIn, int yposIn)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT) {
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);

		PointGl ChessCoor;
		//ptrBoardLoc->resize(widthWindow, heightWindow);
		ptrBoardLoc->getChessPointGl(xpos, ypos, ChessCoor);
		int width = ptrBoardLoc->getWidth();
		ptrChessWhitePainter->addOne(ChessCoor, width);
	}
}
