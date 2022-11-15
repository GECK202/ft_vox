#ifndef TEXTURE_H
# define TEXTURE_H

# include <string>
# include <glad/glad.h>
# include <GLFW/glfw3.h>

class Texture {
public:
	unsigned int id;
	int width;
	int height;
	Texture(unsigned int id, int width, int height);
	Texture(unsigned char* data, int width, int height);
	~Texture();

	void bind();
};

extern Texture* load_texture(std::string filename);

#endif