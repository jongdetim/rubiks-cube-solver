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

#include "cube.h"
#include "solver.h"
#include "database.h"

/*
**	@desc:	Function parses arguments given and converts to moves
**	@param:	const string args: arguments given
**	@ret:	vector<char> moves: vector with moves
*/
vector<char>    parse_args(const string args)
{
	string			legalChars = "ULFRBD2' ";
	string			noStart = "2'";
	vector<char>	moves;
	char			curr;

	for (auto i = args.begin(); i < args.end(); i++)
	{
		if (find(legalChars.begin(), legalChars.end(), *i) == legalChars.end())
			throw "Illegal moves detected";
		while (*i == ' ')
			i++;
		if (i == args.end())
			break ;
		curr = *i;
		if (find(noStart.begin(), noStart.end(), curr) != noStart.end())
			throw "Illegal format detected";
		moves.push_back(curr);
		i++;
		if (*i == '2') {
			moves.push_back(curr);
			i++;
		} else if (*i == '\'') {
			moves.push_back(curr);
			moves.push_back(curr);
			i++;
		}
		if (*i != ' ' && i != args.end()) {
			throw "Moves need to be space seperated";
		}
	}
	if (moves.size() < 1)
		throw "Moves list is empty";
	return (moves);
}

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

bool			checkMoves(vector<string> moves)
{
	string			legalChars = "ULFRBD2' ";
	string			noStart = "2'";
	for (int i = 0; i < int(moves.size()); i++)
	{
		for (int j = 0; j < int(moves[i].size()); j++)
		{	
			if (find(legalChars.begin(), legalChars.end(), moves[i][j]) == legalChars.end())
				throw "Illegal moves detected";
		}
		if ((find(noStart.begin(), noStart.end(), moves[i][0]) != noStart.end()) || moves[i].size() > 2)
			throw "Illegal format detected";
		if (moves[i].size() > 1 && ((moves[i][0] == '\'' && moves[i][0] == '2') || (moves[i][1] != '\'' && moves[i][1] != '2')))
			throw "Illegal format detected";
		std::cout << moves[i] << std::endl;
	}
	return true;
}

int main(int ac, char **av)
{
	vector<char>	moves;
	vector<string>	movesstr;
	Cube			c;
	
	if (ac < 2)
		exit(1);
	movesstr = parse(av[1]);

	queue<Cube> queue;
	queue.push(c);
	create_db();
	generate_db(queue);
	read_db();

	try {
		checkMoves(movesstr);
	} catch (const char *msg) {
		std::cerr << msg << std::endl;
		exit(1);
	}
	// for (auto move : movesstr) {
	// 	c.applyMove(move);
	// }
	Solver s(c);
	s.printCube();
	std::cout << c.get_id_phase1();
	
	return (0);
}

