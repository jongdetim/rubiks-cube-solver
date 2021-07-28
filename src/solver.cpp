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

static void		apply_moves_db(Cube *c, string move)
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
	vector<string>	parsed_moves;
	string			temp;
	int n = 0;

	if (moves == "")
		return;
	for (size_t i = 0; i < moves.length(); i++)
	{
		temp += moves[i];
		if (temp.length() == 2)
		{
			parsed_moves.push_back(temp);
			apply_moves_db(c, parsed_moves[n]);
			// c->path.append((parsed_moves[n]) + " ");
			n++;
			temp = "";
		}
	}
	c->path = parsed_moves;
}

Solver::Solver(Cube cube, Database* database) 
{
    c = cube;
    db = database;
}

string Solver::solve()
{
	string moves;
	uint64_t id;

	for (int phase = 0; phase < 4; phase++)
	{
		printf("phase: %d\n", phase + 1);
		id = c.get_id(phase);
		moves = db->get_value(phase, id);
		while (moves == "NOT FOUND")
		{
			cout << "move not found in db! trying random move" << endl;
			for (int i = 0; i < 6; i++)
			{
				cout << c.get_id(phase) << endl;
				c.applyMove(db->moves[i] + "2");
				id = c.get_id(phase);
				cout << c.get_id(phase) << endl;
				moves = db->get_value(phase, id);
				if (moves == "NOT FOUND")
					c.applyMove(db->moves[i] + "2");
				else
				{
					c.path.append(moves);
					cout << moves << "  breaking..." << endl; 
					break ;
				}
			}
		}
		movestring_split(&c, moves);
	}
	printf("%s\nlen: %lu\n", c.path.c_str(), (unsigned long)(c.path.length() / 3));
	db->close_db();
	return c.path;
}
