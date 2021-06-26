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

#include "cube.h"

/*
** Up turns
*/
Cube &Cube::u(uint8_t amount)
{
	int arr[] = {16, 17, 18, 8, 9, 10, 32, 33, 34, 24, 25, 26};
	for (uint8_t i = 0; i < amount; i++)
	{
		// deze zijn niet nodig om te solven, alleen om te printen
		
		rot90(FACE::UP);
		rotSides90((int *)arr);

		uint8_t temp = edgeOrientation[EDGE::UB];
		edgeOrientation[EDGE::UB] = edgeOrientation[EDGE::UL];
		edgeOrientation[EDGE::UL] = edgeOrientation[EDGE::UF];
		edgeOrientation[EDGE::UF] = edgeOrientation[EDGE::UR];
		edgeOrientation[EDGE::UR] = temp;

		temp = cornerOrientation[CORNER::URF];
		cornerOrientation[CORNER::URF] = cornerOrientation[CORNER::UBR];
		cornerOrientation[CORNER::UBR] = cornerOrientation[CORNER::ULB];
		cornerOrientation[CORNER::ULB] = cornerOrientation[CORNER::UFL];
		cornerOrientation[CORNER::UFL] = temp;

		CORNER cTemp = cornerPosition[CORNER::URF];
		cornerPosition[CORNER::URF] = cornerPosition[CORNER::UBR];
		cornerPosition[CORNER::UBR] = cornerPosition[CORNER::ULB];
		cornerPosition[CORNER::ULB] = cornerPosition[CORNER::UFL];
		cornerPosition[CORNER::UFL] = cTemp;

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
Cube &Cube::l(uint8_t amount)
{
	int arr[] = {0, 7, 6, 16, 23, 22, 40, 47, 46, 36, 35, 34};
	for (uint8_t i = 0; i < amount; i++)
	{
		rot90(FACE::LEFT);
		rotSides90((int *)arr);

		uint8_t temp = edgeOrientation[EDGE::BL];
		edgeOrientation[EDGE::BL] = edgeOrientation[EDGE::DL];
		edgeOrientation[EDGE::DL] = edgeOrientation[EDGE::FL];
		edgeOrientation[EDGE::FL] = edgeOrientation[EDGE::UL];
		edgeOrientation[EDGE::UL] = temp;

		temp = cornerOrientation[CORNER::DLF];
		cornerOrientation[CORNER::DLF] = (1 + cornerOrientation[CORNER::UFL]) % 3;
		cornerOrientation[CORNER::UFL] = (2 + cornerOrientation[CORNER::ULB]) % 3;
		cornerOrientation[CORNER::ULB] = (1 + cornerOrientation[CORNER::DBL]) % 3;
		cornerOrientation[CORNER::DBL] = (2 + temp) % 3;

		CORNER cTemp = cornerPosition[CORNER::DLF];
		cornerPosition[CORNER::DLF] = cornerPosition[CORNER::UFL];
		cornerPosition[CORNER::UFL] = cornerPosition[CORNER::ULB];
		cornerPosition[CORNER::ULB] = cornerPosition[CORNER::DBL];
		cornerPosition[CORNER::DBL] = cTemp;

		EDGE eTemp = edgePosition[EDGE::BL];
		edgePosition[EDGE::BL] = edgePosition[EDGE::DL];
		edgePosition[EDGE::DL] = edgePosition[EDGE::FL];
		edgePosition[EDGE::FL] = edgePosition[EDGE::UL];
		edgePosition[EDGE::UL] = eTemp;
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
		rot90(FACE::FRONT);
		rotSides90((int *)arr);
		
		uint8_t temp = edgeOrientation[EDGE::UF];
		edgeOrientation[EDGE::UF] = 1 - edgeOrientation[EDGE::FL];
		edgeOrientation[EDGE::FL] = 1 - edgeOrientation[EDGE::DF];
		edgeOrientation[EDGE::DF] = 1 - edgeOrientation[EDGE::FR];
		edgeOrientation[EDGE::FR] = 1 - temp;

		temp = cornerOrientation[CORNER::URF];
		cornerOrientation[CORNER::URF] = (2 + cornerOrientation[CORNER::UFL]) % 3;
		cornerOrientation[CORNER::UFL] = (1 + cornerOrientation[CORNER::DLF]) % 3;
		cornerOrientation[CORNER::DLF] = (2 + cornerOrientation[CORNER::DFR]) % 3;
		cornerOrientation[CORNER::DFR] = (1 + temp) % 3;

		CORNER cTemp = cornerPosition[CORNER::URF];
		cornerPosition[CORNER::URF] = cornerPosition[CORNER::UFL];
		cornerPosition[CORNER::UFL] = cornerPosition[CORNER::DLF];
		cornerPosition[CORNER::DLF] = cornerPosition[CORNER::DFR];
		cornerPosition[CORNER::DFR] = cTemp;

		EDGE eTemp = edgePosition[EDGE::UF];
		edgePosition[EDGE::UF] = edgePosition[EDGE::FL];
		edgePosition[EDGE::FL] = edgePosition[EDGE::DF];
		edgePosition[EDGE::DF] = edgePosition[EDGE::FR];
		edgePosition[EDGE::FR] = eTemp;
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
		rot90(FACE::RIGHT);
		rotSides90((int *)arr);

		uint8_t temp = edgeOrientation[EDGE::UR];
		edgeOrientation[EDGE::UR] = edgeOrientation[EDGE::FR];
		edgeOrientation[EDGE::FR] = edgeOrientation[EDGE::DR];
		edgeOrientation[EDGE::DR] = edgeOrientation[EDGE::BR];
		edgeOrientation[EDGE::BR] = temp;

		temp = cornerOrientation[CORNER::URF];
		cornerOrientation[CORNER::URF] = (1 + cornerOrientation[CORNER::DFR]) % 3;
		cornerOrientation[CORNER::DFR] = (2 + cornerOrientation[CORNER::DRB]) % 3;
		cornerOrientation[CORNER::DRB] = (1 + cornerOrientation[CORNER::UBR]) % 3;
		cornerOrientation[CORNER::UBR] = (2 + temp) % 3;

		CORNER cTemp = cornerPosition[CORNER::URF];
		cornerPosition[CORNER::URF] = cornerPosition[CORNER::DFR];
		cornerPosition[CORNER::DFR] = cornerPosition[CORNER::DRB];
		cornerPosition[CORNER::DRB] = cornerPosition[CORNER::UBR];
		cornerPosition[CORNER::UBR] = cTemp;

		EDGE eTemp = edgePosition[EDGE::FR];
		edgePosition[EDGE::FR] = edgePosition[EDGE::DR];
		edgePosition[EDGE::DR] = edgePosition[EDGE::BR];
		edgePosition[EDGE::BR] = edgePosition[EDGE::UR];
		edgePosition[EDGE::UR] = eTemp;
	}
	return *this;
}

/*
** Back turns
*/
Cube&		Cube::b(uint8_t amount)
{
	int		arr[] = {2, 1, 0, 8, 15, 14, 46, 45, 44, 28, 27, 26};
	for (uint8_t i = 0; i < amount; i++)
	{
		rot90(FACE::BACK);
		rotSides90((int*)arr);
		
		uint8_t temp = edgeOrientation[EDGE::BR];
		edgeOrientation[EDGE::BR] = 1 - edgeOrientation[EDGE::DB];
		edgeOrientation[EDGE::DB] = 1 - edgeOrientation[EDGE::BL];
		edgeOrientation[EDGE::BL] = 1 - edgeOrientation[EDGE::UB];
		edgeOrientation[EDGE::UB] = 1 - temp;

		temp = cornerOrientation[CORNER::ULB];
		cornerOrientation[CORNER::ULB] = (2 + cornerOrientation[CORNER::UBR]) % 3;
		cornerOrientation[CORNER::UBR] = (1 + cornerOrientation[CORNER::DRB]) % 3;
		cornerOrientation[CORNER::DRB] = (2 + cornerOrientation[CORNER::DBL]) % 3;
		cornerOrientation[CORNER::DBL] = (1 + temp) % 3;

		CORNER cTemp = cornerPosition[CORNER::ULB];
		cornerPosition[CORNER::ULB] = cornerPosition[CORNER::UBR];
		cornerPosition[CORNER::UBR] = cornerPosition[CORNER::DRB];
		cornerPosition[CORNER::DRB] = cornerPosition[CORNER::DBL];
		cornerPosition[CORNER::DBL] = cTemp;

		EDGE eTemp = edgePosition[EDGE::BR];
		edgePosition[EDGE::BR] = edgePosition[EDGE::DB];
		edgePosition[EDGE::DB] = edgePosition[EDGE::BL];
		edgePosition[EDGE::BL] = edgePosition[EDGE::UB];
		edgePosition[EDGE::UB] = eTemp;
	}
	return *this;
}

/*
** Back turns
*/
Cube&		Cube::d(uint8_t amount)
{
	int		arr[] = {14, 13, 12, 22, 21, 20, 30, 29, 28, 38, 37, 36};
	for (uint8_t i = 0; i < amount; i++)
	{
		rot90(FACE::DOWN);
		rotSides90((int*)arr);

		uint8_t temp = edgeOrientation[EDGE::DF];
		edgeOrientation[EDGE::DF] = edgeOrientation[EDGE::DL];
		edgeOrientation[EDGE::DL] = edgeOrientation[EDGE::DB];
		edgeOrientation[EDGE::DB] = edgeOrientation[EDGE::DR];
		edgeOrientation[EDGE::DR] = temp;

		temp = cornerOrientation[CORNER::DFR];
		cornerOrientation[CORNER::DFR] = cornerOrientation[CORNER::DLF];
		cornerOrientation[CORNER::DLF] = cornerOrientation[CORNER::DBL];
		cornerOrientation[CORNER::DBL] = cornerOrientation[CORNER::DRB];
		cornerOrientation[CORNER::DRB] = temp;

		CORNER cTemp = cornerPosition[CORNER::DFR];
		cornerPosition[CORNER::DFR] = cornerPosition[CORNER::DLF];
		cornerPosition[CORNER::DLF] = cornerPosition[CORNER::DBL];
		cornerPosition[CORNER::DBL] = cornerPosition[CORNER::DRB];
		cornerPosition[CORNER::DRB] = cTemp;

		EDGE eTemp = edgePosition[EDGE::DF];
		edgePosition[EDGE::DF] = edgePosition[EDGE::DL];
		edgePosition[EDGE::DL] = edgePosition[EDGE::DB];
		edgePosition[EDGE::DB] = edgePosition[EDGE::DR];
		edgePosition[EDGE::DR] = eTemp;
	}
	return *this;
}
