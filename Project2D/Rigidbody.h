#pragma once

#include "PhysicsObject.h"

class Rigidbody : public PhysicsObject {
public:
	Rigidbody(ShapeType shapeID, glm::vec2 position, glm::vec2 velocity, float orientation, float mass, float angularVelocity, float moment);
	~Rigidbody() {};

	virtual void fixedUpdate(glm::vec2 gravity, float timeStep);
	void applyForce(glm::vec2 force, glm::vec2 pos);
	//void applyForceToActor(Rigidbody* actor2, glm::vec2 force);
	void resolveCollision(Rigidbody* actor2, glm::vec2 contact, glm::vec2* collisionNormal = nullptr);

	glm::vec2 getPosition() { return m_position; }
	float getOrientatation() { return m_orientation; }
	glm::vec2 getVelocity() { return m_velocity; }
	void setVelocity(float x, float y) { m_velocity.x = x, m_velocity.y = y; }
	float getMass() { return m_mass; }
	float getKineticEnergy() { return (0.5f * (m_mass * glm::dot(m_velocity, m_velocity) + m_moment * m_angularVelocity * m_angularVelocity)); }
	float getPotentialEnergy();
	float getEnergy() { return getPotentialEnergy() + getKineticEnergy(); }
	float getMoment() { return m_moment; }
	float getAngularVelocity() { return m_angularVelocity; }


protected:
	glm::vec2 m_position;
	glm::vec2 m_velocity;
	float m_mass;
	float m_orientation;    //2D so we only need a single float to represent our orientation
	float m_angularVelocity;
	float m_moment;
};

