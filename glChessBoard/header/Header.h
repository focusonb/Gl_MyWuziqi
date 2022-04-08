#pragma once



class ChessMapData;
extern ChessMapData* ptrChessMapData;

class PosMessage;
extern PosMessage posMessage;

class PosEvent;
class PlayChessHandle;
class GlCirclePainter;
class BoardLocation;

namespace sh {
	extern PosEvent posEvent;
	extern PlayChessHandle playChessHandle;
	extern GlCirclePainter* ptrChessWhitePainter;
	extern GlCirclePainter* ptrChessBlackPainter;
	extern BoardLocation* ptrBoardLoc;
	extern int chessCorlor;
}

//namespace sh;