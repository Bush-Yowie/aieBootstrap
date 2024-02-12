#pragma once

#include "PhysicsObject.h"

class Rigidbody : public PhysicsObject {
public:
	Rigidbody(ShapeType shapeID, float elasticity, glm::vec2 position, glm::vec2 velocity, float orientation, float mass, float angularVelocity, float moment, float linearDrag, float angularDrag);
	~Rigidbody() {};

	virtual void fixedUpdate(glm::vec2 gravity, float timeStep);
	void applyForce(glm::vec2 force, glm::vec2 pos);
	//void applyForceToActor(Rigidbody* actor2, glm::vec2 force);
	void resolveCollision(Rigidbody* actor2, glm::vec2 contact, glm::vec2* collisionNormal = nullptr, float pen = 0);
	glm::vec2 toWorld(glm::vec2 contactPos) { return glm::vec2(m_position + m_localX * contactPos + m_localY * contactPos); }

	glm::vec2 getPosition() { return m_position; }
	void setPosition(glm::vec2 pos) { m_position = pos; }
	float getOrientatation() { return m_orientation; }
	glm::vec2 getVelocity() { return m_velocity; }
	void setVelocity(float x, float y) { m_velocity.x = x, m_velocity.y = y; }
	float getMass() { return m_isKinematic ? INT_MAX : m_mass; }
	float getKineticEnergy() { return (0.5f * (m_mass * glm::dot(m_velocity, m_velocity) + m_moment * m_angularVelocity * m_angularVelocity)); }
	float getPotentialEnergy();
	float getEnergy() { return getPotentialEnergy() + getKineticEnergy(); }
	float getMoment() { return m_isKinematic ? INT_MAX : m_moment; }
	float getAngularVelocity() { return m_angularVelocity; }
	float getLinearDrag() { return m_linearDrag; }
	float getAngularDrag() { return m_angularDrag; }
	void setKinematic(bool state) { m_isKinematic = state; }
	bool isKinematic() { return m_isKinematic; }
	glm::vec2 getLocalX() { return m_localX; }
	glm::vec2 getLocalY() { return m_localY; }

	const float MIN_LINEAR_THRESHOLD = 0.05f;
	const float MIN_ANGULAR_THRESHOLD = 0.1f;

protected:
	glm::vec2 m_position;
	glm::vec2 m_velocity;
	float m_mass;
	float m_orientation;    //2D so we only need a single float to represent our orientation
	float m_angularVelocity;
	float m_moment;
	float m_linearDrag;
	float m_angularDrag;
	bool m_isKinematic;
	// store the local x,y axes of the box based on its angle of rotation
	glm::vec2 m_localX;
	glm::vec2 m_localY;
};

