#pragma once
#include <vector>
#include "RigidBody.h"

class PhysicsWorld
{
public:
    std::vector<RigidBody *> bodies;
    Vector2D gravity;

    PhysicsWorld(Vector2D gravity = Vector2D(0, -9.8f));

    void AddBody(RigidBody *body);
    void Step(float dt);
};
