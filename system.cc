#include "system.h"

System::System() : bodies{} {}

System::~System(){
    for(auto body : bodies) {delete body;}
}

void System::addBody(float mass, float radius, Vector3 position, Vector3 velocity, Vector3 acceleration){
    bodies.emplace_back(new Body(mass, radius, position, velocity, acceleration));
}

const std::vector<Body*>& System::getBodies() const {return bodies;}

void System::update(){
    for(auto body : bodies) body->update();
}
