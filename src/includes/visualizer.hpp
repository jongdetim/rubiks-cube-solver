/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   visualizer.hpp                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: tide-jon <tide-jon@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/07/28 17:44:59 by tide-jon      #+#    #+#                 */
/*   Updated: 2021/07/28 19:33:55 by tide-jon      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef VISUALIZER_H
# define VISUALIZER_H

#define GL_SILENCE_DEPRECATION

#include <SFML/OpenGL.hpp>
#include <SFML/Graphics.hpp>
#include <GL/glu.h>
// #include <OpenGL/glu.h>
#include <cmath>
#include "cube.hpp"
#include "solver.hpp"

void perspectiveGL(GLdouble fovY, GLdouble aspect, GLdouble zNear, GLdouble zFar);
// veranderen in macros / defines
void setColour(char colour);
void rotateFace(float x, float y, float z, char face);
void drawFace(Cube cube, char face);
void drawLines();
void reset_values(sf::Clock *clock);
int visualizer(Cube cube, vector<string> solution);

#endif
