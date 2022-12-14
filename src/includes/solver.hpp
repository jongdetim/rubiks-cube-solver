/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   solver.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: asulliva <asulliva@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/08 15:17:09 by asulliva      #+#    #+#                 */
/*   Updated: 2021/04/08 15:17:09 by asulliva      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOLVER_H
# define SOLVER_H

# include "cube.hpp"
# include "database.hpp"

class Solver
{
	private:
		Cube		c;
		Database*	db;
	public:
		Solver(Cube cube, Database* database);
		vector<string>		solve();
};

void		apply_moves_db(Cube *c, string move);

#endif
