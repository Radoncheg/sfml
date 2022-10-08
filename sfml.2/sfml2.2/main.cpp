#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cmath>

int main()
{
    constexpr int pointCount = 200;
    constexpr float period = 3;
    constexpr float rotationLength = 100;
    sf::Vector2f position({400, 300});
    sf::Clock clock;

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(
        sf::VideoMode({800, 600}), "shapeRose",
        sf::Style::Default, settings);

    sf::ConvexShape shapeRose;
    shapeRose.setPosition({position});
    shapeRose.setFillColor(sf::Color(220, 111, 91));
    shapeRose.setPointCount(pointCount);

    for (int pointNo = 0; pointNo < pointCount; ++pointNo)
    {
        float angle = float(2 * M_PI * pointNo) / float(pointCount);
        const float roseRadius = 200 * sin(6 * angle);

        sf::Vector2f point = sf::Vector2f{
            roseRadius * std::sin(angle),
            roseRadius * std::cos(angle)};
        shapeRose.setPoint(pointNo, point);
    }

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        const float time = clock.getElapsedTime().asSeconds();
        const float wavePhase = time * float(2 * M_PI);

        float x = rotationLength * std::cos(wavePhase / period);
        float y = rotationLength * std::sin(wavePhase / period);
        const sf::Vector2f offset = {x, y};

        shapeRose.setPosition(position + offset);

        window.clear();
        window.draw(shapeRose);
        window.display();
    }
}