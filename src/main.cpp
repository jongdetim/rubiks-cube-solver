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

void			apply_moves_db(Cube c, string move)
{
	int		amount;

	amount = move[1] - '0';
	switch (move[0])
	{
		case 'U':
			c.u(amount);
			printf("U Turn\n");
			break;
		case 'L':
			c.l(amount);
			printf("L Turn\n");
			break;
		case 'F':
			c.f(amount);
			printf("F Turn\n");
			break;
		case 'R':
			c.r(amount);
			printf("R Turn\n");
			break;
		case 'B':
			c.b(amount);
			printf("B Turn\n");
			break;
		case 'D':
			c.d(amount);
			printf("D Turn\n");
			break;
	}
}

vector<string>	read_moves_db(Cube c, string moves)
{
	vector<string>	parsed_moves;
	string			temp;
	int n = 0;

	for (size_t i = 0; i < moves.length(); i++)
	{
		temp += moves[i];
		if (temp.length() == 2)
		{
			parsed_moves.push_back(temp);
			// cout << parsed_moves[n] << "\n";
			apply_moves_db(c, parsed_moves[n]);
			n++;
			temp = "";
		}
	}
	return parsed_moves;
}

int main(int ac, char **av)
{
	vector<char>	moves;
	vector<string>	movesstr;
	vector<string>	db_moves;
	Cube			c;
	
	db_moves = read_moves_db(c, "F3R2U1L3");
	c.printCube();
	exit(1);
	if (ac < 2)
		exit(1);
	movesstr = parse(av[1]);

	/*
	** deze functies moeten worden bediend door command line arguments
	*/

	// create_db();
	// generate_db(c);
	read_db(1);
	// rowcount_db(2);
	exit(1);
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

