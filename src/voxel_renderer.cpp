#include "voxel_renderer.h"

int chunk_attrs[] = {3,2,4, 0};

VoxelRenderer::VoxelRenderer(size_t capacity) : capacity(capacity) {
	buffer = new float[capacity * VERTEX_SIZE * 6];
}

VoxelRenderer::~VoxelRenderer(){
	delete[] buffer;
}

inline void _renderBlock(float* buffer, int x, int y, int z, const Chunk** chunks, voxel vox, size_t& index){
	unsigned int id = vox.id;

	if (!id){
		return;
	}

	float l;
	float uvsize = 1.0f/16.0f;

	Block* block = Block::blocks[id];
	unsigned char group = block->drawGroup;

	if (!IS_BLOCKED(x,y+1,z,group)){
		l = 1.0f;

		SETUP_UV(block->textureFaces[3]);

		float lr = LIGHT(x,y+1,z, 0) / 15.0f;
		float lg = LIGHT(x,y+1,z, 1) / 15.0f;
		float lb = LIGHT(x,y+1,z, 2) / 15.0f;
		float ls = LIGHT(x,y+1,z, 3) / 15.0f;

		float lr0 = (LIGHT(x-1,y+1,z,0) + lr*30 + LIGHT(x-1,y+1,z-1,0) + LIGHT(x,y+1,z-1,0)) / 5.0f / 15.0f;
		float lr1 = (LIGHT(x-1,y+1,z,0) + lr*30 + LIGHT(x-1,y+1,z+1,0) + LIGHT(x,y+1,z+1,0)) / 5.0f / 15.0f;
		float lr2 = (LIGHT(x+1,y+1,z,0) + lr*30 + LIGHT(x+1,y+1,z+1,0) + LIGHT(x,y+1,z+1,0)) / 5.0f / 15.0f;
		float lr3 = (LIGHT(x+1,y+1,z,0) + lr*30 + LIGHT(x+1,y+1,z-1,0) + LIGHT(x,y+1,z-1,0)) / 5.0f / 15.0f;

		float lg0 = (LIGHT(x-1,y+1,z,1) + lg*30 + LIGHT(x-1,y+1,z-1,1) + LIGHT(x,y+1,z-1,1)) / 5.0f / 15.0f;
		float lg1 = (LIGHT(x-1,y+1,z,1) + lg*30 + LIGHT(x-1,y+1,z+1,1) + LIGHT(x,y+1,z+1,1)) / 5.0f / 15.0f;
		float lg2 = (LIGHT(x+1,y+1,z,1) + lg*30 + LIGHT(x+1,y+1,z+1,1) + LIGHT(x,y+1,z+1,1)) / 5.0f / 15.0f;
		float lg3 = (LIGHT(x+1,y+1,z,1) + lg*30 + LIGHT(x+1,y+1,z-1,1) + LIGHT(x,y+1,z-1,1)) / 5.0f / 15.0f;

		float lb0 = (LIGHT(x-1,y+1,z,2) + lb*30 + LIGHT(x-1,y+1,z-1,2) + LIGHT(x,y+1,z-1,2)) / 5.0f / 15.0f;
		float lb1 = (LIGHT(x-1,y+1,z,2) + lb*30 + LIGHT(x-1,y+1,z+1,2) + LIGHT(x,y+1,z+1,2)) / 5.0f / 15.0f;
		float lb2 = (LIGHT(x+1,y+1,z,2) + lb*30 + LIGHT(x+1,y+1,z+1,2) + LIGHT(x,y+1,z+1,2)) / 5.0f / 15.0f;
		float lb3 = (LIGHT(x+1,y+1,z,2) + lb*30 + LIGHT(x+1,y+1,z-1,2) + LIGHT(x,y+1,z-1,2)) / 5.0f / 15.0f;

		float ls0 = (LIGHT(x-1,y+1,z,3) + ls*30 + LIGHT(x-1,y+1,z-1,3) + LIGHT(x,y+1,z-1,3)) / 5.0f / 15.0f;
		float ls1 = (LIGHT(x-1,y+1,z,3) + ls*30 + LIGHT(x-1,y+1,z+1,3) + LIGHT(x,y+1,z+1,3)) / 5.0f / 15.0f;
		float ls2 = (LIGHT(x+1,y+1,z,3) + ls*30 + LIGHT(x+1,y+1,z+1,3) + LIGHT(x,y+1,z+1,3)) / 5.0f / 15.0f;
		float ls3 = (LIGHT(x+1,y+1,z,3) + ls*30 + LIGHT(x+1,y+1,z-1,3) + LIGHT(x,y+1,z-1,3)) / 5.0f / 15.0f;

		VERTEX(index, x-0.5f, y+0.5f, z-0.5f, u2,v1, lr0, lg0, lb0, ls0);
		VERTEX(index, x-0.5f, y+0.5f, z+0.5f, u2,v2, lr1, lg1, lb1, ls1);
		VERTEX(index, x+0.5f, y+0.5f, z+0.5f, u1,v2, lr2, lg2, lb2, ls2);

		VERTEX(index, x-0.5f, y+0.5f, z-0.5f, u2,v1, lr0, lg0, lb0, ls0);
		VERTEX(index, x+0.5f, y+0.5f, z+0.5f, u1,v2, lr2, lg2, lb2, ls2);
		VERTEX(index, x+0.5f, y+0.5f, z-0.5f, u1,v1, lr3, lg3, lb3, ls3);
	}
	if (!IS_BLOCKED(x,y-1,z,group)){
		l = 0.75f;

		SETUP_UV(block->textureFaces[2]);

		float lr = LIGHT(x,y-1,z, 0) / 15.0f;
		float lg = LIGHT(x,y-1,z, 1) / 15.0f;
		float lb = LIGHT(x,y-1,z, 2) / 15.0f;
		float ls = LIGHT(x,y-1,z, 3) / 15.0f;

		float lr0 = (LIGHT(x-1,y-1,z-1,0) + lr*30 + LIGHT(x-1,y-1,z,0) + LIGHT(x,y-1,z-1,0)) / 5.0f / 15.0f;
		float lr1 = (LIGHT(x+1,y-1,z+1,0) + lr*30 + LIGHT(x+1,y-1,z,0) + LIGHT(x,y-1,z+1,0)) / 5.0f / 15.0f;
		float lr2 = (LIGHT(x-1,y-1,z+1,0) + lr*30 + LIGHT(x-1,y-1,z,0) + LIGHT(x,y-1,z+1,0)) / 5.0f / 15.0f;
		float lr3 = (LIGHT(x+1,y-1,z-1,0) + lr*30 + LIGHT(x+1,y-1,z,0) + LIGHT(x,y-1,z-1,0)) / 5.0f / 15.0f;

		float lg0 = (LIGHT(x-1,y-1,z-1,1) + lg*30 + LIGHT(x-1,y-1,z,1) + LIGHT(x,y-1,z-1,1)) / 5.0f / 15.0f;
		float lg1 = (LIGHT(x+1,y-1,z+1,1) + lg*30 + LIGHT(x+1,y-1,z,1) + LIGHT(x,y-1,z+1,1)) / 5.0f / 15.0f;
		float lg2 = (LIGHT(x-1,y-1,z+1,1) + lg*30 + LIGHT(x-1,y-1,z,1) + LIGHT(x,y-1,z+1,1)) / 5.0f / 15.0f;
		float lg3 = (LIGHT(x+1,y-1,z-1,1) + lg*30 + LIGHT(x+1,y-1,z,1) + LIGHT(x,y-1,z-1,1)) / 5.0f / 15.0f;

		float lb0 = (LIGHT(x-1,y-1,z-1,2) + lb*30 + LIGHT(x-1,y-1,z,2) + LIGHT(x,y-1,z-1,2)) / 5.0f / 15.0f;
		float lb1 = (LIGHT(x+1,y-1,z+1,2) + lb*30 + LIGHT(x+1,y-1,z,2) + LIGHT(x,y-1,z+1,2)) / 5.0f / 15.0f;
		float lb2 = (LIGHT(x-1,y-1,z+1,2) + lb*30 + LIGHT(x-1,y-1,z,2) + LIGHT(x,y-1,z+1,2)) / 5.0f / 15.0f;
		float lb3 = (LIGHT(x+1,y-1,z-1,2) + lb*30 + LIGHT(x+1,y-1,z,2) + LIGHT(x,y-1,z-1,2)) / 5.0f / 15.0f;

		float ls0 = (LIGHT(x-1,y-1,z-1,3) + ls*30 + LIGHT(x-1,y-1,z,3) + LIGHT(x,y-1,z-1,3)) / 5.0f / 15.0f;
		float ls1 = (LIGHT(x+1,y-1,z+1,3) + ls*30 + LIGHT(x+1,y-1,z,3) + LIGHT(x,y-1,z+1,3)) / 5.0f / 15.0f;
		float ls2 = (LIGHT(x-1,y-1,z+1,3) + ls*30 + LIGHT(x-1,y-1,z,3) + LIGHT(x,y-1,z+1,3)) / 5.0f / 15.0f;
		float ls3 = (LIGHT(x+1,y-1,z-1,3) + ls*30 + LIGHT(x+1,y-1,z,3) + LIGHT(x,y-1,z-1,3)) / 5.0f / 15.0f;

		VERTEX(index, x-0.5f, y-0.5f, z-0.5f, u1,v1, lr0,lg0,lb0,ls0);
		VERTEX(index, x+0.5f, y-0.5f, z+0.5f, u2,v2, lr1,lg1,lb1,ls1);
		VERTEX(index, x-0.5f, y-0.5f, z+0.5f, u1,v2, lr2,lg2,lb2,ls2);

		VERTEX(index, x-0.5f, y-0.5f, z-0.5f, u1,v1, lr0,lg0,lb0,ls0);
		VERTEX(index, x+0.5f, y-0.5f, z-0.5f, u2,v1, lr3,lg3,lb3,ls3);
		VERTEX(index, x+0.5f, y-0.5f, z+0.5f, u2,v2, lr1,lg1,lb1,ls1);
	}

	if (!IS_BLOCKED(x+1,y,z,group)){
		l = 0.95f;

		SETUP_UV(block->textureFaces[1]);

		float lr = LIGHT(x+1,y,z, 0) / 15.0f;
		float lg = LIGHT(x+1,y,z, 1) / 15.0f;
		float lb = LIGHT(x+1,y,z, 2) / 15.0f;
		float ls = LIGHT(x+1,y,z, 3) / 15.0f;

		float lr0 = (LIGHT(x+1,y-1,z-1,0) + lr*30 + LIGHT(x+1,y,z-1,0) + LIGHT(x+1,y-1,z,0)) / 5.0f / 15.0f;
		float lr1 = (LIGHT(x+1,y+1,z-1,0) + lr*30 + LIGHT(x+1,y,z-1,0) + LIGHT(x+1,y+1,z,0)) / 5.0f / 15.0f;
		float lr2 = (LIGHT(x+1,y+1,z+1,0) + lr*30 + LIGHT(x+1,y,z+1,0) + LIGHT(x+1,y+1,z,0)) / 5.0f / 15.0f;
		float lr3 = (LIGHT(x+1,y-1,z+1,0) + lr*30 + LIGHT(x+1,y,z+1,0) + LIGHT(x+1,y-1,z,0)) / 5.0f / 15.0f;

		float lg0 = (LIGHT(x+1,y-1,z-1,1) + lg*30 + LIGHT(x+1,y,z-1,1) + LIGHT(x+1,y-1,z,1)) / 5.0f / 15.0f;
		float lg1 = (LIGHT(x+1,y+1,z-1,1) + lg*30 + LIGHT(x+1,y,z-1,1) + LIGHT(x+1,y+1,z,1)) / 5.0f / 15.0f;
		float lg2 = (LIGHT(x+1,y+1,z+1,1) + lg*30 + LIGHT(x+1,y,z+1,1) + LIGHT(x+1,y+1,z,1)) / 5.0f / 15.0f;
		float lg3 = (LIGHT(x+1,y-1,z+1,1) + lg*30 + LIGHT(x+1,y,z+1,1) + LIGHT(x+1,y-1,z,1)) / 5.0f / 15.0f;

		float lb0 = (LIGHT(x+1,y-1,z-1,2) + lb*30 + LIGHT(x+1,y,z-1,2) + LIGHT(x+1,y-1,z,2)) / 5.0f / 15.0f;
		float lb1 = (LIGHT(x+1,y+1,z-1,2) + lb*30 + LIGHT(x+1,y,z-1,2) + LIGHT(x+1,y+1,z,2)) / 5.0f / 15.0f;
		float lb2 = (LIGHT(x+1,y+1,z+1,2) + lb*30 + LIGHT(x+1,y,z+1,2) + LIGHT(x+1,y+1,z,2)) / 5.0f / 15.0f;
		float lb3 = (LIGHT(x+1,y-1,z+1,2) + lb*30 + LIGHT(x+1,y,z+1,2) + LIGHT(x+1,y-1,z,2)) / 5.0f / 15.0f;

		float ls0 = (LIGHT(x+1,y-1,z-1,3) + ls*30 + LIGHT(x+1,y,z-1,3) + LIGHT(x+1,y-1,z,3)) / 5.0f / 15.0f;
		float ls1 = (LIGHT(x+1,y+1,z-1,3) + ls*30 + LIGHT(x+1,y,z-1,3) + LIGHT(x+1,y+1,z,3)) / 5.0f / 15.0f;
		float ls2 = (LIGHT(x+1,y+1,z+1,3) + ls*30 + LIGHT(x+1,y,z+1,3) + LIGHT(x+1,y+1,z,3)) / 5.0f / 15.0f;
		float ls3 = (LIGHT(x+1,y-1,z+1,3) + ls*30 + LIGHT(x+1,y,z+1,3) + LIGHT(x+1,y-1,z,3)) / 5.0f / 15.0f;

		VERTEX(index, x+0.5f, y-0.5f, z-0.5f, u2,v1, lr0,lg0,lb0,ls0);
		VERTEX(index, x+0.5f, y+0.5f, z-0.5f, u2,v2, lr1,lg1,lb1,ls1);
		VERTEX(index, x+0.5f, y+0.5f, z+0.5f, u1,v2, lr2,lg2,lb2,ls2);

		VERTEX(index, x+0.5f, y-0.5f, z-0.5f, u2,v1, lr0,lg0,lb0,ls0);
		VERTEX(index, x+0.5f, y+0.5f, z+0.5f, u1,v2, lr2,lg2,lb2,ls2);
		VERTEX(index, x+0.5f, y-0.5f, z+0.5f, u1,v1, lr3,lg3,lb3,ls3);
	}
	if (!IS_BLOCKED(x-1,y,z,group)){
		l = 0.85f;

		SETUP_UV(block->textureFaces[0]);

		float lr = LIGHT(x-1,y,z, 0) / 15.0f;
		float lg = LIGHT(x-1,y,z, 1) / 15.0f;
		float lb = LIGHT(x-1,y,z, 2) / 15.0f;
		float ls = LIGHT(x-1,y,z, 3) / 15.0f;

		float lr0 = (LIGHT(x-1,y-1,z-1,0) + lr*30 + LIGHT(x-1,y,z-1,0) + LIGHT(x-1,y-1,z,0)) / 5.0f / 15.0f;
		float lr1 = (LIGHT(x-1,y+1,z+1,0) + lr*30 + LIGHT(x-1,y,z+1,0) + LIGHT(x-1,y+1,z,0)) / 5.0f / 15.0f;
		float lr2 = (LIGHT(x-1,y+1,z-1,0) + lr*30 + LIGHT(x-1,y,z-1,0) + LIGHT(x-1,y+1,z,0)) / 5.0f / 15.0f;
		float lr3 = (LIGHT(x-1,y-1,z+1,0) + lr*30 + LIGHT(x-1,y,z+1,0) + LIGHT(x-1,y-1,z,0)) / 5.0f / 15.0f;

		float lg0 = (LIGHT(x-1,y-1,z-1,1) + lg*30 + LIGHT(x-1,y,z-1,1) + LIGHT(x-1,y-1,z,1)) / 5.0f / 15.0f;
		float lg1 = (LIGHT(x-1,y+1,z+1,1) + lg*30 + LIGHT(x-1,y,z+1,1) + LIGHT(x-1,y+1,z,1)) / 5.0f / 15.0f;
		float lg2 = (LIGHT(x-1,y+1,z-1,1) + lg*30 + LIGHT(x-1,y,z-1,1) + LIGHT(x-1,y+1,z,1)) / 5.0f / 15.0f;
		float lg3 = (LIGHT(x-1,y-1,z+1,1) + lg*30 + LIGHT(x-1,y,z+1,1) + LIGHT(x-1,y-1,z,1)) / 5.0f / 15.0f;

		float lb0 = (LIGHT(x-1,y-1,z-1,2) + lb*30 + LIGHT(x-1,y,z-1,2) + LIGHT(x-1,y-1,z,2)) / 5.0f / 15.0f;
		float lb1 = (LIGHT(x-1,y+1,z+1,2) + lb*30 + LIGHT(x-1,y,z+1,2) + LIGHT(x-1,y+1,z,2)) / 5.0f / 15.0f;
		float lb2 = (LIGHT(x-1,y+1,z-1,2) + lb*30 + LIGHT(x-1,y,z-1,2) + LIGHT(x-1,y+1,z,2)) / 5.0f / 15.0f;
		float lb3 = (LIGHT(x-1,y-1,z+1,2) + lb*30 + LIGHT(x-1,y,z+1,2) + LIGHT(x-1,y-1,z,2)) / 5.0f / 15.0f;

		float ls0 = (LIGHT(x-1,y-1,z-1,3) + ls*30 + LIGHT(x-1,y,z-1,3) + LIGHT(x-1,y-1,z,3)) / 5.0f / 15.0f;
		float ls1 = (LIGHT(x-1,y+1,z+1,3) + ls*30 + LIGHT(x-1,y,z+1,3) + LIGHT(x-1,y+1,z,3)) / 5.0f / 15.0f;
		float ls2 = (LIGHT(x-1,y+1,z-1,3) + ls*30 + LIGHT(x-1,y,z-1,3) + LIGHT(x-1,y+1,z,3)) / 5.0f / 15.0f;
		float ls3 = (LIGHT(x-1,y-1,z+1,3) + ls*30 + LIGHT(x-1,y,z+1,3) + LIGHT(x-1,y-1,z,3)) / 5.0f / 15.0f;

		VERTEX(index, x-0.5f, y-0.5f, z-0.5f, u1,v1, lr0,lg0,lb0,ls0);
		VERTEX(index, x-0.5f, y+0.5f, z+0.5f, u2,v2, lr1,lg1,lb1,ls1);
		VERTEX(index, x-0.5f, y+0.5f, z-0.5f, u1,v2, lr2,lg2,lb2,ls2);

		VERTEX(index, x-0.5f, y-0.5f, z-0.5f, u1,v1, lr0,lg0,lb0,ls0);
		VERTEX(index, x-0.5f, y-0.5f, z+0.5f, u2,v1, lr3,lg3,lb3,ls3);
		VERTEX(index, x-0.5f, y+0.5f, z+0.5f, u2,v2, lr1,lg1,lb1,ls1);
	}

	if (!IS_BLOCKED(x,y,z+1,group)){
		l = 0.9f;

		SETUP_UV(block->textureFaces[5]);

		float lr = LIGHT(x,y,z+1, 0) / 15.0f;
		float lg = LIGHT(x,y,z+1, 1) / 15.0f;
		float lb = LIGHT(x,y,z+1, 2) / 15.0f;
		float ls = LIGHT(x,y,z+1, 3) / 15.0f;

		float lr0 = l*(LIGHT(x-1,y-1,z+1,0) + lr*30 + LIGHT(x,y-1,z+1,0) + LIGHT(x-1,y,z+1,0)) / 5.0f / 15.0f;
		float lr1 = l*(LIGHT(x+1,y+1,z+1,0) + lr*30 + LIGHT(x,y+1,z+1,0) + LIGHT(x+1,y,z+1,0)) / 5.0f / 15.0f;
		float lr2 = l*(LIGHT(x-1,y+1,z+1,0) + lr*30 + LIGHT(x,y+1,z+1,0) + LIGHT(x-1,y,z+1,0)) / 5.0f / 15.0f;
		float lr3 = l*(LIGHT(x+1,y-1,z+1,0) + lr*30 + LIGHT(x,y-1,z+1,0) + LIGHT(x+1,y,z+1,0)) / 5.0f / 15.0f;

		float lg0 = l*(LIGHT(x-1,y-1,z+1,1) + lg*30 + LIGHT(x,y-1,z+1,1) + LIGHT(x-1,y,z+1,1)) / 5.0f / 15.0f;
		float lg1 = l*(LIGHT(x+1,y+1,z+1,1) + lg*30 + LIGHT(x,y+1,z+1,1) + LIGHT(x+1,y,z+1,1)) / 5.0f / 15.0f;
		float lg2 = l*(LIGHT(x-1,y+1,z+1,1) + lg*30 + LIGHT(x,y+1,z+1,1) + LIGHT(x-1,y,z+1,1)) / 5.0f / 15.0f;
		float lg3 = l*(LIGHT(x+1,y-1,z+1,1) + lg*30 + LIGHT(x,y-1,z+1,1) + LIGHT(x+1,y,z+1,1)) / 5.0f / 15.0f;

		float lb0 = l*(LIGHT(x-1,y-1,z+1,2) + lb*30 + LIGHT(x,y-1,z+1,2) + LIGHT(x-1,y,z+1,2)) / 5.0f / 15.0f;
		float lb1 = l*(LIGHT(x+1,y+1,z+1,2) + lb*30 + LIGHT(x,y+1,z+1,2) + LIGHT(x+1,y,z+1,2)) / 5.0f / 15.0f;
		float lb2 = l*(LIGHT(x-1,y+1,z+1,2) + lb*30 + LIGHT(x,y+1,z+1,2) + LIGHT(x-1,y,z+1,2)) / 5.0f / 15.0f;
		float lb3 = l*(LIGHT(x+1,y-1,z+1,2) + lb*30 + LIGHT(x,y-1,z+1,2) + LIGHT(x+1,y,z+1,2)) / 5.0f / 15.0f;

		float ls0 = l*(LIGHT(x-1,y-1,z+1,3) + ls*30 + LIGHT(x,y-1,z+1,3) + LIGHT(x-1,y,z+1,3)) / 5.0f / 15.0f;
		float ls1 = l*(LIGHT(x+1,y+1,z+1,3) + ls*30 + LIGHT(x,y+1,z+1,3) + LIGHT(x+1,y,z+1,3)) / 5.0f / 15.0f;
		float ls2 = l*(LIGHT(x-1,y+1,z+1,3) + ls*30 + LIGHT(x,y+1,z+1,3) + LIGHT(x-1,y,z+1,3)) / 5.0f / 15.0f;
		float ls3 = l*(LIGHT(x+1,y-1,z+1,3) + ls*30 + LIGHT(x,y-1,z+1,3) + LIGHT(x+1,y,z+1,3)) / 5.0f / 15.0f;

		VERTEX(index, x-0.5f, y-0.5f, z+0.5f, u1,v1, lr0,lg0,lb0,ls0);
		VERTEX(index, x+0.5f, y+0.5f, z+0.5f, u2,v2, lr1,lg1,lb1,ls1);
		VERTEX(index, x-0.5f, y+0.5f, z+0.5f, u1,v2, lr2,lg2,lb2,ls2);

		VERTEX(index, x-0.5f, y-0.5f, z+0.5f, u1,v1, lr0,lg0,lb0,ls0);
		VERTEX(index, x+0.5f, y-0.5f, z+0.5f, u2,v1, lr3,lg3,lb3,ls3);
		VERTEX(index, x+0.5f, y+0.5f, z+0.5f, u2,v2, lr1,lg1,lb1,ls1);
	}
	if (!IS_BLOCKED(x,y,z-1,group)){
		l = 0.8f;

		SETUP_UV(block->textureFaces[4]);

		float lr = LIGHT(x,y,z-1, 0) / 15.0f;
		float lg = LIGHT(x,y,z-1, 1) / 15.0f;
		float lb = LIGHT(x,y,z-1, 2) / 15.0f;
		float ls = LIGHT(x,y,z-1, 3) / 15.0f;

		float lr0 = l*(LIGHT(x-1,y-1,z-1,0) + lr*30 + LIGHT(x,y-1,z-1,0) + LIGHT(x-1,y,z-1,0)) / 5.0f / 15.0f;
		float lr1 = l*(LIGHT(x-1,y+1,z-1,0) + lr*30 + LIGHT(x,y+1,z-1,0) + LIGHT(x-1,y,z-1,0)) / 5.0f / 15.0f;
		float lr2 = l*(LIGHT(x+1,y+1,z-1,0) + lr*30 + LIGHT(x,y+1,z-1,0) + LIGHT(x+1,y,z-1,0)) / 5.0f / 15.0f;
		float lr3 = l*(LIGHT(x+1,y-1,z-1,0) + lr*30 + LIGHT(x,y-1,z-1,0) + LIGHT(x+1,y,z-1,0)) / 5.0f / 15.0f;

		float lg0 = l*(LIGHT(x-1,y-1,z-1,1) + lg*30 + LIGHT(x,y-1,z-1,1) + LIGHT(x-1,y,z-1,1)) / 5.0f / 15.0f;
		float lg1 = l*(LIGHT(x-1,y+1,z-1,1) + lg*30 + LIGHT(x,y+1,z-1,1) + LIGHT(x-1,y,z-1,1)) / 5.0f / 15.0f;
		float lg2 = l*(LIGHT(x+1,y+1,z-1,1) + lg*30 + LIGHT(x,y+1,z-1,1) + LIGHT(x+1,y,z-1,1)) / 5.0f / 15.0f;
		float lg3 = l*(LIGHT(x+1,y-1,z-1,1) + lg*30 + LIGHT(x,y-1,z-1,1) + LIGHT(x+1,y,z-1,1)) / 5.0f / 15.0f;

		float lb0 = l*(LIGHT(x-1,y-1,z-1,2) + lb*30 + LIGHT(x,y-1,z-1,2) + LIGHT(x-1,y,z-1,2)) / 5.0f / 15.0f;
		float lb1 = l*(LIGHT(x-1,y+1,z-1,2) + lb*30 + LIGHT(x,y+1,z-1,2) + LIGHT(x-1,y,z-1,2)) / 5.0f / 15.0f;
		float lb2 = l*(LIGHT(x+1,y+1,z-1,2) + lb*30 + LIGHT(x,y+1,z-1,2) + LIGHT(x+1,y,z-1,2)) / 5.0f / 15.0f;
		float lb3 = l*(LIGHT(x+1,y-1,z-1,2) + lb*30 + LIGHT(x,y-1,z-1,2) + LIGHT(x+1,y,z-1,2)) / 5.0f / 15.0f;

		float ls0 = l*(LIGHT(x-1,y-1,z-1,3) + ls*30 + LIGHT(x,y-1,z-1,3) + LIGHT(x-1,y,z-1,3)) / 5.0f / 15.0f;
		float ls1 = l*(LIGHT(x-1,y+1,z-1,3) + ls*30 + LIGHT(x,y+1,z-1,3) + LIGHT(x-1,y,z-1,3)) / 5.0f / 15.0f;
		float ls2 = l*(LIGHT(x+1,y+1,z-1,3) + ls*30 + LIGHT(x,y+1,z-1,3) + LIGHT(x+1,y,z-1,3)) / 5.0f / 15.0f;
		float ls3 = l*(LIGHT(x+1,y-1,z-1,3) + ls*30 + LIGHT(x,y-1,z-1,3) + LIGHT(x+1,y,z-1,3)) / 5.0f / 15.0f;

		VERTEX(index, x-0.5f, y-0.5f, z-0.5f, u2,v1, lr0,lg0,lb0,ls0);
		VERTEX(index, x-0.5f, y+0.5f, z-0.5f, u2,v2, lr1,lg1,lb1,ls1);
		VERTEX(index, x+0.5f, y+0.5f, z-0.5f, u1,v2, lr2,lg2,lb2,ls2);

		VERTEX(index, x-0.5f, y-0.5f, z-0.5f, u2,v1, lr0,lg0,lb0,ls0);
		VERTEX(index, x+0.5f, y+0.5f, z-0.5f, u1,v2, lr2,lg2,lb2,ls2);
		VERTEX(index, x+0.5f, y-0.5f, z-0.5f, u1,v1, lr3,lg3,lb3,ls3);
	}
}

