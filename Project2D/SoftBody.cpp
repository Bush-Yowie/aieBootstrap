#include "SoftBody.h"
#include "Sphere.h"
#include "Spring.h"

void SoftBody::Build(PhysicsScene* scene, glm::vec2 position, float spacing, float springForce, float damping, std::vector<std::string>& strings) {
	int numColumns = strings.size();
	int numRows = strings[0].length();

	// traverse across the array and add balls where the ascii art says they should be
	Sphere** spheres = new Sphere * [numRows * numColumns];
	for (int i = 0; i < numRows; i++) {
		for (int j = 0; j < numColumns; j++) {
			if (strings[j][i] == '0') {
				spheres[i * numColumns + j] = new Sphere(0.8f, position + glm::vec2(i, j) * spacing, glm::vec2(0, 0), 1.0f, glm::vec4(1, 0, 0, 1), 0, 0.1f, 0.1f, 2.0f);
				scene->addActor(spheres[i * numColumns + j]);
			}
			else {
				spheres[i * numColumns + j] = nullptr;
			}
		}
	}

	// second pass - add springs in
	for (int i = 1; i < numRows; i++) {
		for (int j = 1; j < numColumns; j++) {
			Sphere* s11 = spheres[i * numColumns + j];
			Sphere* s01 = spheres[(i - 1) * numColumns + j];
			Sphere* s10 = spheres[i * numColumns + j - 1];
			Sphere* s00 = spheres[(i - 1) * numColumns + j - 1];

			float restLength = 2.0f;

			// make springs to cardinal neighbours
			if (s11 && s01) {
				scene->addActor(new Spring(s11, s01, springForce, damping, restLength));
			}
			if (s11 && s10) {
				scene->addActor(new Spring(s11, s10, springForce, damping, restLength));
			}
			if (s10 && s00) {
				scene->addActor(new Spring(s10, s00, springForce, damping, restLength));
			}
			if (s01 && s00) {
				scene->addActor(new Spring(s01, s00, springForce, damping, restLength));
			}
		}
	}
}