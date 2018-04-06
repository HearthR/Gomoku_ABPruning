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
		bestmove[i] = 0;
		lastmove[i] = 0;
	}

	playerflag = false;
	game_turn = 0;
	winflag = false;
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
		bestmove[i] = other->bestmove[i];
		lastmove[i] = other->lastmove[i];
	}

	playerflag = other->playerflag;
	game_turn = other->game_turn;
	winflag = false;
}


Board::~Board()
{
}

void Board::moveStone()
{
	char row = 0;
	int col = 0;
	BoardEval evaluator;

	if (playerflag == false)
	{
		cout << "Please enter coordinate: ";
		cin >> row >> col;
		row = posTranslate(row);

		//	Board bound check
		if (row != -1 && col >= 0 && col < BOARD_COLUMN)
		{
			game_turn++;
			setMove(row, col);
		}
		else
		{
			cout << "Error: Wrong Position" << endl;
			return;
		}
	}
	else
	{
		if (game_turn < 2)
		{
			evaluator.agentFirstMove(this, lastmove[0], lastmove[1]);
		}
		else
		{
			evaluator.abPruning(this);
		}
	}

	if (evaluator.checkWin(this))
	{
		winflag = true;
		displayBoard();

		if (playerflag == true)
		{
			cout << "\n\n******************  White Win!  ******************\n\n" << endl;
		}
		else
		{
			cout << "\n\n******************  Black Win!  ******************\n\n" << endl;
		}
		return;
	}
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
		return -1;
	}

	return translated_row;
}

int Board::getBoardValue(int row, int col)
{
	return game_board[row][col];
}

int Board::getLastRow()
{
	return lastmove[0];
}

int Board::getLastCol()
{
	return lastmove[1];
}

bool Board::getCurrentPlayer()
{
	return playerflag;
}

int Board::getBestRow()
{
	return bestmove[0];
}

int Board::getBestCol()
{
	return bestmove[1];
}

void Board::setMove(int row, int col)
{
	game_board[row][col] = playerflag ? 1 : -1;
	lastmove[0] = row;
	lastmove[1] = col;
	playerflag = !playerflag;
}

void Board::resetMove(int row, int col)
{
	game_board[row][col] = 0;
	playerflag = !playerflag;
}

void Board::setBestMove(int row, int col)
{
	bestmove[0] = row;
	bestmove[1] = col;
}

bool Board::isWin()
{
	return winflag;
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

	cout << "\n\n";
}
