#include "window.h"

GLFWwindow* Window::window;
int Window::width = 0;
int Window::height = 0;
int Window::x_pos = 0;
int Window::y_pos = 0;
bool Window::win_mode = true;

int Window::initialize(int width, int height, const char* title){
	glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
	window = glfwCreateWindow(width, height, title, nullptr, nullptr);
    if (window == nullptr) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
	glfwSwapInterval(1);
	glfwMakeContextCurrent(window);
	glfwGetFramebufferSize(window, nullptr, nullptr);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cerr << "Failed to initialize GLAD" << std::endl;
		glfwTerminate();
        return -1;
	}
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	glViewport(0,0, width*2, height*2);
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	int width_m, height_m;
	glfwGetMonitorWorkarea(glfwGetPrimaryMonitor(), nullptr, nullptr, &width_m, &height_m);

	Window::width = width;
	Window::height = height;
	Window::x_pos = (width_m - width) / 2;
	Window::y_pos = (height_m - height) / 2;
    return 0;
}

void Window::setCursorMode(int mode){
	glfwSetInputMode(window, GLFW_CURSOR, mode);
}

void Window::terminate(){
	glfwTerminate();
}

bool Window::isShouldClose(){
	return glfwWindowShouldClose(window);
}

void Window::setShouldClose(bool flag){
	glfwSetWindowShouldClose(window, flag);
}

void Window::swapBuffers(){
	glfwSwapBuffers(window);
}

void Window::swapMode() {
	win_mode = !win_mode;
	if (win_mode) {
		glViewport(0,0, width*2, height*2);
		glfwSetWindowMonitor(window, nullptr, x_pos,y_pos,width, height, GLFW_DONT_CARE);
	} else {
		glViewport(0,0, width*4, height*4);
		glfwSetWindowMonitor(window, glfwGetPrimaryMonitor(), 0,0,width, height, GLFW_DONT_CARE);
	}
}
