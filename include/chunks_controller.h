#ifndef CHUNKSCONTROLLER_H
# define CHUNKSCONTROLLER_H

# define MIN_SURROUNDING 9

# include <thread>
# include <iostream>

# include "chunk.h"
# include "chunks.h"
# include "world_generator.h"
# include "mesh.h"
# include "voxel_renderer.h"
# include "lighting.h"
# include "world_files.h"
# include "chunks_loader.h"

class Chunks;
class Lighting;
class WorldFiles;
class VoxelRenderer;
class ChunksLoader;

class ChunksController {
private:
	Chunks* chunks;
	Lighting* lighting;
	ChunksLoader** loaders;
	int loadersCount;
public:
	ChunksController(Chunks* chunks, Lighting* lighting, int seed);
	~ChunksController();

	int countFreeLoaders();
	bool loadVisible(WorldFiles* worldFiles);
	bool _buildMeshes(VoxelRenderer* renderer);
};

#endif 