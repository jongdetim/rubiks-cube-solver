/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   moves.cpp                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: asulliva <asulliva@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/21 20:14:57 by asulliva      #+#    #+#                 */
/*   Updated: 2021/06/22 21:01:12 by asulliva      ########   odam.nl         */
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

		uint8_t temp = this->edgeOrientation[EDGE::UB];
		this->edgeOrientation[EDGE::UB] = this->edgeOrientation[EDGE::UL];
		this->edgeOrientation[EDGE::UL] = this->edgeOrientation[EDGE::UF];
		this->edgeOrientation[EDGE::UF] = this->edgeOrientation[EDGE::UR];
		this->edgeOrientation[EDGE::UR] = temp;

		temp = this->cornerOrientation[CORNER::URF];
		this->cornerOrientation[CORNER::URF] = this->cornerOrientation[CORNER::UBR];
		this->cornerOrientation[CORNER::UBR] = this->cornerOrientation[CORNER::ULB];
		this->cornerOrientation[CORNER::ULB] = this->cornerOrientation[CORNER::UFL];
		this->cornerOrientation[CORNER::UFL] = temp;

		CORNER cTemp = this->cornerPosition[CORNER::URF];
		this->cornerPosition[CORNER::URF] = this->cornerPosition[CORNER::UBR];
		this->cornerPosition[CORNER::UBR] = this->cornerPosition[CORNER::ULB];
		this->cornerPosition[CORNER::ULB] = this->cornerPosition[CORNER::UFL];
		this->cornerPosition[CORNER::UFL] = cTemp;

		EDGE eTemp = this->edgePosition[EDGE::UB];
		this->edgePosition[EDGE::UB] = this->edgePosition[EDGE::UL];
		this->edgePosition[EDGE::UL] = this->edgePosition[EDGE::UF];
		this->edgePosition[EDGE::UF] = this->edgePosition[EDGE::UR];
		this->edgePosition[EDGE::UR] = eTemp;
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

		uint8_t temp = this->edgeOrientation[EDGE::BL];
		this->edgeOrientation[EDGE::BL] = this->edgeOrientation[EDGE::DL];
		this->edgeOrientation[EDGE::DL] = this->edgeOrientation[EDGE::FL];
		this->edgeOrientation[EDGE::FL] = this->edgeOrientation[EDGE::UL];
		this->edgeOrientation[EDGE::UL] = temp;

		temp = this->cornerOrientation[CORNER::DLF];
		this->cornerOrientation[CORNER::DLF] = (1 + this->cornerOrientation[CORNER::UFL]) % 3;
		this->cornerOrientation[CORNER::UFL] = (2 + this->cornerOrientation[CORNER::ULB]) % 3;
		this->cornerOrientation[CORNER::ULB] = (1 + this->cornerOrientation[CORNER::DBL]) % 3;
		this->cornerOrientation[CORNER::DBL] = (2 + temp) % 3;

		CORNER cTemp = this->cornerPosition[CORNER::DLF];
		this->cornerPosition[CORNER::DLF] = this->cornerPosition[CORNER::UFL];
		this->cornerPosition[CORNER::UFL] = this->cornerPosition[CORNER::ULB];
		this->cornerPosition[CORNER::ULB] = this->cornerPosition[CORNER::DBL];
		this->cornerPosition[CORNER::DBL] = cTemp;

		EDGE eTemp = this->edgePosition[EDGE::BL];
		this->edgePosition[EDGE::BL] = this->edgePosition[EDGE::DL];
		this->edgePosition[EDGE::DL] = this->edgePosition[EDGE::FL];
		this->edgePosition[EDGE::FL] = this->edgePosition[EDGE::UL];
		this->edgePosition[EDGE::UL] = eTemp;
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
		this->edgeOrientation[EDGE::UF] = 1 - this->edgeOrientation[EDGE::FL];
		this->edgeOrientation[EDGE::FL] = 1 - this->edgeOrientation[EDGE::DF];
		this->edgeOrientation[EDGE::DF] = 1 - this->edgeOrientation[EDGE::FR];
		this->edgeOrientation[EDGE::FR] = 1 - temp;

		temp = this->cornerOrientation[CORNER::URF];
		this->cornerOrientation[CORNER::URF] = (2 + this->cornerOrientation[CORNER::UFL]) % 3;
		this->cornerOrientation[CORNER::UFL] = (1 + this->cornerOrientation[CORNER::DLF]) % 3;
		this->cornerOrientation[CORNER::DLF] = (2 + this->cornerOrientation[CORNER::DFR]) % 3;
		this->cornerOrientation[CORNER::DFR] = (1 + temp) % 3;

		CORNER cTemp = this->cornerPosition[CORNER::URF];
		this->cornerPosition[CORNER::URF] = this->cornerPosition[CORNER::UFL];
		this->cornerPosition[CORNER::UFL] = this->cornerPosition[CORNER::DLF];
		this->cornerPosition[CORNER::DLF] = this->cornerPosition[CORNER::DFR];
		this->cornerPosition[CORNER::DFR] = cTemp;

		EDGE eTemp = this->edgePosition[EDGE::UF];
		this->edgePosition[EDGE::UF] = this->edgePosition[EDGE::FL];
		this->edgePosition[EDGE::FL] = this->edgePosition[EDGE::DF];
		this->edgePosition[EDGE::DF] = this->edgePosition[EDGE::FR];
		this->edgePosition[EDGE::FR] = eTemp;
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
		this->edgeOrientation[EDGE::DR] = this->edgeOrientation[EDGE::BR];
		this->edgeOrientation[EDGE::BR] = temp;

		temp = this->cornerOrientation[CORNER::URF];
		this->cornerOrientation[CORNER::URF] = (1 + this->cornerOrientation[CORNER::DFR]) % 3;
		this->cornerOrientation[CORNER::DFR] = (2 + this->cornerOrientation[CORNER::DRB]) % 3;
		this->cornerOrientation[CORNER::DRB] = (1 + this->cornerOrientation[CORNER::UBR]) % 3;
		this->cornerOrientation[CORNER::UBR] = (2 + temp) % 3;

		CORNER cTemp = this->cornerPosition[CORNER::URF];
		this->cornerPosition[CORNER::URF] = this->cornerPosition[CORNER::DFR];
		this->cornerPosition[CORNER::DFR] = this->cornerPosition[CORNER::DRB];
		this->cornerPosition[CORNER::DRB] = this->cornerPosition[CORNER::UBR];
		this->cornerPosition[CORNER::UBR] = cTemp;

		EDGE eTemp = this->edgePosition[EDGE::FR];
		this->edgePosition[EDGE::FR] = this->edgePosition[EDGE::DR];
		this->edgePosition[EDGE::DR] = this->edgePosition[EDGE::BR];
		this->edgePosition[EDGE::BR] = this->edgePosition[EDGE::UR];
		this->edgePosition[EDGE::UR] = eTemp;
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
		this->rot90(FACE::BACK);
		this->rotSides90((int*)arr);
		
		uint8_t temp = this->edgeOrientation[EDGE::BR];
		this->edgeOrientation[EDGE::BR] = 1 - this->edgeOrientation[EDGE::DB];
		this->edgeOrientation[EDGE::DB] = 1 - this->edgeOrientation[EDGE::BL];
		this->edgeOrientation[EDGE::BL] = 1 - this->edgeOrientation[EDGE::UB];
		this->edgeOrientation[EDGE::UB] = 1 - temp;

		temp = this->cornerOrientation[CORNER::ULB];
		this->cornerOrientation[CORNER::ULB] = (2 + this->cornerOrientation[CORNER::UBR]) % 3;
		this->cornerOrientation[CORNER::UBR] = (1 + this->cornerOrientation[CORNER::DRB]) % 3;
		this->cornerOrientation[CORNER::DRB] = (2 + this->cornerOrientation[CORNER::DBL]) % 3;
		this->cornerOrientation[CORNER::DBL] = (1 + temp) % 3;

		CORNER cTemp = this->cornerPosition[CORNER::ULB];
		this->cornerPosition[CORNER::ULB] = this->cornerPosition[CORNER::UBR];
		this->cornerPosition[CORNER::UBR] = this->cornerPosition[CORNER::DRB];
		this->cornerPosition[CORNER::DRB] = this->cornerPosition[CORNER::DBL];
		this->cornerPosition[CORNER::DBL] = cTemp;

		EDGE eTemp = this->edgePosition[EDGE::BR];
		this->edgePosition[EDGE::BR] = this->edgePosition[EDGE::DB];
		this->edgePosition[EDGE::DB] = this->edgePosition[EDGE::BL];
		this->edgePosition[EDGE::BL] = this->edgePosition[EDGE::UB];
		this->edgePosition[EDGE::UB] = eTemp;
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
		this->rot90(FACE::DOWN);
		this->rotSides90((int*)arr);

		uint8_t temp = this->edgeOrientation[EDGE::DF];
		this->edgeOrientation[EDGE::DF] = this->edgeOrientation[EDGE::DL];
		this->edgeOrientation[EDGE::DL] = this->edgeOrientation[EDGE::DB];
		this->edgeOrientation[EDGE::DB] = this->edgeOrientation[EDGE::DR];
		this->edgeOrientation[EDGE::DR] = temp;

		temp = this->cornerOrientation[CORNER::DFR];
		this->cornerOrientation[CORNER::DFR] = this->cornerOrientation[CORNER::DLF];
		this->cornerOrientation[CORNER::DLF] = this->cornerOrientation[CORNER::DBL];
		this->cornerOrientation[CORNER::DBL] = this->cornerOrientation[CORNER::DRB];
		this->cornerOrientation[CORNER::DRB] = temp;

		CORNER cTemp = this->cornerPosition[CORNER::DFR];
		this->cornerPosition[CORNER::DFR] = this->cornerPosition[CORNER::DLF];
		this->cornerPosition[CORNER::DLF] = this->cornerPosition[CORNER::DBL];
		this->cornerPosition[CORNER::DBL] = this->cornerPosition[CORNER::DRB];
		this->cornerPosition[CORNER::DRB] = cTemp;

		EDGE eTemp = this->edgePosition[EDGE::DF];
		this->edgePosition[EDGE::DF] = this->edgePosition[EDGE::DL];
		this->edgePosition[EDGE::DL] = this->edgePosition[EDGE::DB];
		this->edgePosition[EDGE::DB] = this->edgePosition[EDGE::DR];
		this->edgePosition[EDGE::DR] = eTemp;
	}
	return *this;
}
