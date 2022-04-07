#pragma once
#include "../Rule/ChessMapData.h"
#include "../Rule/WuziqiRule.h"
#include "BoardLocation.h"
#include "GlCirclePainter.h"

//extern GlCirclePainter* ptrChessWhitePainter;
//extern BoardLocation* ptrBoardLoc;
//extern ChessMapData* ptrChessMapData;

class PlayChessHandle {
public:
	PlayChessHandle() {}
	PlayChessHandle(GlCirclePainter* painter, BoardLocation* loca, ChessMapData*data)
		:m_ptrChessWhitePainter(painter), m_ptrBoardLoc(loca), m_ptrChessMapData(data){};

	bool operator()(GLFWwindow * window, const double& xpos, const double& ypos, PlayRule<ChessMapData>& playRule) {

		PointGl ChessCoor;
		BoardLocation::PointInt ChessSeq;
		int color = 1;

		if (m_ptrBoardLoc->getChessPointGl(xpos, ypos, ChessCoor) == false) {
			cout << "get chess location in window size failed" << endl;
			return false;
		};
		if (m_ptrBoardLoc->getChessPointInt(xpos, ypos, ChessSeq) == false) {
			cout << "get chess sequence failed" << endl;
			return false;
		};

		int width = m_ptrBoardLoc->getWidth();
		m_ptrChessWhitePainter->addOne(ChessCoor, width);//draw new chess

		ChessMapData::SigleChessData sigleChessData(ChessSeq, color);
		m_ptrChessMapData->addNewChess(sigleChessData);//add new chess message into data

		//check if its win
		SigleChessLocation sigleChessLocation(ChessSeq);
		PlayRule<ChessMapData> rule(*m_ptrChessMapData, sigleChessLocation, 5);
		//cout << rule.isWin() << endl;
		playRule = std::move(rule);
		return true;

	};

	void setWhitePainter(GlCirclePainter* painter) {
		m_ptrChessWhitePainter = painter;
	}
	void setBlackPainter(GlCirclePainter* painter) {
		m_ptrChessBlackPainter = painter;
	}
	void setBoardLocation(BoardLocation*boardLocation) {
		m_ptrBoardLoc = boardLocation;
	}
	void setMapData(ChessMapData*data) {
		m_ptrChessMapData = data;
	}
private:
	GlCirclePainter* m_ptrChessWhitePainter;
	BoardLocation* m_ptrBoardLoc;
	ChessMapData* m_ptrChessMapData;
	GlCirclePainter* m_ptrChessBlackPainter;
};