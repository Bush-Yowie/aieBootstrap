#pragma once

#include "Rigidbody.h"

class Sphere : public Rigidbody{
public:
	Sphere(float elasticity, glm::vec2 position, glm::vec2 velocity, float mass, glm::vec4 colour, float angularVelocity, float linearDrag, float angularDrag, float radius);
	~Sphere() {};

	virtual void draw();

	float getRadius() { return m_radius; }
	glm::vec4 getColour() { return m_colour; }

protected:
	float m_radius;
	glm::vec4 m_colour;
};

