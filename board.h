#pragma once

#include <iostream>

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


	void print()
	{
		for (int i = 0; i < 7; ++i)
		{
			for (int j = 0; j < 7; ++j)
			{
				if (elements[i][j] != 2)
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
};
