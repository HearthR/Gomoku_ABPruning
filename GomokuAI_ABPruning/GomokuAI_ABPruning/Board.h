#pragma once

#ifndef BOARD_H
#define BOARD_H

#define BOARD_ROW 19		// Board size must be 
#define BOARD_COLUMN 19		// bigger than 11 * 11

#include <iostream>
#include <iomanip>

class Board
{
public:
	Board();
	Board(Board* other);
	~Board();
	void moveStone();
	int posTranslate(char row);
	int getBoardValue(int row, int col);
	int getLastRow();
	int getLastCol();
	bool getCurrentPlayer();
	int getBestRow();
	int getBestCol();
	void setMove(int row, int col);
	void resetMove(int row, int col);
	void setBestMove(int row, int col);
	bool isWin();
	void displayBoard();

private:
	int game_board[BOARD_ROW][BOARD_COLUMN];	//	0 : empty,  1 : AI,  -1: USER
	int bestmove[2];	//	AI가 판단한 가장 최적의 수를 저장
	int lastmove[2];	//	가장 마지막에 둔 수를 저장
	bool playerflag;	//	true : AI, false : USER
	int game_turn;
	bool winflag;
};

#endif // !BOARD_H