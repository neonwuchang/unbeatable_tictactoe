#pragma once
#include<iostream>
#include <algorithm>
#include <limits>
class Board
{
private:
	struct Choice
	{
		unsigned int x = 0;
		unsigned int y = 0;
	};
	enum class Player
	{
		none='-',
		human = 'x',
		computer = 'o'
	};
	Player board[3][3];
public:
	//constructor
	Board()
	{
		for (int ro = 0; ro < 3; ro++)
		{
			for (int col = 0; col < 3; col++)
			{
				board[ro][col] = Player::none;
			}
		}
	}

	//print board
	void disp_board() const
	{
		int ctr=0;
		for (int x = 0; x < 3; x++)
		{
			for (int y = 0; y < 3; y++)
			{
				ctr++;
				if (board[x][y] == Player::none) std::cout << ctr;
				else std::cout << static_cast<char>(board[x][y]);
				if (y != 2) std::cout << "|";
			}
			if (x != 2)	std::cout << "\n- - -\n";
		}
		std::cout << "\n\n";
	}

	//check if tie
	bool full_board() const
	{
			for (int r = 0; r < 3; r++)
					if ((board[r][0] == Player::none)||(board[r][1] == Player::none)||(board[r][2] == Player::none ))
						return false;
			return true;
	}

	//check if game over
	bool check_win(Player player) const
	{
		for (unsigned int i = 0; i < 3; i++)
		{
			// Check horizontals
			if (board[i][0] == player && board[i][1] == player && board[i][2] == player)
				return true;

			// Check verticals
			if (board[0][i] == player && board[1][i] == player && board[2][i] == player)
				return true;
		}

		// Check diagonals
		if (board[0][0] == player && board[1][1] == player && board[2][2] == player)
			return true;

		if (board[0][2] == player && board[1][1] == player && board[2][0] == player)
			return true;

		return false;
	}

	//update board
	int update_board(bool plyr, int l)
	{
		Choice move;
		switch (l)
		{
		case 1:
			move.x = 0, move.y = 0;
			break;
		case 2:
			move.x = 0, move.y = 1;
			break;
		case 3:
			move.x = 0, move.y = 2;
			break;
		case 4:
			move.x = 1, move.y = 0;
			break;
		case 5:
			move.x = 1, move.y = 1;
			break;
		case 6:
			move.x = 1, move.y = 2;
			break;
		case 7:
			move.x = 2, move.y = 0;
			break;
		case 8:
			move.x = 2, move.y = 1;
			break;
		case 9:
			move.x = 2, move.y = 2;
			break;
		default:
			std::cout << "invalid input" << std::endl;
			break;
		}
		if (board[move.x][move.y]==Player::none)
		{
			if(plyr) board[move.x][move.y] = Player::human; 
			else board[move.x][move.y] = Player::computer;
			return 0;
		}
		else
		{
			std::cout << "ALready played square" << std::endl; 
			return 1;
		}
	}
	/********************************************************
	 * Title: Simple Tic-Tac-Toe with Minimax Algorithm
	 * Author: MORTAL (Stackexchange username)
	 * Date Accessed: 02/02/2023 
	 * Code Version: N/A
	 * Availibility: https://codereview.stackexchange.com/questions/183594/simple-tic-tac-toe-with-minimax-algorithm
	*********************************************************/
	//generate computer move
	Choice minimax()
	{
		int score = std::numeric_limits<int>::max();
		Choice aimove;

		for (unsigned int i = 0; i < 3; i++)
		{
			for (unsigned int j = 0; j < 3; j++)
			{
				if (board[i][j] == Player::none)
				{
					board[i][j] = Player::computer;

					int temp = maxSearch();

					if (temp < score)
					{
						score = temp;
						aimove.x = i;
						aimove.y = j;
					}
					board[i][j] = Player::none;
				}
			}
		}

		return aimove;
	}

	int maxSearch()
	{
		if (check_win(Player::human)) { return 10; }
		else if (check_win(Player::computer)) { return -10; }
		else if (full_board()) { return 0; }

		int score = std::numeric_limits<int>::min();

		for (unsigned int i = 0; i < 3; i++)
		{
			for (unsigned int j = 0; j < 3; j++)
			{
				if (board[i][j] == Player::none)
				{
					board[i][j] = Player::human;
					score = std::max(score, minSearch());
					board[i][j] = Player::none;
				}
			}
		}

		return score;
	}

	int minSearch() 
	{
		if (check_win(Player::human)) { return 10; }
		else if (check_win(Player::computer)) { return -10; }
		else if (full_board()) { return 0; }

		int score = std::numeric_limits<int>::max();

		for (unsigned int i = 0; i < 3; i++)
		{
			for (unsigned int j = 0; j < 3; j++)
			{
				if (board[i][j] == Player::none)
				{
					board[i][j] = Player::computer;
					score = std::min(score, maxSearch());
					board[i][j] = Player::none;
				}
			}
		}

		return score;
	}
	/**************************************************************/

	//create and play the game
	int game()
	{
		bool pl = true;
		disp_board();
		unsigned int turn = 0;
		bool exit = false;
		do
		{
			// human move
			if (pl)
			{
				std::cout << "Enter your move: \n";
				Choice choice;
				int square;
				std::cin >> square;
				int temp = update_board(pl, square);
				if (temp == 0)
				{
					if (check_win(Player::human))
					{
						std::cout << "Human Wins\n";
						exit = true;
					}
				}
			}
			else
			{
				std::cout << "\nComputer Move\n";
				int square;
				Choice aimove = minimax();
				if (aimove.x == 0 && aimove.y == 0) square = 1;
				else if (aimove.x == 0 && aimove.y == 1) square = 2;
				else if (aimove.x == 0 && aimove.y == 2) square = 3;
				else if (aimove.x == 1 && aimove.y == 0) square = 4;
				else if (aimove.x == 1 && aimove.y == 1) square = 5;
				else if (aimove.x == 1 && aimove.y == 2) square = 6;
				else if (aimove.x == 2 && aimove.y == 0) square = 7;
				else if (aimove.x == 2 && aimove.y == 1) square = 8;
				else if (aimove.x == 2 && aimove.y == 2) square = 9;
				int temp = update_board(pl, square);
				if (temp == 0)
				{
					if (check_win(Player::computer))
					{
						std::cout << "Computer Wins\n";
						exit = true;
					}
				}
			}
			if (full_board())
			{
				std::cout << "\nDraw!\n\n";
				exit = true;
			}

			//turn ^= 1;
			disp_board();
			pl = !pl;

		} while (!exit);
		return 0;
	}
	
};