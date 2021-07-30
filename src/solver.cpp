/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   solver.cpp                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: asulliva <asulliva@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/11 17:12:54 by asulliva      #+#    #+#                 */
/*   Updated: 2021/04/11 17:12:54 by asulliva      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "solver.hpp"

void		apply_moves_db(Cube *c, string move)
{
	int		amount;

	amount = move[1] - '0';
	switch (move[0])
	{
		case 'U':
			c->u(amount);
			break;
		case 'L':
			c->l(amount);
			break;
		case 'F':
			c->f(amount);
			break;
		case 'R':
			c->r(amount);
			break;
		case 'B':
			c->b(amount);
			break;
		case 'D':
			c->d(amount);
			break;
	}
}

static void     movestring_split(Cube* c, string moves)
{
	string			temp;
	int n = 0;

	if (moves == "")
		return;
	for (size_t i = 0; i < moves.length(); i++)
	{
		temp += moves[i];
		if (temp.length() == 2)
		{
			c->path_vect.push_back(temp);
			apply_moves_db(c, c->path_vect[n]);
			n++;
			temp = "";
		}
	}
}

Solver::Solver(Cube cube, Database* database) 
{
    c = cube;
    db = database;
}

vector<string> Solver::solve()
{
	string moves;
	uint64_t id;

	for (int phase = 0; phase < 4; phase++)
	{
		printf("phase: %d\n", phase + 1);
		id = c.get_id(phase);
		moves = db->get_value(phase, id);
		if (moves == "NOT FOUND")
		{
			cout << "move not found in db!" << endl;
			// db->close_db();
			break;
		}
		movestring_split(&c, moves);
	}
	for (int i = 0; i < c.path_vect.size(); i++)
		printf("%s ", c.path_vect[i].c_str());
	printf("len: %lu\n", c.path_vect.size());
	db->close_db();
	return c.path_vect;
}
