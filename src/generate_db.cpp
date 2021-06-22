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
std::string moves[6] = {"F","R","U","B","L","D"};
sqlite3* database;
std::map<int64_t, std::string> phaseHash[2];

int create_db()
{
	std::string sql = "CREATE TABLE PHASE1( \
					  KEY INT PRIMARY KEY     NOT NULL, \
					  VALUE           TEXT    NOT NULL);";
	int exit = 0;
	exit = sqlite3_open("rubik.db", &database);
	char* messageError;
	exit = sqlite3_exec(database, sql.c_str(), NULL, 0, &messageError);
  
	if (exit != SQLITE_OK) {
		std::cerr << "Table already exists" << std::endl;
		sqlite3_free(messageError);
	}
	else
		std::cout << "Table created Successfully" << std::endl;
	// sqlite3_close(database);



	return (0);
}

static int callback(void *data, int argc, char **argv, char **azColName){
   int i;
   printf("%s: ", (const char*)data);
   
   for(i = 0; i<argc; i++){
	  printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   
   printf("\n");
   return 0;
}
  
int	read_db()
{
	int exit = 0;
	exit = sqlite3_open("rubik.db", &database);
	char const *data = "CALLBACK FUNCTION";
	char const *sql = "SELECT * FROM PHASE1";
  
	if (exit) {
		std::cerr << "Error open database " << sqlite3_errmsg(database) << std::endl;
		return (-1);
	}
	else
		std::cout << "Opened Database Successfully!" << std::endl;
  
	int rc = sqlite3_exec(database, sql, callback, (void*)data, NULL);
  	// rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);
	if (rc != SQLITE_OK)
		std::cerr << "Error SELECT" << std::endl;
	else {
		std::cout << "Operation OK!" << std::endl;
	}
  
	sqlite3_close(database);
	return (0);
}

// void	write_db

void	generate_db(queue<Cube> queue){
	sqlite3_exec(database, "BEGIN TRANSACTION;", NULL, NULL, NULL);

	char* messageError = NULL;
	Cube cur;
	cur = queue.front();
	int64_t id = cur.get_id_phase1();
	phaseHash[phase][id] = queue.front().path;
	string sql("INSERT INTO PHASE1 (KEY,VALUE) VALUES(" + std::to_string(id) + ",'E')");
	int rc = sqlite3_exec(database, sql.c_str(), NULL, 0, &messageError);
	if (rc != SQLITE_OK)
		fprintf(stderr, "SQL error: %s\n", messageError);

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
					string sql("INSERT INTO PHASE1 (KEY,VALUE) VALUES(" + std::to_string(id) + ",'" + cur.path + "')");
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
	//     std::cout << phaseHash[phase][i] << std::endl;
	// }
	// if (queue.empty())
	// {
	// 	// nextPhase();
	// 	return;
	// }
	sqlite3_exec(database, "COMMIT;", NULL, NULL, NULL);
}