#pragma once

#include <glm/glm.hpp>
#include <vector>
#include "Gizmos.h"

class PhysicsObject;

class PhysicsScene{
public:
	PhysicsScene();
	~PhysicsScene();

	void addActor(PhysicsObject* actor);
	void removeActor(PhysicsObject* actor);
	void update(float dt);
	void draw();

	static bool sphere2Sphere(PhysicsObject*, PhysicsObject*);
	static bool plane2Plane(PhysicsObject*, PhysicsObject*);
	static bool sphere2Plane(PhysicsObject*, PhysicsObject*);
	static bool plane2Sphere(PhysicsObject*, PhysicsObject*);

	void setGravity(const glm::vec2 gravity) { m_gravity = gravity; }
	glm::vec2 getGravity() const { return m_gravity; }

	void setTimeStep(const float timeStep) { m_timeStep = timeStep; }
	float getTimeStep() const { return m_timeStep; }

protected:
	glm::vec2 m_gravity;
	float m_timeStep;
	std::vector<PhysicsObject*> m_actors;
	const int SHAPE_COUNT = 2;
};

enum ShapeType {
	PLANE = 0,
	SPHERE//,
	//BOX
};

class PhysicsObject {
protected:
	PhysicsObject() {}
	PhysicsObject(ShapeType a_shapeID) : m_shapeID(a_shapeID) {}

public:
	virtual void fixedUpdate(glm::vec2 gravity, float timeStep) = 0;
	virtual void draw() = 0;
	virtual void resetPosition() {};

	ShapeType getShapeID() {return m_shapeID;}

protected:
	ShapeType m_shapeID;
};

