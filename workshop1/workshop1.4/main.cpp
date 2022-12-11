#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <cmath>

struct Cat
{
    sf::Texture texture;
    sf::Sprite sprite;
    sf::Vector2f scale;
    sf::Vector2f position;
};

struct Laser
{
    sf::Texture texture;
    sf::Sprite sprite;
    sf::Vector2f scale;
    sf::Vector2f position;
};

void initCat(Cat &cat)
{
    cat.texture.loadFromFile("cat.png");
    cat.sprite.setTexture(cat.texture);
    cat.sprite.setPosition(1500, 1000);
    cat.sprite.setOrigin({15, 15});
    cat.sprite.setScale(3, 3);
}

void initLaser(Laser &laser)
{
    laser.texture.loadFromFile("laser.png");
    laser.sprite.setTexture(laser.texture);
    laser.sprite.setOrigin({15, 15});
}

int main()
{
    constexpr unsigned WINDOW_WIDTH = 3000;
    constexpr unsigned WINDOW_HEIGHT = 2000;

    sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Play with little pussy");

    Cat cat;
    Laser laser;
    sf::Vector2i mousePosition;
    sf::Vector2f newPosition;
    bool isLaserVisible = false;
    bool isRealyTime = false;
    sf::Clock clock;
    float time;

    initCat(cat);
    initLaser(laser);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::MouseButtonPressed:
                mousePosition = sf::Mouse::getPosition(window);
                laser.sprite.setPosition(sf::Vector2f(mousePosition));
                isLaserVisible = true;
                if (not isRealyTime)
                {
                    time = clock.restart().asSeconds();
                    isRealyTime = true;
                }
                break;
            default:
                break;
            }
        }
        window.clear(sf::Color(255, 255, 255));
        window.draw(cat.sprite);
        if ((isLaserVisible) && (isRealyTime))
        {
            sf::Vector2f deltaVector = laser.sprite.getPosition() - cat.sprite.getPosition();
            time = clock.restart().asSeconds();
            const float maxSpeedCat = 1;
            sf::Vector2f maxStepCat = time * maxSpeedCat * deltaVector;

            if (std::hypotf(deltaVector.x, deltaVector.y) > std::hypotf(maxStepCat.x, maxStepCat.y))
            {
                newPosition = cat.sprite.getPosition() + maxStepCat;
                cat.sprite.setPosition(newPosition);
                deltaVector = deltaVector - maxStepCat;
            }
            else if (std::hypotf(deltaVector.x, deltaVector.y) < std::hypotf(maxStepCat.x, maxStepCat.y))
            {
                newPosition = laser.sprite.getPosition();
                cat.sprite.setPosition(newPosition);
            }

            if (maxStepCat.x > 0)
            {
                cat.sprite.setScale(3, 3);
            }
            else
            {
                cat.sprite.setScale(-3, 3);
            }
            window.draw(laser.sprite);
        }
        window.display();
    }
}