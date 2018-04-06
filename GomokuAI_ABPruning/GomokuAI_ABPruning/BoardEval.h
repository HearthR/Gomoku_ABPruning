#pragma once

#ifndef BOARDEVAL_H
#define BOARDEVAL_H
#include "Board.h"


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
	int max_Value(Board *gboard, int a, int b, int depth);
	int min_Value(Board *gboard, int a, int b, int depth);
	int evalFunc(Board *gboard);

	int agent_value[5] = { 0, 50, 300, 1500, 4000 };
	int player_value[5] = {0, 0, -200, -1500, -5000};
};

#endif