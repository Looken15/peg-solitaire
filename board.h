#pragma once

#include <iostream>

enum dir { L, R, U, D };

int b[7][7] = {
	{2,2,1,1,1,2,2},
	{2,2,1,1,1,2,2},
	{1,1,1,1,1,1,1},
	{1,1,1,0,1,1,1},
	{1,1,1,1,1,1,1},
	{2,2,1,1,1,2,2},
	{2,2,1,1,1,2,2}
};

struct board {
	int elements[7][7];

	board() {
		for (int i = 0; i < 7; ++i)
		{
			for (int j = 0; j < 7; ++j)
			{
				elements[i][j] = b[i][j];
			}
		}
	}

	board(int els[7][7])
	{
		memcpy(elements, els, sizeof(int) * 16);
	}

	void print()
	{
		for (int i = 0; i < 7; ++i)
		{
			for (int j = 0; j < 7; ++j)
			{
				if (elements[i][j] == 1)
					std::cout << elements[i][j];
				else
					std::cout << " ";
			}
			std::cout << "\n";
		}
	}

	bool is_solution()
	{
		int n = 0;
		for (int i = 0; i < 7; ++i)
		{
			for (int j = 0; j < 7; ++j)
			{
				if (elements[i][j] == 1)
					n++;
			}
		}
		return n == 1;
	}

	int count_1()
	{
		int c = 0;
		for (int i = 0; i < 7; ++i)
		{
			for (int j = 0; j < 7; ++j)
			{
				if (elements[i][j] == 1)
					c++;
			}
		}
		return c;
	}

	int count_pos_moves()
	{
		int c = 0;
		for (int i = 0; i < 7; ++i)
		{
			for (int j = 0; j < 7; ++j)
			{
				if (can_make_move(i, j, L) || can_make_move(i, j, R) || can_make_move(i, j, U) || can_make_move(i, j, D))
					c++;
			}
		}
		return c;
	}

	int min_moves()
	{
		int pegs = count_1();
		int moves = count_pos_moves();

		return pegs - 1 - (moves / (moves + 1));
	}

	double man()
	{
		double p = 0;
		double m = 0;
		for (int i = 0; i < 7; ++i)
		{
			for (int j = 0; j < 7; ++j)
			{
				if (elements[i][j] == 1)
				{
					p++;
				}
				for (int ii = 0; ii < 7; ++ii)
				{
					for (int jj = 0; jj < 7; ++jj)
					{
						if (elements[ii][jj] == 1)
							m += abs(i - ii) + abs(j - jj);
					}
				}
			}
		}
		return m / (2 * p);
	}

	bool can_make_move(int x, int y, dir where)
	{
		if (elements[x][y] == 1)
		{
			switch (where)
			{
			case L:
				return y >= 2 && elements[x][y - 1] == 1 && elements[x][y - 2] == 0;
			case R:
				return y <= 4 && elements[x][y + 1] == 1 && elements[x][y + 2] == 0;
			case U:
				return x >= 2 && elements[x - 1][y] == 1 && elements[x - 2][y] == 0;
			case D:
				return x <= 4 && elements[x + 1][y] == 1 && elements[x + 2][y] == 0;
			default:
				return false;
			}
		}
		else return false;
	}

	void make_move(int x, int y, dir where)
	{
		elements[x][y] = 0;
		switch (where)
		{
		case U:
		{
			{
				elements[x - 1][y] = 0;
				elements[x - 2][y] = 1;
			}

			break;
		}
		case D:
		{
			elements[x + 1][y] = 0;
			elements[x + 2][y] = 1;
			break;
		}
		case R:
		{
			elements[x][y + 1] = 0;
			elements[x][y + 2] = 1;
			break;
		}
		case L:
		{
			elements[x][y - 1] = 0;
			elements[x][y - 2] = 1;
			break;
		}
		default:
			break;
		}
	}
};

struct node {
	board b;
	node* parent;
	double g;
	double h;

	node(board _b)
	{
		b = _b;
	}

	node(board _b, node* _p, double _g, double _h)
	{
		b = _b;
		parent = _p;
		g = _g;
		h = _h;
	}
};

class Compare
{
public:
	bool operator()(node* n1, node* n2)
	{
		return n1->g + n1->h > n2->g + n2->h;
	}
};
