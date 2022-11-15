#ifndef EVENTS_H
# define EVENTS_H

# define _MOUSE_BUTTONS 1024

# include <glad/glad.h>
# include <GLFW/glfw3.h>
# include <string.h>

# include "window.h"

typedef unsigned int uint;

class Player;
class PhysicsSolver;
class Chunks;

class Events {
public:
	static bool* _keys;
	static uint* _frames;
	static uint _current;
	static float deltaX;
	static float deltaY;
	static float x;
	static float y;
	static bool _cursor_locked;
	static bool _cursor_started;

	static int initialize();
	static void finalize();
	static void pullEvents();
	static bool pressed(int keycode);
	static bool jpressed(int keycode);
	static bool clicked(int button);
	static bool jclicked(int button);
	static void toogleCursor();
};

extern void update_controls(PhysicsSolver* physics,
		Chunks* chunks,
		Player* player,
		float delta);

#endif
