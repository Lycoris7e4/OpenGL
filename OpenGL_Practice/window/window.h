#ifndef WINDOW_H_
#define WINDOW_H_

struct GLFWwindow;

namespace ERROR {
	class WINDOWCREATION {};
	class GLADINIT {};
}

class Window {
	GLFWwindow* window = nullptr;
	int SCR_WIDTH = 800;
	int SCR_HEIGHT = 600;
public:
	Window();
	~Window();
	Window(const Window& other) = delete;
	Window(const Window&& other) = delete;

	void setup(int width, int height, const char* title);
	void update();
	void terminate();

	bool shouldClose();
	void processInput();

	void setCursor();
	void setScroll();
	void disableCursor();
	void setDepthTest();
};

#endif // WINDOW_H_
