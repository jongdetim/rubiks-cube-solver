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

# include <string>
# include "../cube/cube.h"
using std::string;

class Solver
{
    private:
        Cube c;
    public:
        Solver(Cube initialState) {
            c = initialState;
        }
        void printCube() {
            c.printCube();
        }
};

#endif