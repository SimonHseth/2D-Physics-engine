#pragma once
#include "Vector2D.h"

class RigidBody
{
public:
    Vector2D position;
    Vector2D velocity;
    Vector2D force;

    float mass;
    float invMass;
    float radius; // ✅ Needed for collision

    RigidBody(Vector2D pos, float m, float r); // ✅ Updated constructor

    void ApplyForce(const Vector2D &f);
    void Integrate(float dt);
};
