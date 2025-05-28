#include "PhysicsWorld.h"
#include <cmath>

PhysicsWorld::PhysicsWorld(Vector2D gravity) : gravity(gravity) {}

void PhysicsWorld::AddBody(RigidBody *body)
{
    bodies.push_back(body);
}

void PhysicsWorld::Step(float dt)
{
    // Apply forces and integrate motion
    for (auto body : bodies)
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

            Vector2D delta = B->position - A->position;
            float dist = delta.Magnitude();
            float combinedRadius = A->radius + B->radius;

            if (dist < combinedRadius && dist > 0.0f)
            {
                Vector2D normal = delta * (1.0f / dist); // normalized
                float penetration = combinedRadius - dist;

                // Positional correction (to prevent sinking)
                A->position -= normal * (penetration * 0.5f);
                B->position += normal * (penetration * 0.5f);

                // Relative velocity
                Vector2D relVel = B->velocity - A->velocity;
                float velAlongNormal = relVel.Dot(normal);

                if (velAlongNormal < 0)
                {
                    float restitution = 0.5f; // elasticity
                    float impulseScalar = -(1 + restitution) * velAlongNormal;
                    impulseScalar /= A->invMass + B->invMass;

                    Vector2D impulse = normal * impulseScalar;
                    A->velocity -= impulse * A->invMass;
                    B->velocity += impulse * B->invMass;
                }
            }
        }
    }
}
