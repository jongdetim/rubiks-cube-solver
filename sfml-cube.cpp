#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/graphics.hpp>
#include <SFML/system.hpp>
#include <cmath>
#include <iostream>

void perspectiveGL( GLdouble fovY, GLdouble aspect, GLdouble zNear, GLdouble zFar )
{
    const GLdouble pi = 3.1415926535897932384626433832795;
    GLdouble fW, fH;

    //fH = tan( (fovY / 2) / 180 * pi ) * zNear;
    fH = std::tan( fovY / 360 * pi ) * zNear;
    fW = fH * aspect;

    glFrustum( -fW, fW, -fH, fH, zNear, zFar );
}

int main()
{
    // create the window
    sf::Window window(sf::VideoMode(800, 600), "OpenGL", sf::Style::Default, sf::ContextSettings(32));
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
    glClearColor(0.3f, 0.3f, 0.3f, 0.f);
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);

    // sf::View view1(sf::FloatRect(200.f, 200.f, 300.f, 200.f));
    sf::View view1;
    view1.reset(sf::FloatRect(0, 0, 800, 600));
    // view1.setRotation(10.f);
    //// Setup a perspective projection & Camera position
    glMatrixMode(GL_PROJECTION);
    glLoadMatrixf(view1.getTransform().getMatrix());
    // std::cout << *(view1.getTransform().getMatrix()) << std::endl;
    glLoadIdentity();
    perspectiveGL(90.f, 1.f, 100.f, 300.0f);//fov, aspect, zNear, zFar
    // glLoadMatrixf(view1.getTransform().getMatrix());


    // load resources, initialize the OpenGL states, ...

    // run the main loop
    bool running = true;
    while (running)
    {
        // handle events
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                // end the program
                running = false;
            }
            else if (event.type == sf::Event::Resized)
            {
                // adjust the viewport when the window is resized
                glViewport(0, 0, event.size.width, event.size.height);
            }
        }

        // clear the buffers
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Apply some transformations for the cube
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glTranslatef(0.f, 0.f, -200.f);
		
		if(rotate)
			angle=Clock.getElapsedTime().asSeconds();
		// glRotatef(angle * 30, 1.f, 0.f, 0.f);
		glRotatef(angle * 30, 0.f, 1.f, 0.f);
            // glRotatef(20.f, 1.f, 0.f, 0.f);

        // draw...
        glBegin(GL_QUADS);//draw some squares
            glColor3f(0,1,1); //cyan
            glVertex3f(-50.f, -50.f, -50.f);
            glVertex3f(-50.f,  50.f, -50.f);
            glVertex3f( 50.f,  50.f, -50.f);
            glVertex3f( 50.f, -50.f, -50.f);

            glColor3f(0,0,1); //blue
            glVertex3f( 50.f, -50.f, 50.f);
            glVertex3f( 50.f,  50.f, 50.f);
            glVertex3f(-50.f,  50.f, 50.f);
            glVertex3f(-50.f, -50.f, 50.f);

            glColor3f(1,0,1); //magenta
            glVertex3f(-50.f, -50.f,  50.f);
            glVertex3f(-50.f,  50.f,  50.f);
            glVertex3f(-50.f,  50.f, -50.f);
            glVertex3f(-50.f, -50.f, -50.f);

            glColor3f(0,1,0); //green
            glVertex3f(50.f, -50.f, -50.f);
            glVertex3f(50.f,  50.f, -50.f);
            glVertex3f(50.f,  50.f,  50.f);
            glVertex3f(50.f, -50.f,  50.f);

            glColor3f(1,1,0); //yellow
            glVertex3f(-50.f, -50.f,  50.f);
            glVertex3f(-50.f, -50.f, -50.f);
            glVertex3f( 50.f, -50.f, -50.f);
            glVertex3f( 50.f, -50.f,  50.f);

            glColor3f(1,0,0); //red
            glVertex3f( 50.f, 50.f,  50.f);
            glVertex3f( 50.f, 50.f, -50.f);
            glVertex3f(-50.f, 50.f, -50.f);
            glVertex3f(-50.f, 50.f,  50.f);
        glEnd();

        // end the current frame (internally swaps the front and back buffers)
        window.display();
    }

    // release resources...

    return 0;
}