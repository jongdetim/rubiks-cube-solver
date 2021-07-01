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

# include "main.hpp"
# include "cube.hpp"
# include "database.hpp"

class Solver
{
	private:
		Cube		c;
		sqlite3*	sqldb;
		Database	db;
	public:
		Solver(Cube cube, Database database, sqlite3* sqldatabase);
		void		solve();
};

#endif
