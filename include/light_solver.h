#ifndef LIGHT_SOLVER_H
#define LIGHT_SOLVER_H

#include <queue>

#include "lightmap.h"
#include "chunks.h"
#include "chunk.h"
#include "voxel.h"
#include "block.h"

class Chunks;

struct lightentry {
	int x;
	int y;
	int z;
	unsigned char light;
};

class LightSolver {
	std::queue<lightentry> addqueue;
	std::queue<lightentry> remqueue;
	Chunks* chunks;
	int channel;
public:
	LightSolver(Chunks* chunks, int channel);

	void add(int x, int y, int z);
	void add(int x, int y, int z, int emission);
	void remove(int x, int y, int z);
	void solve();
};

#endif