/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: asulliva <asulliva@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/11 17:27:16 by asulliva      #+#    #+#                 */
/*   Updated: 2021/04/12 17:23:10 by kpereira      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

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

/*
**	@desc:	Function applies moves to cube
**	@param:	vector<char> moves: moves to be made
*/
Cube	applyMoves(vector<char> moves)
{
	Cube c;

	for (auto move : moves)
	{
		if (move == 'U')
			c.u();
		if (move == 'L')
			c.l();
		if (move == 'F')
			c.f();
		if (move == 'R')
			c.r();
		if (move == 'B')
			c.b();
		if (move == 'D')
			c.d();
	}
	return (c);
}

int main(int ac, char **av)
{
	vector<char>	moves;
	if (ac < 2)
		exit(1);
	try {
		moves = parse_args(av[1]);
	} catch (const char *msg) {
		std::cerr << msg << std::endl;
	}
	Solver s(applyMoves(moves));
	s.printCube();
	return (0);
}
