#include "game.h"


Assets* Game::assets = nullptr;
WorldFiles* Game::wfile = nullptr;
Chunks* Game::chunks = nullptr;
Player* Game::player = nullptr;
VoxelRenderer* Game::renderer = nullptr;
PhysicsSolver* Game::physics = nullptr;
Lighting* Game::lighting = nullptr;
ChunksController* Game::chunksController = nullptr;
float Game::lastTime = glfwGetTime();
float Game::delta = 0.0f;
long Game::frame = 0;
bool Game::occlusion = false;


int Game::initialise() {
	setup_definitions();

	Window::initialize(WIDTH, HEIGHT, "ft_vox");
	Events::initialize();

	std::cout << "-- loading assets" << std::endl;
	Assets* assets = new Assets();
	int result = initialize_assets(assets);
	if (result){
		delete assets;
		Window::terminate();
		return result;
	}
	std::cout << "-- loading world" << std::endl;

	vec3 spawnpoint(0, 255, 0);
	WorldFiles *wfile = new WorldFiles("world/", REGION_VOL * (CHUNK_VOL * 2 + 8));
	Chunks *chunks = new Chunks(32,1,32, 0,0,0);
	Camera *camera = new Camera(spawnpoint, radians(90.0f));


	Player* player = new Player(vec3(camera->position), DEFAULT_PLAYER_SPEED, camera);
	wfile->readPlayer(player);
	camera->rotation = mat4(1.0f);
	camera->rotate(player->camY, player->camX, 0);

	std::cout << "-- preparing systems" << std::endl;

	VoxelRenderer* renderer = new VoxelRenderer(1024*1024);
	PhysicsSolver* physics = new PhysicsSolver(vec3(0,-GRAVITY,0));
	Lighting* lighting= new Lighting(chunks);

	init_renderer();

	ChunksController* chunksController = new ChunksController(chunks, lighting);

    Game::assets = assets;
    Game::wfile = wfile;
    Game::chunks = chunks;
    Game::player = player;

    Game::renderer = renderer;
    Game::physics = physics;
    Game::lighting =  lighting;
    Game::chunksController =  chunksController;

	std::cout << "-- initializing finished" << std::endl;
	return 0;
}

void Game::update_interaction(){
	Camera* camera = Game::player->camera;
	vec3 end;
	vec3 norm;
	vec3 iend;
	voxel* vox = Game::chunks->rayCast(camera->position, camera->front, 10.0f, end, norm, iend);
	if (vox != nullptr){
		if (Events::jclicked(GLFW_MOUSE_BUTTON_1)){
			int x = (int)iend.x;
			int y = (int)iend.y;
			int z = (int)iend.z;
			Game::chunks->set(x,y,z, 0);
			Game::lighting->onBlockSet(x,y,z,0);
		}
		if (Events::jclicked(GLFW_MOUSE_BUTTON_2)){
			int x = (int)(iend.x)+(int)(norm.x);
			int y = (int)(iend.y)+(int)(norm.y);
			int z = (int)(iend.z)+(int)(norm.z);
			if (!Game::physics->isBlockInside(x,y,z, Game::player->hitbox)){
				Game::chunks->set(x, y, z, Game::player->choosenBlock);
				Game::lighting->onBlockSet(x,y,z, Game::player->choosenBlock);
			}
		}
	}
}

