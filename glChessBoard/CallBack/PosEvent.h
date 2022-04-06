#pragma once
#include <deque>
#include <tuple>
#include <mutex>
#include <windows.h>

#include "../header/Header.h"
#include "../DrawBoard/PlayChessHandle.h"

using std::tuple;
using std::pair;
using std::deque;
using std::mutex;

struct GLFWwindow;
class PosMessage {
public:
	using MessageUnit = PlayRule<ChessMapData>;
	bool readUnit(MessageUnit& unit);
	void writeUnit(MessageUnit& unit);
private:
	deque<MessageUnit> m_messageDeque;
	mutex m_mutex;
};

class PosEvent {
public:
	void send(PosMessage::MessageUnit& unit) {
		m_PosMessage.writeUnit(unit);
	};
	void handle() {
		while (1) {
			Sleep(200);
			PosMessage::MessageUnit unit;
			if (m_PosMessage.readUnit(unit) == false)
				continue;
			cout << unit.isWin() << endl;
		}
	};
private:
	PosMessage m_PosMessage;
};