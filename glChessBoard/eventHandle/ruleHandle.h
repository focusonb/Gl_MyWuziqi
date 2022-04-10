#pragma once

#include "../DrawBoard/PlayChessHandle.h"
#include "../CallBack/PosMessage.h"

void ruleHandle(PosMessage::MessageUnit rule) {
	cout << rule.isWin() << endl;
}