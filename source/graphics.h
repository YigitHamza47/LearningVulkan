#ifndef INC_905VULKANOGR_GRAPHICS_H
#define INC_905VULKANOGR_GRAPHICS_H

#include <vulkan/vulkan.h>
#include "glfw_window.h"
#include <vector>
#include <GLFW/glfw3.h>



namespace veng {

    class Graphics  final {

    public:
        Graphics(gsl::not_null<Window*> window);
        ~Graphics();

    private:
        void InitializeVulkan();
        void CreateInstance();
        static gsl::span<gsl::czstring> GetSuggestedInstanceExtensions();
        static std::vector<VkExtensionProperties> GetSupportedInstanceExtensions();


        VkInstance instance_;
        gsl::not_null <Window*> window_;

    };


}

#endif //INC_905VULKANOGR_GRAPHICS_H
