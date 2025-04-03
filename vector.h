#ifndef VECTOR_H
#define VECTOR_H

struct Vector3;

struct Vector2{
    float x, y;

    Vector2(float x = 0, float y = 0);
    Vector2(const Vector3& vec);

    Vector2 operator+(const Vector2& other) const;
    Vector2& operator+=(const Vector2& other);

    Vector2 operator-() const;
    Vector2 operator-(const Vector2& other) const;
    Vector2& operator-=(const Vector2& other);

    Vector2 operator*(float scalar) const;
    float operator*(const Vector2& other) const;
    Vector2& operator*=(float scalar);

    float length() const;
    Vector2 normal() const;
};

struct Vector3{
    float x, y, z;

    Vector3(float x = 0, float y = 0, float z = 0);
    Vector3(const Vector2& vec);

    Vector3 operator+(const Vector3& other) const;
    Vector3& operator+=(const Vector3& other);

    Vector3 operator-() const;
    Vector3 operator-(const Vector3& other) const;
    Vector3& operator-=(const Vector3& other);

    Vector3 operator*(float scalar) const;
    float operator*(const Vector3& other) const;
    Vector3& operator*=(float scalar);

    Vector3 cross(const Vector3& other) const;

    float length() const;
    Vector3 normal() const;
};



#endif //VECTOR_H
