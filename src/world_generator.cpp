#define FNL_IMPL
#include "world_generator.h"
#include "FastNoiseLite.h"

float calc_height(fnl_state *noise, int real_x, int real_z){
	const float s = 0.2f;
	float height = fnlGetNoise3D(noise, real_x*0.0125f*s*32,real_z*0.0125f*s*32, 0.0f);
	height += fnlGetNoise3D(noise, real_x*0.025f*s*32,real_z*0.025f*s*32, 0.0f)*0.5f;
	height += fnlGetNoise3D(noise, real_x*0.05f*s*32,real_z*0.05f*s*32, 0.0f)*0.25f;
	height += fnlGetNoise3D(noise, real_x*0.1f*s*32,real_z*0.1f*s*32, 0.0f)*0.225f;
	height += fnlGetNoise3D(noise, real_x*0.2f*s*32,real_z*0.2f*s*32, 0.0f)*0.125f;
	height += fnlGetNoise3D(noise, real_x*0.4f*s*32,real_z*0.4f*s*32, 0.0f)*0.125f*0.5F;
	height = height * 0.5f + 0.5f;
	height *= height;
	height *= (140.0f)*0.12f/s;
	height += (42)*0.12f/s;
	return height;
}

void WorldGenerator::generate(voxel* voxels, int cx, int cy, int cz, int seed){
	fnl_state noise = fnlCreateState();
	noise.noise_type = FNL_NOISE_OPENSIMPLEX2;
	noise.seed = seed;

	fnl_state worm1 = fnlCreateState();
	worm1.noise_type = FNL_NOISE_PERLIN;
	worm1.seed = seed;
	worm1.frequency = 0.05;
	worm1.octaves = 8;
	worm1.lacunarity = 0.1;
	worm1.gain = 10.45;
	
	fnl_state worm2 = fnlCreateState();
	worm2.noise_type = FNL_NOISE_PERLIN;
	worm2.seed = seed;
	worm2.frequency = 0.02;
	worm2.octaves = 4;
	worm2.lacunarity = 0.01;
	worm2.gain = 0.45;

	for (int z = 0; z < CHUNK_SIZE_D; z++){
		int real_z = z + cz * CHUNK_SIZE_D;
		for (int x = 0; x < CHUNK_SIZE_W; x++){
			int real_x = x + cx * CHUNK_SIZE_W;
			float height = calc_height(&noise, real_x, real_z);
			for (int y = 0; y < CHUNK_SIZE_H; y++){
				int real_y = y + cy * CHUNK_SIZE_H;
				
				int id = 0;
				//*
				if (real_y == (int)height) {
					if (real_y < 50)
						id = 10;
					else
						id = 2;

				}
				else if (real_y < height){
					if (real_y < height-6)
						id = 8;
					else
						id = 1;
				}
				//*/
				
				if (real_y < height){
					float worm_height;
					if (height > 100) {
						worm_height = abs(fnlGetNoise3D(&worm2, real_x,real_y * 3, real_z*0.5));
					} else {
						worm_height = abs(fnlGetNoise3D(&worm1, real_x*0.5,real_y * 3, real_z));
					}
					if (worm_height < 0.9 && worm_height > 0.5)
						id = 0;
				}
				if (id == 0 && real_y < 48)
					id = 9;
				if (real_y <= 2)
					id = 8;
				voxels[(y * CHUNK_SIZE_D + z) * CHUNK_SIZE_W + x].id = id;
			}
		}
	}
}