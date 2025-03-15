#ifndef BODY_H
#define BODY_H
#include "vector.h"

class Body{
public:
    Body(float mass, float radius, Vector3 position = Vector3(), Vector3 velocity = Vector3(), Vector3 acceleration = Vector3());

    float getMass() const;
    float getRadius() const;
    Vector3 getPosition() const;
    Vector3 getVelocity() const;
    Vector3 getAcceleration() const;

    void accelerate(const Vector3& acc);

    void update();
private:
    float mass;
    float radius;
    Vector3 position;
    Vector3 velocity;
    Vector3 acceleration;
};

#endif //BODY_H
