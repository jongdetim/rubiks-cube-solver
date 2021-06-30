/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   database.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: tide-jon <tide-jon@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/21 19:49:39 by tide-jon      #+#    #+#                 */
/*   Updated: 2021/06/22 16:38:10 by asulliva      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATABASE_H
# define DATABASE_H

# include "main.hpp"
# include "cube.hpp"

extern	string moves[6];
extern	unordered_map<int64_t, string> phaseHash[5];
extern	int phase;
extern	sqlite3* database;

class Database
{
	private:
		bool							allowedMoves[18];
		bool							is_open;
		unordered_map<int64_t, string>	phaseHash[5];
		string							moves[6] = {"F","R","U","B","L","D"};
		sqlite3*						database;

	public:
		void	open_db();
		int		create_db();
		int		read_db(int phase);
		void	generate_db(Cube c);
		int		rowcount_db(int phase);
		string	get_value(int phase, uint64_t key);
		void	disable_moves(int phase);
		void	execute_sql(string sql, bool read);

};
#endif