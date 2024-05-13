#ifndef INC_905VULKANOGR_GLFW_INITILAZITION_H
#define INC_905VULKANOGR_GLFW_INITILAZITION_H


namespace veng {

    struct GlfwInitialization {
    public:
        GlfwInitialization();

        ~GlfwInitialization();

        GlfwInitialization(const GlfwInitialization &) = delete;

        GlfwInitialization &operator=(const GlfwInitialization &) = delete;
    };


}
#endif //INC_905VULKANOGR_GLFW_INITILAZITION_H
