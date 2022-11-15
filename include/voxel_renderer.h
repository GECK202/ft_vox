#ifndef VOXEL_RENDERER_H
# define VOXEL_RENDERER_H

# define VERTEX_SIZE (3 + 2 + 4)

# include <stdlib.h>
# include "mesh.h"
# include "chunk.h"
# include "voxel.h"
# include "block.h"
# include "lightmap.h"

# define CDIV(X,A) (((X) < 0) ? ((X) / (A) - 1) : ((X) / (A)))
# define LOCAL_NEG(X, SIZE) (((X) < 0) ? ((SIZE)+(X)) : (X))
# define LOCAL(X, SIZE) ((X) >= (SIZE) ? ((X) - (SIZE)) : LOCAL_NEG(X, SIZE))
# define IS_CHUNK(X,Y,Z) (GET_CHUNK(X,Y,Z) != nullptr)
# define GET_CHUNK(X,Y,Z) (chunks[((CDIV(Y, CHUNK_SIZE_H)+1) * 3 + CDIV(Z, CHUNK_SIZE_D) + 1) * 3 + CDIV(X, CHUNK_SIZE_W) + 1])
# define LIGHT(X,Y,Z, CHANNEL) (IS_CHUNK(X,Y,Z) ? GET_CHUNK(X,Y,Z)->lightmap->get(LOCAL(X, CHUNK_SIZE_W), LOCAL(Y, CHUNK_SIZE_H), LOCAL(Z, CHUNK_SIZE_D), (CHANNEL)) : 0)
# define VOXEL(X,Y,Z) (GET_CHUNK(X,Y,Z)->voxels[(LOCAL(Y, CHUNK_SIZE_H) * CHUNK_SIZE_D + LOCAL(Z, CHUNK_SIZE_D)) * CHUNK_SIZE_W + LOCAL(X, CHUNK_SIZE_W)])
# define IS_BLOCKED(X,Y,Z,GROUP) ((!IS_CHUNK(X, Y, Z)) || Block::blocks[VOXEL(X, Y, Z).id]->drawGroup == (GROUP))
# define VERTEX(INDEX, X,Y,Z, U,V, R,G,B,S) buffer[INDEX+0] = (X);\
								  buffer[INDEX+1] = (Y);\
								  buffer[INDEX+2] = (Z);\
								  buffer[INDEX+3] = (U);\
								  buffer[INDEX+4] = (V);\
								  buffer[INDEX+5] = (R);\
								  buffer[INDEX+6] = (G);\
								  buffer[INDEX+7] = (B);\
								  buffer[INDEX+8] = (S);\
								  INDEX += VERTEX_SIZE;
# define SETUP_UV(INDEX) float u1 = ((INDEX) % 16) * uvsize;\
				float v1 = 1-((1 + (INDEX) / 16) * uvsize);\
				float u2 = u1 + uvsize;\
				float v2 = v1 + uvsize;

class Mesh;
class Chunk;

class VoxelRenderer {
	float* buffer;
	size_t capacity;
public:
	VoxelRenderer(size_t capacity);
	~VoxelRenderer();

	Mesh* render(Chunk* chunk, const Chunk** chunks);
};

#endif