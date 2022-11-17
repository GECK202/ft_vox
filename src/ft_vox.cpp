# include "ft_vox.h"

void update_controls(PhysicsSolver* physics,
		Chunks* chunks,
		Player* player,
		float delta){

	if (Events::jpressed(GLFW_KEY_TAB)){
		Events::toogleCursor();
	}

	for (int i = 0; i < 10; i++){
		if (Events::jpressed(GLFW_KEY_0+i)){
			if (i == 0)
				i = 10;
			player->choosenBlock = i;
		}
	}

	Camera* camera = player->camera;
	Hitbox* hitbox = player->hitbox;
	bool sprint = Events::pressed(GLFW_KEY_LEFT_CONTROL);
	bool shift = Events::pressed(GLFW_KEY_LEFT_SHIFT) && hitbox->grounded && !sprint;
	float speed = player->speed;
	if (player->flight){
		speed *= FLIGHT_SPEED_MUL;
	}
	int substeps = (int)(delta * 1000);
	substeps = (substeps <= 0 ? 1 : (substeps > 100 ? 100 : substeps));
	physics->step(chunks, hitbox, delta, substeps, shift, player->flight ? 0.0f : 1.0f);
	camera->position.x = hitbox->position.x;
	camera->position.y = hitbox->position.y + 0.5f;
	camera->position.z = hitbox->position.z;

	if (player->flight && hitbox->grounded)
		player->flight = false;
	if (Events::jpressed(GLFW_KEY_F)){
		player->flight = !player->flight;
		if (player->flight){
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
	if (player->flight){
		hitbox->linear_damping = PLAYER_NOT_ONGROUND_DAMPING;
		hitbox->velocity.y *= 1.0f - delta * 9;
		if (Events::pressed(GLFW_KEY_SPACE)){
			hitbox->velocity.y += speed * delta * 9;
		}
		if (Events::pressed(GLFW_KEY_LEFT_SHIFT)){
			hitbox->velocity.y -= speed * delta * 9;
		}
	}
	if (length(dir) > 0.0f){
		dir = normalize(dir);

		if (!hitbox->grounded)
			hitbox->linear_damping = PLAYER_NOT_ONGROUND_DAMPING;

		hitbox->velocity.x += dir.x * speed * delta * 9;
		hitbox->velocity.z += dir.z * speed * delta * 9;
	}

	if (Events::_cursor_locked){
		player->camY += -Events::deltaY / Window::height * 2;
		player->camX += -Events::deltaX / Window::height * 2;

		if (player->camY < -radians(89.0f)){
			player->camY = -radians(89.0f);
		}
		if (player->camY > radians(89.0f)){
			player->camY = radians(89.0f);
		}

		camera->rotation = mat4(1.0f);
		camera->rotate(player->camY, player->camX, 0);
	}
}

void update_interaction(Chunks* chunks, PhysicsSolver* physics, Player* player, Lighting* lighting){
	Camera* camera = player->camera;
	vec3 end;
	vec3 norm;
	vec3 iend;
	voxel* vox = chunks->rayCast(camera->position, camera->front, 10.0f, end, norm, iend);
	if (vox != nullptr){
		if (Events::jclicked(GLFW_MOUSE_BUTTON_1)){
			int x = (int)iend.x;
			int y = (int)iend.y;
			int z = (int)iend.z;
			chunks->set(x,y,z, 0);
			lighting->onBlockSet(x,y,z,0);
		}
		if (Events::jclicked(GLFW_MOUSE_BUTTON_2)){
			int x = (int)(iend.x)+(int)(norm.x);
			int y = (int)(iend.y)+(int)(norm.y);
			int z = (int)(iend.z)+(int)(norm.z);
			if (!physics->isBlockInside(x,y,z, player->hitbox)){
				chunks->set(x, y, z, player->choosenBlock);
				lighting->onBlockSet(x,y,z, player->choosenBlock);
			}
		}
	}
}

int initialise(Assets* assets, WorldFiles *wfile, Player* player, Camera *camera) {
	setup_definitions();
	Window::initialize(WIDTH, HEIGHT, "VoxelEngine Part-11");
	Events::initialize();

	std::cout << "-- loading assets" << std::endl;
	int result = initialize_assets(assets);
	if (result){
		delete assets;
		Window::terminate();
		return result;
	}
	std::cout << "-- loading world" << std::endl;
	wfile->readPlayer(player);
	camera->rotation = mat4(1.0f);
	camera->rotate(player->camY, player->camX, 0);
	return 0;
}

void main_cycle(Assets* assets,WorldFiles *wfile,Player* player,Chunks *chunks,Camera *camera,int seed) {
	std::cout << "-- preparing systems" << std::endl;
	VoxelRenderer renderer(1024*1024);
	PhysicsSolver physics(vec3(0,-GRAVITY,0));
	Lighting lighting(chunks); 
	init_renderer();
	ChunksController chunksController(chunks, &lighting, seed);
	std::cout << "-- initializing finished" << std::endl;
	float lastTime = glfwGetTime();
	float delta = 0.0f;
	float fpsTime = lastTime;
	int fps = 0;
	float fps_r = 0.0f;
	while (!Window::isShouldClose()){
		float currentTime = glfwGetTime();
		delta = currentTime - lastTime;
		lastTime = currentTime;
		fps++;
		if ((currentTime - fpsTime) >= 1) {
			fps_r = (float) fps;
			fps = 0;
			fpsTime = currentTime;
		}

		if (Events::jpressed(GLFW_KEY_ESCAPE)){
			Window::setShouldClose(true);
		}

		update_controls(&physics, chunks, player, delta);
		update_interaction(chunks, &physics, player, &lighting);

		chunks->setCenter(wfile, camera->position.x,0,camera->position.z);
		chunksController._buildMeshes(&renderer);

		int freeLoaders = chunksController.countFreeLoaders();
		for (int i = 0; i < freeLoaders; i++)
			chunksController.loadVisible(wfile);

		draw_world(camera, assets, chunks, fps_r);

		Window::swapBuffers();
		Events::pullEvents();
	}
}

void finalize(Assets* assets,WorldFiles *wfile,Player* player,Chunks *chunks) {
	std::cout << "-- saving world" << std::endl;
	wfile->writePlayer(player);
	write_world(wfile, chunks);
	close_world(wfile, chunks);

	std::cout << "-- shutting down" << std::endl;
	delete assets;
	finalize_renderer();
	Events::finalize();
	Window::terminate();
}

int main(int argc, char *argv[]) {
	int seed = 0;
	if (argc == 2) {
		seed = std::atoi(argv[1]);
	}
	
	Assets* assets = new Assets();
	Camera *camera = new Camera(vec3 (0, 255, 0), radians(80.0f));
	WorldFiles *wfile = new WorldFiles("world/", REGION_VOL * (CHUNK_VOL * 2 + 8));
	Chunks *chunks = new Chunks(32,1,32, 0,0,0);
	Player* player = new Player(vec3(camera->position), DEFAULT_PLAYER_SPEED, camera);

	if (initialise(assets,  wfile, player, camera) != 0)
		return 1;

	main_cycle(assets,wfile,player,chunks,camera,seed);
	finalize(assets, wfile, player,chunks);

	return 0;
}
