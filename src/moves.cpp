/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   moves.cpp                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: asulliva <asulliva@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/21 20:14:57 by asulliva      #+#    #+#                 */
/*   Updated: 2021/06/26 21:35:08 by tide-jon      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cube.hpp"

/*
** Up turns
*/
Cube &Cube::u(int amount)
{
	int arr[] = {16, 17, 18, 8, 9, 10, 32, 33, 34, 24, 25, 26};
	for (int i = 0; i < amount; i++)
	{
		// deze zijn niet nodig om te solven, alleen om te printen
		
		rot90(FACE::UP);
		rotSides90((int *)arr);

		char temp = edgeOrientation[UB];
		edgeOrientation[UB] = edgeOrientation[UL];
		edgeOrientation[UL] = edgeOrientation[UF];
		edgeOrientation[UF] = edgeOrientation[UR];
		edgeOrientation[UR] = temp;

		temp = cornerOrientation[URF];
		cornerOrientation[URF] = cornerOrientation[UBR];
		cornerOrientation[UBR] = cornerOrientation[ULB];
		cornerOrientation[ULB] = cornerOrientation[UFL];
		cornerOrientation[UFL] = temp;

		CORNER cTemp = cornerPosition[URF];
		cornerPosition[URF] = cornerPosition[UBR];
		cornerPosition[UBR] = cornerPosition[ULB];
		cornerPosition[ULB] = cornerPosition[UFL];
		cornerPosition[UFL] = cTemp;

		EDGE eTemp = edgePosition[UB];
		edgePosition[UB] = edgePosition[UL];
		edgePosition[UL] = edgePosition[UF];
		edgePosition[UF] = edgePosition[UR];
		edgePosition[UR] = eTemp;
	}
	return *this;
}

/*
** Left turns
*/
Cube &Cube::l(int amount)
{
	int arr[] = {0, 7, 6, 16, 23, 22, 40, 47, 46, 36, 35, 34};
	for (int i = 0; i < amount; i++)
	{
		rot90(FACE::LEFT);
		rotSides90((int *)arr);

		char temp = edgeOrientation[BL];
		edgeOrientation[BL] = edgeOrientation[DL];
		edgeOrientation[DL] = edgeOrientation[FL];
		edgeOrientation[FL] = edgeOrientation[UL];
		edgeOrientation[UL] = temp;

		temp = cornerOrientation[DLF];
		cornerOrientation[DLF] = (1 + cornerOrientation[UFL]) % 3;
		cornerOrientation[UFL] = (2 + cornerOrientation[ULB]) % 3;
		cornerOrientation[ULB] = (1 + cornerOrientation[DBL]) % 3;
		cornerOrientation[DBL] = (2 + temp) % 3;

		CORNER cTemp = cornerPosition[DLF];
		cornerPosition[DLF] = cornerPosition[UFL];
		cornerPosition[UFL] = cornerPosition[ULB];
		cornerPosition[ULB] = cornerPosition[DBL];
		cornerPosition[DBL] = cTemp;

		EDGE eTemp = edgePosition[BL];
		edgePosition[BL] = edgePosition[DL];
		edgePosition[DL] = edgePosition[FL];
		edgePosition[FL] = edgePosition[UL];
		edgePosition[UL] = eTemp;
	}
	return *this;
}

/*
**	Front turns
*/
Cube &Cube::f(int amount)
{
	int arr[] = {12, 11, 10, 6, 5, 4, 24, 31, 30, 42, 41, 40};
	for (int i = 0; i < amount; i++)
	{
		rot90(FACE::FRONT);
		rotSides90((int *)arr);
		
		char temp = edgeOrientation[UF];
		edgeOrientation[UF] = 1 - edgeOrientation[FL];
		edgeOrientation[FL] = 1 - edgeOrientation[DF];
		edgeOrientation[DF] = 1 - edgeOrientation[FR];
		edgeOrientation[FR] = 1 - temp;

		temp = cornerOrientation[URF];
		cornerOrientation[URF] = (2 + cornerOrientation[UFL]) % 3;
		cornerOrientation[UFL] = (1 + cornerOrientation[DLF]) % 3;
		cornerOrientation[DLF] = (2 + cornerOrientation[DFR]) % 3;
		cornerOrientation[DFR] = (1 + temp) % 3;

		CORNER cTemp = cornerPosition[URF];
		cornerPosition[URF] = cornerPosition[UFL];
		cornerPosition[UFL] = cornerPosition[DLF];
		cornerPosition[DLF] = cornerPosition[DFR];
		cornerPosition[DFR] = cTemp;

		EDGE eTemp = edgePosition[UF];
		edgePosition[UF] = edgePosition[FL];
		edgePosition[FL] = edgePosition[DF];
		edgePosition[DF] = edgePosition[FR];
		edgePosition[FR] = eTemp;
	}
	return *this;
}

