
#pragma onece

class Vector2D {
    public:
    float x, y;

    Vector2D();
    Vector2D(float x, float y);

    Vector2D operator+(const Vector2D& other) const;
    Vector2D operator-(const Vector2D& other) const;
    Vector2D operator*(float scalar) const;
    Vector2D& operator+=(const Vector2D& other);

    float Magnitude() const;
    Vector2D Normalize() const;
    float Dot(const Vector2D& other) const;
};

