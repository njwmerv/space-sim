#include "vector.h"

// 2D Vectors
Vector2::Vector2(float x, float y) : x{x}, y{y} {}

Vector2::Vector2(const Vector3& vec) : x{vec.x}, y{vec.y} {}

//// Addition
Vector2 Vector2::operator+(const Vector2& other) const {
    return {x + other.x, y + other.y};
}

Vector2& Vector2::operator+=(const Vector2& other) {
    x += other.x;
    y += other.y;
    return *this;
}

//// Subtraction
Vector2 Vector2::operator-() const {
    return {-x, -y};
}

Vector2 Vector2::operator-(const Vector2& other) const {
    return {x - other.x, y - other.y};
}

Vector2& Vector2::operator-=(const Vector2& other) {
    x -= other.x;
    y -= other.y;
    return *this;
}

//// Multiplication
Vector2 Vector2::operator*(float scalar) const {
    return {x * scalar, y * scalar};
}

Vector2& Vector2::operator*=(float scalar) {
    x *= scalar;
    y *= scalar;
    return *this;
}

Vector2 operator*(float scalar, Vector2& vec){
    return {vec * scalar};
}

float Vector2::operator*(const Vector2& other) const {
    return x * other.x + y * other.y;
}

// 3D Vectors
Vector3::Vector3(float x, float y, float z) : x{x}, y{y}, z{z} {}

Vector3::Vector3(const Vector2& vec) : x{vec.x}, y{vec.y}, z{0} {}

//// Addition
Vector3 Vector3::operator+(const Vector3& other) const {
    return {x + other.x, y + other.y, z + other.z};
}

Vector3& Vector3::operator+=(const Vector3& other) {
    x += other.x;
    y += other.y;
    z += other.z;
    return *this;
}

//// Subtraction
Vector3 Vector3::operator-() const {
    return {-x, -y, -z};
}

Vector3 Vector3::operator-(const Vector3& other) const {
    return {x - other.x, y - other.y, z - other.z};
}

Vector3& Vector3::operator-=(const Vector3& other) {
    x -= other.x;
    y -= other.y;
    z -= other.z;
    return *this;
}

//// Multiplication
Vector3 Vector3::operator*(float scalar) const {
    return {x * scalar, y * scalar, z * scalar};
}

Vector3& Vector3::operator*=(float scalar) {
    x *= scalar;
    y *= scalar;
    z *= scalar;
    return *this;
}

Vector3 operator*(float scalar, Vector3& vec){
    return {vec * scalar};
}

float Vector3::operator*(const Vector3& other) const {
    return x * other.x + y * other.y + z * other.z;
}

Vector3 Vector3::cross(const Vector3& other) const {
    float X = (y * other.z) - (z * other.y);
    float Y = (z * other.x) - (x * other.z);
    float Z = (x * other.y) - (y * other.x);
    return {X, Y, Z};
}
