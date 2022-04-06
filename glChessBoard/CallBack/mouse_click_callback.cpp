#include "mouse_click_callback.h"
#include "../DrawBoard/PlayChessHandle.h"
#include "PosEvent.h"
#include "../header/Header.h"

#include <glfw3.h>
#include <iostream>

#include <chrono>
using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::microseconds;

PosEvent posEvent;


using std::cout;
using std::endl;



void mouseClick_callback(GLFWwindow * window, int button, int xposIn, int yposIn)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT) {
		auto start = high_resolution_clock::now();

		double xPos, yPos;
		glfwGetCursorPos(window, &xPos, &yPos);

		PlayRule<ChessMapData> rule;
		PlayChessHandle playChessHandle(ptrChessWhitePainter, ptrBoardLoc, ptrChessMapData);
		playChessHandle(window, xPos, yPos, rule);

		posEvent.send(rule);
		//posEvent();

		auto stop = high_resolution_clock::now();
		auto duration = duration_cast<microseconds>(stop - start);
		cout << duration.count() << endl;
	}

}

