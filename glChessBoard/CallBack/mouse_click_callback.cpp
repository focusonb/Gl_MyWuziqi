#include "mouse_click_callback.h"
#include "../DrawBoard/BoardLocation.h"
#include "../DrawBoard/GlCirclePainter.h"
#include "../Rule/ChessMapData.h"

#include "../Rule/WuziqiRule.h"


#include <glfw3.h>
#include <iostream>
using std::cout;
using std::endl;

void addNewChessAtCurPos(GLFWwindow * window) {
	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);

	PointGl ChessCoor;
	BoardLocation::PointInt ChessSeq;
	int color = 1;

	if (ptrBoardLoc->getChessPointGl(xpos, ypos, ChessCoor) == false) {
		cout << "get chess location in window size failed" << endl;
		return;
	};
	if (ptrBoardLoc->getChessPointInt(xpos, ypos, ChessSeq) == false) {
		cout << "get chess sequence failed" << endl;
		return;
	};

	int width = ptrBoardLoc->getWidth();
	ptrChessWhitePainter->addOne(ChessCoor, width);//draw new chess

	ChessMapData::SigleChessData sigleChessData(ChessSeq, color);
	ptrChessMapData->addNewChess(sigleChessData);//add new chess message into data

	//check if its win
	PlayRule<ChessMapData> rule(*ptrChessMapData);
	SigleChessLocation sigleChessLocation(ChessSeq);
	cout << rule.isWin(sigleChessLocation,5) << endl;
}

void mouseClick_callback(GLFWwindow * window, int button, int xposIn, int yposIn)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT) {
		addNewChessAtCurPos(window);
	}
}
