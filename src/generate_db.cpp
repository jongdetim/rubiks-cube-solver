/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   generate_db.cpp                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: tide-jon <tide-jon@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/12 19:02:30 by tide-jon      #+#    #+#                 */
/*   Updated: 2021/06/21 17:43:38 by asulliva      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
// using namespace std;

#include <queue>
#include <map>
#include "cube.h"
using std::queue;

std::string moves[6] = {"F","R","U","B","L","D"};
std::map<int64_t, std::string> phaseHash[2];
int phase = 0;

enum edges {uf, ur, ub, ul, df, dr, db, dl, fr, br, bl, fl};

void	generate_db(int step, queue<Cube> queue){
    string a = "adad";
    a.insert(0, "a");
	// if (step == 0){
	// 	int64_t id = getPhaseId(queue.front(), phase);
	// 	ofs << id << " " << "E" << endl;
	// 	phaseHash[phase][id] = queue.front().path;
	// }
	step = 0;
	// queue<Cube> next;
	Cube cur;
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
                    phaseHash[phase][id] = cur.path;
                    queue.push(cur);
                    cur.path = cur.path.substr(2);
                }
			}
			cur.applyMove(moves[move]);
		}
	}
    for (size_t i = 0; i < phaseHash[phase].size(); i++)
    {
        std::cout << phaseHash[phase][i] << std::endl;
    }
	// if (queue.empty())
	// {
	// 	// nextPhase();
	// 	return;
	// }
}