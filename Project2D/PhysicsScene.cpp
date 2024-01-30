#include "PhysicsScene.h"
#include "Gizmos.h"

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

        // check for collisions (ideally you'd want to have some sort of 
        // scene management in place)
        int actorCount = m_actors.size();

        // need to check for collisions against all objects except this one.
        for (int outer = 0; outer < actorCount - 1; outer++)
        {
            for (int inner = outer + 1; inner < actorCount; inner++)
            {
                PhysicsObject* object1 = m_actors[outer];
                PhysicsObject* object2 = m_actors[inner];

                // for now we can assume both shapes are spheres, 
                // since that is all we’ve implemented for now.
                sphere2Sphere(object1, object2);
            }
        }
    }
}

void PhysicsScene::draw(){
    for (auto pActor : m_actors) {
        pActor->draw();
    }
}

Rigidbody::Rigidbody(ShapeType shapeID, glm::vec2 position, glm::vec2 velocity, float orientation, float mass) {
    m_shapeID = shapeID;
    m_position = position;
    m_velocity = velocity;
    m_orientation = orientation;
    m_mass = mass;
}

//Applies Newton's second law
void Rigidbody::applyForce(glm::vec2 force) {
    m_velocity + ((force.x / m_mass), (force.y / m_mass));
}

//Applies Newton's third law
void Rigidbody::applyForceToActor(Rigidbody* actor2, glm::vec2 force) {
    actor2->applyForce(force);
    this->applyForce(-force);
}

//Apply gravity
void Rigidbody::fixedUpdate(glm::vec2 gravity, float timeStep) {
    m_position += m_velocity * timeStep;
    applyForce(gravity * m_mass * timeStep);
}

Sphere::Sphere(glm::vec2 position, glm::vec2 velocity, float mass, float radius, glm::vec4 colour) : Rigidbody(SPHERE, position, velocity, 0, mass){
    m_radius = radius;
    m_colour = colour;
}

void Sphere::draw() {
    aie::Gizmos::add2DCircle(m_position,m_radius,16,m_colour);
}

bool PhysicsScene::sphere2Sphere(PhysicsObject* obj1, PhysicsObject* obj2){
    // try to cast objects to sphere and sphere
    Sphere* sphere1 = dynamic_cast<Sphere*>(obj1);
    Sphere* sphere2 = dynamic_cast<Sphere*>(obj2);
    // if we are successful then test for collision
    if (sphere1 != nullptr && sphere2 != nullptr){
        if (glm::distance(sphere1->getPosition(), sphere2->getPosition()) <= (sphere1->getRadius() + sphere1->getRadius())) {
            // TODO if the spheres touch, set their velocities to zero for now
            sphere1->setVelocity(0, 0);
            sphere2->setVelocity(0, 0);

            return true;
        }
    }
}

PhysicsScene::~PhysicsScene(){
    for (auto pActor : m_actors)
    {
        delete pActor;
    }
}