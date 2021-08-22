/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cube.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: asulliva <asulliva@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/21 20:15:04 by asulliva      #+#    #+#                 */
/*   Updated: 2021/03/21 20:15:04 by asulliva      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */
#ifndef CUBE_H
# define CUBE_H

# include "main.hpp"
//						0      1     2     3     4       5
// enum COLOR : uint8_t {WHITE, GREEN, RED, YELLOW, BLUE, ORANGE};
// enum FACE : uint8_t {UP, FRONT, RIGHT, DOWN, BACK, LEFT};
enum COLOR : uint8_t {WHITE, ORANGE, GREEN, RED, BLUE, YELLOW};
enum FACE : uint8_t {UP, LEFT, FRONT, RIGHT, BACK, DOWN};

enum EDGE {UF, UR, UB, UL, DF, DR, DB, DL, FR, FL, BR, BL};
enum CORNER {URF, UBR, ULB, UFL, DFR, DLF, DBL, DRB};

class Cube
{
	private:
		void rot90(FACE f);
		void rotSides90(int* arr);
		uint64_t get_id_phase1();
		uint64_t get_id_phase2();
		uint64_t get_id_phase3();
		uint64_t get_id_phase4();

	public:
		array<COLOR, 48> cube;
		char	cornerOrientation[8] = {0, 0, 0, 0, 0, 0, 0, 0};
		char 	edgeOrientation[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
		CORNER	cornerPosition[8] = {URF, UBR, ULB, UFL, DFR, DLF, DBL, DRB};
		EDGE	edgePosition[12] = {UF, UR, UB, UL, DF, DR, DB, DL, FR, FL, BR, BL};
		string cornerNames[8] = {"URF", "UBR", "ULB", "UFL", "DFR", "DLF", "DBL", "DRB"};
		string edgeNames[12] = {"UF", "UR", "UB", "UL", "DF", "DR", "DB", "DL", "FR", "FL", "BR", "BL"};
		string path = "";
		vector<string> path_vect;

		Cube();
		uint64_t getFace(FACE f) const;
		bool isSolved() const;
		bool operator==(const Cube& c) const;
		Cube& operator=(const Cube* c);

		// Moves
		void applyMove(string move);
		Cube& u(int amount);
		Cube& l(int amount);
		Cube& f(int amount);
		Cube& r(int amount);
		Cube& b(int amount);
		Cube& d(int amount);

		// Unique state ID
		uint64_t get_id(int phase);
};

char	getColor(int v);

#endif
