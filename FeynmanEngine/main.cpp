#include <SFML/Graphics.hpp>
#include "PhysicsWorld.h"

int main()
{
    sf::Vector2u windowSize(800, 600);
    sf::RenderWindow window(sf::VideoMode(windowSize, 32), "FeynmanEngine");
    window.setFramerateLimit(60);

    PhysicsWorld world(Vector2D(0, -9.8f), 8.0f, 6.0f);
    const float scale = 100.0f;
    const Vector2D offset(400, 300);

    // Create two circles
    RigidBody *ball1 = new RigidBody(Vector2D(-2.0f, 0), 0.5f, 1.0f, ShapeType::Circle);
    RigidBody *ball2 = new RigidBody(Vector2D(2.0f, 0), 0.5f, 1.0f, ShapeType::Circle);
    ball1->velocity = Vector2D(0.0f, 0.0f);
    ball2->velocity = Vector2D(0.0f, 0.0f);

    world.AddBody(ball1);
    world.AddBody(ball2);

    sf::CircleShape shape1(ball1->radius * scale);
    shape1.setFillColor(sf::Color::Red);
    shape1.setOrigin(sf::Vector2f(ball1->radius * scale, ball1->radius * scale));

    sf::CircleShape shape2(ball2->radius * scale);
    shape2.setFillColor(sf::Color::Blue);
    shape2.setOrigin(sf::Vector2f(ball2->radius * scale, ball2->radius * scale));

    RigidBody *selected = nullptr;

    while (window.isOpen())
    {
        while (const std::optional<sf::Event> event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();

            if (event->is<sf::Event::MouseButtonPressed>())
            {
                auto mp = sf::Mouse::getPosition(window);
                Vector2D mouseWorld((mp.x - offset.x) / scale, -(mp.y - offset.y) / scale);

                for (RigidBody *body : world.bodies)
                {
                    if (body->shapeType == ShapeType::Circle)
                    {
                        Vector2D toCenter = mouseWorld - body->position;
                        if (toCenter.Magnitude() < body->radius)
                        {
                            selected = body;
                            selected->isKinematic = true;
                            break;
                        }
                    }
                }
            }

            if (event->is<sf::Event::MouseButtonReleased>())
            {
                if (selected)
                {
                    selected->isKinematic = false;
                    selected = nullptr;
                }
            }
        }

        if (selected)
        {
            auto mp = sf::Mouse::getPosition(window);
            selected->position = Vector2D((mp.x - offset.x) / scale, -(mp.y - offset.y) / scale);
        }

        world.Step(0.016f);

        shape1.setPosition(sf::Vector2f(ball1->position.x * scale + offset.x,
                                        -ball1->position.y * scale + offset.y));

        shape2.setPosition(sf::Vector2f(ball2->position.x * scale + offset.x,
                                        -ball2->position.y * scale + offset.y));

        // Dynamic outline based on selection
        if (selected == ball1)
        {
            shape1.setOutlineColor(sf::Color::Green);
            shape1.setOutlineThickness(2.0f);
        }
        else
        {
            shape1.setOutlineColor(sf::Color::Transparent);
            shape1.setOutlineThickness(0.0f);
        }

        if (selected == ball2)
        {
            shape2.setOutlineColor(sf::Color::Green);
            shape2.setOutlineThickness(2.0f);
        }
        else
        {
            shape2.setOutlineColor(sf::Color::Transparent);
            shape2.setOutlineThickness(0.0f);
        }

        window.clear(sf::Color::Black);
        window.draw(shape1);
        window.draw(shape2);
        window.display();
    }

    return 0;
}
 