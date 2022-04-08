#pragma once
#include <iostream>
using std::cout;
using std::endl;

template<typename DataType>
class PlayRule
{
	using ChessData = typename DataType::SigleChessLoca;
	using ChessLocation = typename DataType::ChessLocation;
	using ChessColor = typename DataType::ChessColor;
public:
	PlayRule():m_chessData(nullptr), m_currentChess(nullptr){};
	PlayRule(const PlayRule&playRule)
		:m_chessData(new DataType(*(playRule.m_chessData)))
		, m_currentChess (new ChessData(*(playRule.m_currentChess)))
		, m_max (playRule.m_max){}

	PlayRule(PlayRule&&playRule)
		:m_chessData(playRule.m_chessData)
		, m_currentChess(playRule.m_currentChess)
		, m_max(playRule.m_max)
	{
		playRule.m_chessData = nullptr;
		playRule.m_currentChess = nullptr;
	}

	PlayRule(DataType& data, const ChessData& currentChess, const int& max)
		:m_chessData(new DataType(data))
		, m_currentChess(new ChessData(currentChess))
		,m_max(max){ }

	void operator =(PlayRule&&playRule) {
		m_chessData = playRule.m_chessData;
		m_currentChess = playRule.m_currentChess;
		m_max = playRule.m_max;
		playRule.m_chessData = nullptr;
		playRule.m_currentChess = nullptr;
	}
	bool isEmpty() {
		return (m_chessData == nullptr || m_currentChess == nullptr);
	}

	bool isWin()const {
		return isWin(*m_currentChess, m_max);
	};
	~PlayRule() {
		delete m_chessData;
		delete m_currentChess;
	}
protected:
	//bool getMaxNum(const ChessData& chessLocation) const;
	bool isWin(const ChessData& chessLocation, int max)const;
	int getLeftUpNum(ChessData chessLocation) const;
	int getLeftDownNum(ChessData chessLocation) const;
	int getRightUpNum(ChessData chessLocation) const;
	int getRightDownNum(ChessData chessLocation) const;
	int getUpNum(ChessData chessLocation) const;
	int getDownNum(ChessData chessLocation) const;
	int getLeftNum(ChessData chessLocation) const;
	int getRightNum(ChessData chessLocation) const;
	void setNewData(const DataType& data) { *m_chessData = data; }
private:
	DataType* m_chessData;
	ChessData* m_currentChess;
	int m_max;
};

template<typename DataType>
inline bool PlayRule<DataType>::isWin(const ChessData& chessLocation, int max) const
{
	if (getLeftUpNum(chessLocation) + getRightDownNum(chessLocation) + 1 >= max
		|| getRightUpNum(chessLocation) + getLeftDownNum(chessLocation) + 1 >= max
		|| getUpNum(chessLocation) + getDownNum(chessLocation) + 1 >= max
		|| getLeftNum(chessLocation) + getRightNum(chessLocation) + 1 >= max)
		return true;
	else
		//cout << getLeftUpNum(chessLocation) + getRightDownNum(chessLocation) + 1 << endl;
		//cout << getRightUpNum(chessLocation) + getLeftDownNum(chessLocation) + 1 << endl;
		//cout << getUpNum(chessLocation) + getDownNum(chessLocation) + 1 << endl;
		//cout << getLeftNum(chessLocation) + getRightNum(chessLocation) + 1 << endl;
		return false;
}

template<typename DataType>
inline int PlayRule<DataType>::getLeftUpNum(ChessData chessLocation) const
{
	int num = 0;
	while (m_chessData->getColor(chessLocation.getLeftUpLoc()) == m_chessData->getColor(chessLocation.getLoc()) &&
		m_chessData->getColor(chessLocation.getLoc())!=0)
	{
		++num;
		ChessLocation chessLoca = chessLocation.getLeftUpLoc();
		chessLocation.setLoca(chessLoca);
	}
	return num;
}
template<typename DataType>
inline int PlayRule<DataType>::getLeftDownNum(ChessData chessLocation) const
{
	int num = 0;
	while (m_chessData->getColor(chessLocation.getLeftDownLoc()) == m_chessData->getColor(chessLocation.getLoc())&&
		m_chessData->getColor(chessLocation.getLoc()) != 0)
	{
		++num;
		ChessLocation chessLoca = chessLocation.getLeftDownLoc();
		chessLocation.setLoca(chessLoca);
	}
	return num;
}
template<typename DataType>
inline int PlayRule<DataType>::getRightUpNum(ChessData chessLocation) const
{
	int num = 0;
	while (m_chessData->getColor(chessLocation.getRightUpLoc()) == m_chessData->getColor(chessLocation.getLoc())&&
		m_chessData->getColor(chessLocation.getLoc()) != 0)
	{
		++num;
		ChessLocation chessLoca = chessLocation.getRightUpLoc();
		chessLocation.setLoca(chessLoca);
	}
	return num;
}
template<typename DataType>
inline int PlayRule<DataType>::getRightDownNum(ChessData chessLocation) const
{
	int num = 0;
	while (m_chessData->getColor(chessLocation.getRightDownLoc()) == m_chessData->getColor(chessLocation.getLoc())&&
		m_chessData->getColor(chessLocation.getLoc()) != 0)
	{
		int c = m_chessData->getColor(chessLocation.getRightDownLoc());
		int d = m_chessData->getColor(chessLocation.getLoc());
		++num;
		ChessLocation chessLoca = chessLocation.getRightDownLoc();
		chessLocation.setLoca(chessLoca);
	}
	return num;
}
template<typename DataType>
inline int PlayRule<DataType>::getUpNum(ChessData chessLocation) const
{
	int num = 0;
	while (m_chessData->getColor(chessLocation.getUpLoc()) == m_chessData->getColor(chessLocation.getLoc())&&
		m_chessData->getColor(chessLocation.getLoc()) != 0)
	{
		++num;
		ChessLocation chessLoca = chessLocation.getUpLoc();
		chessLocation.setLoca(chessLoca);
	}
	return num;
}
template<typename DataType>
inline int PlayRule<DataType>::getDownNum(ChessData chessLocation) const
{
	int num = 0;
	while (m_chessData->getColor(chessLocation.getDownLoc()) == m_chessData->getColor(chessLocation.getLoc())&&
		m_chessData->getColor(chessLocation.getLoc()) != 0)
	{
		++num;
		ChessLocation chessLoca = chessLocation.getDownLoc();
		chessLocation.setLoca(chessLoca);
	}
	return num;
}
template<typename DataType>
inline int PlayRule<DataType>::getLeftNum(ChessData chessLocation) const
{
	int num = 0;
	while (m_chessData->getColor(chessLocation.getLeftLoc()) == m_chessData->getColor(chessLocation.getLoc())&&
		m_chessData->getColor(chessLocation.getLoc()) != 0)
	{
		++num;
		ChessLocation chessLoca = chessLocation.getLeftLoc();
		chessLocation.setLoca(chessLoca);
	}
	return num;
}
template<typename DataType>
inline int PlayRule<DataType>::getRightNum(ChessData chessLocation) const
{
	int num = 0;
	while (m_chessData->getColor(chessLocation.getRightLoc()) == m_chessData->getColor(chessLocation.getLoc())&&
		m_chessData->getColor(chessLocation.getLoc()) != 0)
	{
		++num;
		ChessLocation chessLoca = chessLocation.getRightLoc();
		chessLocation.setLoca(chessLoca);
	}
	return num;
}