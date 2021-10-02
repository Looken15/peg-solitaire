#pragma once

#include <iostream>
#include <queue>
#include <vector>
#include <deque>
#include <Windows.h>

#include "board.h"

void astar()
{
	board b = board();
	node* first = new node{ b, NULL, 0, b.man() };
	std::priority_queue<node*, std::vector<node*>, Compare> pq;

	node* curr_node = first;

	while (!curr_node->b.is_solution())
	{
		//std::cout << (int)curr_node->g << " + " << (int)curr_node->h << " = " << curr_node->g + curr_node->h << std::endl;
		for (int i = 0; i < 7; ++i)
		{
			for (int j = 0; j < 7; ++j)
			{
				auto ln = new board{ curr_node->b };
				if (ln->can_make_move(i, j, L))
				{
					ln->make_move(i, j, L);
					auto new_node = new node{ *ln,curr_node,curr_node->g + 1, ln->man() };
					pq.push(new_node);
				}
				auto rn = new board{ curr_node->b };
				if (rn->can_make_move(i, j, R))
				{
					rn->make_move(i, j, R);
					auto new_node = new node{ *rn,curr_node,curr_node->g + 1, rn->man() };
					pq.push(new_node);
				}
				auto un = new board{ curr_node->b };
				if (un->can_make_move(i, j, U))
				{
					un->make_move(i, j, U);
					auto new_node = new node{ *un,curr_node,curr_node->g + 1, un->man() };
					pq.push(new_node);
				}
				auto dn = new board{ curr_node->b };
				if (dn->can_make_move(i, j, D))
				{
					dn->make_move(i, j, D);
					auto new_node = new node{ *dn,curr_node,curr_node->g + 1, dn->man() };
					pq.push(new_node);
				}
			}
		}
		curr_node = pq.top();
		pq.pop();
	}
	std::deque<node*> solution;
	while (curr_node->parent != nullptr)
	{
		solution.push_back(curr_node);
		curr_node = curr_node->parent;
	}


	reverse(solution.begin(), solution.end());
	solution.push_front(first);

	/*for (auto x : solution)
	{
		x->b.print();
		Sleep(1000);
		printf("\033c");
	}*/

	std::cout << "Количество ходов: " << solution.size() - 1 << std::endl;

}
