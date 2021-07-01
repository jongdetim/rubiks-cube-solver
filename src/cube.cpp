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

#include "cube.hpp"

/*	
**	@desc	Gets cube face as 64-bit int
**	@param	FACE f, Face to return
**	@return	uint64_t, the correct face
*/
uint64_t Cube::getFace(FACE f) const
{
	return *(uint64_t *)&cube[(unsigned)f * 8];
}

/*	
**	@desc	Function check if cube is in solved state
**	@return	true or false
*/
bool Cube::isSolved() const
{
	return (
		(getFace(FACE::UP) == 0x0000000000000000) &
		(getFace(FACE::LEFT) == 0x0101010101010101) &
		(getFace(FACE::FRONT) == 0x0202020202020202) &
		(getFace(FACE::LEFT) == 0x0303030303030303) &
		(getFace(FACE::BACK) == 0x0404040404040404) &
		(getFace(FACE::DOWN) == 0x0505050505050505));
}

/*
**	@desc	Controller function for getting phase id
**	@param	int phase: current phase
**	@return	phase id for the corresponding phase
*/
uint64_t	Cube::get_id(int phase)
{
	switch (phase)
	{
		case 0:
			return get_id_phase1();
		case 1:
			return get_id_phase2();
		case 2:
			return get_id_phase3();
		case 3:
			return get_id_phase4();
		default:
			cout << "error: impossible phase number" << endl;
			exit(1);
	}
}

/*
**	@desc	Function for getting id phase 1
**	@return	phase id
*/
uint64_t	Cube::get_id_phase1()
{
	uint64_t id = 0; 
	for (int edge = 0; edge < 11; edge++)
	{
		id <<= 1;
		id += edgeOrientation[edge];
	}
	return id;
}

/*
**	@desc	Function for getting id phase 2
**	@return	phase id
*/
uint64_t	Cube::get_id_phase2(){
	uint64_t id = 0; 
	for (int corner = 0; corner < 8; corner++)
	{
		id <<= 2;
		id += cornerOrientation[corner];
	}
	for (int edge = 0; edge < 12; edge++){
		id <<= 2;
		if (edgePosition[edge] < 8)
			id++;
	}
	return id;
}

/*
**	@desc	Function for getting id phase 3
**	@return	phase id
*/
uint64_t		Cube::get_id_phase3(){
	string faces = "FRUBLD";

	uint64_t id = 0;
	for (int i = 0; i < 7; i++){
		for (int j = 0; j < 3; j++){
			id <<= 1;
			char t = cornerNames[cornerPosition[i]][(cornerOrientation[i] + j) % 3];
			if (!(t == cornerNames[i][j] ||
				t == faces[(faces.find(cornerNames[i][j]) + 3) % 6]))
					id++;
		}	
	}
	for (int i = 0; i < 11; i++){
		for (int j = 0; j < 2; j++){
			id <<= 1;
			char t = edgeNames[edgePosition[i]][(edgeOrientation[i] + j) % 2];
			if (!(t == edgeNames[i][j] ||
				t == faces[(faces.find(edgeNames[i][j]) + 3) % 6])){
				id++;
			}
		}			
	}	
	for (int i = 0; i < 8; i++)
	{
		id <<= 1;
		if (cornerPosition[i] % 4 != i % 4)
			id++;
	}	
	id <<= 1;
	for (int i = 0; i < 8; i++ )
	{
		for(int j = i + 1; j < 8; j++)
			id ^= this->cornerPosition[i] > this->cornerPosition[j];
	}	
	return id;
}

uint64_t	Cube::get_id_phase4(){
	string faces = "FRUBLD";
	
	uint64_t id = 0; 
	for (int i = 0; i < 8; i++){
		for (int j = 0; j < 3; j++){
			id <<= 1;
			char t = cornerNames[cornerPosition[i]][(cornerOrientation[i] + j) % 3];
			if (t == faces[(faces.find(cornerNames[i][j]) + 3) % 6]){
				id++;
			}
		}
	}
	for (int i = 0; i < 12; i++){
		for (int j = 0; j < 2; j++){
			id <<= 1;
			char t = edgeNames[edgePosition[i]][(edgeOrientation[i] + j) % 2];
			if (t == faces[(faces.find(edgeNames[i][j]) + 3) % 6]){
				id++;
			}
		}			
	}
	return id;
}

/*	
**	@desc	Fill cube at creation constructor function
*/
Cube::Cube(void)
{
	array<COLOR, 48>::iterator start = cube.begin();
	array<COLOR, 48>::iterator end = next(start, 8);

	for (int i = 0; i < 6; i++)
	{
		fill(start, end, (COLOR)i);
		centers[i] = (COLOR)i;
		start = end;
		advance(end, 8);
	}
}

/*
**	@desc	function returns first letter of color of sticker
**	@param	int v, color code
**	@return	char first letter of color of sticker
*/
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
		printf("([%d, %c]) ", i, getColor((int)cube[i]));
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
		if (getFace((FACE)i) != c.getFace((FACE)i))
			return false;
	return true;
}

/*
**	@desc	Function copies from given
**	@param	const Cube *c, pointer to cube to copy to
**	@return	pointer new filled cube
*/
Cube &Cube::operator=(const Cube *c)
{
	memcpy((void *)&cube[0], (void *)&c->cube[0], 48);
	memcpy((void *)&centers[0], (void *)&c->centers[0], 6);
	return *this;
}

void	Cube::applyMove(string move)
{
	if (move == "U")
		u(1);
	else if (move == "L")
		l(1);
	else if (move == "F")
		f(1);
	else if (move == "R")
		r(1);
	else if (move == "B")
		b(1);
	else if (move == "D")
		d(1);
	else if (move == "U2")
		u(2);
	else if (move == "L2")
		l(2);
	else if (move == "F2")
		f(2);
	else if (move == "R2")
		r(2);
	else if (move == "B2")
		b(2);
	else if (move == "D2")
		d(2);
	else if (move == "U'")
		u(3);
	else if (move == "L'")
		l(3);
	else if (move == "F'")
		f(3);
	else if (move == "R'")
		r(3);
	else if (move == "B'")
		b(3);
	else if (move == "D'")
		d(3);
}
