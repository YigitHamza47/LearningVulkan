#include "graphics.h"
#include <GLFW/glfw3.h>


namespace veng {

   Graphics::Graphics(gsl::not_null<Window*> window) : window_(window){
        InitializeVulkan();
   }
    Graphics::~Graphics(){
        if(instance_!= nullptr){ vkDestroyInstance(instance_, nullptr); }
   }

    void Graphics::InitializeVulkan() {
        CreateInstance();
    }

    void Graphics::CreateInstance() {
       gsl::span<gsl::czstring> suggested_Extension =  GetSuggestedInstanceExtensions();


        VkApplicationInfo app_info = {};
        app_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        app_info.pNext = nullptr;
        app_info.pApplicationName = "BaboEngine";
        app_info.applicationVersion = VK_MAKE_VERSION(1,0,0);
        app_info.pEngineName = "Babo";
        app_info.engineVersion = VK_MAKE_VERSION(1,0,0);
        app_info.apiVersion = VK_API_VERSION_1_3;


        VkInstanceCreateInfo instance_create_info = {};
        instance_create_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        instance_create_info.pNext = nullptr;
        instance_create_info.pApplicationInfo = &app_info;
        instance_create_info.enabledExtensionCount = suggested_Extension.size();
        instance_create_info.ppEnabledExtensionNames = suggested_Extension.data();
        instance_create_info.enabledLayerCount = 0;

        VkResult result = vkCreateInstance(&instance_create_info, nullptr, &instance_);
        if (result != VK_SUCCESS){
            std::exit(EXIT_FAILURE);
        }
    }

    gsl::span<gsl::czstring> Graphics::GetSuggestedInstanceExtensions(){
        std::uint32_t glfw_Extension_Count = 0;
        gsl::czstring* glfw_Extension;
        glfw_Extension = glfwGetRequiredInstanceExtensions(&glfw_Extension_Count);
        return {glfw_Extension, glfw_Extension_Count};
    }

    std::vector<VkExtensionProperties> Graphics::GetSupportedInstanceExtensions() {
        std::uint32_t count;
        vkEnumerateDeviceExtensionProperties(nullptr,&count, nullptr);

        if(count == 0){return {};}

        std::vector<VkExtensionProperties> properties(count);
        vkEnumerateDeviceExtensionProperties(nullptr,&count,properties.data());
        return properties;
   }


}