/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   visualizer.cpp                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: tide-jon <tide-jon@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/07/28 17:45:59 by tide-jon      #+#    #+#                 */
/*   Updated: 2021/07/31 19:29:06 by tide-jon      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.hpp"

// globals
float FOV = 90.f;
int X_SIZE = 1200;
int Y_SIZE = 900;
float MUSIC_VOLUME = 10.f;

Visualizer::Visualizer(Cube cube, vector<string> solution)
{
	this->cube = cube;
	this->solution = solution;
	this->it = std::begin(this->solution);
}

void Visualizer::perspectiveGL(GLdouble fovY, GLdouble aspect, GLdouble zNear, GLdouble zFar)
{
	const GLdouble pi = 3.1415926535897932384626433832795;
	GLdouble fW, fH;

	fH = std::tan(fovY / 360 * pi) * zNear;
	fW = fH * aspect;
	glFrustum(-fW, fW, -fH, fH, zNear, zFar);
}

void Visualizer::setColour(char colour)
{
	switch ((char)colour)
	{
	case 'Y':
		glColor3f(1, 1, 0);
		break;
	case 'B':
		glColor3f(0, 0, 1);
		break;
	case 'R':
		glColor3f(1, 0, 0);
		break;
	case 'G':
		glColor3f(0, 1, 0);
		break;
	case 'O':
		glColor3f(1.0f, 0.5f, 0.0f);
		break;
	case 'W':
		glColor3f(1, 1, 1);
		break;
	default:
		glColor3f(0, 0, 0);
		break;
	}
}

void Visualizer::rotateFace(float x, float y, float z, FACE face)
{
	float theta = 1.5707963268;
	switch (face)
	{
	case FACE::BACK:
		theta *= 2;
		glVertex3f(x * cos(theta) - z * sin(theta), y, x * sin(theta) + z * cos(theta));
		break;
	case FACE::FRONT:
		glVertex3f(x, y, z);
		break;
	case FACE::RIGHT:
		theta *= -1;
		glVertex3f(x * cos(theta) - z * sin(theta), y, x * sin(theta) + z * cos(theta));
		break;
	case FACE::LEFT:
		glVertex3f(x * cos(theta) - z * sin(theta), y, x * sin(theta) + z * cos(theta));
		break;
	case FACE::UP:
		theta *= -1;
		glVertex3f(x, y * cos(theta) - z * sin(theta), y * sin(theta) + z * cos(theta));
		break;
	case FACE::DOWN:
		glVertex3f(x, y * cos(theta) - z * sin(theta), y * sin(theta) + z * cos(theta));
		break;
	}
}

int Visualizer::spiralToRows(int i, int face)
{
	face *= 8;
	if (i == 3 + face)
		return 7 + face;
	if (i == 4 + face)
		return 3 + face;
	if (i == 5 + face)
		return 6 + face;
	if (i == 6 + face)
		return 5 + face;
	if (i == 7 + face)
		return 4 + face;
	return i;
}

void Visualizer::drawFace(Cube cube, FACE face)
{
	int j = 0;
	for (int i = 0; i < 9; i++)
	{
		if (i == 4)
			setColour(getColor((int)face));
		else
		{
			setColour(getColor((int)(cube.cube[spiralToRows((int)face * 8 + j, (int)face)])));
			j++;
		}
		rotateFace(100.f * (float((i % 3) + 1) / 3) - 50, 50 - (100.f * (float((i / 3) + 1) / 3)), 50.f, face);
		rotateFace(100.f * (float((i % 3) + 1) / 3) - 50, 50 - (100.f * (float(i / 3) / 3)), 50.f, face);
		rotateFace(100.f * (float(i % 3) / 3) - 50, 50 - (100.f * (float(i / 3) / 3)), 50.f, face);
		rotateFace(100.f * (float(i % 3) / 3) - 50, 50 - (100.f * (float((i / 3) + 1) / 3)), 50.f, face);
	}
}

void Visualizer::drawLines()
{
	setColour('X');

	for (int j = 0; j < 6; j++)
	{
		for (int i = 0; i < 4; i++)
		{
			rotateFace(-50.3, 50.3 - i * (100.6 / 3), 50.3, (FACE)j);
			rotateFace(50.3, 50.3 - i * (100.6 / 3), 50.3, (FACE)j);
		}
		for (int i = 0; i < 4; i++)
		{
			rotateFace(-50.3 + i * (100.6 / 3), 50.3, 50.3, (FACE)j);
			rotateFace(-50.3 + i * (100.6 / 3), -50.3, 50.3, (FACE)j);
		}
	}
}

void Visualizer::renderCube()
{
	glBegin(GL_QUADS);
	for (int i = 0; i < 6; i++)
		drawFace(cube, (FACE)i);
	glEnd();

	glBegin(GL_LINES);
	drawLines();
	glEnd();
}

void Visualizer::resetValues()
{
	rotate = true;
	mousePressed = false;
	angle = 0.0;
	paused_angle = 0.0;
	mouse_y = 0.0;
	mouse_x = 0.0;
	mouse_yd = 0.0;
	mouse_xd = 0.0;
	previous_mouse_y = 0.0;
	previous_mouse_x = 0.0;
	y_angle = 0.0;
	x_angle = 0.0;
	clock.restart();
}

string Visualizer::reverseMove(string move)
{
	move[1] = '4' - (move[1] - '0');
	return move;
}

void Visualizer::handleKeyPressed()
{
	switch (event.key.code)
	{
	case sf::Keyboard::Space:
		rotate = 1 - rotate;
		if (rotate == true)
			clock.restart();
		else
			paused_angle = angle;
		break;
	case sf::Keyboard::R:
		resetValues();
		break;
	case sf::Keyboard::Right:
		if (it != std::end(solution))
		{
			apply_moves_db(&cube, *it);
			it++;
		}
		break;
	case sf::Keyboard::Left:
		if (it != std::begin(solution))
		{
			it--;
			apply_moves_db(&cube, reverseMove(*it));
		}
		break;
	case sf::Keyboard::Escape:
		running = false;
		break;
	case sf::Keyboard::M:
		cout << music.Status::Playing << endl;
		if (sf::Music::Playing == music.getStatus())
			music.pause();
		else
			music.play();
		break;
	default:
		break;
	}
}

void Visualizer::handleEvent()
{
	while (window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::KeyPressed:
			handleKeyPressed();
			break;
		case sf::Event::MouseButtonPressed:
			mousePressed = true;
			previous_mouse_y = event.mouseButton.y;
			previous_mouse_x = event.mouseButton.x;
			break;
		case sf::Event::MouseButtonReleased:
			mousePressed = false;
			break;
		case sf::Event::MouseMoved:
			if (mousePressed)
			{
				mouse_y = event.mouseMove.y;
				mouse_x = event.mouseMove.x;
				mouse_yd = previous_mouse_y - mouse_y;
				mouse_xd = previous_mouse_x - mouse_x;
				y_angle -= mouse_yd;
				x_angle -= mouse_xd;
				previous_mouse_y = event.mouseMove.y;
				previous_mouse_x = event.mouseMove.x;
			}
			break;
		case sf::Event::Closed:
			running = false;
			break;
		case sf::Event::Resized:
			glViewport(0, 0, event.size.width, event.size.height);
			glLineWidth(((((float(window.getSize().x)) + (float(window.getSize().y))) / 2) - 70) / 250);
			break;
		default:
			break;
		}
	}
}

void Visualizer::glSettings()
{
	glClearDepth(1.f);
	glClearColor(0.f, 0.f, 0.f, 0.f);
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glLineWidth(((((float(X_SIZE)) + (float(Y_SIZE))) / 2) - 70) / 250);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	perspectiveGL(FOV, float(X_SIZE) / Y_SIZE, 1.f, 300.0f);
}

void Visualizer::createWindow()
{
	sf::ContextSettings settings;
	sf::Image icon;

	settings.depthBits = 24;
	settings.stencilBits = 8;
	settings.antialiasingLevel = 12;

	window.create(sf::VideoMode(X_SIZE, Y_SIZE), "Rubik", sf::Style::Default, settings);
	window.setVerticalSyncEnabled(true);

	icon.loadFromFile(ICON_PATH);
	window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
	window.setActive(true);
}

void Visualizer::setText()
{
	array<string, 7> controls;
	sf::FloatRect bounds;

	controls[0] =
		"Step through solution\n"
		"Toggle auto rotation\n"
		"Rotate cube\n"
		"Toggle music\n"
		"Reset camera\n"
		"Exit\n";
	controls[1] = "Arrow keys";
	controls[2] = "Space";
	controls[3] = "Drag mouse";
	controls[4] = "M";
	controls[5] = "R";
	controls[6] = "Esc";

	if (!font.loadFromFile(FONT_PATH))
	{
		cout << "error loading font!" << endl;
		exit(1);
	}
	for (int i = 0; i < 7; i++)
	{
		text[i].setFont(font);
		text[i].setCharacterSize(18);
		text[i].setString(controls[i]);
		if (i == 0)
			text[i].setPosition(10, Y_SIZE - 155);
		else
		{
			bounds = text[i].getLocalBounds();
			text[i].setPosition(500 - bounds.width, Y_SIZE - (155 - 25 * (i - 1)));
		}
	}
}

void Visualizer::playMusic()
{
	if (!music.openFromFile(MUSIC_PATH))
		return;
	music.setLoop(true);
	music.setVolume(MUSIC_VOLUME);
	music.play();
}

void Visualizer::visualize()
{
	// create window, initiate variables & prepare OpenGL settings and projection, text and audio
	createWindow();
	setText();
	resetValues();
	glSettings();
	playMusic();

	// run the main loop
	while (running)
	{
		handleEvent();

		// clear the buffers
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// set up camera pov
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glTranslatef(0.f, 0.f, -200.f);
		gluLookAt(0.5, 0.5, 0.5, 0, 0, 0, 0, 1.f, 0);

		if (rotate)
			angle = paused_angle + clock.getElapsedTime().asSeconds();

		// rotate cube from initial angle
		glRotatef(y_angle / 10, 1.f, 0.f, -1.f);
		glRotatef((x_angle / 10) + (angle * 30), 0.f, 1.f, 0.f);

		// draw the cube
		renderCube();
		window.pushGLStates();

		// draw text
		for (const auto& elem : text)
			window.draw(elem);
		window.popGLStates();

		window.display();
	}
}
