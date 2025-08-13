#include "PhysicsWorld.h"
#include "ShapeType.h"
#include <cmath>

PhysicsWorld::PhysicsWorld(Vector2D gravity, float width, float height)
    : gravity(gravity), worldWidth(width), worldHeight(height) {}

void PhysicsWorld::AddBody(RigidBody *body)
{
    bodies.push_back(body);
}

void PhysicsWorld::Step(float dt)
{
    // Forces + integrate
    for (auto *body : bodies)
    {
        if (!body->isKinematic)
        {
            body->ApplyForce(gravity * body->mass);
        }
        body->Integrate(dt);
    }

    // Circle–circle collisions (elastic impulse)
    for (size_t i = 0; i < bodies.size(); ++i)
    {
        for (size_t j = i + 1; j < bodies.size(); ++j)
        {
            RigidBody *A = bodies[i];
            RigidBody *B = bodies[j];

            if (A->shapeType == ShapeType::Circle && B->shapeType == ShapeType::Circle)
            {
                Vector2D d = B->position - A->position;
                float dist = d.Magnitude();
                float rSum = A->radius + B->radius;

                if (dist > 0.f && dist < rSum)
                {
                    Vector2D n = d * (1.0f / dist); // normal
                    float pen = rSum - dist;

                    // separate
                    A->position -= n * (pen * 0.5f);
                    B->position += n * (pen * 0.5f);

                    // relative velocity
                    Vector2D rel = B->velocity - A->velocity;
                    float vn = rel.Dot(n);
                    if (vn < 0.f)
                    {
                        const float e = 0.5f; // restitution
                        float j = -(1.f + e) * vn / (A->invMass + B->invMass);
                        Vector2D impulse = n * j;
                        A->velocity -= impulse * A->invMass;
                        B->velocity += impulse * B->invMass;
                    }
                }
            }

            // (You can add Rectangle–Rectangle here as needed)
        }
    }

    // Wall collisions (AABB in world units centered at origin)
    for (auto *body : bodies)
    {
        float left = -worldWidth * 0.5f + (body->shapeType == ShapeType::Circle ? body->radius : body->size.x * 0.5f);
        float right = worldWidth * 0.5f - (body->shapeType == ShapeType::Circle ? body->radius : body->size.x * 0.5f);
        float bottom = -worldHeight * 0.5f + (body->shapeType == ShapeType::Circle ? body->radius : body->size.y * 0.5f);
        float top = worldHeight * 0.5f - (body->shapeType == ShapeType::Circle ? body->radius : body->size.y * 0.5f);

        if (body->position.x < left)
        {
            body->position.x = left;
            body->velocity.x *= -1.f;
        }
        if (body->position.x > right)
        {
            body->position.x = right;
            body->velocity.x *= -1.f;
        }
        if (body->position.y < bottom)
        {
            body->position.y = bottom;
            body->velocity.y *= -1.f;
        }
        if (body->position.y > top)
        {
            body->position.y = top;
            body->velocity.y *= -1.f;
        }
    }
}
