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

	//	가장 마지막에 둔 수를 중심으로 5*5 영역만 체크하도록 범위를 제한합니다.
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
		//	상대편의 돌이 발견되면 0을 반환합니다.
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
		//	상대편의 돌이 발견되면 0을 반환합니다.
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
		//	상대편의 돌이 발견되면 0을 반환합니다.
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
		//	상대편의 돌이 발견되면 0을 반환합니다.
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
	int max_eval_value = INT_MIN;
	int max_eval_coor[2] = { 0, 0 };
	clock_t start_time = clock();

	//	Iterative deepening
	for (int depth = 0;; depth++)
	{

		cur_depth_eval = max_Value(&tboard, INT_MIN, INT_MAX, depth, start_time);

		//	시간제한을 초과했는지 체크합니다.
		if ((clock() - start_time) / CLOCKS_PER_SEC >= TIME_LIMIT)
		{
			break;
		}

		//	현재 depth의 결과와 이전 depth의 결과 중 더 큰 결과를 저장합니다.
		if (cur_depth_eval > max_eval_value)
		{
			max_eval_value = cur_depth_eval;
			max_eval_coor[0] = tboard.getBestRow();
			max_eval_coor[1] = tboard.getBestCol();
		}
	}

	gboard->setMove(max_eval_coor[0], max_eval_coor[1]);
}

int BoardEval::max_Value(Board *gboard, int a, int b, int depth, clock_t s_time)
{
	//	terminal state인지, depth가 0인지, 시간제한을 초과했는지 체크합니다.
	if (checkWin(gboard) || depth == 0 || (clock() - s_time) / CLOCKS_PER_SEC >= TIME_LIMIT)
	{
		return evalFunc(gboard);
	}

	int min_player_value;

	for (int i = 0; i < BOARD_ROW; i++)
	{
		for (int j = 0; j < BOARD_COLUMN; j++)
		{
			//	legal move인지 체크합니다.
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
			//	다음 state를 위해 이번 state에서 취한 action을 초기화합니다.
			gboard->resetMove(i, j);

			if (b <= a)
			{
				return a;
			}
		}
	}

	return a;
}

int BoardEval::min_Value(Board *gboard, int a, int b, int depth, clock_t s_time)
{
	//	terminal state인지, depth가 0인지, 시간제한을 초과했는지 체크합니다.
	if (checkWin(gboard) || depth == 0 || (clock() - s_time) / CLOCKS_PER_SEC >= TIME_LIMIT)
	{
		return evalFunc(gboard);
	}

	int max_player_value;

	for (int i = 0; i < BOARD_ROW; i++)
	{
		for (int j = 0; j < BOARD_COLUMN; j++)
		{
			//	legal move인지 체크합니다.
			if (gboard->getBoardValue(i, j) == 0)
			{
				gboard->setMove(i, j);
			}
			else
			{
				continue;
			}

			max_player_value = max_Value(gboard, a, b, depth - 1, s_time);

			//	min(beta, max_val)
			if (max_player_value < b)
			{
				b = max_player_value;
			}
			//	다음 state를 위해 이번 state에서 취한 action을 초기화합니다.
			gboard->resetMove(i, j);

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
	int stone_agent[6] = { 0, };
	int stone_player[6] = { 0, };
	int result = 0;

	//	보드의 모든 위치에 대해 점수를 산출합니다.
	for (int i = 0; i < BOARD_ROW; i++)
	{
		for (int j = 0; j < BOARD_COLUMN; j++)
		{
			//	각 check 함수들은 보드의 i, j 위치를 중심으로 각 방향에 맞게 5칸을 살펴보는데,
			//	만약 5칸 안에 cur_player의 상대편의 돌이 하나라도 발견된다면 0을 반환하고
			//	상대편의 돌이 없다면 5칸 안에 들어있는 cur_player의 돌의 개수를 반환합니다.
			//	이는 5칸 안에 돌을 계속해서 뒀을 경우 이길 수 있는 유효한 위치를 판별합니다.
			stone_agent[checkHorizontal(gboard, 1, i, j)] += 1;
			stone_agent[checkVertical(gboard, 1, i, j)] += 1;
			stone_agent[checkDiagonalA(gboard, 1, i, j)] += 1;
			stone_agent[checkDiagonalB(gboard, 1, i, j)] += 1;

			stone_player[checkHorizontal(gboard, -1, i, j)] += 1;
			stone_player[checkVertical(gboard, -1, i, j)] += 1;
			stone_player[checkDiagonalA(gboard, -1, i, j)] += 1;
			stone_player[checkDiagonalB(gboard, -1, i, j)] += 1;
		}
	}
	//	만약 5칸 안에 AI의 돌이 5개가 들어있는 위치가 한 번이라도 발견되었다면
	//	이는 AI의 승리를 의미하므로 최댓값을 반환합니다.
	if (stone_agent[5] > 0)
	{
		return INT_MAX;
	}
	//	만약 5칸 안에 player의 돌이 5개가 들어있는 위치가 한 번이라도 발견되었다면
	//	이는 player의 승리를 의미하므로 최솟값을 반환합니다.
	else if (stone_player[5] > 0)
	{
		return INT_MIN;
	}
	//	둘 다 아니라면 weight를 곱해서 점수를 산출합니다.
	else
	{
		for (int i = 0; i < 5; i++)
		{
			result += (agent_value[i] * stone_agent[i]) + (player_value[i] * stone_player[i]);
		}
	}

	return result;
}


//	만약 첫 번째 턴일 경우 이 함수가 호출됩니다.
void BoardEval::agentFirstMove(Board *gboard, int row, int col)
{
	int random_row = 1, random_col = 1;
	srand((unsigned int)time(NULL));

	//	플레이어가 둔 수가 보드의 중앙 영역에 있는지 체크합니다.
	if (row >= (BOARD_ROW / 2) - 3 && row <= (BOARD_ROW / 2) + 3 && col >= (BOARD_COLUMN / 2) - 3 && col <= (BOARD_COLUMN / 2) + 3)
	{
		//	AI는 플레이어가 둔 수에 인접한 위치 중 랜덤한 위치에 수를 둡니다.
		while (random_row == 1 && random_col == 1)
		{
			random_row = rand() % 3;
			random_col = rand() % 3;
		}

		gboard->setMove(row - 1 + random_row, col - 1 + random_col);
	}
	else
	{
		//	AI는 보드의 정 중앙에 수를 둡니다.
		gboard->setMove(BOARD_ROW / 2, BOARD_COLUMN / 2);
	}
}