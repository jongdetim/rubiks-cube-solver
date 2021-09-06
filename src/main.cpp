/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: asulliva <asulliva@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/11 17:27:16 by asulliva      #+#    #+#                 */
/*   Updated: 2021/06/22 16:38:29 by asulliva      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "main.hpp"
#include "cube.hpp"
#include "solver.hpp"
#include "database.hpp"
#include "visualizer.hpp"

/*
**	@desc:	function checks if moves are legal
**	@param:	vector<string> moves: move strings
**	@ret:	bool, true if legal
*/
bool checkMoves(vector<string> moves)
{
	string legalChars = "ULFRBD2' ";
	string noStart = "2'";

	for (int i = 0; i < int(moves.size()); i++)
	{
		for (int j = 0; j < int(moves[i].size()); j++)
		{
			if (find(legalChars.begin(), legalChars.end(), moves[i][j]) == legalChars.end())
			{
				printf("%c is illegal\n", moves[i][j]);
				throw "Illegal moves detected";
			}
		}
		if ((find(noStart.begin(), noStart.end(), moves[i][0]) != noStart.end()) || moves[i].size() > 2)
			throw "Illegal start character detected";
		if (moves[i].size() > 1 && ((moves[i][0] == '\'' && moves[i][0] == '2') ||
									(moves[i][1] != '\'' && moves[i][1] != '2')))
			throw "Illegal format detected";
	}
	return true;
}

/*
**	@desc:	Function splits up input string into a vector of movestrings
**	@param:	const string args: arguments given
**	@ret:	vector<string> moves: vector with moves
*/
void parse(string args, Cube* c)
{
	vector<string> moves;
	char *token = std::strtok(const_cast<char*>(args.c_str()), " ");

	while (token != nullptr)
	{
		moves.push_back(string(token));
		token = std::strtok(nullptr, " ");
	}
	for (auto move : moves)
		printf("%s ", move.c_str());
	printf("\n");
	try
	{
		checkMoves(moves);
	}
	catch (const char *msg)
	{
		std::cerr << msg << std::endl;
		exit(1);
	}
	for (auto move : moves)
		c->applyMove(move);
}

string random_moves(int len = 10)
{
	string movestring;
	vector<string> moves =   {"F", "R", "U", "B", "L", "D", "F2", "R2", "U2",
								"B2", "L2", "D2", "F'", "R'", "U'", "B'", "L'", "D'"};
	std::random_device rd;
  	std::default_random_engine gen(rd());
  	std::uniform_int_distribution<uint_fast8_t> dist(0, moves.size() - 1);

	for (int i = 0; i < len; i++)
	{
		if (i > 0)
			movestring += " ";
		movestring += moves[dist(gen)];
	}
	return movestring;
}

static bool file_exists(char *db)
{
	if (FILE *file = fopen(db, "r"))
	{
		fclose(file);
		return true;
	}
	else
	{
		return false;
	}
}

static void remove_db(const char *name)
{
	std::remove(name);
}

void parse_cmdline_args(int ac, char **av, argparse::ArgumentParser* program)
{
	program->add_argument("scramble")
		.help("Scramble set to use")
		.default_value(string(""))
		.action([](const string &value)
				{
					return value;
				});
	program->add_argument("-g", "--generate")
		.help("Generate database")
		.default_value(false)
		.implicit_value(true);
	program->add_argument("-v", "--visualizer")
		.help("Turn off cube visualization")
		.default_value(true)
		.implicit_value(false);
	program->add_argument("-r", "--random")
		.help("Scramble the cube by a specified amount of random moves. Ignores scramble argument");
	try
	{
		program->parse_args(ac, av);
	}
	catch (const std::runtime_error &err)
	{
		cout << err.what() << endl;
		cout << *program;
		exit(1);
	}
}

void handle_db(Database* db, Cube c)
{
	cout << "Database generation mode\n";
	if (file_exists((char *)DB_NAME))
		remove_db(DB_NAME);
	db->create_db();
	db->generate_db(c);
	cout << DB_NAME << " generated" << endl;
	exit(0);
}

int main(int ac, char **av)
{
	Cube c;
	Database db;
	vector<string> solution;
	string input;
	argparse::ArgumentParser program("rubik");

	parse_cmdline_args(ac, av, &program);

	if (program["--generate"] == true)
		handle_db(&db, c);
	if (program.is_used("--random") == true)
	{
		int shuffles = stoi(program.get<string>("-r"));
		input = random_moves(shuffles);
	}
	else
		input = program.get<string>("scramble");
	parse(input, &c);

	Solver s(c, &db);
	solution = s.solve();

	if (program["--visualizer"] == true)
	{
		Visualizer v(c, solution);
		v.visualize();
	}
	return (0);
}
