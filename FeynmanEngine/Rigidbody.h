#pragma once
#include "Vector2D.h"
#include "ShapeType.h"

class RigidBody
{
public:
    // Kinematics
    Vector2D position{};
    Vector2D velocity{};
    Vector2D force{}; // <-- accumulate forces here

    // Mass
    float mass{1.0f};
    float invMass{1.0f};

    // Shape
    ShapeType shapeType{ShapeType::Circle};
    float radius{0.0f};        // for circles
    Vector2D size{0.0f, 0.0f}; // for rectangles (width, height)

    // Dragging
    bool isKinematic{false};

    // Constructors (declarations only)
    // Circle
    RigidBody(Vector2D pos, float r, float m, ShapeType type = ShapeType::Circle);
    // Rectangle by width/height
    RigidBody(Vector2D pos, float width, float height, float m, ShapeType type = ShapeType::Rectangle);
    // Rectangle by size vector (optional convenience)
    RigidBody(Vector2D pos, Vector2D sz, float m, ShapeType type = ShapeType::Rectangle);

    // Forces/integration
    void ApplyForce(const Vector2D &f);
    void Integrate(float dt);
};
