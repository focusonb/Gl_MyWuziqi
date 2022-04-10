#include "mouse_click_callback.h"
#include "../DrawBoard/PlayChessHandle.h"
#include "PosMessage.h"
#include "../header/Header.h"
#include "../ThirdParty/event/szevent.h"
#include "../ThirdParty/event/szcolored.h"

#include <glfw3.h>
#include <iostream>

#include <chrono>
using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::microseconds;


using std::cout;
using std::endl;
//using namespace sh;

extern sz::event<PosMessage::MessageUnit> ruleEvnet;
extern sz::event<GLFWwindow *, double, double> drawChessEvent;

void mouseClick_callback(GLFWwindow * window, int button, int xposIn, int yposIn)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT) {
		auto start = high_resolution_clock::now();
		//cout << xposIn << "  " << yposIn << endl;
		if (xposIn == 1) {
			return;
		}
		double xPos, yPos;
		glfwGetCursorPos(window, &xPos, &yPos);

		drawChessEvent(window, xPos, yPos);

		auto stop = high_resolution_clock::now();
		auto duration = duration_cast<microseconds>(stop - start);
		cout << duration.count() << endl;
	}
}

bool handlePos(GLFWwindow * window, double xPos, double yPos) {
	EventMessage message;
	message.m_corlor = sh::chessCorlor;
	if (sh::playChessHandle(window, xPos, yPos, &message) == false)
		return false;
	ruleEvnet.call_async(message.m_rule);


	//test
	switch (sh::chessCorlor) {
	case 1: {
		sh::chessCorlor = 2;
		break;
	}
	case 2: {
		sh::chessCorlor = 1;
		break;
	}
	}

	return true;
}
