// OOY
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <cmath>

#define PI 3.1415926535898

int main()

{
    sf::RenderWindow window(sf::VideoMode({1200, 800}), "title");

    window.clear();
    //background
    sf::RectangleShape shape1;
    shape1.setSize({1200, 800});
    shape1.setFillColor(sf::Color(0xFF, 0xFF, 0xFF));
    window.draw(shape1);

    //letters O
    float radius_x1 = 150;
    float radius_y1 = 200;
    float radius_x2 = 130;
    float radius_y2 = 180;

    unsigned short quality = 70;

    sf::ConvexShape oEllipse1;
    sf::ConvexShape oEllipse2;
    sf::ConvexShape oEllipse3;
    sf::ConvexShape oEllipse4;

    oEllipse1.setPointCount(quality);
    oEllipse2.setPointCount(quality);
    oEllipse3.setPointCount(quality);
    oEllipse4.setPointCount(quality);

    for (unsigned short i = 0; i < quality; ++i)
    {
        float rad = (360 / quality * i) / (360 / PI / 2);
        float x1 = cos(rad) * radius_x1;
        float y1 = sin(rad) * radius_y1;
        float x2 = cos(rad) * radius_x2;
        float y2 = sin(rad) * radius_y2;

        oEllipse1.setPoint(i, sf::Vector2f(x1, y1));
        oEllipse2.setPoint(i, sf::Vector2f(x2, y2));
        oEllipse3.setPoint(i, sf::Vector2f(x1, y1));
        oEllipse4.setPoint(i, sf::Vector2f(x2, y2));
    };
    oEllipse1.setFillColor(sf::Color(0x00, 0x00, 0x00));
    oEllipse1.setPosition(170, 240);
    oEllipse2.setFillColor(sf::Color(0xFF, 0xFF, 0xFF));
    oEllipse2.setPosition(170, 240);
    oEllipse3.setFillColor(sf::Color(0x00, 0x00, 0x00));
    oEllipse3.setPosition(500, 240);
    oEllipse4.setFillColor(sf::Color(0xFF, 0xFF, 0xFF));
    oEllipse4.setPosition(500, 240);

    window.draw(oEllipse1);
    window.draw(oEllipse2);
    window.draw(oEllipse3);
    window.draw(oEllipse4);

    //letter Y

    sf::RectangleShape yBox1;
    yBox1.setSize({270, 20});
    yBox1.setRotation(60);
    yBox1.setPosition({690, 40});
    yBox1.setFillColor(sf::Color(0x0, 0x0, 0x0));
    window.draw(yBox1);

    sf::RectangleShape yBox2;
    yBox2.setSize({270, 20});
    yBox2.setRotation(120);
    yBox2.setPosition({959, 40});
    yBox2.setFillColor(sf::Color(0x0, 0x0, 0x0));
    window.draw(yBox2);

    sf::RectangleShape yBox3;
    yBox3.setSize({190, 20});
    yBox3.setRotation(90);
    yBox3.setPosition({823, 250});
    yBox3.setFillColor(sf::Color(0x0, 0x0, 0x0));
    window.draw(yBox3);

    window.display();

    sf::sleep(sf::seconds(10));
}