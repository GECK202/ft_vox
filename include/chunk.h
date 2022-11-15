#ifndef CHUNK_H
# define CHUNK_H

# define CHUNK_SIZE_W 16
# define CHUNK_SIZE_H 256
# define CHUNK_SIZE_D 16
# define CHUNK_VOL (CHUNK_SIZE_W * CHUNK_SIZE_H * CHUNK_SIZE_D)

# include "voxel.h"
# include "lightmap.h"

class voxel;
class Lightmap;

class Chunk {
public:
	int x,y,z;
	voxel* voxels;
	Lightmap* lightmap;
	bool modified = true;
	bool ready = false;
	bool loaded = false;
	int surrounding = 0;
	int references = 1;
	Chunk(int x, int y, int z);
	~Chunk();

	bool isEmpty();

	void incref();
	void decref();
};

#endif