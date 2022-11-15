#ifndef CUBEMAP_H
# define CUBEMAP_H

# include <vector>
# include <string>
# include <glad/glad.h>
# include <GLFW/glfw3.h>

class Cubemap {
public:
	unsigned int id;
	Cubemap(unsigned int id);
	~Cubemap();

	void bind();
};

extern Cubemap* load_cubemap(std::vector<std::string> faces);

#endif