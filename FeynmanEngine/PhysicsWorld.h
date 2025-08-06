#pragma once
#include <vector>
#include "RigidBody.h"

class PhysicsWorld
{
public:
    std::vector<RigidBody *> bodies;
    Vector2D gravity;
    float worldWidth, worldHeight;

    PhysicsWorld(Vector2D gravity, float width, float height);

    void AddBody(RigidBody *body);
    void Step(float dt);
};
