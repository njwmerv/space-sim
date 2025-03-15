#include "body.h"

Body::Body(float mass, float radius, Vector3 position, Vector3 velocity, Vector3 acceleration) :
    mass{mass}, radius{radius}, position{position}, velocity{velocity}, acceleration{acceleration}{}

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