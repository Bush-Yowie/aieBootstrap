#include "Box.h"
#include <iostream>

Box::Box(float elasticity, glm::vec2 position, glm::vec2 velocity, float orientation, float mass, glm::vec4 colour, float angularVelocity, float linearDrag, float angularDrag, glm::vec2 extents) : Rigidbody(BOX, elasticity, position, velocity, orientation, mass, angularVelocity, (1.0f / 12.0f * mass * (extents.x*2) * (extents.y * 2)), linearDrag, angularDrag) {
	m_colour = colour;
	m_extents = extents;
	/*m_localX = glm::vec2(0, 0);
	m_localY = glm::vec2(0, 0);*/
}

//void Box::fixedUpdate(glm::vec2 gravity, float timeStep){
//	Rigidbody::fixedUpdate(gravity, timeStep);
//	//store the local axes
//	/*float cs = cosf(m_orientation);
//	float sn = sinf(m_orientation);
//	m_localX = glm::normalize(glm::vec2(cs, sn));
//	m_localY = glm::normalize(glm::vec2(-sn, cs));*/
//    //std::cout << "Box pos: " << m_position.x << ", " << m_position.y << std::endl;
//}

void Box::draw(){
	// if only using rotation
	// glm::mat4 transform = glm::rotate(m_rotation, glm::vec3(0, 0, 1));
	// aie::Gizmos::add2DAABBFilled(getCenter(),
	// m_extents, m_colour, &transform);
	// draw using local axes
	glm::vec2 p1 = m_position - m_localX * m_extents.x - m_localY * m_extents.y;
	glm::vec2 p2 = m_position + m_localX * m_extents.x - m_localY * m_extents.y;
	glm::vec2 p3 = m_position - m_localX * m_extents.x + m_localY * m_extents.y;
	glm::vec2 p4 = m_position + m_localX * m_extents.x + m_localY * m_extents.y;
	aie::Gizmos::add2DTri(p1, p2, p4, m_colour);
	aie::Gizmos::add2DTri(p1, p4, p3, m_colour);
}

// check if any of the other box's corners are inside this box
bool Box::checkBoxCorners(Box& box, glm::vec2& contact, int& numContacts, float& pen, glm::vec2& edgeNormal){
    float minX, maxX, minY, maxY;

    float boxW = box.getExtents().x * 2;
    float boxH = box.getExtents().y * 2;

    int numLocalContacts = 0;

    glm::vec2 localContact(0, 0);

    bool first = true;

    // loop over all corners of the other box
    for (float x = -box.getExtents().x; x < boxW; x += boxW)
    {
        for (float y = -box.getExtents().y; y < boxH; y += boxH)
        {
            // get the position in worldspace
            glm::vec2 p = box.getPosition() + x * box.m_localX + y * box.m_localY;
            // get the position in our box's space
            glm::vec2 p0(glm::dot(p - m_position, m_localX),
                glm::dot(p - m_position, m_localY));
            // update the extents in each cardinal direction in our box's space
            // (ie extents along the separating axes)
            if (first || p0.x < minX) { 
                minX = p0.x;
            }
            if (first || p0.x > maxX) { 
                maxX = p0.x; 
            }
            if (first || p0.y < minY) { 
                minY = p0.y;
            }
            if (first || p0.y > maxY) { 
                maxY = p0.y; 
            }

            // if this corner is inside the box, add it to the list of contact points
            if (p0.x >= -m_extents.x && p0.x <= m_extents.x && p0.y >= -m_extents.y && p0.y <= m_extents.y){
                numLocalContacts++;

                localContact += p0;
            }

            first = false;
        }
    }

    // if we lie entirely to one side of the box along one axis, we've found a separating axis, and we can exit
    if (maxX <= -m_extents.x || minX >= m_extents.x || maxY <= -m_extents.y || minY >= m_extents.y) {
        return false;
    }

    if (numLocalContacts == 0) {
        return false;
    }

    bool res = false;

    contact += m_position + (localContact.x * m_localX + localContact.y * m_localY) / (float)numLocalContacts;

    numContacts++;

    // find the minimum penetration vector as a penetration amount and normal
    float pen0 = m_extents.x - minX;
    if (pen0 > 0 && (pen0 < pen || pen == 0)) {
        edgeNormal = m_localX;
        pen = pen0;
        res = true;
    }
    pen0 = maxX + m_extents.x;
    if (pen0 > 0 && (pen0 < pen || pen == 0)) {
        edgeNormal = -m_localX;
        pen = pen0;
        res = true;
    }
    pen0 = m_extents.y - minY;
    if (pen0 > 0 && (pen0 < pen || pen == 0)) {
        edgeNormal = m_localY;
        pen = pen0;
        res = true;
    }
    pen0 = maxY + m_extents.y;
    if (pen0 > 0 && (pen0 < pen || pen == 0)) {
        edgeNormal = -m_localY;
        pen = pen0;
        res = true;
    }
    return res;
}