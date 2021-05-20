/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   moves.cpp                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: asulliva <asulliva@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/21 20:14:57 by asulliva      #+#    #+#                 */
/*   Updated: 2021/04/12 15:46:53 by kpereira      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

/*
** Up turns
*/
Cube &Cube::u()
{
    int arr[] = {16, 17, 18, 8, 9, 10, 32, 33, 34, 24, 25, 26};

    this->rot90(FACE::UP);
    this->rotSides90((int *)arr);
    return *this;
}

Cube &Cube::u2()
{
    int arr[] = {16, 17, 18, 32, 33, 34, 24, 25, 26, 8, 9, 10};

    this->rot180(FACE::UP);
    this->rotSides180((int *)arr);
    return *this;
}

Cube &Cube::uPrime()
{
    int arr[] = {8, 9, 10, 16, 17, 18, 24, 25, 26, 32, 33, 34};

    this->rot270(FACE::UP);
    this->rotSides90((int *)arr);
    return *this;
}

/*
** Left turns
*/
Cube &Cube::l()
{
    int arr[] = {0, 7, 6, 16, 23, 22, 40, 47, 46, 36, 35, 34};

    this->rot90(FACE::LEFT);
    this->rotSides90((int *)arr);
    return *this;
}

Cube &Cube::l2()
{
    int arr[] = {22, 23, 16, 34, 35, 36, 0, 7, 6, 40, 47, 46};

    this->rot180(FACE::LEFT);
    this->rotSides180((int *)arr);
    return *this;
}

Cube &Cube::lPrime()
{
    int arr[] = {40, 47, 46, 16, 23, 22, 0, 7, 6, 34, 35, 36};

    this->rot270(FACE::LEFT);
    this->rotSides90((int *)arr);
    return *this;
}

/*
**	Front turns
*/
Cube &Cube::f()
{
    int arr[] = {12, 11, 10, 6, 5, 4, 24, 31, 30, 42, 41, 40};

    this->rot90(FACE::FRONT);
    this->rotSides90((int *)arr);
    return *this;
}

Cube &Cube::f2()
{
    int arr[] = {6, 5, 4, 42, 41, 40, 24, 31, 30, 12, 11, 10};

    this->rot180(FACE::FRONT);
    this->rotSides180((int *)arr);
    return *this;
}

Cube &Cube::fPrime()
{
    int arr[] = {6, 5, 4, 12, 11, 10, 40, 41, 42, 24, 31, 30};

    this->rot270(FACE::FRONT);
    this->rotSides90((int *)arr);
    return *this;
}

/*
** Right turns
*/
Cube &Cube::r()
{
    int arr[] = {2, 3, 4, 38, 39, 32, 42, 43, 44, 18, 19, 20};

    this->rot90(FACE::RIGHT);
    this->rotSides90((int *)arr);
    return *this;
}

Cube &Cube::r2()
{
    int arr[] = {2, 3, 4, 42, 43, 44, 32, 39, 38, 18, 19, 20};

    this->rot180(FACE::RIGHT);
    this->rotSides180((int *)arr);
    return *this;
}

Cube &Cube::rPrime()
{
    int arr[] = {18, 19, 20, 42, 43, 44, 38, 39, 32, 2, 3, 4};

    this->rot270(FACE::RIGHT);
    this->rotSides90((int *)arr);
    return *this;
}

/*
** Back turns
*/
Cube&       Cube::b()
{
    int     arr[] = {2, 1, 0, 8, 15, 14, 46, 45, 44, 28, 27, 26};

    this->rot90(FACE::BACK);
    this->rotSides90((int*)arr);
    return *this;
}

Cube&       Cube::b2()
{
    int     arr[] = {0, 1, 2, 44, 45, 46, 8, 15, 14, 28, 27, 26};

    this->rot180(FACE::BACK);
    this->rotSides180((int*)arr);
    return *this;
}

Cube&       Cube::bPrime()
{
    int     arr[] = {0, 1, 2, 26, 27, 28, 44, 45, 46, 14, 15, 8};

    this->rot270(FACE::BACK);
    this->rotSides90((int*)arr);
    return *this;
}

/*
** Back turns
*/
Cube&       Cube::d()
{
    int     arr[] = {14, 13, 12, 22, 21, 20, 30, 29, 28, 38, 37, 36};

    this->rot90(FACE::DOWN);
    this->rotSides90((int*)arr);
    return *this;
}

Cube&       Cube::d2()
{
    int     arr[] = {22, 21, 20, 38, 37, 36, 14, 13, 12, 30, 29, 28};

    this->rot180(FACE::DOWN);
    this->rotSides180((int*)arr);
    return *this;
}

Cube&       Cube::dPrime()
{
    int     arr[] = {38, 37, 36, 30, 39, 28, 22, 21, 20, 14, 13, 12};

    this->rot270(FACE::DOWN);
    this->rotSides90((int*)arr);
    return *this;
}