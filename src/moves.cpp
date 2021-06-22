/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   moves.cpp                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: asulliva <asulliva@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/21 20:14:57 by asulliva      #+#    #+#                 */
/*   Updated: 2021/06/21 20:04:05 by asulliva      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

/*
** Up turns
*/
Cube &Cube::u(uint8_t amount)
{
    int arr[] = {16, 17, 18, 8, 9, 10, 32, 33, 34, 24, 25, 26};
    for (uint8_t i = 0; i < amount; i++)
    {
        this->rot90(FACE::UP);
        this->rotSides90((int *)arr);

        uint8_t temp = this->edgeOrientation[EDGE::UF];
        this->edgeOrientation[EDGE::UF] = 1 - this->edgeOrientation[EDGE::UR];
        this->edgeOrientation[EDGE::UR] = 1 - this->edgeOrientation[EDGE::UB];
        this->edgeOrientation[EDGE::UB] = 1 - this->edgeOrientation[EDGE::UL];
        this->edgeOrientation[EDGE::UL] = 1 - temp;
    }
    return *this;
}

/*
** Left turns
*/
Cube &Cube::l(uint8_t amount)
{
    int arr[] = {0, 7, 6, 16, 23, 22, 40, 47, 46, 36, 35, 34};
    for (uint8_t i = 0; i < amount; i++)
    {
        this->rot90(FACE::LEFT);
        this->rotSides90((int *)arr);

        uint8_t temp = this->edgeOrientation[EDGE::UL];
        this->edgeOrientation[EDGE::UL] = this->edgeOrientation[EDGE::LB];
        this->edgeOrientation[EDGE::LB] = this->edgeOrientation[EDGE::DL];
        this->edgeOrientation[EDGE::DL] = this->edgeOrientation[EDGE::FL];
        this->edgeOrientation[EDGE::FL] = temp;
    }
    return *this;
}

/*
**	Front turns
*/
Cube &Cube::f(uint8_t amount)
{
    int arr[] = {12, 11, 10, 6, 5, 4, 24, 31, 30, 42, 41, 40};
    for (uint8_t i = 0; i < amount; i++)
    {
        this->rot90(FACE::FRONT);
        this->rotSides90((int *)arr);
        
        uint8_t temp = this->edgeOrientation[EDGE::UF];
        this->edgeOrientation[EDGE::UF] = this->edgeOrientation[EDGE::FL];
        this->edgeOrientation[EDGE::FL] = this->edgeOrientation[EDGE::DF];
        this->edgeOrientation[EDGE::DF] = this->edgeOrientation[EDGE::FR];
        this->edgeOrientation[EDGE::FR] = temp;
    }
    return *this;
}

/*
** Right turns
*/
Cube &Cube::r(uint8_t amount)
{
    int arr[] = {2, 3, 4, 38, 39, 32, 42, 43, 44, 18, 19, 20};
    for (uint8_t i = 0; i < amount; i++)
    {
        this->rot90(FACE::RIGHT);
        this->rotSides90((int *)arr);

        uint8_t temp = this->edgeOrientation[EDGE::UR];
        this->edgeOrientation[EDGE::UR] = this->edgeOrientation[EDGE::FR];
        this->edgeOrientation[EDGE::FR] = this->edgeOrientation[EDGE::DR];
        this->edgeOrientation[EDGE::DR] = this->edgeOrientation[EDGE::RB];
        this->edgeOrientation[EDGE::RB] = temp;
    }
    return *this;
}

/*
** Back turns
*/
Cube&       Cube::b(uint8_t amount)
{
    int     arr[] = {2, 1, 0, 8, 15, 14, 46, 45, 44, 28, 27, 26};
    for (uint8_t i = 0; i < amount; i++)
    {
        this->rot90(FACE::BACK);
        this->rotSides90((int*)arr);
        
        uint8_t temp = this->edgeOrientation[EDGE::UB];
        this->edgeOrientation[EDGE::UB] = this->edgeOrientation[EDGE::RB];
        this->edgeOrientation[EDGE::RB] = this->edgeOrientation[EDGE::DB];
        this->edgeOrientation[EDGE::DB] = this->edgeOrientation[EDGE::LB];
        this->edgeOrientation[EDGE::LB] = temp;
    }
    return *this;
}

/*
** Back turns
*/
Cube&       Cube::d(uint8_t amount)
{
    int     arr[] = {14, 13, 12, 22, 21, 20, 30, 29, 28, 38, 37, 36};
    for (uint8_t i = 0; i < amount; i++)
    {
        this->rot90(FACE::DOWN);
        this->rotSides90((int*)arr);

        uint8_t temp = this->edgeOrientation[EDGE::DF];
        this->edgeOrientation[EDGE::DF] = 1 - this->edgeOrientation[EDGE::DL];
        this->edgeOrientation[EDGE::DL] = 1 - this->edgeOrientation[EDGE::DB];
        this->edgeOrientation[EDGE::DB] = 1 - this->edgeOrientation[EDGE::DR];
        this->edgeOrientation[EDGE::DR] = 1 - temp;
    }
    return *this;
}
