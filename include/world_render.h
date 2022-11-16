#ifndef WORLD_RENDERER_H
# define WORLD_RENDERER_H

# include <vector>
# include <algorithm>
# include <glad/glad.h>
# include <glm/glm.hpp>
# include <glm/ext.hpp>
# include <glm/gtc/matrix_transform.hpp>

# include "window.h"
# include "camera.h"
# include "mesh.h"
# include "shader.h"
# include "texture.h"
# include "chunks.h"
# include "chunk.h"
# include "cubemap.h"

float _camera_cx;
float _camera_cz;
Chunks* _chunks;

Mesh *crosshair;
Mesh *sky;
Mesh *fps;

float vertices[] = {
		// x    y
	   -0.01f,-0.01f,
	    0.01f, 0.01f,

	   -0.01f, 0.01f,
	    0.01f,-0.01f,
};

int attrs[] = {
		2,  0 //null terminator
};

float sky_vertices[] = {       
        // positions          
        -1.0f,  1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

        -1.0f,  1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f,  1.0f
};

int sky_attrs[] = {
		3,  0 //null terminator
};

float fps_vertices[] = {
//   x   y  №
	-1, -1, 0,
	 1, -1, 0,
	-1,  1, 0,

	 1, -1, 0,
	 1,  1, 0,
	-1,  1, 0,

	-1, -1, 1,
	 1, -1, 1,
	-1,  1, 1,

	 1, -1, 1,
	 1,  1, 1,
	-1,  1, 1,

	-1, -1, 2,
	 1, -1, 2,
	-1,  1, 2,

	 1, -1, 2,
	 1,  1, 2,
	-1,  1, 2,

	-1, -1, 3,
	 1, -1, 3,
	-1,  1, 3,

	 1, -1, 3,
	 1,  1, 3,
	-1,  1, 3,	
};

int fps_attrs[] = {
		2, 1, 0 //null terminator
};

void init_renderer(){
	crosshair = new Mesh(vertices, 4, attrs);
	sky = new Mesh(sky_vertices, 36, sky_attrs);
	fps = new Mesh(fps_vertices, 24, fps_attrs);
}


void finalize_renderer(){
	delete crosshair;
	delete sky;
	delete fps;
}

void draw_chunk(size_t index, Shader* shader){
	Chunk* chunk = _chunks->chunks[index];
	Mesh* mesh = _chunks->meshes[index];
	if (mesh == nullptr)
		return;
	mat4 model = glm::translate(mat4(1.0f), vec3(chunk->x*CHUNK_SIZE_W+0.5f, chunk->y*CHUNK_SIZE_H+0.5f, chunk->z*CHUNK_SIZE_D+0.5f));
	shader->uniformMatrix("u_model", model);
	mesh->draw(GL_TRIANGLES);
}

bool chunks_comparator(size_t i, size_t j) {
	Chunk* a = _chunks->chunks[i];
	Chunk* b = _chunks->chunks[j];
	return ((a->x + 0.5f - _camera_cx)*(a->x + 0.5f - _camera_cx) + (a->z + 0.5f - _camera_cz)*(a->z + 0.5f - _camera_cz)
			>
			(b->x + 0.5f - _camera_cx)*(b->x + 0.5f - _camera_cx) + (b->z + 0.5f - _camera_cz)*(b->z + 0.5f - _camera_cz));
}


void draw_world(Camera* camera, Assets* assets,
				Chunks* chunks, float fps_r){
	glClearColor(0.7f,0.71f,0.73f,1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	_chunks = chunks;

	// Draw VAO
	Texture* texture = assets->getTexture("block");
	Shader* shader = assets->getShader("main");
	Shader* crosshairShader = assets->getShader("crosshair");
	Cubemap* skyCubemap = assets->getCubemap("sky");
	Shader* skyShader = assets->getShader("sky");
	Texture* fpsTexture = assets->getTexture("fps");
	Shader* fpsShader = assets->getShader("fps");

	shader->use();
	shader->uniformMatrix("u_proj", camera->getProjection());
	shader->uniformMatrix("u_view", camera->getView());
	shader->uniform1f("u_gamma", 1.6f);
	shader->uniform3f("u_skyLightColor", 1.8f,1.8f,1.8f);
	shader->uniform3f("u_fogColor", 0.27f,0.36f,0.44f);
	shader->uniform3f("u_cameraPos", camera->position.x,camera->position.y,camera->position.z);
	skyCubemap->bind();
	texture->bind();

	std::vector<size_t> indices;

	for (size_t i = 0; i < chunks->volume; i++){
		Chunk* chunk = chunks->chunks[i];
		if (chunk == nullptr)
			continue;
		if (chunks->meshes[i] != nullptr)
			indices.push_back(i);
	}

	float px = camera->position.x / (float)CHUNK_SIZE_W;
	float pz = camera->position.z / (float)CHUNK_SIZE_D;

	_camera_cx = px;
	_camera_cz = pz;

	std::sort(indices.begin(), indices.end(), chunks_comparator);


	for (size_t i = 0; i < indices.size(); i++){
		draw_chunk(indices[i], shader);
	}

	glDepthFunc(GL_LEQUAL);
	skyShader->use();
	skyShader->uniformMatrix("u_proj", camera->getProjection());
	skyShader->uniformMatrix("u_view", camera->getView());
	skyCubemap->bind();
	sky->draw(GL_TRIANGLES);
	glDepthFunc(GL_LESS);

	float ar = (float)Window::height / (float)Window::width;
	float scale = 1000.0f / (float)Window::height;
	fpsShader->use();
	fpsShader->uniform1f("u_fps", fps_r);
	fpsShader->uniform1f("u_ar", ar);
	fpsShader->uniform1f("u_scale", scale);
	fpsTexture->bind();
	fps->draw(GL_TRIANGLES);

	crosshairShader->use();
	crosshairShader->uniform1f("u_ar", ar);
	crosshairShader->uniform1f("u_scale", scale);
	crosshair->draw(GL_LINES);
}

#endif 