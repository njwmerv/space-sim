#include "body.h"

Body::Body(const float mass, const float radius, const Vector3 position, const Vector3 velocity, const Vector3 acceleration, const Vector3 colour) :
    mass{mass}, radius{radius}, position{position}, velocity{velocity}, acceleration{acceleration}, colour{colour}{}

float Body::getMass() const {return mass;}
float Body::getRadius() const {return radius;}
Vector3 Body::getPosition() const {return position;}
Vector3 Body::getVelocity() const {return velocity;}
Vector3 Body::getAcceleration() const {return acceleration;}

void Body::accelerate(const Vector3& acc) {this->acceleration += acc;}

void Body::update(){
    velocity += acceleration;
    position += velocity;
}