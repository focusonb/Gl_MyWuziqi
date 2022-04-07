#include "PosEvent.h"

bool PosMessage::readUnit(MessageUnit& unit)
{
	std::lock_guard<mutex> lc(m_mutex);
	if (m_messageDeque.empty() == true)
		return false;
	unit = std::move(m_messageDeque.front());
	m_messageDeque.erase(m_messageDeque.begin());
	return true;
}

void PosMessage::writeUnit(MessageUnit& unit)
{
	std::lock_guard<mutex> lc(m_mutex);
	m_messageDeque.push_back(unit);
	//m_messageDeque.push_back(std::move(unit));
}
