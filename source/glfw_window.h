#ifndef INC_905VULKANOGR_GLFW_WINDOW_H
#define INC_905VULKANOGR_GLFW_WINDOW_H
#include <GLFW/glfw3.h>
#include "glfw_monitor.h"


struct GLFWwindow;

namespace veng {

    class Window {
    public:
        Window(gsl::czstring name,glm::ivec2 size);
        ~Window();
        glm::ivec2 GetWindowSize() const;

        bool ShouldClose() const;
        GLFWwindow* GetHandle() const;


    private:
        GLFWwindow* window_;
    };

}

#endif //INC_905VULKANOGR_GLFW_WINDOW_H
