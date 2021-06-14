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

# include <iostream>
# include <cstdio>
# include <stdint.h>
# include <array>
# include <cstring>
# include <algorithm>
# include <vector>
using std::advance;
using std::array;
using std::fill;
using std::next;
using std::swap;
using std::memcpy;
using std::vector;
using std::array;


//							  0      1     2     3     4       5
enum COLOR : uint8_t {WHITE, GREEN, RED, BLUE, ORANGE, YELLOW};
enum FACE : uint8_t {UP, LEFT, FRONT, RIGHT, BACK, DOWN};
enum EDGE : uint8_t {UF, UR, UB, UL, DF, DR, DB, DL, LB, FR, FL, RB};
enum CORNER : uint8_t {URF, UBR, DLF, DFR, ULB, DRB, DBL};

class Cube
{
	private:
		array<COLOR, 48> cube;
		array<COLOR, 6> centers;

		uint8_t	cornerOrientation[8] = {1, 1, 1, 1, 1, 1, 1, 1};
		uint8_t edgeOrientation[12] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};

		using edge_t = array<COLOR, 2>;
		using corner_t = array<COLOR, 3>;
		Cube *parent;
		int cost;
		int weight;

		vector<Cube> children; //possible next moves
		// Rotations
		void rot90(FACE f);
		void rot180(FACE f);
		void rot270(FACE f);

		void rotSides90(int* arr);
		void rotSides180(int* arr);
	public:
		Cube( void );
		Cube(const Cube *parent);

		uint64_t getFace(FACE f) const;
		bool isSolved() const;
		void printCube() const;

		// Compare cube
		bool operator==(const Cube& c) const;

		// Copy cube
		Cube& operator=(const Cube* c);

		// Moves
		void applyMove(char move);
		void reverseMove(char move);
		Cube& u(uint8_t amount);

		Cube& l(uint8_t amount);

		Cube& f(uint8_t amount);

		Cube& r(uint8_t amount);

		Cube& b(uint8_t amount);

		Cube& d(uint8_t amount);

		uint64_t get_id_phase1();
};

#endif
