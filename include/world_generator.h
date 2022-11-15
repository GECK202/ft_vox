#ifndef WORLD_GENERATOR_H
# define WORLD_GENERATOR_H

# include <math.h>
# include <glm/glm.hpp>
# include <glm/gtc/noise.hpp>
# include <time.h>
# include <iostream>

# include "voxel.h"
# include "chunk.h"

class voxel;

class WorldGenerator {
public:
	static void generate(voxel* voxels, int x, int y, int z, int seed);
};

#endif