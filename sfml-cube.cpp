#define GL_SILENCE_DEPRECATION

#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <OpenGL/glext.h>
#include <GLUT/glut.h>
#include <cmath>
#include <iostream>

// clang++ sfml-cube.cpp -I /Users/tide-jon/.brew/Cellar/sfml/2.5.1_1/include -L /Users/tide-jon/.brew/Cellar/sfml/2.5.1_1/lib/ -lsfml-window -lsfml-graphics -lsfml-system -lsfml-audio -lsfml-network -framework OpenGL -framework GLUT

void perspectiveGL( GLdouble fovY, GLdouble aspect, GLdouble zNear, GLdouble zFar )
{
    const GLdouble pi = 3.1415926535897932384626433832795;
    GLdouble fW, fH;

    //fH = tan( (fovY / 2) / 180 * pi ) * zNear;
    fH = std::tan( fovY / 360 * pi ) * zNear;
    fW = fH * aspect;

    glFrustum( -fW, fW, -fH, fH, zNear, zFar );
}

void setColour(char colour)
{
    switch ((char)colour)
    {
        case 'Y':
            glColor3f(1,1,0);
            break ;
        case 'B':
            glColor3f(0, 0, 1);
            break ;
        case 'R':
            glColor3f(1,0,0);
            break;
        case 'G':
            glColor3f(0,1,0);
            break;
        case 'O':
            glColor3f(1.0f, 0.5f, 0.0f);
            break;
        case 'W':
            glColor3f(1,1,1);
            break;
        default:
            glColor3f(0,1,1);
            break ;
    }
}

void rotateFace(double x, double y, double z, char face)
{
    double theta = 1.5707963268;
    switch (face)
    {
        case 'B':
            theta *= 2;
            glVertex3f(x*cos(theta) - z*sin(theta), y, x*sin(theta) + z*cos(theta));
            break ;
        case 'F':
            glVertex3f(x, y, z);
            break ;
        case 'R':
            theta *= -1;
            glVertex3f(x*cos(theta) - z*sin(theta), y, x*sin(theta) + z*cos(theta));
            break ;
        case 'L':
            glVertex3f(x*cos(theta) - z*sin(theta), y, x*sin(theta) + z*cos(theta));
            break ;
        case 'U':
            glVertex3f(x, y*cos(theta) - z*sin(theta), y*sin(theta) + z*cos(theta));
            break ;
        case 'D':
            theta *= -1;
            glVertex3f(x, y*cos(theta) - z*sin(theta), y*sin(theta) + z*cos(theta));
            break ;



    }
}

void drawFace(std::string stickers, char face)
{
    for (int i = 0; i < 9; i++)
    {
        // setColour(stickers[i]);
        // rotateFace( 100 * ((i % 3) / 3) - 50, 50 - (100 * ((i / 3) / 3)), 50.f, face);
        // rotateFace( 100 * ((i % 3) / 3) - 50, 50 - (100 * (((i / 3) + 1) / 3)), 50.f, face);
        // rotateFace( 100 * (((i % 3) + 1) / 3) - 50, 50 - (100 * (((i / 3) + 1) / 3)), 50.f, face);
        // rotateFace( 100 * (((i % 3) + 1) / 3) - 50, 50 - (100 * ((i / 3) / 3)), 50.f, face);

        setColour(stickers[i]);
        rotateFace( 100.f * (float((i % 3) + 1) / 3) - 50, 50 - (100.f * (float((i / 3) + 1) / 3)), 50.f, face);
        rotateFace( 100.f * (float((i % 3) + 1) / 3) - 50, 50 - (100.f * (float(i / 3) / 3)), 50.f, face);
        rotateFace( 100.f * (float(i % 3) / 3) - 50, 50 - (100.f * (float(i / 3) / 3)), 50.f, face);
        rotateFace( 100.f * (float(i % 3) / 3) - 50, 50 - (100.f * (float((i / 3) + 1) / 3)), 50.f, face);
        // exit(1);
    }
}

