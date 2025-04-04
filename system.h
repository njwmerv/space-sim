#ifndef SYSTEM_H
#define SYSTEM_H
#include "body.h"
#include "vector.h"
#include <vector>

class System {
public:
    System();

    ~System();

    void addBody(float mass, float radius, Vector3 position = Vector3(), Vector3 velocity = Vector3(), Vector3 acceleration = Vector3(), Vector3 colour = Vector3(), bool still = false);

    void update(float dt);

    [[nodiscard]] const std::vector<Body*>& getBodies() const;
    [[nodiscard]] unsigned int getNumBodies() const;
private:
    std::vector<Body*> bodies;

    static Vector3 calculateGravity(const Body* a, const Body* b);
};

#endif //SYSTEM_H
