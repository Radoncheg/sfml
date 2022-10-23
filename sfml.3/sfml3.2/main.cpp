#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

// структура глаза
// самого глаза shape
// глазного яблока shape
// позиция глазного яблока Vector2f
// поворот глаза int
struct Eye
{
    sf::ConvexShape eye;
    sf::ConvexShape apple;
    sf::Vector2f position;
    float rotation = 0;
};

// из 04 задания
sf::Vector2f toEuclidean(float radiusX, float radiusY, float angle)
{
    return {
        radiusX * cos(angle),
        radiusY * sin(angle)};
}

// обновляем позиция глаза
void updateEyeElements(Eye &Eye)
{
    Eye.eye.setPosition(Eye.position);
    const sf::Vector2f apple0ffset = toEuclidean(25, 55, Eye.rotation);
    Eye.apple.setPosition(Eye.position + apple0ffset);
}

//  рисуем глаз
void initdrawEye(Eye &Eye)
{
    const sf::Vector2f eyeRadius = {40.f, 80.f};
    const int pointCount = 100;

    Eye.eye.setFillColor(sf::Color(0xFF, 0xFF, 0xFF));
    Eye.eye.setPointCount(pointCount);
    for (int pointI = 0; pointI < pointCount; ++pointI)
    {
        float angle = float(2 * M_PI * pointI) / float(pointCount);
        sf::Vector2f point = {
            eyeRadius.x * std::sin(angle),
            eyeRadius.y * std::cos(angle)};
        Eye.eye.setPoint(pointI, point);
    }
}

//рисуем глазное яблоко
void initdrawApple(Eye &Eye)
{
    const sf::Vector2f appleRadius = {10.f, 20.f};
    const int pointCount = 100;
    Eye.apple.setFillColor(sf::Color(0, 0, 0));
    Eye.apple.setPointCount(pointCount);
    for (int pointI = 0; pointI < pointCount; ++pointI)
    {
        float angle = float(2 * M_PI * pointI) / float(pointCount);
        sf::Vector2f point = {
            appleRadius.x * std::sin(angle),
            appleRadius.y * std::cos(angle)};
        Eye.apple.setPoint(pointI, point);
    }
}

// инициализируем глаза
void initEyes(Eye &EyeLeft, Eye &EyeRight)
{
    EyeLeft.position = {350, 300};
    EyeRight.position = {450, 300};

    initdrawEye(EyeLeft);
    initdrawEye(EyeRight);

    initdrawApple(EyeLeft);
    initdrawApple(EyeRight);

    updateEyeElements(EyeLeft);
    updateEyeElements(EyeRight);
}

// из 04 задания
void onMouseMove(const sf::Event::MouseMoveEvent &event, sf::Vector2f &mousePosition)
{
    std::cout << "mouse x=" << event.x << " mouse y=" << event.y << std::endl;
    mousePosition = {float(event.x), float(event.y)};
}

// из 04 задания
void pollEvents(sf::RenderWindow &window, sf::Vector2f &mousePosition)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            window.close();
            break;
        case sf::Event::MouseMoved:
            onMouseMove(event.mouseMove, mousePosition);
            break;
        default:
            break;
        }
    }
}

// обновляем кадр и вызываем функции обновления глаз
void update(const sf::Vector2f &mousePosition, Eye &EyeLeft, Eye &EyeRight)
{
    const sf::Vector2f delta1 = mousePosition - EyeLeft.position;
    EyeLeft.rotation = atan2(delta1.y, delta1.x);
    updateEyeElements(EyeLeft);

    const sf::Vector2f delta2 = mousePosition - EyeRight.position;
    EyeRight.rotation = atan2(delta2.y, delta2.x);
    updateEyeElements(EyeRight);
}

void drawEye(sf::RenderWindow &window, Eye &Eye)
{
    window.draw(Eye.eye);
    window.draw(Eye.apple);
}

// перерисовываем кадр
void redrawFrame(sf::RenderWindow &window, Eye &EyeLeft, Eye &EyeRight)
{
    window.clear();
    drawEye(window, EyeLeft);
    drawEye(window, EyeRight);
    window.display();
}

int main()
{
    constexpr unsigned WINDOW_WIDTH = 800;
    constexpr unsigned WINDOW_HEIGHT = 600;

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(
        sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}),
        "Eyes follow the cursor", sf::Style::Default, settings);

    Eye EyeLeft;
    Eye EyeRight;
    initEyes(EyeLeft, EyeRight);
    sf::Vector2f mousePosition;

    while (window.isOpen())
    {
        pollEvents(window, mousePosition);
        update(mousePosition, EyeLeft, EyeRight);
        redrawFrame(window, EyeLeft, EyeRight);
    }
}