#include "BoardEval.h"
#include <iostream>


BoardEval::BoardEval()
{
}


BoardEval::~BoardEval()
{
}

bool BoardEval::checkWin(Board *gboard)
{
	int cur_player = 0;
	int a, b, c, d;
	
	for (int i = 0; i < BOARD_ROW; i++)
	{
		for (int j = 0; j < BOARD_COLUMN; j++)
		{
			cur_player = gboard->getBoardValue(i, j);

			if (cur_player == 0)
			{
				continue;
			}

			else
			{
				a = checkHorizontal(gboard, cur_player, i, j);
				b = checkVertical(gboard, cur_player, i, j);
				c = checkDiagonalA(gboard, cur_player, i, j);
				d = checkDiagonalB(gboard, cur_player, i, j);

//				std::cout << "Current: " << cur_player << " coor: " << i << j << " " << a << " " << b << " " << c << " " << d << std::endl;

				if (a == 4 || b == 4 || c == 4 || d == 4)
				{
					return true;
				}
			}
		}
	}

	return false;
}

int BoardEval::checkHorizontal(Board *gboard, int cur_player, int row, int col)
{
	int stone_count = 0;
	
	// board bound check
	if (col + 2 > BOARD_COLUMN || col - 2 < 0)
	{
		return stone_count;
	}
	
	if (cur_player == gboard->getBoardValue(row, col + 1))
	{
		if (cur_player == gboard->getBoardValue(row, col + 2))
		{
			stone_count += 2;
		}
		else
		{
			stone_count += 1;
		}
	}
	else
	{
		if (gboard->getBoardValue(row, col + 1) == 0 && cur_player == gboard->getBoardValue(row, col + 2))
		{
			stone_count += 1;
		}
	}

	if (cur_player == gboard->getBoardValue(row, col - 1))
	{
		if (cur_player == gboard->getBoardValue(row, col - 2))
		{
			stone_count += 2;
		}
		else
		{
			stone_count += 1;
		}
	}
	else
	{
		if (gboard->getBoardValue(row, col - 1) == 0 && cur_player == gboard->getBoardValue(row, col - 2))
		{
			stone_count += 1;
		}
	}


	return stone_count;
}

int BoardEval::checkVertical(Board *gboard, int cur_player, int row, int col)
{
	int stone_count = 0;

	// board bound check
	if (row + 2 > BOARD_ROW || row - 2 < 0)
	{
		return stone_count;
	}

	if (cur_player == gboard->getBoardValue(row + 1, col))
	{
		if (cur_player == gboard->getBoardValue(row + 2, col))
		{
			stone_count += 2;
		}
		else
		{
			stone_count += 1;
		}
	}
	else
	{
		if (gboard->getBoardValue(row + 1, col) == 0 && cur_player == gboard->getBoardValue(row + 2, col))
		{
			stone_count += 1;
		}
	}

	if (cur_player == gboard->getBoardValue(row - 1, col))
	{
		if (cur_player == gboard->getBoardValue(row - 2, col))
		{
			stone_count += 2;
		}
		else
		{
			stone_count += 1;
		}
	}
	else
	{
		if (gboard->getBoardValue(row - 1, col) == 0 && cur_player == gboard->getBoardValue(row - 2, col))
		{
			stone_count += 1;
		}
	}

	return stone_count;
}

int BoardEval::checkDiagonalA(Board *gboard, int cur_player, int row, int col)
{
	int stone_count = 0;

	// board bound check
	if (col + 2 > BOARD_COLUMN || row + 2 > BOARD_ROW || col - 2 < 0 || row - 2 < 0)
	{
		return stone_count;
	}

	if (cur_player == gboard->getBoardValue(row + 1, col + 1))
	{
		if (cur_player == gboard->getBoardValue(row + 2, col + 2))
		{
			stone_count += 2;
		}
		else
		{
			stone_count += 1;
		}
	}
	else
	{
		if (gboard->getBoardValue(row + 1, col + 1) == 0 && cur_player == gboard->getBoardValue(row + 2, col + 2))
		{
			stone_count += 1;
		}
	}

	if (cur_player == gboard->getBoardValue(row - 1, col - 1))
	{
		if (cur_player == gboard->getBoardValue(row - 2, col - 2))
		{
			stone_count += 2;
		}
		else
		{
			stone_count += 1;
		}
	}
	else
	{
		if (gboard->getBoardValue(row - 1, col - 1) == 0 && cur_player == gboard->getBoardValue(row - 2, col - 2))
		{
			stone_count += 1;
		}
	}

	return stone_count;
}

