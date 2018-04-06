#pragma once

#ifndef BOARD_H
#define BOARD_H

#define BOARD_ROW 15
#define BOARD_COLUMN 15

class Board
{
public:
	Board();
	Board(Board* other);
	~Board();
	void moveStone();
	int posTranslate(char input1);
	int getBoardValue(int x, int y);
	int *getLatestPos();
	void displayBoard();

	int game_board[BOARD_ROW][BOARD_COLUMN]; // 0 : empty, 1 : AI, -1: USER
	int status[2];
	bool playerflag; // true : AI, false : USER
};

#endif // !BOARD_H