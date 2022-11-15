#ifndef MESH_H
# define MESH_H

# include <stdlib.h>
# include <glad/glad.h>
# include <GLFW/glfw3.h>

class Mesh {
	unsigned int vao;
	unsigned int vbo;
	size_t vertices;
	size_t vertexSize;
public:
	Mesh(const float* buffer, size_t vertices, const int* attrs);
	~Mesh();

	void draw(unsigned int primitive);
};

#endif