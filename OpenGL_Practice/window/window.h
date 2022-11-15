#ifndef WINDOW_H_
#define WINDOW_H_

struct GLFWwindow;

// Error Type
namespace ERROR {
	class WINDOWCREATION {};
	class GLADINIT {};
}

class Window {
private:
	GLFWwindow* window = nullptr;
	int SCR_WIDTH = 800;
	int SCR_HEIGHT = 600;

public:
	Window();
	~Window();
	Window(const Window& other) = delete;
	Window(const Window&& other) = delete;

	// Interface Functions
	GLFWwindow* getWindow();
	float getWidth();
	float getHeight();

	// Initialization
	void setup(int width, int height, const char* title);

	// Operations
	void update();
	void terminate();

	void setCursor(void (* callback)(GLFWwindow* window, double xpos, double ypos));
	void setScroll(void (*callback)(GLFWwindow* window, double xoffset, double yoffset));
	void disableCursor();
	void setDepthTest();

	// States
	void close();
	bool shouldClose();
};

#endif // WINDOW_H_
