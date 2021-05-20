/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cube.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: asulliva <asulliva@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/21 20:14:44 by asulliva      #+#    #+#                 */
/*   Updated: 2021/03/21 20:14:44 by asulliva      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

/*	
**	@desc	Gets cube face as 64-bit int
**	@param	FACE f, Face to return
**	@return	uint64_t, the correct face
*/
uint64_t Cube::getFace(FACE f) const
{
	return *(uint64_t *)&this->cube[(unsigned)f * 8];
}

/*	
**	@desc	Function check if cube is in solved state
**	@return	true or false
*/
bool Cube::isSolved() const
{
	return (
		(this->getFace(FACE::UP) == 0x0000000000000000) &
		(this->getFace(FACE::LEFT) == 0x0101010101010101) &
		(this->getFace(FACE::FRONT) == 0x0202020202020202) &
		(this->getFace(FACE::LEFT) == 0x0303030303030303) &
		(this->getFace(FACE::BACK) == 0x0404040404040404) &
		(this->getFace(FACE::DOWN) == 0x0505050505050505));
}

/*	
**	@desc	Fill cube at creation constructor function
*/
Cube::Cube(void)
{
	array<Color, 48>::iterator start = this->cube.begin();
	array<Color, 48>::iterator end = next(start, 8);

	this->cost = 0;
	this->weight = 0;
	this->parent = NULL;
	for (int i = 0; i < 6; i++)
	{
		fill(start, end, (Color)i);
		centers[i] = (Color)i;
		start = end;
		advance(end, 8);
	}
}

Cube::Cube(const Cube *parent)
{
	this->cost = parent->cost + 1;
	this->weight = 0;
	this->parent = (Cube*)parent;
}

char	getColor(int v)
{
	if (v == 0)
		return 'W';
	else if (v == 1)
		return 'G';
	else if (v == 2)
		return 'R';
	else if (v == 3)
		return 'B';
	else if (v == 4)
		return 'O';
	else if (v == 5)
		return 'Y';
	return 'U';
}
/*
**	@desc	function to print the cube
*/
void Cube::printCube() const
{
	uint8_t i = 0;

	printf("(index, color)\n");
	while (i < 48)
	{
		printf("([%d, %c]) ", i, getColor((int)this->cube[i]));
		i++;
		if (i % 8 == 0)
			printf("\n");
	}
}

/*
**	@desc	Compare two cubes to eachother
**	@param	const Cube&, refernce to the cube to be compared
**	@return	true if equal, false if not
*/
bool Cube::operator==(const Cube &c) const
{
	for (int i = 0; i < 6; i++)
		if (this->getFace((FACE)i) != c.getFace((FACE)i))
			return false;
	return true;
}

/*
**	@desc	Function copies from given
*/
Cube &Cube::operator=(const Cube *c)
{
	memcpy((void *)&this->cube[0], (void *)&c->cube[0], 48);
	memcpy((void *)&this->centers[0], (void *)&c->centers[0], 6);
	return *this;
}