/*
** Right turns
*/
Cube &Cube::r(int amount)
{
	int arr[] = {2, 3, 4, 38, 39, 32, 42, 43, 44, 18, 19, 20};
	for (int i = 0; i < amount; i++)
	{
		rot90(FACE::RIGHT);
		rotSides90((int *)arr);

		char temp = edgeOrientation[FR];
		edgeOrientation[FR] = edgeOrientation[DR];
		edgeOrientation[DR] = edgeOrientation[BR];
		edgeOrientation[BR] = edgeOrientation[UR];
		edgeOrientation[UR] = temp;

		temp = cornerOrientation[URF];
		cornerOrientation[URF] = (1 + cornerOrientation[DFR]) % 3;
		cornerOrientation[DFR] = (2 + cornerOrientation[DRB]) % 3;
		cornerOrientation[DRB] = (1 + cornerOrientation[UBR]) % 3;
		cornerOrientation[UBR] = (2 + temp) % 3;

		CORNER cTemp = cornerPosition[URF];
		cornerPosition[URF] = cornerPosition[DFR];
		cornerPosition[DFR] = cornerPosition[DRB];
		cornerPosition[DRB] = cornerPosition[UBR];
		cornerPosition[UBR] = cTemp;

		EDGE eTemp = edgePosition[FR];
		edgePosition[FR] = edgePosition[DR];
		edgePosition[DR] = edgePosition[BR];
		edgePosition[BR] = edgePosition[UR];
		edgePosition[UR] = eTemp;
	}
	return *this;
}

/*
** Back turns
*/
Cube&		Cube::b(int amount)
{
	int		arr[] = {2, 1, 0, 8, 15, 14, 46, 45, 44, 28, 27, 26};
	for (int i = 0; i < amount; i++)
	{
		rot90(FACE::BACK);
		rotSides90((int*)arr);
		
		char temp = edgeOrientation[BR];
		edgeOrientation[BR] = 1 - edgeOrientation[DB];
		edgeOrientation[DB] = 1 - edgeOrientation[BL];
		edgeOrientation[BL] = 1 - edgeOrientation[UB];
		edgeOrientation[UB] = 1 - temp;

		temp = cornerOrientation[ULB];
		cornerOrientation[ULB] = (2 + cornerOrientation[UBR]) % 3;
		cornerOrientation[UBR] = (1 + cornerOrientation[DRB]) % 3;
		cornerOrientation[DRB] = (2 + cornerOrientation[DBL]) % 3;
		cornerOrientation[DBL] = (1 + temp) % 3;

		CORNER cTemp = cornerPosition[ULB];
		cornerPosition[ULB] = cornerPosition[UBR];
		cornerPosition[UBR] = cornerPosition[DRB];
		cornerPosition[DRB] = cornerPosition[DBL];
		cornerPosition[DBL] = cTemp;

		EDGE eTemp = edgePosition[BR];
		edgePosition[BR] = edgePosition[DB];
		edgePosition[DB] = edgePosition[BL];
		edgePosition[BL] = edgePosition[UB];
		edgePosition[UB] = eTemp;
	}
	return *this;
}

/*
** Back turns
*/
Cube&		Cube::d(int amount)
{
	int		arr[] = {14, 13, 12, 22, 21, 20, 30, 29, 28, 38, 37, 36};
	for (int i = 0; i < amount; i++)
	{
		rot90(FACE::DOWN);
		rotSides90((int*)arr);

		char temp = edgeOrientation[DF];
		edgeOrientation[DF] = edgeOrientation[DL];
		edgeOrientation[DL] = edgeOrientation[DB];
		edgeOrientation[DB] = edgeOrientation[DR];
		edgeOrientation[DR] = temp;

		temp = cornerOrientation[DFR];
		cornerOrientation[DFR] = cornerOrientation[DLF];
		cornerOrientation[DLF] = cornerOrientation[DBL];
		cornerOrientation[DBL] = cornerOrientation[DRB];
		cornerOrientation[DRB] = temp;

		CORNER cTemp = cornerPosition[DFR];
		cornerPosition[DFR] = cornerPosition[DLF];
		cornerPosition[DLF] = cornerPosition[DBL];
		cornerPosition[DBL] = cornerPosition[DRB];
		cornerPosition[DRB] = cTemp;

		EDGE eTemp = edgePosition[DF];
		edgePosition[DF] = edgePosition[DL];
		edgePosition[DL] = edgePosition[DB];
		edgePosition[DB] = edgePosition[DR];
		edgePosition[DR] = eTemp;
	}
	return *this;
}
