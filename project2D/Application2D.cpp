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
#include "Spring.h"
#include "SoftBody.h"

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

	//Object Type = Object Type(Elasticity, Position, Velocity, Orientation (IGNORE IF CIRCLE), Mass, Colour, Angular Velocity, Linear Drag, Angular Drag, SHAPE TYPE SPECIFIC VARIABLES)
	
	/*Sphere* ball1 = new Sphere(0.8f, glm::vec2(-15, 0), glm::vec2(0.0f, 0), 4, glm::vec4(1, 0, 0, 1),0,0.1f,0.1f,4);
	Sphere* ball2 = new Sphere(0.8f, glm::vec2(15, 0), glm::vec2(0, 0), 4, glm::vec4(0, 1, 0, 1),0,0.1f,0.1f,4);
	Sphere* ball3 = new Sphere(0.8f, glm::vec2(0, 0), glm::vec2(0, 0), 4, glm::vec4(0, 0, 1, 1),0,0.1f,0.1f,4);*/

	//Box* box = new Box(1,glm::vec2(-20, 0), glm::vec2(25.0f, 0.0f), 0.23, 4, glm::vec4(1, 1, 0, 1), 0,0.1f,0.1f, glm::vec2(4, 4));
	//Box* box1 = new Box(glm::vec2(20, 0), glm::vec2(-25.0f, 0.0f), 3, 4, glm::vec4(1, 1, 1, 1), 0, glm::vec2(4, 4));

	//Spring* spring = new Spring(ball1, ball3, 3, 0, 1);
	
	Plane* plane  = new Plane(0.6f,glm::vec2(0, 1),  -40);
	Plane* plane1 = new Plane(0.6f, glm::vec2(0, -1), -40);
	Plane* plane2 = new Plane(0.6f, glm::vec2(1, 0),  -90);
	Plane* plane3 = new Plane(0.6f, glm::vec2(-1, 0), -90);

	/*m_physicsScene->addActor(ball1);
	m_physicsScene->addActor(ball2);
	m_physicsScene->addActor(ball3);*/
	//m_physicsScene->addActor(box);
	//m_physicsScene->addActor(box1);
	//m_physicsScene->addActor(spring);
	m_physicsScene->addActor(plane);
	m_physicsScene->addActor(plane1);
	m_physicsScene->addActor(plane2);
	m_physicsScene->addActor(plane3);

	//ball3->setKinematic(true);

	//Rope(30);

	std::vector<std::string> sb;
	sb.push_back("000000");
	sb.push_back("000000");
	sb.push_back("00....");
	sb.push_back("00....");
	sb.push_back("000000");
	sb.push_back("000000");

	SoftBody::Build(m_physicsScene, glm::vec2(-50, 0), 5.0f, 10.0f, 10.0f, sb);

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

void Application2D::Rope(int num){
	m_physicsScene->setGravity(glm::vec2(0, -9.82f));

	Sphere* prev = nullptr;

	for (int i = 0; i < num; i++){
		// spawn a sphere to the right and below the previous one, so that the whole rope acts under gravity and swings
		Sphere* sphere = new Sphere(0.8f, glm::vec2(i * 1, 30 - i * 1.5),glm::vec2(0), 10, glm::vec4(1,0, 0, 1), 2, 0.1f, 0.1f, 0.8f);

		if (i == 0) {
			sphere->setKinematic(true);
		}
		m_physicsScene->addActor(sphere);
		if (prev)
			m_physicsScene->addActor(new Spring(sphere, prev, 900, 10, 0.4f));
		prev = sphere;
	}
	// add a kinematic box at an angle for the rope to drape over
	Box* box = new Box(0.8f,glm::vec2(0, -20), glm::vec2(0), 0.3f, 20, glm::vec4(0, 0, 1, 1),3, 0.1f, 0.1f, glm::vec2(8, 2));
	box->setKinematic(true);
	m_physicsScene->addActor(box);
}