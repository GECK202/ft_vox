#ifndef CHUNKS_H
# define CHUNKS_H

# include <stdlib.h>
# include <glm/glm.hpp>
# include <math.h>
# include <limits.h>

# include "chunk.h"
# include "voxel.h"
# include "lightmap.h"
# include "block.h"
# include "world_files.h"
# include "world_generator.h"
# include "mesh.h"

using namespace glm;

class Mesh;
class VoxelRenderer;
class Chunk;
class voxel;
class WorldFiles;

class Chunks {
public:
	Chunk** chunks;
	Chunk** chunksSecond;
	Mesh** meshes;
	Mesh** meshesSecond;
	size_t volume;
	unsigned int w,h,d;
	int ox,oy,oz;

	Chunks(int w, int h, int d, int ox, int oy, int oz);
	~Chunks();

	void _setOffset(int x, int y, int z);

	bool putChunk(Chunk* chunk);
	Chunk* getChunk(int x, int y, int z);
	Chunk* getChunkByVoxel(int x, int y, int z);
	voxel* get(int x, int y, int z);
	unsigned short getLight(int x, int y, int z);
	unsigned char getLight(int x, int y, int z, int channel);
	void set(int x, int y, int z, int id);
	voxel* rayCast(vec3 start, vec3 dir, float maxLength, vec3& end, vec3& norm, vec3& iend);
	bool isObstacle(int x, int y, int z);
	void setCenter(WorldFiles* worldFiles, int x, int y, int z);
	void translate(WorldFiles* worldFiles, int x, int y, int z);
	void clear(bool freeMemory);
};

#endif