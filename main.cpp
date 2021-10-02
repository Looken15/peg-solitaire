#include <iostream>

#include "board.h"
#include "alg.h"

int main()
{
    setlocale(LC_ALL, "RUSSIAN");
	time_t start = clock();

	astar();

	std::cout << (double)(clock() - start) / CLOCKS_PER_SEC << std::endl;
}
