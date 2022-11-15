#ifndef LIGHTING_H
# define LIGHTING_H

# include "light_solver.h"
# include "lightmap.h"
# include "chunks.h"
# include "chunk.h"
# include "voxel.h"
# include "block.h"

class Chunks;
class LightSolver;

class Lighting {
	Chunks* chunks = nullptr;
	LightSolver* solverR = nullptr;
	LightSolver* solverG = nullptr;
	LightSolver* solverB = nullptr;
	LightSolver* solverS = nullptr;
public:
	Lighting(Chunks* chunks);
	~Lighting();

	void clear();
	void onChunkLoaded(int cx, int cy, int cz, bool sky);
	void onBlockSet(int x, int y, int z, int id);
};

#endif