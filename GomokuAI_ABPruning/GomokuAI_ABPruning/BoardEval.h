#pragma once

#ifndef BOARDEVAL_H
#define BOARDEVAL_H

#define TIME_LIMIT 15

#include "Board.h"
#include <iostream>
#include <ctime>

class BoardEval
{
public:
	BoardEval();
	~BoardEval();
	bool checkWin(Board *gboard);
	int checkHorizontal(Board *gboard, int cur_player, int row, int col);
	int checkVertical(Board *gboard, int cur_player, int row, int col);
	int checkDiagonalA(Board *gboard, int cur_player, int row, int col);
	int checkDiagonalB(Board *gboard, int cur_player, int row, int col);
	void abPruning(Board *gboard);
	int max_Value(Board *gboard, int a, int b, int depth, clock_t s_time);
	int min_Value(Board *gboard, int a, int b, int depth, clock_t s_time);
	int evalFunc(Board *gboard);

	int agent_value[6] = { 0, 50, 500, 4000, 20000, 0 };
	int player_value[6] = {0, 0, -200, -15000, -50000, 0};
};

#endif