int BoardEval::checkDiagonalB(Board *gboard, int cur_player, int row, int col)
{
	int stone_count = 0;

	// board bound check
	if (col + 2 > BOARD_COLUMN || row + 2 > BOARD_ROW || col - 2 < 0 || row - 2 < 0)
	{
		return stone_count;
	}

	if (cur_player == gboard->getBoardValue(row + 1, col - 1))
	{
		if (cur_player == gboard->getBoardValue(row + 2, col - 2))
		{
			stone_count += 2;
		}
		else
		{
			stone_count += 1;
		}
	}
	else
	{
		if (gboard->getBoardValue(row + 1, col - 1) == 0 && cur_player == gboard->getBoardValue(row + 2, col - 2))
		{
			stone_count += 1;
		}
	}

	if (cur_player == gboard->getBoardValue(row - 1, col + 1))
	{
		if (cur_player == gboard->getBoardValue(row - 2, col + 2))
		{
			stone_count += 2;
		}
		else
		{
			stone_count += 1;
		}
	}
	else
	{
		if (gboard->getBoardValue(row - 1, col + 1) == 0 && cur_player == gboard->getBoardValue(row - 2, col + 2))
		{
			stone_count += 1;
		}
	}

	return stone_count;
}

void BoardEval::abPruning(Board *gboard)
{
	Board tboard(gboard);

	for (int depth = 0; depth < 2; depth++)	// 최선의 선택을 어떻게 저장(반환)할 것인지 다시 생각해보기
	{										// pruning이 제대로 되는지 확인해보기(시간), evaluation function 다시 확인, check함수들 다시 확인
		std::cout << depth << std::endl;
		max_Value(&tboard, INT_MIN, INT_MAX, depth);
	}

	gboard->game_board[tboard.status[0]][tboard.status[1]] = 1;
}

int BoardEval::max_Value(Board *gboard, int a, int b, int depth)
{
	if (depth == 0 || checkWin(gboard))
	{
//		gboard->displayBoard();
//		std::cout << evalFunc(gboard) << std::endl;
		return evalFunc(gboard);
	}

	int min_player_value;

	for (int i = 0; i < BOARD_ROW; i++)
	{
		for (int j = 0; j < BOARD_COLUMN; j++)
		{
			if (gboard->game_board[i][j] == 0)
			{
//				gboard->status[0] = i;
//				gboard->status[1] = j;
				gboard->game_board[i][j] = 1;
			}
			else
			{
				continue;
			}

			min_player_value = min_Value(gboard, a, b, depth - 1);

			// max(alpha, min_val)
			if (min_player_value > a)
			{
				gboard->status[0] = i;
				gboard->status[1] = j;
				a = min_player_value;
			}

			gboard->game_board[i][j] = 0;

			if (b <= a)
			{
				return a;
			}
		}
	}

	return a;
}

int BoardEval::min_Value(Board *gboard, int a, int b, int depth)
{
	if (depth == 0 || checkWin(gboard))
	{
//		std::cout << a << " " << b << std::endl;
		return evalFunc(gboard);
	}
	int max_player_value;

	for (int i = 0; i < BOARD_ROW; i++)
	{
		for (int j = 0; j < BOARD_COLUMN; j++)
		{
			if (gboard->game_board[i][j] == 0)
			{
//				gboard->status[0] = i;
//				gboard->status[1] = j;
				gboard->game_board[i][j] = -1;
			}
			else
			{
				continue;
			}

			max_player_value = max_Value(gboard, a, b, depth - 1);

			// min(beta, max_val)
			if (max_player_value < b)
			{
				gboard->status[0] = i;
				gboard->status[1] = j;
				b = max_player_value;
			}
			
			gboard->game_board[i][j] = 0;

			if (b <= a)
			{
				return b;
			}
		}
	}

	return b;
}

int BoardEval::evalFunc(Board *gboard)
{
	int cur_player = gboard->playerflag ? 1 : -1;
	int a, b, c, d;
	int stone_agent[5] = { 0, };
	int stone_player[5] = { 0, };
	int result = 0;

	for (int i = 0; i < BOARD_ROW; i++)
	{
		for (int j = 0; j < BOARD_COLUMN; j++)
		{
			stone_agent[checkHorizontal(gboard, 1, i, j)] += 1;
			stone_agent[checkVertical(gboard, 1, i, j)] += 1;
			stone_agent[checkDiagonalA(gboard, 1, i, j)] += 1;
			stone_agent[checkDiagonalB(gboard, 1, i, j)] += 1;
		}
	}

	for (int i = 0; i < BOARD_ROW; i++)
	{
		for (int j = 0; j < BOARD_COLUMN; j++)
		{
			stone_player[checkHorizontal(gboard, -1, i, j)] += 1;
			stone_player[checkVertical(gboard, -1, i, j)] += 1;
			stone_player[checkDiagonalA(gboard, -1, i, j)] += 1;
			stone_player[checkDiagonalB(gboard, -1, i, j)] += 1;
		}
	}

	for (int i = 0; i < 5; i++)
	{
		result += (agent_value[i] * stone_agent[i]) + (player_value[i] * stone_player[i]);
	}

	return result;
}