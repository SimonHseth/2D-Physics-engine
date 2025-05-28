#include <SFML/Graphics.hpp>
#include "PhysicsWorld.h"

int main()
{
    sf::Vector2u windowSize(800, 600);
    sf::RenderWindow window(sf::VideoMode(windowSize, 32), "FeynmanEngine");
    window.setFramerateLimit(60);

    PhysicsWorld world(Vector2D(0, 0));
    const float scale = 100.0f;
    const Vector2D offset(400, 300);

    RigidBody ball1(Vector2D(-2.0f, 0), 1.0f, 1.0f);
    RigidBody ball2(Vector2D(2.0f, 0), 1.0f, 1.0f);
    ball1.velocity = Vector2D(1.5f, 0);
    ball2.velocity = Vector2D(-1.5f, 0);
    world.AddBody(&ball1);
    world.AddBody(&ball2);

    sf::CircleShape shape1(ball1.radius * scale);
    shape1.setFillColor(sf::Color::Red);
    shape1.setOrigin(sf::Vector2f(ball1.radius * scale, ball1.radius * scale));

    sf::CircleShape shape2(ball2.radius * scale);
    shape2.setFillColor(sf::Color::Blue);
    shape2.setOrigin(sf::Vector2f(ball2.radius * scale, ball2.radius * scale));

    while (window.isOpen())
    {
        for (const sf::Event &event : window.pollEvents())
        {
            if (event.getType() == sf::Event::Closed)
                window.close();
        }

        world.Step(0.016f);

        shape1.setPosition(sf::Vector2f(ball1.position.x * scale + offset.x,
                                        -ball1.position.y * scale + offset.y));
        shape2.setPosition(sf::Vector2f(ball2.position.x * scale + offset.x,
                                        -ball2.position.y * scale + offset.y));

        window.clear(sf::Color::Black);
        window.draw(shape1);
        window.draw(shape2);
        window.display();
    }

    return 0;
}
