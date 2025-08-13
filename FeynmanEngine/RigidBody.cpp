#include "RigidBody.h"

// Circle
RigidBody::RigidBody(Vector2D pos, float r, float m, ShapeType type)
{
    position = pos;
    radius = r;
    mass = m;
    shapeType = type; // should be Circle
    size = Vector2D(0, 0);
    invMass = (mass > 0.f) ? 1.0f / mass : 0.0f;
    velocity = Vector2D(0, 0);
    force = Vector2D(0, 0);
}

// Rectangle by width/height
RigidBody::RigidBody(Vector2D pos, float width, float height, float m, ShapeType type)
{
    position = pos;
    size = Vector2D(width, height);
    mass = m;
    shapeType = type; // should be Rectangle
    radius = 0.0f;
    invMass = (mass > 0.f) ? 1.0f / mass : 0.0f;
    velocity = Vector2D(0, 0);
    force = Vector2D(0, 0);
}

// Rectangle by size vector
RigidBody::RigidBody(Vector2D pos, Vector2D sz, float m, ShapeType type)
{
    position = pos;
    size = sz;
    mass = m;
    shapeType = type; // Rectangle
    radius = 0.0f;
    invMass = (mass > 0.f) ? 1.0f / mass : 0.0f;
    velocity = Vector2D(0, 0);
    force = Vector2D(0, 0);
}

void RigidBody::ApplyForce(const Vector2D &f)
{
    force += f;
}

void RigidBody::Integrate(float dt)
{
    if (isKinematic || invMass == 0.f)
    {
        force = Vector2D(0, 0);
        return;
    }
    const Vector2D a = force * invMass;
    velocity += a * dt;
    position += velocity * dt;
    force = Vector2D(0, 0);
}
