#include "cubemap.h"

Cubemap::Cubemap(unsigned int id) : id(id){
}

Cubemap::~Cubemap() {
	glDeleteTextures(1, &id);
}

void Cubemap::bind(){
	glBindTexture(GL_TEXTURE_CUBE_MAP, id);
}

