#ifndef CAMERA_H
# define CAMERA_H

# include <glm/ext.hpp>
# include <glm/glm.hpp>

# include "window.h"

using namespace glm;

class Camera {
	void updateVectors();
public:
	vec3 front;
	vec3 up;
	vec3 right;
	vec3 dir;

	vec3 position;
	float fov;
	mat4 rotation;
	Camera(vec3 position, float fov);

	void rotate(float x, float y, float z);

	mat4 getProjection();
	mat4 getView();
};

#endif 