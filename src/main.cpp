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

#include "cube.hpp"
#include "solver.hpp"
#include "database.hpp"
#include "visualizer.hpp"
// #include "main.hpp"

/*
**	@desc:	Function splits up arguments into seperate strings
**	@param:	const string args: arguments given
**	@ret:	vector<string> moves: vector with moves
*/
vector<string>	parse(string args)
{
	char			*token = std::strtok(const_cast<char*>(args.c_str()), " ");
	vector<string>	moves;
	while (token != nullptr) {
		moves.push_back(string(token));
		token = std::strtok(nullptr, " ");
	}
	return (moves);
}

/*
**	@desc:	function checks if moves are legal
**	@param:	vector<string> moves: move strings
**	@ret:	bool, true if legal
*/
bool			checkMoves(vector<string> moves)
{
	string			legalChars = "ULFRBD2' ";
	string			noStart = "2'";

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

string	random_moves(int len = 10)
{
	string	moves;
	vector<string>	allowed = {"F","R","U","B","L","D"};

	srand((int)time(nullptr));
	for (int i = 0; i < len; i++)
	{
		if (i > 0)
			moves += " ";
		moves += allowed[rand() % 6];
	}
	return moves;
}

static bool	file_exists(char *db)
{
	if (FILE *file = fopen(db, "r")) {
        fclose(file);
        return true;
    } else {
        return false;
    }   
}

static void	remove_db(const char *name)
{
	using std::remove;

	remove(name);
}

int main(int ac, char **av)
{
	vector<string>	moves;
	Cube			c;
	Database		db;
	string			solution;

	// Argumentparsing bullshit
	argparse::ArgumentParser program("rubik");
	program.add_argument("scramble")
		.help("Scramble set to use")
		.action([](const string& value) 
		{
			if (value.empty())
				return random_moves();
			return value;
		});
	program.add_argument("-g", "--generate")
		.help("Generate database")
		.default_value(false)
		.implicit_value(true);
	program.add_argument("-v", "--visualizer")
		.help("Turn off cube visualization")
		.default_value(true)
		.implicit_value(false);
	try {
		program.parse_args(ac, av);
	} catch (const std::runtime_error& err) {
		cout << err.what() << endl;
		cout << program;
		exit(1);
	}
	// To generate database
	if (program["-g"] == true || program["--generate"] == true)
	{
		cout << "Database generation mode\n";
		if (file_exists((char*)"rubik.db"))
			remove_db("rubik.db");
		db.open_db();
		db.create_db();
		db.generate_db(c);
		db.close_db();
		exit(1);
	}
	// int i = 0;
	// while (++i < 5)
	// 	db.rowcount_db(i);
	// To solve a cube
	cout << "Solver mode\n";
	auto input = program.get<string>("scramble");
	moves = parse(input);
	for (auto move : moves)
		printf("%s ", move.c_str());
	printf("\n");
	try {
		checkMoves(moves);
	} catch (const char *msg) {
		std::cerr << msg << std::endl;
		exit(1);
	}
	for (auto move : moves) {
		c.applyMove(move);
	}
	c.printCube();
	// printf("%llu\n", c.get_id_phase4());
	// exit(1);
	Solver s(c, &db);
	solution = s.solve();
	Cube kubus;
	// if (c == kubus)
	// 	printf("Cube is solved\n");
	if (program["-v"] == true || program["--visualizer"] == true)
		visualizer(c, solution);
	return (0);
}

