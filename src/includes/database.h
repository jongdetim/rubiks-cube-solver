/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   database.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: tide-jon <tide-jon@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/21 19:49:39 by tide-jon      #+#    #+#                 */
/*   Updated: 2021/06/21 20:30:05 by tide-jon      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATABASE_H
# define DATABASE_H

#include <iostream>
// using namespace std;
#include <sqlite3.h>
#include <queue>
#include <map>
#include "cube.h"
using std::queue;

extern std::string moves[6];
extern std::map<int64_t, std::string> phaseHash[2];
extern int phase;
extern sqlite3* database;

int create_db();
int	read_db();
void	generate_db(queue<Cube> queue);

#endif