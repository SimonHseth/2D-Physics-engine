
#include <SFML/Graphics.hpp>
#include <imgui.h>
#include <imgui-SFML.h>
#include "ShapeType.h"

#include "PhysicsWorld.h"

// Note: requires ImGui-SFML built for SFML 3.0 (ProcessEvent/Update/Render signatures below)

int main()
{
    // --- Window ---
    sf::Vector2u windowSize(800, 600);
    sf::RenderWindow window(sf::VideoMode(windowSize, 32), "FeynmanEngine + ImGui");
    window.setFramerateLimit(120);

    // --- World / units ---
    const float scale = 100.0f;                         // 1 world unit = 100 pixels
    const Vector2D offset(400, 300);                    // screen center in pixels
    PhysicsWorld world(Vector2D(0, -9.8f), 8.0f, 6.0f); // width/height in world units

    // --- Bodies (2 circles you can drag) ---
    RigidBody *ball1 = new RigidBody(Vector2D(-2.0f, 0.5f), 0.5f, 1.0f, ShapeType::Circle);
    RigidBody *ball2 = new RigidBody(Vector2D(2.0f, 1.0f), 0.5f, 1.0f, ShapeType::Circle);
    world.AddBody(ball1);
    world.AddBody(ball2);

    sf::CircleShape shape1(ball1->radius * scale);
    shape1.setFillColor(sf::Color::Red);
    shape1.setOrigin(sf::Vector2f(ball1->radius * scale, ball1->radius * scale));

    sf::CircleShape shape2(ball2->radius * scale);
    shape2.setFillColor(sf::Color::Blue);
    shape2.setOrigin(sf::Vector2f(ball2->radius * scale, ball2->radius * scale));

    // --- ImGui init ---
    ImGui::SFML::Init(window);
    sf::Clock deltaClock;

    // --- UI state ---
    bool paused = false;
    float gravityY = world.gravity.y; // will bind to slider
    float mass1 = ball1->mass;
    float mass2 = ball2->mass;

    // --- Dragging state ---
    RigidBody *selected = nullptr;
    

    while (window.isOpen())
    {
        // --- Events ---
        while (const std::optional<sf::Event> event = window.pollEvent())
        {
            // ImGui gets first dibs on all events
            (void)ImGui::SFML::ProcessEvent(window, *event);

            if (event->is<sf::Event::Closed>())
                window.close();

            // If UI wants the mouse, skip our picking logic
            if (ImGui::GetIO().WantCaptureMouse)
                continue;

            if (event->is<sf::Event::MouseButtonPressed>())
            {
                auto mp = sf::Mouse::getPosition(window);
                Vector2D mouseWorld((mp.x - offset.x) / scale, -(mp.y - offset.y) / scale);

                for (RigidBody *body : world.bodies)
                {
                    if (body->shapeType == ShapeType::Circle)
                    {
                        Vector2D toCenter = mouseWorld - body->position;
                        if (toCenter.Magnitude() <= body->radius)
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

        // --- ImGui per-frame update ---
        sf::Time dt = deltaClock.restart();
        ImGui::SFML::Update(window, dt);

        // --- UI: Simulation Controls ---
        ImGui::Begin("Simulation Controls");
        if (ImGui::Checkbox("Paused", &paused))
        {
            // no-op; just toggles pause
        }
        if (ImGui::SliderFloat("Gravity Y", &gravityY, -25.0f, 25.0f, "%.2f m/s^2"))
        {
            world.gravity.y = gravityY;
        }
        if (ImGui::SliderFloat("Ball 1 Mass", &mass1, 0.1f, 10.0f, "%.2f kg"))
        {
            ball1->mass = mass1;
            ball1->invMass = (mass1 > 0.f) ? 1.0f / mass1 : 0.0f;
        }
        if (ImGui::SliderFloat("Ball 2 Mass", &mass2, 0.1f, 10.0f, "%.2f kg"))
        {
            ball2->mass = mass2;
            ball2->invMass = (mass2 > 0.f) ? 1.0f / mass2 : 0.0f;
        }
        ImGui::Text("Tip: Drag circles with the mouse.\nImGui grabs the mouse when hovering this window.");
        ImGui::End();

        // --- Dragging follow (only if UI isn't capturing the mouse) ---
        if (selected && !ImGui::GetIO().WantCaptureMouse)
        {
            auto mp = sf::Mouse::getPosition(window);
            selected->position = Vector2D((mp.x - offset.x) / scale, -(mp.y - offset.y) / scale);
            selected->velocity = Vector2D(0, 0);
        }

        // --- Physics step ---
        if (!paused)
        {
            world.Step(0.016f); // ~60 FPS step
        }

        // --- Sync SFML shapes with physics ---
        shape1.setPosition(sf::Vector2f(
            ball1->position.x * scale + offset.x,
            -ball1->position.y * scale + offset.y));
        shape2.setPosition(sf::Vector2f(
            ball2->position.x * scale + offset.x,
            -ball2->position.y * scale + offset.y));

        // Selection outline
        if (selected == ball1)
        {
            shape1.setOutlineColor(sf::Color::Green);
            shape1.setOutlineThickness(2.f);
        }
        else
        {
            shape1.setOutlineColor(sf::Color::Transparent);
            shape1.setOutlineThickness(0.f);
        }
        if (selected == ball2)
        {
            shape2.setOutlineColor(sf::Color::Green);
            shape2.setOutlineThickness(2.f);
        }
        else
        {
            shape2.setOutlineColor(sf::Color::Transparent);
            shape2.setOutlineThickness(0.f);
        }

        // --- Render ---
        window.clear(sf::Color::Black);
        window.draw(shape1);
        window.draw(shape2);

        // ImGui draw last
        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();
    return 0;
}
