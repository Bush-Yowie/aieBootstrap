#pragma once

#include <glm/glm.hpp>
#include <vector>
#include "Gizmos.h"
#include "PhysicsObject.h"
#include "Rigidbody.h"

class PhysicsScene{
public:
	PhysicsScene();
	~PhysicsScene();

	void addActor(PhysicsObject* actor);
	void removeActor(PhysicsObject* actor);
	void update(float dt);
	void draw();

	static void ApplyContactForces(Rigidbody* body1, Rigidbody* body2, glm::vec2 norm, float pen);

	static bool sphere2Sphere(PhysicsObject*, PhysicsObject*);
	static bool plane2Plane(PhysicsObject*, PhysicsObject*);
	static bool sphere2Plane(PhysicsObject*, PhysicsObject*);
	static bool plane2Sphere(PhysicsObject*, PhysicsObject*);
	static bool plane2Box(PhysicsObject*, PhysicsObject*);
	static bool box2Sphere(PhysicsObject*, PhysicsObject*);
	static bool box2Box(PhysicsObject*, PhysicsObject*);
	static bool box2Plane(PhysicsObject*, PhysicsObject*);
	static bool sphere2Box(PhysicsObject*, PhysicsObject*);

	void setGravity(const glm::vec2 gravity) { m_gravity = gravity; }
	static glm::vec2 getGravity() { return m_gravity; }
	void setTimeStep(const float timeStep) { m_timeStep = timeStep; }
	float getTimeStep() const { return m_timeStep; }
	float getTotalEnergy();

protected:
	static glm::vec2 m_gravity;
	float m_timeStep;
	std::vector<PhysicsObject*> m_actors;
	const int SHAPE_COUNT = 3;
};