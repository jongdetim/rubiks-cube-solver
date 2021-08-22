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
		(getFace(FACE::RIGHT) == 0x0303030303030303) &
		(getFace(FACE::BACK) == 0x0404040404040404) &
		(getFace(FACE::DOWN) == 0x0505050505050505));
}

/*
**	@desc	Controller function for getting phase id
**	@param	int phase: current phase
**	@return	phase id for the corresponding phase
*/
uint64_t Cube::get_id(int phase)
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
uint64_t Cube::get_id_phase1()
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
uint64_t Cube::get_id_phase2()
{
	uint64_t id = 0;

	for (int corner = 0; corner < 7; corner++)
	{
		id <<= 2;
		id += cornerOrientation[corner];
	}
	for (int edge = 0; edge < 12; edge++)
	{
		id <<= 2;
		if (edgePosition[edge] < 8)
			id++;
	}
	return id;
}

uint64_t Cube::get_id_phase3()
{
	uint64_t id = 0;
	// 24 + 24 + 1 = 49 bits

	// edge slices M & S    		   = 24 bits
	// 4 keer true, 8 keer false.
	// is 2, 1, of 0
	for (int e = 0; e < 12; e++)
		id |= ((edgePosition[e] > 7) ? 2 : (edgePosition[e] & 1)) << (2 * e);
	// corner tetrads      			   = 24 bits
	id <<= 24;
	for (int c = 0; c < 8; c++)
		id |= (cornerPosition[c] & 5) << (3 * c);
	// parity check, altijd 0 of 1     = 1 bit
	id <<= 1;
	for (int i = 0; i < 8; i++)
		for (int j = i + 1; j < 8; j++)
			id ^= cornerPosition[i] > cornerPosition[j];
	return id;
}

uint64_t Cube::get_id_phase4()
{
	string faces = "FRUBLD";

	uint64_t id = 0;
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			id <<= 1;
			char t = cornerNames[cornerPosition[i]][(cornerOrientation[i] + j) % 3];
			if (t == faces[(faces.find(cornerNames[i][j]) + 3) % 6])
			{
				id++;
			}
		}
	}
	for (int i = 0; i < 12; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			id <<= 1;
			char t = edgeNames[edgePosition[i]][(edgeOrientation[i] + j) % 2];
			if (t == faces[(faces.find(edgeNames[i][j]) + 3) % 6])
			{
				id++;
			}
		}
	}
	return id;
}

/*	
**	@desc	Fill cube at creation constructor function
*/
Cube::Cube()
{
	array<COLOR, 48>::iterator start = cube.begin();
	array<COLOR, 48>::iterator end = next(start, 8);

	for (int i = 0; i < 6; i++)
	{
		fill(start, end, (COLOR)i);
		start = end;
		advance(end, 8);
	}
}

/*
**	@desc	function returns first letter of color of sticker
**	@param	int v, color code
**	@return	char first letter of color of sticker
*/
char getColor(int v)
{
	switch (v)
	{
	case 0:
		return 'W';
	case 1:
		return 'O';
	case 2:
		return 'G';
	case 3:
		return 'R';
	case 4:
		return 'B';
	case 5:
		return 'Y';
	default:
		return 'U';
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
	return *this;
}

void Cube::applyMove(string move)
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
