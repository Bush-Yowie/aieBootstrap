#include "Application2D.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include <glm\ext.hpp>
#include "Gizmos.h"
#include "Rigidbody.h"
#include "Sphere.h"
#include "Plane.h"
#include "Box.h"

Application2D::Application2D() {}

Application2D::~Application2D() {}

bool Application2D::startup() {
	// increase the 2d line count to maximize the number of objects we can draw
	aie::Gizmos::create(255U, 255U, 65535U, 65535U);

	m_2dRenderer = new aie::Renderer2D();
	m_font = new aie::Font("./font/consolas.ttf", 32);

	m_physicsScene = new PhysicsScene();
	m_physicsScene->setTimeStep(0.01f);

	//m_physicsScene->setGravity(glm::vec2(0, 0));

	//Sphere* ball1 = new Sphere(glm::vec2(-20, 0), glm::vec2(25.0f, 0), 4, 4, glm::vec4(1, 0, 0, 1),0);
	//Sphere* ball2 = new Sphere(glm::vec2(20, 0), glm::vec2(-25.0f,0), 4, 4, glm::vec4(0, 1, 0, 1),0);
	//Sphere* ball3 = new Sphere(glm::vec2(0, 0), glm::vec2(0.0f,0), 4, 4, glm::vec4(0, 1, 1, 1),0);
	Box* box = new Box(glm::vec2(-20, 0), glm::vec2(25.0f, 0.0f), 0, 4, glm::vec4(1, 1, 0, 1), 0, glm::vec2(4, 4));
	//Box* box1 = new Box(glm::vec2(20, 0), glm::vec2(-25.0f, 0.0f), 3, 4, glm::vec4(1, 1, 1, 1), 0, glm::vec2(4, 4));
	Plane* plane  = new Plane(glm::vec2(0, 1),  -40);
	Plane* plane1 = new Plane(glm::vec2(0, -1), -40);
	Plane* plane2 = new Plane(glm::vec2(1, 0),  -90);
	Plane* plane3 = new Plane(glm::vec2(-1, 0), -90);

	//m_physicsScene->addActor(ball1);
	//m_physicsScene->addActor(ball2);
	//m_physicsScene->addActor(ball3);
	m_physicsScene->addActor(box);
	//m_physicsScene->addActor(box1);
	m_physicsScene->addActor(plane);
	m_physicsScene->addActor(plane1);
	m_physicsScene->addActor(plane2);
	m_physicsScene->addActor(plane3);

	//ball1->applyForce(glm::vec2(30.0f, 0));
	//ball2->applyForce(glm::vec2(-15.0f, 0));

	return true;
}

void Application2D::shutdown() {
	delete m_font;
	//delete m_texture;
	//delete m_shipTexture;
	delete m_2dRenderer;
}

void Application2D::update(float deltaTime) {
	// input example
	aie::Input* input = aie::Input::getInstance();

	aie::Gizmos::clear();

	m_physicsScene->update(deltaTime);
	m_physicsScene->draw();

	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

void Application2D::draw() {
	// wipe the screen to the background colour
	clearScreen();

	// begin drawing sprites
	m_2dRenderer->begin();

	// draw your stuff here!
	static float aspectRatio = 16 / 9.f;
	aie::Gizmos::draw2D(glm::ortho<float>(-100, 100, -100 / aspectRatio, 100 / aspectRatio, -1.0f, 1.0f));

	// output some text, uses the last used colour
	m_2dRenderer->drawText(m_font, "Press ESC to quit", 0, 0);
	// done drawing sprites
	m_2dRenderer->end();
}