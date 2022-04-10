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