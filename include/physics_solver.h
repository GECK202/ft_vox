#ifndef PHYSICSSOLVER_H
# define PHYSICSSOLVER_H

# define E 0.03
# define DEFAULT_FRICTION 10.0

# include <iostream>
# include <glm/glm.hpp>
# include <glm/ext.hpp>
# include <glm/gtc/matrix_transform.hpp>

# include "chunks.h"
# include "hitbox.h"

using namespace glm;

class Hitbox;
class Chunks;

class PhysicsSolver {
	vec3 gravity;
public:
	PhysicsSolver(vec3 gravity);
	void step(Chunks* chunks, Hitbox* hitbox, float delta, unsigned substeps, bool shifting, float gravityScale);
	bool isBlockInside(int x, int y, int z, Hitbox* hitbox);
};

#endif