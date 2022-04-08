#pragma once
#include "../Rule/ChessMapData.h"
#include "../Rule/WuziqiRule.h"
#include "BoardLocation.h"
#include "GlCirclePainter.h"

//extern GlCirclePainter* ptrChessWhitePainter;
//extern BoardLocation* ptrBoardLoc;
//extern ChessMapData* ptrChessMapData;
struct EventMessage {
	using ChessCorlor = int;
	using MessageUnit = PlayRule<ChessMapData>;
	ChessCorlor m_corlor;
	MessageUnit m_rule;
};

class PlayChessHandle {
public:
	PlayChessHandle() {}
	PlayChessHandle(GlCirclePainter* painter, BoardLocation* loca, ChessMapData*data)
		:m_ptrChessWhitePainter(painter), m_ptrBoardLoc(loca), m_ptrChessMapData(data){};

	bool operator()(GLFWwindow * window, const double& xpos, const double& ypos, EventMessage* message) {

		PointGl ChessCoor;
		BoardLocation::PointInt ChessSeq;
		int& color = message->m_corlor;

		if (m_ptrBoardLoc->getChessPointGl(xpos, ypos, ChessCoor) == false) {
			cout << "get chess location in window size failed" << endl;
			return false;
		};
		if (m_ptrBoardLoc->getChessPointInt(xpos, ypos, ChessSeq) == false) {
			cout << "get chess sequence failed" << endl;
			return false;
		};
		if (m_ptrChessMapData->getColor(ChessSeq) != 0) {
			return false;
		}

		int width = m_ptrBoardLoc->getWidth();
		switch (color) {
		case 1: {
			m_ptrChessWhitePainter->addOne(ChessCoor, width);//draw new chess
			break;
		}
		case 2: {
			m_ptrChessBlackPainter->addOne(ChessCoor, width);//draw new chess
			break;
		}
		}

		ChessMapData::SigleChessData sigleChessData(ChessSeq, color);
		m_ptrChessMapData->addNewChess(sigleChessData);//add new chess message into data

		//check if its win
		SigleChessLocation sigleChessLocation(ChessSeq);
		PlayRule<ChessMapData> rule(*m_ptrChessMapData, sigleChessLocation, 5);
		//cout << rule.isWin() << endl;
		message->m_rule = std::move(rule);
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