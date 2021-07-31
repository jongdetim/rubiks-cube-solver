/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   visualizer.hpp                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: tide-jon <tide-jon@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/07/28 17:44:59 by tide-jon      #+#    #+#                 */
/*   Updated: 2021/07/31 19:29:29 by tide-jon      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef VISUALIZER_H
# define VISUALIZER_H

#define GL_SILENCE_DEPRECATION

#include <SFML/OpenGL.hpp>
#include <SFML/Graphics.hpp>
#include <openGL/glu.h>
// #include <OpenGL/glu.h>
#include <cmath>
#include "cube.hpp"
#include "solver.hpp"

class Visualizer
{
	private:
		bool rotate;
		bool mousePressed;
		float angle;
		float paused_angle;
		float mouse_y;
		float mouse_x;
		float mouse_yd;
		float mouse_xd;
		float previous_mouse_y;
		float previous_mouse_x;
		float y_angle;
		float x_angle;
        bool running = true;
		Cube cube;
		vector<string> solution;
        sf::Event event;
        sf::Clock clock;
        vector<string>::iterator it;

		void perspectiveGL(GLdouble, GLdouble, GLdouble, GLdouble);
		void setColour(char);
		void rotateFace(float, float, float, FACE);
		int spiralToRows(int, int);
		void drawFace(Cube, FACE);
		void drawLines();
		void resetValues(sf::Clock*);
		string reverseMove(string);
        void renderCube();
        void handleEvent(sf::Window*);
        void glSettings();
        void createWindow(sf::Window*);
        void handleKeyPressed();

	public:
		Visualizer(Cube, vector<string>);
		void visualize();

};

#endif
