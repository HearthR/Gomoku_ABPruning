#include <iostream>
#include "Board.h"
#include "BoardEval.h"
#include <iomanip>

using namespace std;



int main()
{
	Board board_init;
	BoardEval evaluator;
	
	board_init.game_board[10][10] = -1;
	board_init.game_board[10][11] = 1;
	board_init.game_board[9][10] = -1;
	board_init.game_board[11][10] = 1;


	for (int i = 0; i < 15; i++)
	{
		board_init.moveStone();
	}
	
	return 0;
}