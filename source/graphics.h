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
        void SetupDebugMessenger();
        void PickPhysicalDevice();
        static gsl::span<gsl::czstring> GetSuggestedInstanceExtensions();
        std::vector<gsl::czstring> GetRequiredInstanceExtensions();
        static std::vector<VkExtensionProperties> GetSupportedInstanceExtensions();
        static bool AreaAllExtensionSupported(gsl::span<gsl::czstring> extensions);

        static std::vector<VkLayerProperties> GetSupportedValidationLayers();
        static bool AreaAllLayerSupported(gsl::span<gsl::czstring> extensions);


        bool IsDeviceSuitable(VkPhysicalDevice device);
        std::vector<VkPhysicalDevice> GetAvailableDevices();

        VkInstance instance_;
        VkPhysicalDevice physicalDevice = nullptr;
        VkDebugUtilsMessengerEXT debug_messenger_;
        gsl::not_null <Window*> window_;
        bool validation_enebled_ = false;

    };


}

#endif //INC_905VULKANOGR_GRAPHICS_H
