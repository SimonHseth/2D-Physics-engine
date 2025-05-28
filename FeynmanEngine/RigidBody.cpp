#include "RigidBody.h"

RigidBody::RigidBody(Vector2D pos, float m, float r)
    : position(pos), velocity(0, 0), force(0, 0), mass(m), radius(r)
{
    invMass = (mass != 0) ? 1.0f / mass : 0;
}

void RigidBody::ApplyForce(const Vector2D &f)
{
    force += f;
}

void RigidBody::Integrate(float dt)
{
    Vector2D acceleration = force * invMass;
    velocity += acceleration * dt;
    position += velocity * dt;
    force = Vector2D(0, 0); // Clear force
}
