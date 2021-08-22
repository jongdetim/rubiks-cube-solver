/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rotate.cpp                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: asulliva <asulliva@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/21 20:15:52 by asulliva      #+#    #+#                 */
/*   Updated: 2021/06/21 20:04:03 by asulliva      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cube.hpp"

/*
**	@desc	Function rotates face 90 degrees
**	@param	FACE f, face to turn
*/
void Cube::rot90(FACE f)
{
	uint64_t face = *(uint64_t *)&this->cube[(unsigned)f * 8];
	asm ("rolq $16, %[face]" : [face] "+r" (face) : );
	*(uint64_t *)&this->cube[(unsigned)f * 8] = face;
}

/*
**	@desc	rotate sides by 90
**	@param	int* arr, array[12] with indexes to be rotated 
*/
void Cube::rotSides90(int *arr)
{
	COLOR tmp[3];

	for (int i = 0; i < 3; i++)
		tmp[i] = this->cube[arr[9 + i]];
	for (int i = 11; i >= 3; i--)
		this->cube[arr[i]] = this->cube[arr[i - 3]];
	for (int i = 0; i < 3; i++)
		this->cube[arr[i]] = tmp[i];
}