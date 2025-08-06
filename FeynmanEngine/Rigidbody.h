#pragma once
#include "Vector2D.h"
#include "ShapeType.h"

class RigidBody
{
public:
    Vector2D position;
    Vector2D velocity;
    float mass;
    float invMass;

    bool isKinematic = false; // for dragged objects (ignore physics forces)

    // Circle-specific
    float radius;

    // Rectangle-specific
    Vector2D size;

    ShapeType shapeType;

    // Circle constructor
    RigidBody(Vector2D pos, float r, float m)
        : position(pos), velocity(0, 0), mass(m), radius(r), size(0, 0), shapeType(ShapeType::Circle)
    {
        invMass = (mass > 0) ? 1.0f / mass : 0.0f;
    }

    // Rectangle constructor
    RigidBody(Vector2D pos, float width, float height, ShapeType type = ShapeType::Rectangle)
        : position(pos), velocity(0, 0), mass(1.0f), radius(0), size(width, height), shapeType(type)
    {
        invMass = (mass > 0) ? 1.0f / mass : 0.0f;
    }

    void ApplyForce(const Vector2D &force)
    {
        Vector2D acceleration = force * invMass;
        velocity += acceleration;
    }

    void Integrate(float dt)
    {
        position += velocity * dt;
    }
};
  