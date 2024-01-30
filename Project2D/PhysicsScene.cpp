#include "PhysicsScene.h"

void PhysicsScene::addActor(PhysicsObject* actor) {
	m_actors.push_back(actor);
}

//Uses the erase-remove idiom to delete the desired pointer from the vector (The shouldnt be duplicates anyway, however if there are, all copies will be deleted)
void PhysicsScene::removeActor(PhysicsObject* actor) {
	m_actors.erase(std::remove(m_actors.begin(), m_actors.end(), actor));
}

PhysicsScene::PhysicsScene() : m_timeStep(0.01f), m_gravity(glm::vec2(0, 0)){
}

void PhysicsScene::update(float dt){
    // update physics at a fixed time step
    static float accumulatedTime = 0.0f;
    accumulatedTime += dt;

    while (accumulatedTime >= m_timeStep){
        for (auto pActor : m_actors){
            pActor->fixedUpdate(m_gravity, m_timeStep);
        }
        accumulatedTime -= m_timeStep;
    }
}

void PhysicsScene::draw(){
    for (auto pActor : m_actors) {
        pActor->draw();
    }
}