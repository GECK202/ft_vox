#include "assets.h"

Assets::~Assets() {
	for (auto& iter : shaders){
		delete iter.second;
	}

	for (auto& iter : textures){
		delete iter.second;
	}

	for (auto& iter : cubemaps){
		delete iter.second;
	}
}

Texture* Assets::getTexture(std::string name){
	return textures[name];
}

void Assets::store(Texture* texture, std::string name){
	textures[name] = texture;
}


Shader* Assets::getShader(std::string name){
	return shaders[name];
}

void Assets::store(Shader* shader, std::string name){
	shaders[name] = shader;
}

Cubemap* Assets::getCubemap(std::string name){
	return cubemaps[name];
}

void Assets::store(Cubemap* cubemap, std::string name){
	cubemaps[name] = cubemap;
}

