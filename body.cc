#include "body.h"

Body::Body(const float mass, const float radius, const Vector3 position, const Vector3 velocity, const Vector3 acceleration, const Vector3 colour, const bool still) :
    mass{mass}, radius{radius}, position{position}, velocity{velocity}, acceleration{acceleration}, colour{colour}, still{still}{}

bool Body::isStill() const {return still;}
float Body::getMass() const {return mass;}
float Body::getRadius() const {return radius;}
Vector3 Body::getColour() const {return colour;}
Vector3 Body::getPosition() const {return position;}
Vector3 Body::getVelocity() const {return velocity;}
Vector3 Body::getAcceleration() const {return acceleration;}

void Body::accelerate(const Vector3& acc) {this->acceleration += acc;}

void Body::update(const float dt){
    if(still) return;
    velocity += acceleration * dt;
    position += velocity * dt;
}