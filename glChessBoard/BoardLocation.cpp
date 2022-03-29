#include "BoardLocation.h"

BoardLocation::BoardLocation(GlSize width, GlSize height, int widNum, int heiNUm)
{

}

bool BoardLocation::getChessPointGl(GlSize cursor_width, GlSize cursor_height, PointGl& point) const
{
	GlSize widOutput, heiOutput;
	int widNum = static_cast<int>(cursor_width / m_width);
	GlSize nearestWidth = m_width * widNum;
	GlSize pointDistenceWid = cursor_width - nearestWidth;
	if (pointDistenceWid > 0.5* cursor_width)
		widOutput = nearestWidth + m_width;
	else
		widOutput = nearestWidth;
	int heiNum = static_cast<int>(cursor_height / m_height);
	GlSize nearestHeight = m_height * heiNum;
	GlSize pointDistenceHei = cursor_height - nearestHeight;
	if (pointDistenceHei > 0.5*cursor_height)
		heiOutput = pointDistenceHei + m_height;
	else
		heiOutput = pointDistenceHei;
	auto iterator = m_loca.find(PointGl(widOutput, heiOutput));
	if (iterator == m_loca.end())
		return false;
	point= PointGl(widOutput, heiOutput);
	return true;

}

bool BoardLocation::getChessPointInt(GlSize cursor_width, GlSize cursor_height, PointInt & point) const
{
	int widOutput, heiOutput;
	int widNum = static_cast<int>(cursor_width / m_width);
	GlSize nearestWidth = m_width * widNum;
	GlSize pointDistenceWid = cursor_width - nearestWidth;
	if (pointDistenceWid > 0.5* cursor_width)
		widOutput = 1 + widNum;
	else
		widOutput = widNum;
	int heiNum = static_cast<int>(cursor_height / m_height);
	GlSize nearestHeight = m_height * heiNum;
	GlSize pointDistenceHei = cursor_height - nearestHeight;
	if (pointDistenceHei > 0.5* cursor_height)
		heiOutput = 1 + heiNum;
	else
		heiOutput = heiNum;
	auto iterator = m_loca.find(PointGl(widOutput*m_width, heiOutput*m_height));
	if (iterator == m_loca.end())
		return false;
	point = PointInt(widOutput, heiOutput);
	return true;
}

BoardLocation::MapLoca BoardLocation::getAllPoint()
{
	return m_loca;
}
