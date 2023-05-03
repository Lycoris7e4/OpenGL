#ifndef WINDOW_H_
#define WINDOW_H_

#include <vector>

struct GLFWwindow;

// Error Type
namespace ERROR {
	class WINDOWCREATION {};
	class GLADINIT {};
}

enum class SETTINGS {
	BLEND, LINE_SMOOTH, DEPTH_TEST, POINT_SIZE, CULL_FACE, MULTISAMPLE
};

class Window {
private:
	GLFWwindow* window = nullptr;
	int SCR_WIDTH = 800;
	int SCR_HEIGHT = 600;

public:
	Window(int major = 3, int minor = 3);
	~Window();
	Window(const Window& other) = delete;
	Window(const Window&& other) = delete;

	// Interface Functions
	GLFWwindow* getWindow();
	float getWidth();
	float getHeight();

	// Initialization
	void init(int width, int height, const char* title);
	void setup(std::vector<SETTINGS> settings);

	// Operations
	void update();
	void terminate();

	void setCursor(void (* callback)(GLFWwindow* window, double xpos, double ypos));
	void setScroll(void (*callback)(GLFWwindow* window, double xoffset, double yoffset));
	void disableCursor();

	// States
	void close();
	bool shouldClose();
};

#endif // WINDOW_H_
