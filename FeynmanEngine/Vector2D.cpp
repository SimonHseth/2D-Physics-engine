
#include "Vector2D.h"
#include <cmath>

Vector2D::Vector2D(): x(0), y(0) {}
Vector2D::Vector2D(float x, float y) : x(x), y(y) {}

Vector2D Vector2D::operator+(const Vector2D& other) const {
    return Vector2D(x + other.x, y + other.y);
}

Vector2D Vector2D::operator-(const Vector2D& other) const {
    return Vector2D(x - other.x, y - other.y);
}

Vector2D Vector2D::operator*(float scalar) const {
    return Vector2D(x * scalar, y * scalar);
}

Vector2D& Vector2D::operator+=(const Vector2D& other) {
    x += other.x;
    y += other.y;
    return *this;
}

Vector2D &Vector2D::operator-=(const Vector2D &other)
{
    x -= other.x;
    y -= other.y;
    return *this;
}

float Vector2D::Magnitude() const {
    return std::sqrt(x * x + y * y);
}

Vector2D Vector2D::Normalize() const {
    float mag = Magnitude();
    return mag == 0 ? Vector2D(0, 0) : Vector2D(x / mag, y / mag);
}


float Vector2D::Dot(const Vector2D& other) const {
    return x * other.x + y * other.y;
}
