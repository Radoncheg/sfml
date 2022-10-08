#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <cmath>

constexpr unsigned WINDOW_WIDTH = 800;
constexpr unsigned WINDOW_HEIGHT = 600;

int main()
{
    constexpr float BALL_SIZE = 40;

    constexpr float amplitudeY = 80.f;
    constexpr float periodY = 2;
    float timeY = 0;

    sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Wave Moving Ball");
    sf::Clock clock;

    sf::CircleShape ball(BALL_SIZE);
    ball.setFillColor(sf::Color(0xFF, 0xFF, 0xFF));

    sf::Vector2f position = {10, 350};
    float speedX = 100.f;
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

        if ((position.x + 2 * BALL_SIZE >= WINDOW_WIDTH) && (speedX > 0))
        {
            speedX = -speedX;
        }
        if ((position.x < 0) && (speedX < 0))
        {
            speedX = -speedX;
        }

        const float dt = clock.restart().asSeconds();
        position.x += speedX * dt;

        timeY += dt;

        const float wavePhase = timeY * float(2 * M_PI);
        const float y = amplitudeY * std::sin(wavePhase / periodY);
        const sf::Vector2f offset = {0, y};

        ball.setPosition(position + offset);

        window.clear();
        window.draw(ball);
        window.display();
    }
}