#pragma once
extern struct GLFWwindow;
class GlfwConfigure
{
public:
	GlfwConfigure(const GlfwConfigure&) = delete;
	void operator=(const GlfwConfigure &) = delete;
	GLFWwindow* getGlfWindowHandle() const;
	static GlfwConfigure* getInstance();
protected:
	GlfwConfigure() { 
		if (run() == false)
			m_singleton = nullptr;
	};
	bool run();
private:
	static GLFWwindow* m_window;
	static GlfwConfigure* m_singleton;
};

