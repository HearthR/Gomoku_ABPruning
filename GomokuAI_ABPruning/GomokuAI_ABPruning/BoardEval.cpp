#include "BoardEval.h"


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
	
	for (int i = gboard->getLastRow() - 2; i < gboard->getLastRow() + 3; i++)
	{
		for (int j = gboard->getLastCol() - 2; j < gboard->getLastCol() + 3; j++)
		{
			if (i < 0 || i >= BOARD_ROW || j < 0 || j >= BOARD_COLUMN)
			{
				continue;
			}

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

				if (a == 5 || b == 5 || c == 5 || d == 5)
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
	
	for (int i = 0; i < 5; i++)
	{
		if (gboard->getBoardValue(row, col - 2 + i) == -cur_player)
		{
			return 0;
		}
		else if(gboard->getBoardValue(row, col - 2 + i) == cur_player)
		{
			stone_count++;
		}
		else
		{
			continue;
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

	for (int i = 0; i < 5; i++)
	{
		if (gboard->getBoardValue(row - 2 + i, col) == -cur_player)
		{
			return 0;
		}
		else if (gboard->getBoardValue(row - 2 + i, col) == cur_player)
		{
			stone_count++;
		}
		else
		{
			continue;
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

	for (int i = 0; i < 5; i++)
	{
		if (gboard->getBoardValue(row - 2 + i, col - 2 + i) == -cur_player)
		{
			return 0;
		}
		else if (gboard->getBoardValue(row - 2 + i, col - 2 + i) == cur_player)
		{
			stone_count++;
		}
		else
		{
			continue;
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

	for (int i = 0; i < 5; i++)
	{
		if (gboard->getBoardValue(row - 2 + i, col + 2 - i) == -cur_player)
		{
			return 0;
		}
		else if (gboard->getBoardValue(row - 2 + i, col + 2 - i) == cur_player)
		{
			stone_count++;
		}
		else
		{
			continue;
		}
	}

	return stone_count;
}

void BoardEval::abPruning(Board *gboard)
{
	Board tboard(gboard);
	int cur_depth_eval;
	int max_eval = INT_MIN;
	int max_eval_coor[2] = { 0, 0 };
	clock_t start_time = clock();

	for (int depth = 0;; depth++)
	{
//		std::cout << "Current depth: " << depth << std::endl;
		cur_depth_eval = max_Value(&tboard, INT_MIN, INT_MAX, depth, start_time);
//		std::cout << "cur_depth_eval: " << cur_depth_eval << " max_eval: " << max_eval <<  std::endl;

		if ((clock() - start_time) / CLOCKS_PER_SEC >= TIME_LIMIT)
		{
			break;
		}

		if (cur_depth_eval > max_eval)
		{
			tboard.setBestMove(max_eval_coor[0], max_eval_coor[1]);
			max_eval = cur_depth_eval;
		}
	}
//	std::cout << "final max_eval: " << max_eval << std::endl;
	gboard->setMove(tboard.getBestRow(), tboard.getBestCol());
}

int BoardEval::max_Value(Board *gboard, int a, int b, int depth, clock_t s_time)
{
	if (checkWin(gboard) || depth == 0 || (clock() - s_time) / CLOCKS_PER_SEC >= TIME_LIMIT)
	{
		return evalFunc(gboard);
	}

	int min_player_value;

	for (int i = 0; i < BOARD_ROW; i++)
	{
		for (int j = 0; j < BOARD_COLUMN; j++)
		{
			if (gboard->getBoardValue(i, j) == 0)
			{
				gboard->setMove(i, j);
			}
			else
			{
				continue;
			}

			min_player_value = min_Value(gboard, a, b, depth - 1, s_time);

			// max(alpha, min_val)
			if (min_player_value > a)
			{
				gboard->setBestMove(i, j);
				a = min_player_value;
			}

			gboard->resetMove(i, j);

			if (b <= a)
			{
//				std::cout << "Pruning occured!" << std::endl;
				return a;
			}
		}
	}

	return a;
}

int BoardEval::min_Value(Board *gboard, int a, int b, int depth, clock_t s_time)
{
	if (checkWin(gboard) || depth == 0 || (clock() - s_time) / CLOCKS_PER_SEC >= TIME_LIMIT)
	{
		return evalFunc(gboard);
	}

	int max_player_value;

	for (int i = 0; i < BOARD_ROW; i++)
	{
		for (int j = 0; j < BOARD_COLUMN; j++)
		{
			if (gboard->getBoardValue(i, j) == 0)
			{
				gboard->setMove(i, j);
			}
			else
			{
				continue;
			}

			max_player_value = max_Value(gboard, a, b, depth - 1, s_time);

			// min(beta, max_val)
			if (max_player_value < b)
			{
				gboard->setBestMove(i, j);
				b = max_player_value;
			}
			
			gboard->resetMove(i, j);

			if (b <= a)
			{
//				std::cout << "Pruning occured!" << std::endl;
				return b;
			}
		}
	}

	return b;
}

int BoardEval::evalFunc(Board *gboard)
{
	int stone_agent[6] = { 0, };
	int stone_player[6] = { 0, };
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

	if (stone_agent[5] > 0)
	{
		return INT_MAX;
	}
	else if (stone_player[5] > 0)
	{
		return INT_MIN;
	}
	else
	{
		for (int i = 0; i < 5; i++)
		{
			result += (agent_value[i] * stone_agent[i]) + (player_value[i] * stone_player[i]);
		}
	}

	return result;
}


//	When the first turn of the game
//	this function will be called to prevent useless calculation
void BoardEval::agentFirstMove(Board *gboard, int row, int col)
{
	int random_row = 1, random_col = 1;
	srand((unsigned int)time(NULL));

	//	Check if player's move is in middle area
	if (row >= (BOARD_ROW / 2) - 3 && row <= (BOARD_ROW / 2) + 3 && col >= (BOARD_COLUMN / 2) - 3 && col <= (BOARD_COLUMN / 2) + 3)
	{
		//	Agent makes move at random position among adjacent to the player's move
		while (random_row == 1 && random_col == 1)
		{
			random_row = rand() % 3;
			random_col = rand() % 3;
		}

		gboard->setMove(row - 1 + random_row, col - 1 + random_col);
	}
	else
	{
		//	Agent makes move at middle of the board
		gboard->setMove(BOARD_ROW / 2, BOARD_COLUMN / 2);
	}
}