#include "BoardLocation.h"

BoardLocation::BoardLocation(GlSize widthWindow, GlSize heightWindow, int widNum, int heiNum):
	m_widthWindow(widthWindow), m_heightWindow(heightWindow), m_widNum(widNum), m_heiNum(heiNum)
{
	m_width = widthWindow / (widNum + 4);
	m_height = heightWindow / (heiNum + 4);
	int posX = 0;
	int posY = 0;

	for (int i = 0; i < heiNum; ++i) {
		for (int j = 0; j < widNum; ++j) {
			posX = (j + 2)*m_width;
			posY = (i + 2)*m_height;
			m_loca.insert(pair< PointGl, PointInt>(PointGl(posX, posY), PointInt(j, i)));
		}
	}
}

void BoardLocation::resize(const GlSize widthWindow, const GlSize heightWindow)
{
	//float kWidth = static_cast<float>(widthWindow) / static_cast<float>(m_widthWindow);
	//float kHeight = static_cast<float>(heightWindow) / static_cast<float>(m_heightWindow);
	m_width = widthWindow / (m_widNum + 4);
	m_height = heightWindow / (m_heiNum + 4);
	m_widthWindow = widthWindow;
	m_heightWindow = heightWindow;
	int xPos;
	int yPos;
	MapLoca tmpLoca;
	for (int i = 0; i < m_heiNum; ++i) {
		for (int j = 0; j < m_widNum; ++j) {
			xPos = (j + 2)*m_width;
			yPos = (i + 2)*m_height;
			tmpLoca.insert(pair< PointGl, PointInt>(PointGl(xPos, yPos), PointInt(j, i)));
		}
	}
	m_loca.swap(tmpLoca);
}

bool BoardLocation::getChessPointGl(const GlSize cursorXPos, const GlSize cursorYPos, PointGl& point) const
{
	GlSize widOutput, heiOutput;
	int widNum = static_cast<int>(cursorXPos / m_width);
	GlSize nearestWidth = m_width * widNum;
	GlSize pointDistenceWid = cursorXPos - nearestWidth;
	if (widNum == 0)
		return false;
	else if (pointDistenceWid > 0.5* m_width)
		widOutput = nearestWidth + m_width;
	else
		widOutput = nearestWidth;

	int heiNum = static_cast<int>(cursorYPos / m_height);
	GlSize nearestHeight = m_height * heiNum;
	GlSize pointDistenceHei = cursorYPos - nearestHeight;
	if (heiNum == 0)
		return false;
	else if (pointDistenceHei > 0.5*m_width)
		heiOutput = nearestHeight + m_height;
	else
		heiOutput = nearestHeight;
	auto iterator = m_loca.find(PointGl(widOutput, heiOutput));
	if (iterator == m_loca.end())
		return false;
	point= PointGl(widOutput, heiOutput);
	return true;

}

bool BoardLocation::getChessPointInt(const GlSize cursor_width, const GlSize cursor_height, PointInt & point) const
{
	int widOutput, heiOutput;
	int widNum = static_cast<int>(cursor_width / m_width);
	GlSize nearestWidth = m_width * widNum;
	GlSize pointDistenceWid = cursor_width - nearestWidth;
	if (widNum == 0)
		return false;
	if (pointDistenceWid > 0.5* m_width)
		widOutput = 1 + widNum;
	else
		widOutput = widNum;
	int heiNum = static_cast<int>(cursor_height / m_height);
	GlSize nearestHeight = m_height * heiNum;
	GlSize pointDistenceHei = cursor_height - nearestHeight;
	if (heiNum == 0)
		return false;
	if (pointDistenceHei > 0.5* m_height)
		heiOutput = 1 + heiNum;
	else
		heiOutput = heiNum;
	auto iterator = m_loca.find(PointGl(widOutput*m_width, heiOutput*m_height));
	if (iterator == m_loca.end())
		return false;
	point = PointInt(widOutput, heiOutput);
	return true;
}

const GlSize BoardLocation::getWidth() const
{
	return m_width;
}

const BoardLocation::MapLoca BoardLocation::getAllPoint() const
{
	return m_loca;
}
