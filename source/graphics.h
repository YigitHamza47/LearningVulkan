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

        struct QueueFamilyIndices{
            std::optional<std::uint32_t> graphics_family = std::nullopt;
            std::optional<std::uint32_t> presentation_family = std::nullopt;

            bool Isvalid() const{return graphics_family.has_value() && presentation_family.has_value();}

        };

        void InitializeVulkan();
        void CreateInstance();
        void SetupDebugMessenger();
        void PickPhysicalDevice();
        void CreateLogicalDeviceAndQueues();
        void CreateSurface();
        static gsl::span<gsl::czstring> GetSuggestedInstanceExtensions();
        std::vector<gsl::czstring> GetRequiredInstanceExtensions();
        static std::vector<VkExtensionProperties> GetSupportedInstanceExtensions();
        static bool AreaAllExtensionSupported(gsl::span<gsl::czstring> extensions);

        static std::vector<VkLayerProperties> GetSupportedValidationLayers();
        static bool AreaAllLayerSupported(gsl::span<gsl::czstring> extensions);

        QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice device);


        bool IsDeviceSuitable(VkPhysicalDevice device);
        std::vector<VkPhysicalDevice> GetAvailableDevices();
        bool AreAllDeviceExtensionsSupported(VkPhysicalDevice device);
        std::vector<VkExtensionProperties> GetDeviceAvailableExtensions(VkPhysicalDevice device);

        std::array<gsl::czstring,1> required_device_extensions_ = {
                VK_KHR_SWAPCHAIN_EXTENSION_NAME
        };


        VkInstance instance_ = VK_NULL_HANDLE;


        VkPhysicalDevice physical_Device_ = VK_NULL_HANDLE;
        VkDevice logical_device_ = VK_NULL_HANDLE;
        VkQueue graphics_queue_ = VK_NULL_HANDLE;
        VkQueue present_queue_ = VK_NULL_HANDLE;

        VkSurfaceKHR surface_ = VK_NULL_HANDLE;

        VkDebugUtilsMessengerEXT debug_messenger_;
        gsl::not_null <Window*> window_;
        bool validation_enebled_ = false;

    };


}

#endif //INC_905VULKANOGR_GRAPHICS_H
