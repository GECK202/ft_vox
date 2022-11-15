#ifndef PLAYER_H
# define PLAYER_H

# include <glm/glm.hpp>
# include "hitbox.h"

# include <glm/glm.hpp>

class Camera;
class Hitbox;

class Player {
public:
	float speed;
	Camera* camera;
	Hitbox* hitbox;
	bool flight = false;
	int choosenBlock;
	float camX, camY;
	glm::vec3 interpVel {0.0f, 0.0f, 0.0f};
	Player(glm::vec3 position, float speed, Camera* camera);
	~Player();
};

#endif