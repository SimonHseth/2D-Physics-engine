#include "PhysicsWorld.h"
#include <cmath>

PhysicsWorld::PhysicsWorld(Vector2D gravity, float width, float height)
    : gravity(gravity), worldWidth(width), worldHeight(height) {}

void PhysicsWorld::AddBody(RigidBody *body)
{
    bodies.push_back(body);
}

void PhysicsWorld::Step(float dt)
{
    // Apply forces and integrate motion
    if (!body->isKinematic)
    {
        body->ApplyForce(gravity * body->mass);
        body->Integrate(dt);
    }

    // Collision detection and resolution (circle vs. circle)
    for (size_t i = 0; i < bodies.size(); ++i)
    {
        for (size_t j = i + 1; j < bodies.size(); ++j)
        {
            RigidBody *A = bodies[i];
            RigidBody *B = bodies[j];

            if (A->shapeType == ShapeType::Circle && B->shapeType == ShapeType::Circle)
            {
                // existing circle-vs-circle code (leave unchanged)
                ...
            }
            else if (A->shapeType == ShapeType::Rectangle && B->shapeType == ShapeType::Rectangle)
            {
                Vector2D halfA = A->size * 0.5f;
                Vector2D halfB = B->size * 0.5f;

                Vector2D delta = B->position - A->position;
                float overlapX = halfA.x + halfB.x - std::abs(delta.x);
                float overlapY = halfA.y + halfB.y - std::abs(delta.y);

                if (overlapX > 0 && overlapY > 0)
                {
                    // Collision occurred
                    // Resolve using the smaller overlap axis
                    if (overlapX < overlapY)
                    {
                        float correction = overlapX * 0.5f * (delta.x < 0 ? -1.0f : 1.0f);
                        A->position.x -= correction;
                        B->position.x += correction;

                        float velA = A->velocity.x;
                        float velB = B->velocity.x;
                        A->velocity.x = velB;
                        B->velocity.x = velA;
                    }
                    else
                    {
                        float correction = overlapY * 0.5f * (delta.y < 0 ? -1.0f : 1.0f);
                        A->position.y -= correction;
                        B->position.y += correction;

                        float velA = A->velocity.y;
                        float velB = B->velocity.y;
                        A->velocity.y = velB;
                        B->velocity.y = velA;
                    }
                }
            }

            // Optionally handle Circle vs Rectangle later
        }
    }

    // Wall collisions
    for (auto body : bodies)
    {
        float left = -worldWidth / 2 + body->radius;
        float right = worldWidth / 2 - body->radius;
        float bottom = -worldHeight / 2 + body->radius;
        float top = worldHeight / 2 - body->radius;

        if (body->position.x < left)
        {
            body->position.x = left;
            body->velocity.x *= -1.0f;
        }
        else if (body->position.x > right)
        {
            body->position.x = right;
            body->velocity.x *= -1.0f;
        }

        if (body->position.y < bottom)
        {
            body->position.y = bottom;
            body->velocity.y *= -1.0f;
        }
        else if (body->position.y > top)
        {
            body->position.y = top;
            body->velocity.y *= -1.0f;
        }
    }
}
