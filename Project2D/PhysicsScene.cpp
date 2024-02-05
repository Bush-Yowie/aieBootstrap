#include "PhysicsScene.h"
#include "Sphere.h"
#include "Plane.h"



PhysicsScene::PhysicsScene() : m_timeStep(0.01f), m_gravity(glm::vec2(0, 0)){}

PhysicsScene::~PhysicsScene() {
    for (auto pActor : m_actors)
    {
        delete pActor;
    }
}

void PhysicsScene::addActor(PhysicsObject* actor) {
    m_actors.push_back(actor);
}

//Uses the erase-remove idiom to delete the desired pointer from the vector (The shouldnt be duplicates anyway, however if there are, all copies will be deleted)
void PhysicsScene::removeActor(PhysicsObject* actor) {
    m_actors.erase(std::remove(m_actors.begin(), m_actors.end(), actor));
}

// function pointer array for doing our collisions
typedef bool(*fn)(PhysicsObject*, PhysicsObject*);

static fn collisionFunctionArray[] =
{
    PhysicsScene::plane2Plane, PhysicsScene::plane2Sphere,
    PhysicsScene::sphere2Plane, PhysicsScene::sphere2Sphere,
};


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
                int shapeId1 = object1->getShapeID();
                int shapeId2 = object2->getShapeID();

                // using function pointers
                int functionIdx = (shapeId1 * SHAPE_COUNT) + shapeId2;
                fn collisionFunctionPtr = collisionFunctionArray[functionIdx];
                if (collisionFunctionPtr != nullptr)
                {
                    // did a collision occur?
                    collisionFunctionPtr(object1, object2);
                }
            }
        }
    }
}

void PhysicsScene::draw(){
    for (auto pActor : m_actors) {
        pActor->draw();
    }
}

bool PhysicsScene::sphere2Sphere(PhysicsObject* obj1, PhysicsObject* obj2){
    // try to cast objects to sphere and sphere
    Sphere* sphere1 = dynamic_cast<Sphere*>(obj1);
    Sphere* sphere2 = dynamic_cast<Sphere*>(obj2);
    // if we are successful then test for collision
    if (sphere1 != nullptr && sphere2 != nullptr){
        if (glm::distance(sphere1->getPosition(), sphere2->getPosition()) <= (sphere1->getRadius() + sphere1->getRadius())) {
            sphere1->resolveCollision(sphere2);

            return true;
        }
    }
}

bool PhysicsScene::plane2Plane(PhysicsObject*, PhysicsObject*) { 
    return false; 
}

bool PhysicsScene::sphere2Plane(PhysicsObject* obj1, PhysicsObject* obj2){
    Sphere* sphere = dynamic_cast<Sphere*>(obj1);
    Plane* plane = dynamic_cast<Plane*>(obj2);
    //if we are successful then test for collision
    if (sphere != nullptr && plane != nullptr)
    {
        glm::vec2 collisionNormal = plane->getNormal();
        float sphereToPlane = glm::dot(sphere->getPosition(), plane->getNormal()) - plane->getDistance();

        float intersection = sphere->getRadius() - sphereToPlane;
        float velocityOutOfPlane = glm::dot(sphere->getVelocity(), plane->getNormal());
        if (intersection > 0 && velocityOutOfPlane < 0)
        {
            ////set sphere velocity to zero here
            //sphere->applyForce(-sphere->getVelocity() * sphere->getMass());
            plane->resolveCollision(sphere);
            return true;
        }
    }
    return false;
}

bool PhysicsScene::plane2Sphere(PhysicsObject* obj1, PhysicsObject* obj2) {
    // reverse the order of arguments, as obj1 is the plane and obj2 is the sphere
    return sphere2Plane(obj2, obj1);
}