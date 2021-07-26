// #define SFML_STATIC

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Main.hpp>

// clang++ sfml-test.cpp -I /Users/tide-jon/.brew/Cellar/sfml/2.5.1_1/include -L /Users/tide-jon/.brew/Cellar/sfml/2.5.1_1/lib/
// -lsfml-window -lsfml-graphics -lsfml-system -lsfml-audio -lsfml-network

int main()
{
    sf::RenderWindow window(
        sf::VideoMode(640, 480),
        "Hello World");
    sf::CircleShape shape(200);
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event))
            if (event.type == 
            sf::Event::Closed)
                window.close();
        window.clear();
        window.draw(shape);
        window.display();
    }
    return 0;
}