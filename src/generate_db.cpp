/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   generate_db.cpp                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: tide-jon <tide-jon@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/12 19:02:30 by tide-jon      #+#    #+#                 */
/*   Updated: 2021/06/22 16:45:14 by asulliva      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

// enum edges {uf, ur, ub, ul, df, dr, db, dl, fr, br, bl, fl};

#include "database.h"
#include "cube.h"

int phase = 0;
string moves[6] = {"F","R","U","B","L","D"};
sqlite3* database;
map<int64_t, string> phaseHash[2];

void	open_db()
{
	int rc = 0;
	rc = sqlite3_open("rubik.db", &database);
	if (rc)
	{
		cout << "Error opening database " << sqlite3_errmsg(database) << endl;
		exit(1);
	}
	else
		cout << "Opened Database Successfully!" << endl;
}

static int callback(void *data, int argc, char **argv, char **azColName)
{
	int i;
	(void)data;
	for(i = 0; i<argc; i++)
		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	printf("\n");
	return 0;
}

void	execute_sql(string sql, bool read)
{
	char *messageError;
	int rc;

	if (read == true)
		rc = sqlite3_exec(database, sql.c_str(), callback, 0, &messageError);
	else
		rc = sqlite3_exec(database, sql.c_str(), NULL, 0, &messageError);
	if (rc != SQLITE_OK)
		printf("SQL error: %s\n", messageError);
		sqlite3_free(messageError);
}

int create_db()
{
	open_db();
	for (int i = 0; i < 4; i++)
	{
		string sql = "CREATE TABLE PHASE" + to_string(i+1) + 
		"( KEY INT PRIMARY KEY NOT NULL, VALUE TEXT NOT NULL);";
		execute_sql(sql, false);
	}
	return (0);
}
  
int	read_db()
{
	string sql = "SELECT * FROM PHASE1";
	
	open_db();
	execute_sql(sql, true);
	return (0);
}

// void	write_db

void	generate_db(Cube solved)
{
	char* messageError = NULL;
	Cube cur;
	queue<Cube> queue;

	sqlite3_exec(database, "BEGIN TRANSACTION;", NULL, NULL, NULL);
	// 4x loop
	queue.push(solved);
	cur = queue.front();
	int64_t id = cur.get_id_phase1();
	phaseHash[phase][id] = queue.front().path;
	string sql = "INSERT INTO PHASE1 (KEY,VALUE) VALUES(" + to_string(id) + ",'E')";
	int rc = sqlite3_exec(database, sql.c_str(), NULL, 0, &messageError);
	if (rc != SQLITE_OK)
		printf("SQL error: %s\n", messageError);

	while (!queue.empty())
	{
		cur = queue.front();
		queue.pop();
		for (int move = 0; move < 6; move++)
		{
			for (int amount = 0; amount < 3; amount++)
			{
				cur.applyMove(moves[move]);
				int64_t id;
				id = cur.get_id_phase1();
				if (phaseHash[phase].find(id) == phaseHash[phase].end())
				{
					cur.path.insert(cur.path.begin(), '3' - amount);
					cur.path.insert(cur.path.begin(),  moves[move][0]);
					// const char *sql = "INSERT INTO PHASE1 VALUES (1, 'abc')";
					string sql("INSERT INTO PHASE1 (KEY,VALUE) VALUES(" + to_string(id) + ",'" + cur.path + "')");
					int rc = sqlite3_exec(database, sql.c_str(), NULL, 0, &messageError);
					if (rc != SQLITE_OK)
						fprintf(stderr, "SQL error: %s\n", messageError);
					phaseHash[phase][id] = cur.path;
					queue.push(cur);
					cur.path = cur.path.substr(2);
				}
			}
			cur.applyMove(moves[move]);
		}
	}
	// for (uint i = 0; i < phaseHash[phase].size(); i++)
	// {
	//     cout << phaseHash[phase][i] << endl;
	// }
	// if (queue.empty())
	// {
	// 	// nextPhase();
	// 	return;
	// }
	sqlite3_exec(database, "COMMIT;", NULL, NULL, NULL);
}