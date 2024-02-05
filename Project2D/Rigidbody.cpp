#include "Rigidbody.h"
#include <iostream>

Rigidbody::Rigidbody(ShapeType shapeID, glm::vec2 position, glm::vec2 velocity, float orientation, float mass) {
    m_shapeID = shapeID;
    m_position = position;
    m_velocity = velocity;
    m_orientation = orientation;
    m_mass = mass;
}

//Applies Newton's second law
void Rigidbody::applyForce(glm::vec2 force) {
    m_velocity += force / m_mass;
}

//Applies Newton's third law
void Rigidbody::applyForceToActor(Rigidbody* actor2, glm::vec2 force) {
    actor2->applyForce(force);
    this->applyForce(-force);
}

//Apply gravity
void Rigidbody::fixedUpdate(glm::vec2 gravity, float timeStep) {
    m_position += m_velocity * timeStep;
    applyForce(gravity * m_mass * timeStep);
}

void Rigidbody::resolveCollision(Rigidbody* actor2){
    glm::vec2 normal = glm::normalize(actor2->getPosition() - m_position);
    glm::vec2 relativeVelocity = actor2->getVelocity() - m_velocity;
    // if the objects are already moving apart, we don't need to do anything
    if (glm::dot(normal, relativeVelocity) >= 0)
        return;
    float elasticity = 1;

    float j = glm::dot(-(1 + elasticity) * (relativeVelocity), normal) / ((1/ m_mass) + (1/ actor2->getMass()));

    glm::vec2 force = normal * j;

    //float kePre = getKineticEnergy() + actor2->getKineticEnergy();

    applyForceToActor(actor2, force);

    //float kePost = getKineticEnergy() + actor2->getKineticEnergy();

    /*float deltaKE = kePost - kePre;
    if (deltaKE > kePost * 0.01f) {
        std::cout << "Kinetic Energy discrepancy greater than 1% detected!!";
    }*/
}