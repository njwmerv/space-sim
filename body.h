#ifndef BODY_H
#define BODY_H
#include "vector.h"

class Body{
public:
    Body(float mass, float radius, Vector3 position = Vector3(), Vector3 velocity = Vector3(), Vector3 acceleration = Vector3(), Vector3 colour = Vector3(), bool still = false);

    [[nodiscard]] bool isStill() const;
    [[nodiscard]] float getMass() const;
    [[nodiscard]] float getRadius() const;
    [[nodiscard]] Vector3 getColour() const;
    [[nodiscard]] Vector3 getPosition() const;
    [[nodiscard]] Vector3 getVelocity() const;
    [[nodiscard]] Vector3 getAcceleration() const;

    void accelerate(const Vector3& acc);

    void update(float dt);
private:
    bool still;
    float mass;
    float radius;
    Vector3 colour;
    Vector3 position;
    Vector3 velocity;
    Vector3 acceleration;
};

#endif //BODY_H
