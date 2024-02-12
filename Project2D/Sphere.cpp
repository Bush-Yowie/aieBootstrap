#include "Sphere.h"

Sphere::Sphere(float elasticity, glm::vec2 position, glm::vec2 velocity, float mass, glm::vec4 colour, float angularVelocity, float linearDrag, float angularDrag, float radius) : Rigidbody(SPHERE, elasticity, position, velocity, 0, mass, angularVelocity, (0.5f * mass * (radius * radius)), linearDrag, angularDrag){
    m_radius = radius;
    m_colour = colour;
    m_moment = 0.5f * mass * radius * radius;
}

void Sphere::draw() {
    glm::vec2 end = glm::vec2(std::cos(m_orientation), std::sin(m_orientation)) *
        m_radius;
    aie::Gizmos::add2DCircle(m_position, m_radius, 12, m_colour);
    aie::Gizmos::add2DLine(m_position, m_position + end, glm::vec4(1, 1, 1, 1));
}