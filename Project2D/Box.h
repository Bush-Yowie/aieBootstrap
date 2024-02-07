#pragma once

#include "Rigidbody.h"

class Box : public Rigidbody {
public:
	//Box();
	Box(glm::vec2 position, glm::vec2 velocity, float orientation, float mass, glm::vec4 colour, float angularVelocity, glm::vec2 extents);
	~Box() {};

	void fixedUpdate(glm::vec2 gravity,float timeStep);
	virtual void draw();
	bool checkBoxCorners(Box& box, glm::vec2& contact, int& numContacts, float& pen, glm::vec2& edgeNormal);

	glm::vec2 getExtents() { return m_extents; }
	float getWidth() { return m_extents.x*2; }
	float getHeight() { return m_extents.y*2; }
	glm::vec4 getColour() { return m_colour; }
	glm::vec2 getLocalX() { return m_localX; }
	glm::vec2 getLocalY() { return m_localY; }

protected:
	glm::vec2 m_extents; // the halfedge lengths
	glm::vec4 m_colour;
	// store the local x,y axes of the box based on its angle of rotation
	glm::vec2 m_localX;
	glm::vec2 m_localY;
};

