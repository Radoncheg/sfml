// traffic light
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode({800, 600}), "title");

    window.clear();

    sf::RectangleShape shape1;
    shape1.setSize({800, 600});
    shape1.setFillColor(sf::Color(0xFF, 0xFF, 0xFF));
    window.draw(shape1);

    sf::RectangleShape lightBox;
    lightBox.setSize({160, 500});
    lightBox.setPosition({30, 50});
    lightBox.setFillColor(sf::Color(0x37, 0x37, 0x37));
    window.draw(lightBox);

    sf::CircleShape lightCircle1(70);
    lightCircle1.setPosition({40, 75});
    lightCircle1.setFillColor(sf::Color(0x00, 0x80, 0x00));
    window.draw(lightCircle1);

    sf::CircleShape lightCircle2(70);
    lightCircle2.setPosition({40, 230});
    lightCircle2.setFillColor(sf::Color(0xFF, 0xD7, 0x00));
    window.draw(lightCircle2);

    sf::CircleShape lightCircle3(70);
    lightCircle3.setPosition({40, 385});
    lightCircle3.setFillColor(sf::Color(0xFF, 0x00, 0x00));
    window.draw(lightCircle3);

    window.display();

    sf::sleep(sf::seconds(10));
}