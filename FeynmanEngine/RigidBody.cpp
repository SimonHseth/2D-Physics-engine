#include "RigidBody.h"

RigidBody::RigidBody(Vector2D pos, float rad, float m)
    : position(pos), radius(rad), size(0, 0), mass(m), shapeType(ShapeType::Circle)
{
    invMass = (m > 0) ? 1.0f / m : 0.0f;
    velocity = force = Vector2D(0, 0);
}

RigidBody::RigidBody(Vector2D pos, Vector2D sz, float m)
    : position(pos), size(sz), radius(0), mass(m), shapeType(ShapeType::Rectangle)
{
    invMass = (m > 0) ? 1.0f / m : 0.0f;
    velocity = force = Vector2D(0, 0);
}

void RigidBody::ApplyForce(const Vector2D &f)
{
    force += f;
}

void RigidBody::Integrate(float dt)
{
    if (invMass == 0)
        return;
    Vector2D acceleration = force * invMass;
    velocity += acceleration * dt;
    position += velocity * dt;
    force = Vector2D(0, 0);
}
