#include "system.h"

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

void System::update(){
    for(auto body : bodies) body->update();
}
