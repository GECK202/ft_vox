#ifndef ASSETS_H
# define ASSETS_H

# include <string>
# include <unordered_map>
# include "cubemap.h"
# include "texture.h"
# include "shader.h"

class Texture;
class Shader;

class Assets {
	std::unordered_map<std::string, Texture*> textures;
	std::unordered_map<std::string, Shader*> shaders;
	std::unordered_map<std::string, Cubemap*> cubemaps;
public:
	~Assets();
	Texture* getTexture(std::string name);
	void store(Texture* texture, std::string name);

	Shader* getShader(std::string name);
	void store(Shader* shader, std::string name);

	Cubemap* getCubemap(std::string name);
	void store(Cubemap* cubemap, std::string name);
};

#endif