#include "Board.h"
#include "BoardEval.h"


using namespace std;

Board::Board()
{
	for (int i = 0; i < BOARD_ROW; i++)
	{
		for (int j = 0; j < BOARD_COLUMN; j++)
		{
			game_board[i][j] = 0;
		}
	}
	
	for (int i = 0; i < 2; i++)
	{
		status[i] = 0;
	}

	playerflag = false;
}

Board::Board(Board* other)
{
	for (int i = 0; i < BOARD_ROW; i++)
	{
		for (int j = 0; j < BOARD_COLUMN; j++)
		{
			game_board[i][j] = other->game_board[i][j];
		}
	}

	for (int i = 0; i < 2; i++)
	{
		status[i] = 0;
	}

	playerflag = other->playerflag;
}


Board::~Board()
{
}

void Board::moveStone()
{
	char row = 0;
	int col = 0;
	BoardEval evaluator;

	cin >> row >> col;
	row = posTranslate(row);

	if (row != -1 && col >= 0 && col < BOARD_COLUMN)
	{
		game_board[row][col] = -1;
	}
	else
	{
		return;
	}

	displayBoard();

	if (evaluator.checkWin(this))
	{
		cout << "Black Win" << endl;
		return;
	}

	playerflag = !playerflag;

	evaluator.abPruning(this);
	displayBoard();

	if (evaluator.checkWin(this))
	{
		cout << "White Win" << endl;
		return;
	}

	playerflag = !playerflag;
}

int Board::posTranslate(char row)
{
	int translated_row = 0;
	if ((int)row >= (int)('A') && (int)row < (int)('A' + BOARD_ROW))
	{
		translated_row = (int)(row - 65);
	}
	else if ((int)row >= (int)('a') && (int)row < (int)('a' + BOARD_ROW))
	{
		translated_row = (int)(row - 97);
	}
	else
	{
		cout << "Error: Wrong Position" << endl;
		return -1;
	}

	return translated_row;
}

int Board::getBoardValue(int row, int col)
{
	return game_board[row][col];
}

int *Board::getLatestPos()
{
	return status;
}

void Board::displayBoard()
{
	for (int i = 0; i <= BOARD_COLUMN; i++)
	{
		if (i == 0)
		{
			cout << " ";
		}
		else
		{
			cout << setw(3) << i - 1;
		}
	}
	for (int i = 0; i < BOARD_ROW; i++)
	{
		cout << endl;
		for (int j = 0; j < BOARD_COLUMN; j++)
		{
			if (j == 0)
			{
				cout << (char)(i + 65);
			}
			if (game_board[i][j] == 1)
			{
				wcout << setw(3) << "¡Û";
			}
			else if (game_board[i][j] == -1)
			{
				wcout << setw(3) << "¡Ü";
			}
			else
			{
				wcout << setw(3) << "¢Æ";
			}
		}
	}

	cout << endl;
}
