#include "Board.h"
#include "BoardEval.h"
#include <iostream>

using namespace std;

int main()
{
	Board board_init;
	BoardEval evaluator;
	
	cout << "\n\n";
	wcout << "\t######################################" << endl;
	wcout << "\t####                              ####" << endl;
	wcout << "\t####     ¡Ü = Black (You)         ####" << endl;
	wcout << "\t####     ¡Û = White (Computer)    ####" << endl;
	wcout << "\t####                              ####" << endl;
	wcout << "\t######################################\n\n" << endl;

	while (!board_init.isWin())
	{
		board_init.displayBoard();
		board_init.moveStone();
	}
	
	return 0;
}