#pragma once
#include <map>

using std::map;
using std::pair;

namespace spgl {
	using GlSize = float;
	using PointGl = pair<GlSize, GlSize>;
};
using namespace spgl;
class BoardLocation
{
public:
	
	using PointInt = pair<int, int>;
	using MapLoca = map<PointGl, PointInt>;

	BoardLocation(GlSize width, GlSize height, int widNum,int heiNUm);

	bool getChessPointGl(GlSize cursor_width, GlSize cursor_height, PointGl& point) const;
	bool getChessPointInt(GlSize cursor_width, GlSize cursor_height, PointInt& point) const;
	MapLoca getAllPoint();

private:
	GlSize m_width;
	GlSize m_height;
	MapLoca m_loca;
};