Mesh* VoxelRenderer::render(Chunk* chunk, const Chunk** chunks){
	size_t index = 0;
	for (int y = 0; y < CHUNK_SIZE_H; y++){
		for (int z = 0; z < CHUNK_SIZE_D; z++){
			for (int x = 0; x < CHUNK_SIZE_W; x++){
				voxel vox = chunk->voxels[(y * CHUNK_SIZE_D + z) * CHUNK_SIZE_W + x];
				if (vox.id == 9 || vox.id == 4)
					continue;
				_renderBlock(buffer, x, y, z, chunks, vox, index);
			}
		}
	}

	for (int y = 0; y < CHUNK_SIZE_H; y++){
		for (int z = 0; z < CHUNK_SIZE_D; z++){
			for (int x = 0; x < CHUNK_SIZE_W; x++){
				voxel vox = chunk->voxels[(y * CHUNK_SIZE_D + z) * CHUNK_SIZE_W + x];
				if (vox.id != 9)
					continue;
				_renderBlock(buffer, x, y, z, chunks, vox, index);
			}
		}
	}

	for (int y = 0; y < CHUNK_SIZE_H; y++){
		for (int z = 0; z < CHUNK_SIZE_D; z++){
			for (int x = 0; x < CHUNK_SIZE_W; x++){
				voxel vox = chunk->voxels[(y * CHUNK_SIZE_D + z) * CHUNK_SIZE_W + x];
				if (vox.id != 4)
					continue;
				_renderBlock(buffer, x, y, z, chunks, vox, index);
			}
		}
	}
	return new Mesh(buffer, index / VERTEX_SIZE, chunk_attrs);
}