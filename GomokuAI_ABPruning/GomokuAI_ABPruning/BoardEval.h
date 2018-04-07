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
	void agentFirstMove(Board *gboard, int row, int col);

private:
	int agent_value[6] = { 0, 3, 30, 150, 1500, 0 };	//	AI의 evaluation weight 값
	int player_value[6] = {0, 0, -20, -3000, -10000, 0};//	player의 evaluation weight 값
};

#endif