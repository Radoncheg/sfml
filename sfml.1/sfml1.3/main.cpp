// home homework
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

int main()
{
    sf::RectangleShape background;
    background.setSize({800, 600});
    background.setFillColor(sf::Color(0xFF, 0xFF, 0xFF));

    sf::RectangleShape homeBox;
    homeBox.setSize({500, 250});
    homeBox.setPosition({150, 350});
    homeBox.setFillColor(sf::Color(77, 46, 11));

    sf::RectangleShape homeDoor;
    homeDoor.setSize({80, 150});
    homeDoor.setPosition({200, 450});
    homeDoor.setFillColor(sf::Color(24, 23, 23));

    sf::ConvexShape homeRoof;
    homeRoof.setFillColor(sf::Color(93, 30, 23));
    homeRoof.setPosition(280, 240);
    homeRoof.setPointCount(4);
    homeRoof.setPoint(0, {0, 0});
    homeRoof.setPoint(1, {+240, 0});
    homeRoof.setPoint(2, {+420, 110});
    homeRoof.setPoint(3, {-180, 110});

    sf::RectangleShape homePipe1;
    homePipe1.setSize({44, 60});
    homePipe1.setPosition({460, 230});
    homePipe1.setFillColor(sf::Color(59, 56, 56));

    sf::RectangleShape homePipe2;
    homePipe2.setSize({64, 40});
    homePipe2.setPosition({450, 190});
    homePipe2.setFillColor(sf::Color(59, 56, 56));

    sf::CircleShape smoke1(20);
    smoke1.setPosition({473, 160});
    smoke1.setFillColor(sf::Color(191, 191, 191));

    sf::CircleShape smoke2(23);
    smoke2.setPosition({480, 125});
    smoke2.setFillColor(sf::Color(191, 191, 191));

    sf::CircleShape smoke3(26);
    smoke3.setPosition({490, 90});
    smoke3.setFillColor(sf::Color(191, 191, 191));

    sf::CircleShape smoke4(29);
    smoke4.setPosition({497, 55});
    smoke4.setFillColor(sf::Color(191, 191, 191));

    sf::RenderWindow window(sf::VideoMode({800, 600}), "Convex Shapes");
    window.clear();
    window.draw(background);
    window.draw(homeBox);
    window.draw(homeDoor);
    window.draw(homeRoof);
    window.draw(homePipe1);
    window.draw(smoke1);
    window.draw(smoke2);
    window.draw(smoke3);
    window.draw(smoke4);
    window.draw(homePipe2);
    window.display();

    sf::sleep(sf::seconds(10));
}