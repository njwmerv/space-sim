#include "system.h"
#include <cmath>

System::System() : bodies{} {}

System::~System(){
    for(auto body : bodies) {delete body;}
}

void System::addBody(const float mass, const float radius, const Vector3 position, const Vector3 velocity,
                     const Vector3 acceleration, const Vector3 colour, const bool still){
    bodies.emplace_back(new Body(mass, radius, position, velocity, acceleration, colour, still));
}

const std::vector<Body*>& System::getBodies() const {return bodies; }

unsigned int System::getNumBodies() const { return bodies.size();}

void System::update(const float dt){
    for(int i = 0; i < bodies.size(); i++){
        Body* body = bodies.at(i);
        for(int j = i + 1; j < bodies.size(); j++){
            Body* b = bodies.at(j);
            Vector3 gravityForce = calculateGravity(body, b);
            body->accelerate(gravityForce * dt / body->getMass());
            b->accelerate(-gravityForce * dt / b->getMass());
        }
    }
    for(Body* body : bodies) body->update(dt);
}

Vector3 System::calculateGravity(const Body* a, const Body* b){
    constexpr double G = 1.993560809749174e-32;
    const float MIN_DISTANCE = a->getRadius() + b->getRadius();

    const Vector3 delta = b->getPosition() - a->getPosition();
    const float r = std::max(delta.length(), MIN_DISTANCE);
    const float magnitude = G * a->getMass() * b->getMass() / (r * r);
    const Vector3 rHat = delta.normal();

    return rHat * magnitude;
}

