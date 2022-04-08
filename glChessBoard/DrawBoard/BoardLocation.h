#pragma once
#include <map>

using std::map;
using std::pair;

namespace spgl {
	using GlSize = int;
	using PointGl = pair<GlSize, GlSize>;
};
using namespace spgl;
class BoardLocation
{
public:
	
	using PointInt = pair<int, int>;
	using MapLoca = map<PointGl, PointInt>;
	//widNUm is number of rows and collums of the board
	BoardLocation(GlSize widthWindow, GlSize heightWindow, int widNum,int heiNUm);
	void resize(const GlSize widthWindow, const GlSize heightWindow);

	bool getChessPointGl(const GlSize cursorXPos, const GlSize cursorYPos, PointGl& point) const;
	bool getChessPointInt(const GlSize cursorXPos, const GlSize cursorYPos, PointInt& point) const;
	
	const GlSize getWidth() const;
	const MapLoca getAllPoint() const;

private:
	GlSize m_width;
	GlSize m_height;
	GlSize m_widthWindow;
	GlSize m_heightWindow;
	int m_widNum;
	int m_heiNum;

	MapLoca m_loca;
};

