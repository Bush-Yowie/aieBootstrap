#include "Rigidbody.h"
#include "PhysicsScene.h"
#include <iostream>

Rigidbody::Rigidbody(ShapeType shapeID, float elasticity, glm::vec2 position, glm::vec2 velocity, float orientation, float mass, float angularVelocity, float moment, float linearDrag, float angularDrag) : PhysicsObject(shapeID, elasticity){
    //m_shapeID = shapeID;
    m_position = position;
    m_velocity = velocity;
    m_orientation = orientation;
    m_mass = mass;
    m_angularVelocity = angularVelocity;
    m_moment = moment;
    m_linearDrag = linearDrag;
    m_angularDrag = angularDrag;
    m_isKinematic = false;
    m_localX = glm::vec2(0, 0);
    m_localY = glm::vec2(0, 0);
}

//Applies Newton's second law
void Rigidbody::applyForce(glm::vec2 force, glm::vec2 pos) {
    m_velocity += force / m_mass;
    m_angularVelocity += (force.y * pos.x - force.x * pos.y) / getMoment();
}

float Rigidbody::getPotentialEnergy() {
    return -getMass() * glm::dot(PhysicsScene::getGravity(), getPosition());
}

//Apply gravity
void Rigidbody::fixedUpdate(glm::vec2 gravity, float timeStep) {
    float cs = cosf(m_orientation);
    float sn = sinf(m_orientation);
    m_localX = glm::normalize(glm::vec2(cs, sn));
    m_localY = glm::normalize(glm::vec2(-sn, cs));

    if (m_isKinematic){
        m_velocity = glm::vec2(0);
        m_angularVelocity = 0;
        return;
    }

    m_position += m_velocity * timeStep;
    applyForce(gravity * m_mass * timeStep,glm::vec2(0,0));

    m_orientation += m_angularVelocity * timeStep;

    m_velocity -= m_velocity * m_linearDrag * timeStep;
    m_angularVelocity -= m_angularVelocity * m_angularDrag * timeStep;

    if (length(m_velocity) < MIN_LINEAR_THRESHOLD) {
        m_velocity = glm::vec2(0, 0);
    }
    if (abs(m_angularVelocity) < MIN_ANGULAR_THRESHOLD) {
        m_angularVelocity = 0;
    }

}

void Rigidbody::resolveCollision(Rigidbody* actor2, glm::vec2 contact, glm::vec2* collisionNormal, float pen){
    // find the vector between their centres, or use the provided direction of force, and make sure it's normalised
    glm::vec2 normal = glm::normalize(collisionNormal ? *collisionNormal : actor2->m_position - m_position);

    // get the vector perpendicular to the collision normal
    glm::vec2 perp(normal.y, -normal.x);

    // determine the total velocity of the contact points for the two objects, for both linear and rotational 
    //'r' is the radius from axis to application of force
    float r1 = glm::dot(contact - m_position, -perp);
    float r2 = glm::dot(contact - actor2->m_position, perp);

    // velocity of the contact point on this object
    float v1 = glm::dot(m_velocity, normal) - r1 * m_angularVelocity;
    
    // velocity of contact point on actor2
    float v2 = glm::dot(actor2->m_velocity, normal) + r2 * actor2->m_angularVelocity;

    // they're moving closer
    if (v1 > v2) {
        // calculate the effective mass at contact point for each object
        // ie how much the contact point will move due to the force applied.
        float mass1 = 1.0f / (1.0f / m_mass + (r1 * r1) / m_moment);
        float mass2 = 1.0f / (1.0f / actor2->m_mass + (r2 * r2) / actor2->m_moment);
        float elasticity = (getElasticity() + actor2->getElasticity()) / 2.0f;

        glm::vec2 force = (1.0f + elasticity) * mass1 * mass2 / (mass1 + mass2) * (v1 - v2) * normal;

        //apply equal and opposite forces
        applyForce(-force, contact - m_position);
        actor2->applyForce(force, contact - actor2->m_position);
    }

    if (pen > 0) {
        PhysicsScene::ApplyContactForces(this, actor2, normal, pen);
    }
}