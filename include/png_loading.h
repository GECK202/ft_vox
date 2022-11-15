#ifndef PNG_LOADING_H
# define PNG_LOADING_H

# include <string>
# include <vector>
# include <iostream>
# include <glad/glad.h>
# include <GLFW/glfw3.h>
# include <png.h>

# include "texture.h"
# include "cubemap.h"


class Texture;

extern Texture* load_texture(std::string filename);

extern Cubemap* load_cubemap(std::vector<std::string> faces);

#endif