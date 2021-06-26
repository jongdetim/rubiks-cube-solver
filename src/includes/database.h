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

# include "main.h"
# include "cube.h"

extern	string moves[6];
extern	map<int64_t, string> phaseHash[5];
extern	int phase;
extern	sqlite3* database;

int 	create_db();
int		read_db(int phase);
void	generate_db(Cube solved);
int		rowcount_db(int phase);

#endif