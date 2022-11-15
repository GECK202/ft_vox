#include "events.h"

bool* Events::_keys;
uint* Events::_frames;
uint Events::_current = 0;
float Events::deltaX = 0.0f;
float Events::deltaY = 0.0f;
float Events::x = 0.0f;
float Events::y = 0.0f;
bool Events::_cursor_locked = false;
bool Events::_cursor_started = false;

void cursor_position_callback(GLFWwindow*, double xp, double yp){
	if (Events::_cursor_started){
		Events::deltaX += xp-Events::x;
		Events::deltaY += yp-Events::y;
	}
	else {
		Events::_cursor_started = true;
	}
	Events::x = xp;
	Events::y = yp;
}

void mouse_button_callback(GLFWwindow*, int btn, int act, int){
	if (act == GLFW_PRESS){
		Events::_keys[_MOUSE_BUTTONS+btn] = true;
		Events::_frames[_MOUSE_BUTTONS+btn] = Events::_current;
	}
	else if (act == GLFW_RELEASE){
		Events::_keys[_MOUSE_BUTTONS+btn] = false;
		Events::_frames[_MOUSE_BUTTONS+btn] = Events::_current;
	}
}

void key_callback(GLFWwindow*, int key, int, int act, int) {
	if (act == GLFW_PRESS){
		Events::_keys[key] = true;
		Events::_frames[key] = Events::_current;
	}
	else if (act == GLFW_RELEASE){
		Events::_keys[key] = false;
		Events::_frames[key] = Events::_current;
	}
}

void window_size_callback(GLFWwindow*, int w, int h){
	glViewport(0,0, w, h);
	Window::width = w;
	Window::height = h;
}

int Events::initialize(){
	GLFWwindow* window = Window::window;
	_keys = new bool[1032];
	_frames = new uint[1032];

	memset(_keys, false, 1032*sizeof(bool));
	memset(_frames, 0, 1032*sizeof(uint));

	glfwSetKeyCallback(window, key_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwSetCursorPosCallback(window, cursor_position_callback);
	glfwSetWindowSizeCallback(window, window_size_callback);
	return 0;
}

void Events::finalize(){
	delete[] _keys;
	delete[] _frames;
}

bool Events::pressed(int keycode){
	if (keycode < 0 || keycode >= _MOUSE_BUTTONS)
		return false;
	return _keys[keycode];
}

bool Events::jpressed(int keycode){
	if (keycode < 0 || keycode >= _MOUSE_BUTTONS)
		return false;
	return _keys[keycode] && _frames[keycode] == _current;
}

bool Events::clicked(int button){
	int index = _MOUSE_BUTTONS+button;
	return _keys[index];
}

bool Events::jclicked(int button){
	int index = _MOUSE_BUTTONS+button;
	return _keys[index] && _frames[index] == _current;
}

void Events::toogleCursor(){
	_cursor_locked = !_cursor_locked;
	Window::setCursorMode(_cursor_locked ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL);
}

void Events::pullEvents(){
	_current++;
	deltaX = 0.0f;
	deltaY = 0.0f;
	glfwPollEvents();
}

