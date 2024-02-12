#pragma once

#include <glm/glm.hpp>
#include "Gizmos.h"

enum ShapeType {
	JOINT = -1,
	PLANE = 0,
	SPHERE,
	BOX
};

class PhysicsObject {
protected:
	PhysicsObject() {}
	PhysicsObject(ShapeType a_shapeID, float elasticity) : m_shapeID(a_shapeID), m_elasticity(elasticity) {}
	//~PhysicsObject() {}

public:
	virtual void fixedUpdate(glm::vec2 gravity, float timeStep) = 0;
	virtual void draw() = 0;
	virtual void resetPosition() {};
	virtual float getEnergy() { return 0; }

	ShapeType getShapeID() {return m_shapeID;}
	float getElasticity() {return m_elasticity;}

protected:
	ShapeType m_shapeID;
	float m_elasticity;
};

