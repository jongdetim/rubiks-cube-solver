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

#include "database.hpp"
#include "cube.hpp"

void	Database::open_db()
{
	int rc = 0;
	if (is_open == false)
	{
		rc = sqlite3_open("rubik.db", &database);
		if (rc)
		{
			cout << "error opening database " << sqlite3_errmsg(database) << endl;
			exit(1);
		}
		is_open = true;
	}
}

void	Database::disable_moves(int phase)
{
	switch (phase)
	{
		case 0:
			//FB quarter turns
			this->allowedMoves[0] = false;
			allowedMoves[2] = false;
			allowedMoves[9] = false;
			allowedMoves[11] = false;
			break;
		case 1:
			// RL quarter turns
			allowedMoves[3] = false;
			allowedMoves[5] = false;
			allowedMoves[12] = false;
			allowedMoves[14] = false;
			break;
		case 2:
			// UD quarter turns
			allowedMoves[6] = false;
			allowedMoves[8] = false;
			allowedMoves[15] = false;
			allowedMoves[17] = false;
		default :
			break;
	}
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

void	Database::execute_sql(string sql, bool read)
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

int Database::create_db()
{
	open_db();
	for (int i = 0; i < 4; i++)
	{
		string sql = "CREATE TABLE PHASE" + to_string(i+1) + 
		"( KEY INT PRIMARY KEY NOT NULL, VALUE TEXT UNIQUE NOT NULL);";
		execute_sql(sql, false);
	}
	return (0);
}
  
int	Database::read_db(int phase)
{
	string sql = "SELECT * FROM PHASE" + to_string(phase);
	
	open_db();
	execute_sql(sql, true);
	return (0);
}

int	Database::rowcount_db(int phase)
{
	string sql = "SELECT COUNT(*) FROM PHASE" + to_string(phase);
	
	open_db();
	execute_sql(sql, true);
	return (0);
}

string	Database::get_value(int phase, uint64_t key)
{
	sqlite3_stmt *stmt;
	string sql = "SELECT * FROM PHASE" + to_string(phase + 1) + " WHERE KEY = " + to_string(key);
	string value;

	open_db();
	int rc = sqlite3_prepare_v2(database, sql.c_str(), sql.length(), &stmt, nullptr);
	if (rc != SQLITE_OK)
	{
		cout << string(sqlite3_errmsg(database)) << endl;
		exit(1);
	}
	rc = sqlite3_step(stmt);
	if (rc == SQLITE_ROW)
	{
		value = string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
		sqlite3_finalize(stmt);
		return value;
	}
	else
		return "NOT FOUND";
	
}

void	Database::close_db()
{
	sqlite3_close(database);
}

void	Database::generate_db(Cube solved)
{
	Cube cur;
	queue<Cube> queue;
	uint64_t id;

	for (int i = 0; i < 18; i++)
		allowedMoves[i] = true;
	open_db();
	sqlite3_exec(database, "BEGIN TRANSACTION;", NULL, NULL, NULL);
	// 4x loop

	for (int phase = 0; phase < 4; phase++)
	{
		cout << "generating lookup table for phase " + to_string(phase+1) + "...\n";
		queue.push(solved);
		cur = queue.front();
		cur.path = "";
		id = cur.get_id(phase);
		phaseHash[phase][id] = queue.front().path;
		string sql = "INSERT INTO PHASE" + to_string(phase + 1) +
		" (KEY,VALUE) VALUES(" + to_string(id) + ",'')";
		execute_sql(sql, false);
		while (!queue.empty())
		{
			int count = 0;
			cur = queue.front();
			queue.pop();
			for (int move = 0; move < 6; move++)
			{
				for (int times = 0; times < 3; times++)
				{
					cur.applyMove(moves[move]);
					if (allowedMoves[count] == true)
					{
						id = cur.get_id(phase);
						if (phaseHash[phase].count(id) == 0)
						{
							// if (phase==2)
							// 	cout << "new id found" << endl;
							cur.path.insert(cur.path.begin(), '3' - times);
							cur.path.insert(cur.path.begin(),  moves[move][0]);
							string sql("INSERT INTO PHASE" + to_string(phase + 1) +
							" (KEY,VALUE) VALUES(" + to_string(id) + ",'" + cur.path + "')");
							execute_sql(sql, false);
							phaseHash[phase][id] = cur.path;
							queue.push(cur);
							// if (phase==3)
							// 	cout << cur.path << endl;
							cur.path = cur.path.substr(2);
						}
					}
					count++;
				}
				cur.applyMove(moves[move]);
			}
		}
		disable_moves(phase);
	}
	sqlite3_exec(database, "COMMIT;", NULL, NULL, NULL);
}