void Game::update_controls(){

	if (Events::jpressed(GLFW_KEY_Q)){
		Window::swapMode();
	}

	if (Events::jpressed(GLFW_KEY_TAB)){
		Events::toogleCursor();
	}

	for (int i = 1; i < 10; i++){
		if (Events::jpressed(GLFW_KEY_0+i)){
			Game::player->choosenBlock = i;
		}
	}

	// Controls
	Camera* camera = Game::player->camera;
	Hitbox* hitbox = Game::player->hitbox;
	bool sprint = Events::pressed(GLFW_KEY_LEFT_CONTROL);
	bool shift = Events::pressed(GLFW_KEY_LEFT_SHIFT) && hitbox->grounded && !sprint;

	float speed = Game::player->speed;
	if (Game::player->flight){
		speed *= FLIGHT_SPEED_MUL;
	}
	int substeps = (int)(Game::delta * 1000);
	substeps = (substeps <= 0 ? 1 : (substeps > 100 ? 100 : substeps));
	Game::physics->step(Game::chunks, hitbox, Game::delta, substeps, shift, Game::player->flight ? 0.0f : 1.0f);
	camera->position.x = hitbox->position.x;
	camera->position.y = hitbox->position.y + 0.5f;
	camera->position.z = hitbox->position.z;

	if (Game::player->flight && hitbox->grounded)
		Game::player->flight = false;
	Game::player->interpVel = Game::player->interpVel * (1.0f - Game::delta * 5) + hitbox->velocity * Game::delta * 0.1f;
	if (hitbox->grounded && Game::player->interpVel.y < 0.0f){
		Game::player->interpVel.y *= -30.0f;
	}
	camera->position -= min(Game::player->interpVel * 0.05f, 1.0f);

	if (Events::jpressed(GLFW_KEY_F)){
		Game::player->flight = !Game::player->flight;
		if (Game::player->flight){
			hitbox->velocity.y += 1;
			hitbox->grounded = false;
		}
	}

	if (Events::pressed(GLFW_KEY_SPACE) && hitbox->grounded){
		hitbox->velocity.y = JUMP_FORCE;
	}

	vec3 dir(0,0,0);
	if (Events::pressed(GLFW_KEY_W)){
		dir.x += camera->dir.x;
		dir.z += camera->dir.z;
	}
	if (Events::pressed(GLFW_KEY_S)){
		dir.x -= camera->dir.x;
		dir.z -= camera->dir.z;
	}
	if (Events::pressed(GLFW_KEY_D)){
		dir.x += camera->right.x;
		dir.z += camera->right.z;
	}
	if (Events::pressed(GLFW_KEY_A)){
		dir.x -= camera->right.x;
		dir.z -= camera->right.z;
	}

	hitbox->linear_damping = DEFAULT_AIR_DAMPING;
	if (Game::player->flight){
		hitbox->linear_damping = PLAYER_NOT_ONGROUND_DAMPING;
		hitbox->velocity.y *= 1.0f - Game::delta * 9;
		if (Events::pressed(GLFW_KEY_SPACE)){
			hitbox->velocity.y += speed * Game::delta * 9;
		}
		if (Events::pressed(GLFW_KEY_LEFT_SHIFT)){
			hitbox->velocity.y -= speed * Game::delta * 9;
		}
	}
	if (length(dir) > 0.0f){
		dir = normalize(dir);

		if (!hitbox->grounded)
			hitbox->linear_damping = PLAYER_NOT_ONGROUND_DAMPING;

		hitbox->velocity.x += dir.x * speed * Game::delta * 9;
		hitbox->velocity.z += dir.z * speed * Game::delta * 9;
	}

	if (Events::_cursor_locked){
		Game::player->camY += -Events::deltaY / Window::height * 2;
		Game::player->camX += -Events::deltaX / Window::height * 2;

		if (Game::player->camY < -radians(89.0f)){
			Game::player->camY = -radians(89.0f);
		}
		if (Game::player->camY > radians(89.0f)){
			Game::player->camY = radians(89.0f);
		}

		camera->rotation = mat4(1.0f);
		camera->rotate(Game::player->camY, Game::player->camX, 0);
	}
}

void Game::update() {
    while (!Window::isShouldClose()){
		Game::frame++;
		float currentTime = glfwGetTime();
		Game::delta = currentTime - Game::lastTime;
		Game::lastTime = currentTime;
        Camera* camera = Game::player->camera;

		if (Events::jpressed(GLFW_KEY_ESCAPE)){
			Window::setShouldClose(true);
		}

		if (Events::jpressed(GLFW_KEY_O)){
			Game::occlusion = !Game::occlusion;
		}

		update_controls();
		update_interaction();

		Game::chunks->setCenter(Game::wfile, camera->position.x,0,camera->position.z);
		Game::chunksController->_buildMeshes(Game::renderer);

		int freeLoaders = Game::chunksController->countFreeLoaders();
		for (int i = 0; i < freeLoaders; i++)
			Game::chunksController->loadVisible(Game::wfile);

		draw_world(camera, Game::assets, Game::chunks, Game::occlusion);

		Window::swapBuffers();
		Events::pullEvents();
	}
	std::cout << "-- saving world" << std::endl;
}

void Game::finalize() {
    Game::wfile->writePlayer(Game::player);
	write_world(Game::wfile, Game::chunks);
	close_world(Game::wfile, Game::chunks);

	std::cout << "-- shutting down" << std::endl;

	delete Game::assets;
	finalize_renderer();
	Events::finalize();
	Window::terminate();
}