int main()
{
    // create the window
    sf::Window window(sf::VideoMode(800, 600), "Rubik", sf::Style::Default, sf::ContextSettings(32));
    window.setVerticalSyncEnabled(true);

    // activate the window
    window.setActive(true);

    // Create a clock for measuring time elapsed
    sf::Clock Clock;

    bool rotate=true;
    bool initial=true;
	float angle;

        //prepare OpenGL surface for HSR
	glClearDepth(1.f);
    glClearColor(0.f, 0.f, 0.f, 0.f);
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);

    // sf::View view1(sf::FloatRect(200.f, 200.f, 300.f, 200.f));
    // sf::View view1;
    // view1.reset(sf::FloatRect(0, 0, 800, 600));
    // view1.setRotation(10.f);
    //// Setup a perspective projection & Camera position
    glMatrixMode(GL_PROJECTION);
    // glLoadMatrixf(view1.getTransform().getMatrix());
    // std::cout << *(view1.getTransform().getMatrix()) << std::endl;
    // glLoadIdentity();
    // perspectiveGL(90.f, 1.f, 200.f, 300.0f);//fov, aspect, zNear, zFar
    // glLoadMatrixf(view1.getTransform().getMatrix());
    glLoadIdentity();
    perspectiveGL(90.f, 1.f, 1.f, 300.0f);//fov, aspect, zNear, zFar
    // glLoadMatrixf(view1.getTransform().getMatrix());
        // glLoadIdentity();



    // load resources, initialize the OpenGL states, ...

    // run the main loop
    bool running = true;
    while (running)
    {
        // handle events
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch(event.type)
            {
                case sf::Event::KeyPressed:
                    if(event.key.code != sf::Keyboard::Escape) { break; }
                case sf::Event::Closed:
                    running = false;
                    break;
                case sf::Event::Resized:
                    glViewport(0, 0, event.size.width, event.size.height);
                default:
                    break;
            }
        }

        // clear the buffers
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Apply some transformations for the cube
            // glLoadMatrixf(view1.getTransform().getMatrix());
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glTranslatef(0.f, 0.f, -200.f);
        gluLookAt(1,1,0, 0,0,1, 0,1.f,0);


		if(rotate)
			angle=Clock.getElapsedTime().asSeconds();
		// glRotatef(angle * 30, 1.f, 0.f, 0.f);
		glRotatef(angle * 30, 0.f, 1.f, 0.f);
            // glRotatef(20.f, 1.f, 0.f, 0.f);

        // draw...
        glBegin(GL_QUADS);//draw some squares
            // for (int i = 0; i < 9; i++)
            // {
            //     glColor3f(0,1,1); //cyan
            //     glVertex3f( 50/3, 50.f, -50.f);
            //     glVertex3f( 50/3,  50/3, -50.f);
            //     glVertex3f( 50.f, 50/3, -50.f);
            //     glVertex3f( 50.f,  50.f, -50.f);
            // }

            std::string stickers = "YORBGWYOR";
            drawFace(stickers, 'F');

            // glColor3f(0,0,1); //blue
            // glVertex3f( 50.f, -50.f, 50.f);
            // glVertex3f( 50.f,  50.f, 50.f);
            // glVertex3f(-50.f,  50.f, 50.f);
            // glVertex3f(-50.f, -50.f, 50.f);
            stickers = "CBBBCCCBC";
            drawFace(stickers, 'B');

            stickers = "RRRRRRRRR";
            drawFace(stickers, 'R');

            stickers = "WWWWWWWWW";
            drawFace(stickers, 'U');

            stickers = "YYYYYYYYY";
            drawFace(stickers, 'D');

            stickers = "OOOOOOOOO";
            drawFace(stickers, 'L');


        glEnd();

        // end the current frame (internally swaps the front and back buffers)
        window.display();
    }

    // release resources...

    return 0;
}