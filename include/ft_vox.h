#ifndef FT_VOX_HPP
# define FT_VOX_HPP

#define WIDTH 1280
#define HEIGHT 720
#define GRAVITY 19.6f
#define DEFAULT_PLAYER_SPEED 4.0f
#define RUN_SPEED_MUL 1.5f
#define DEFAULT_AIR_DAMPING 0.1f
#define PLAYER_NOT_ONGROUND_DAMPING 10.0f
#define FLIGHT_SPEED_MUL 5.0f
#define JUMP_FORCE 7.0f

# include <iostream>
# include <cstdlib>
# include <cmath>
# include <glad/glad.h>
# include <GLFW/glfw3.h>
# include <vector>
# include <ctime>
# include <glm/glm.hpp>
# include <glm/ext.hpp>
# include <glm/gtc/matrix_transform.hpp>

# include "shader.h"
# include "texture.h"
# include "mesh.h"
# include "voxel_renderer.h"
# include "window.h"
# include "events.h"
# include "camera.h"
# include "png_loading.h"
# include "voxel.h"
# include "chunk.h"
# include "chunks.h"
# include "block.h"
# include "world_generator.h"
# include "chunks_controller.h"
# include "files.h"
# include "light_solver.h"
# include "lightmap.h"
# include "lighting.h"
# include "hitbox.h"
# include "physics_solver.h"
# include "assets.h"
# include "player.h"
# include "declarations.h"
# include "world_render.h"
# include "world_files.h"

#endif
