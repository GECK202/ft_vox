#ifndef SHADER_H
# define SHADER_H

# include <string>
# include <exception>
# include <fstream>
# include <iostream>
# include <sstream>
# include <glm/glm.hpp>
# include <glm/gtc/type_ptr.hpp>
# include <glad/glad.h>
# include <GLFW/glfw3.h>

class Shader {
public:
	unsigned int id;

	Shader(unsigned int id);
	~Shader();

	void use();
	void uniformMatrix(std::string name, glm::mat4 matrix);
	void uniform1i(std::string name, int x);
	void uniform1f(std::string name, float x);
	void uniform2f(std::string name, float x, float y);
	void uniform3f(std::string name, float x, float y, float z);
};

extern Shader* load_shader(std::string vertexFile, std::string fragmentFile);

#endif