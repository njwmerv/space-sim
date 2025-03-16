#ifndef SYSTEM_H
#define SYSTEM_H
#include "body.h"
#include "vector.h"
#include <vector>

class System {
public:
    System();

    ~System();

    void addBody(float mass, float radius, Vector3 position = Vector3(), Vector3 velocity = Vector3(), Vector3 acceleration = Vector3());

    void update();

    const std::vector<Body*>& getBodies() const;
private:
    std::vector<Body*> bodies;
};

#endif //SYSTEM_H
