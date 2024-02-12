#pragma once

//#include "PhysicsObject.h"
#include "Rigidbody.h"

class Spring : public PhysicsObject{
public:
	Spring() {};
	Spring(Rigidbody* body1, Rigidbody* body2, float springCoefficient, float damping, float restLength, glm::vec2 contact1 = glm::vec2(0, 0), glm::vec2 contact2 = glm::vec2(0, 0));
	~Spring() {};

	void fixedUpdate(glm::vec2 gravity, float timeStep);
	virtual void draw();

	glm::vec2 getContact1() { return m_body1 ? m_body1->toWorld(m_contact1) : m_contact1; }
	//glm::vec2 getContact1() { return m_body1 ? m_body1->toWorld() : m_contact1; }
	glm::vec2 getContact2() { return m_body2 ? m_body2->toWorld(m_contact2) : m_contact2; }
	//glm::vec2 getContact2() { return m_body2 ? m_body2->toWorld() : m_contact2; }

protected:
	Rigidbody* m_body1;
	Rigidbody* m_body2;

	glm::vec2 m_contact1;
	glm::vec2 m_contact2;

	float m_damping;
	float m_restLength;
	float m_springCoefficient; // the restoring force;
};

