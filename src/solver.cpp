#include "solver.hpp"

void print_formatted_move(string move)
{
	cout << move[0];
	switch (move[1])
	{
	case '1':
		cout << " ";
		break;
	case '2':
		cout << "2 ";
		break;
	case '3':
		cout << "' ";
		break;
	}
}

void apply_moves_db(Cube *c, string move)
{
	int amount;

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
	default:
		cout << "Trying impossible move: " << move << endl;
		exit(1);
	}
	print_formatted_move(move);
}

static void movestring_split(Cube *c, string moves)
{
	vector<string> parsed_moves;
	string temp;
	int n = 0;

	if (moves == "")
		return;
	for (size_t i = 0; i < moves.length(); i++)
	{
		temp += moves[i];
		if (temp.length() == 2)
		{
			parsed_moves.push_back(temp);
			c->path_vect.push_back(temp);
			apply_moves_db(c, parsed_moves[n]);
			n++;
			temp = "";
		}
	}
}

Solver::Solver(Cube cube, Database *database)
{
	c = cube;
	db = database;
}

void print_solution(Cube c)
{
	cout << "\nsolution:" << endl;
	for (int i = 0; i < (int)c.path_vect.size(); i++)
		print_formatted_move(c.path_vect[i]);
	printf("\nsolved in: %lu moves\n", (long)c.path_vect.size());
}

vector<string> Solver::solve()
{
	string moves;
	uint64_t id;

	for (int phase = 0; phase < 4; phase++)
	{
		printf("\nPhase: %d\n", phase + 1);
		id = c.get_id(phase);
		moves = db->get_value(phase, id);
		if (moves == "NOT FOUND")
		{
			cout << "move not found in db!" << endl;
			exit(1);
		}
		movestring_split(&c, moves);
	}
	print_solution(c);
	db->close_db();
	return c.path_vect;
}
