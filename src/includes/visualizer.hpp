/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   visualizer.hpp                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: tide-jon <tide-jon@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/07/28 17:44:59 by tide-jon      #+#    #+#                 */
/*   Updated: 2021/08/30 19:09:12 by tide-jon      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef VISUALIZER_H
# define VISUALIZER_H

#define GL_SILENCE_DEPRECATION

#include <SFML/OpenGL.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#ifdef _WIN64
	#include <GL/glu.h>
#elif __APPLE__
	#include <OpenGL/glu.h>
#endif
#include <cmath>
#include "cube.hpp"
#include "solver.hpp"

#define FONT_PATH "data/nebulosa_display_solid.otf"
#define	ICON_PATH "data/pngegg.png"
#define	MUSIC_PATH "data/Outrun.ogg"

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
		sf::RenderWindow window;
		array<sf::Text, 7>text;
		sf::Font font;
		sf::Music music;

		void perspectiveGL(GLdouble, GLdouble, GLdouble, GLdouble);
		void setColour(char);
		void rotateFace(float, float, float, FACE);
		int spiralToRows(int, int);
		void drawFace(Cube, FACE);
		void drawLines();
		void resetValues();
		string reverseMove(string);
        void renderCube();
        void handleEvent();
        void glSettings();
        void createWindow();
        void handleKeyPressed();
		void setText();
		void playMusic();

	public:
		Visualizer(Cube, vector<string>);
		void visualize();

};

#endif
