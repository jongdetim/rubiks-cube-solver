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


//							  0      1     2     3     4       5
enum class Color : uint8_t {WHITE, GREEN, RED, BLUE, ORANGE, YELLOW};
enum class FACE : uint8_t {UP, LEFT, FRONT, RIGHT, BACK, DOWN};
class Cube
{
	private:
		array<Color, 48> cube;
		array<Color, 6> centers;

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
        Cube& u();
		Cube& u2();
		Cube& uPrime();

		Cube& l();
		Cube& l2();
		Cube& lPrime();

		Cube& f();
		Cube& f2();
		Cube& fPrime();

		Cube& r();
		Cube& r2();
		Cube& rPrime();

		Cube& b();
		Cube& b2();
		Cube& bPrime();

		Cube& d();
		Cube& d2();
		Cube& dPrime();
};

#endif
