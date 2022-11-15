#ifndef WINDOW_H
# define WINDOW_H

# include <iostream>
# include <glad/glad.h>
# include <GLFW/glfw3.h>

class GLFWwindow;

class Window {
public:
	static int width;
	static int height;
	static bool win_mode;
	static int x_pos;
	static int y_pos;
	static GLFWwindow* window;
	static int initialize(int width, int height, const char* title);
	static void terminate();

	static void setCursorMode(int mode);
	static bool isShouldClose();
	static void setShouldClose(bool flag);
	static void swapBuffers();
	static void swapMode();
};

#endif