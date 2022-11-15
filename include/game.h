#ifndef GAME_H
# define GAME_H

# define WIDTH 1280
# define HEIGHT 1024
# define RUN_SPEED_MUL 1.5f
# define GRAVITY 19.6f
# define DEFAULT_PLAYER_SPEED 2.0f
# define FLIGHT_SPEED_MUL 20.0f
# define JUMP_FORCE 7.0f
# define DEFAULT_AIR_DAMPING 0.1f
# define PLAYER_NOT_ONGROUND_DAMPING 10.0f

# include "window.h"
# include "events.h"
# include "declarations.h"
# include "world_files.h"
# include "player.h"
# include "voxel_renderer.h"
# include "lighting.h"
# include "world_render.h"
# include "chunks_controller.h"
# include "physics_solver.h"
# include "chunks.h"
# include "camera.h"

//class Window;
//class Events;
//class WorldFiles;
//class Player;
//class VoxelRenderer;
//class Lighting;
//class ChunksController;

class Game {
public:

    static Assets* assets;
    static WorldFiles* wfile;
    static Chunks* chunks;
    static Player* player;
    static VoxelRenderer* renderer;
    static PhysicsSolver* physics;
    static Lighting* lighting;
    static ChunksController* chunksController;


    static float lastTime;
	static float delta;
	static long frame;
    static bool occlusion;

	static int initialise();
    static void update_controls();
	static void update_interaction();
    static void update();
    static void finalize();
};

#endif