#include "graphics.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <spdlog/spdlog.h>


VKAPI_ATTR VkResult VKAPI_CALL VkCreateDebugUtilsMessengerEXT(
        VkInstance instance,
        const VkDebugReportCallbackCreateInfoEXT* info,
        const VkAllocationCallbacks* allocator,
        VkDebugUtilsMessengerEXT* debug_messenger
        ){
        PFN_vkCreateDebugUtilsMessengerEXT function =
               reinterpret_cast<PFN_vkCreateDebugUtilsMessengerEXT>(
                       vkGetInstanceProcAddr(instance,"VkCreateDebugUtilsMessengerEXT"));

        if(function != nullptr){
            return function(instance, info,allocator,debug_messenger);

        }else{
            return VK_ERROR_EXTENSION_NOT_PRESENT;
        }
    }

namespace veng {

    static VKAPI_ATTR VkBool32 VKAPI_CALL ValidationCallback(VkDebugUtilsMessageSeverityFlagBitsEXT severity,
    VkDebugUtilsMessageTypeFlagsEXT type,
    const VkDebugUtilsMessengerCallbackDataEXT* callback_data,
    void* user_data
    ){
        if(severity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT){
            spdlog::warn("Vulkan validation: {}",callback_data->pMessage);
        } else{
            spdlog::warn("Vulkan Error: {}",callback_data->pMessage);
        }

        return VK_FALSE;


    }
    static VkDebugUtilsMessengerCreateInfoEXT GetCreateMessengerInfo(){
        VkDebugUtilsMessengerCreateInfoEXT creation_info = {};
        creation_info.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;

        creation_info.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
                VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;


        creation_info.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT;


        creation_info.pfnUserCallback = ValidationCallback;
        creation_info.pUserData = nullptr;

        return creation_info;

    }


   Graphics::Graphics(gsl::not_null<Window*> window) : window_(window){
        #if !defined(NDEBUG)
        validation_enebled_ = true;
        #endif


        InitializeVulkan();
   }
    Graphics::~Graphics(){
        if(instance_!= nullptr){ vkDestroyInstance(instance_, nullptr); }
   }

    void Graphics::InitializeVulkan() {
        CreateInstance();
        SetupDebugMessenger();
    }

    void Graphics::CreateInstance() {

        std::array<gsl::czstring,1> validation_layers = { "VK_LAYER_KHRONOS_validation" };

        std::vector<gsl::czstring>  required_extensions = GetRequiredInstanceExtensions();

        if(!AreaAllLayerSupported(validation_layers)){
            validation_enebled_ = false;
        }


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
        instance_create_info.enabledExtensionCount = required_extensions.size();
        instance_create_info.ppEnabledExtensionNames = required_extensions.data();

        VkDebugUtilsMessengerCreateInfoEXT  messenger_create_info = GetCreateMessengerInfo();

        if(validation_enebled_){

            instance_create_info.pNext = &messenger_create_info;
            instance_create_info.enabledLayerCount = validation_layers.size();
            instance_create_info.ppEnabledLayerNames = validation_layers.data();
        }else{
            instance_create_info.enabledLayerCount = 0;
            instance_create_info.ppEnabledLayerNames = nullptr;

        }


        VkResult result = vkCreateInstance(&instance_create_info, nullptr, &instance_);
        if (result != VK_SUCCESS){
            std::exit(EXIT_FAILURE);
        }
    }
    void Graphics::SetupDebugMessenger() {
        if(validation_enebled_){
            return;
        }
        VkDebugUtilsMessengerCreateInfoEXT info = GetCreateMessengerInfo();
        VkResult result = PFN_vkCreateDebugUtilsMessengerEXT(instance_,&info, nullptr,&debug_messenger_);
    }

    gsl::span<gsl::czstring> Graphics::GetSuggestedInstanceExtensions(){
        std::uint32_t glfw_Extension_Count = 0;
        gsl::czstring* glfw_Extension;
        glfw_Extension = glfwGetRequiredInstanceExtensions(&glfw_Extension_Count);
        return {glfw_Extension, glfw_Extension_Count};
    }

    std::vector<gsl::czstring> Graphics::GetRequiredInstanceExtensions(){
        gsl::span<gsl::czstring> suggested_extension =  GetSuggestedInstanceExtensions();
        std::vector<gsl::czstring> required_extensions(suggested_extension.size());
        std::copy(suggested_extension.begin(),suggested_extension.end(),required_extensions.begin());

        if(validation_enebled_){
            required_extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
        }


        if(!AreaAllExtensionSupported(required_extensions)){
            std::exit(EXIT_FAILURE);
        }

        return required_extensions;
    }



    std::vector<VkExtensionProperties> Graphics::GetSupportedInstanceExtensions() {
        std::uint32_t count;
        vkEnumerateInstanceExtensionProperties(nullptr, &count, nullptr);

        if(count == 0){return {};}

        std::vector<VkExtensionProperties> properties(count);
        vkEnumerateInstanceExtensionProperties(nullptr, &count, properties.data());
        return properties;
   }


   bool ExtensionMatchesName(gsl::czstring name,const VkExtensionProperties& properties){
       return veng::streq(properties.extensionName,name);

   }




   bool IsextensionSupported(gsl::span<VkExtensionProperties> extension,gsl::czstring name){
       return std::any_of(extension.begin(),extension.end()
               ,std::bind_front(ExtensionMatchesName,name)
       );
   }

   bool Graphics::AreaAllExtensionSupported(gsl::span<gsl::czstring> extensions) {
        std::vector<VkExtensionProperties> supported_extensions = GetSupportedInstanceExtensions();

        return std::all_of(extensions.begin(),extensions.end(),std::bind_front(IsextensionSupported,supported_extensions));
   }


   std::vector<VkLayerProperties> Graphics::GetSupportedValidationLayers(){

       std::uint32_t count;
       vkEnumerateInstanceLayerProperties(&count, nullptr);

       if(count == 0){return {};}

       std::vector<VkLayerProperties> properties(count);
       vkEnumerateInstanceLayerProperties(&count, properties.data());
       return properties;
   }



    bool LayerMatchesName(gsl::czstring name,const VkLayerProperties& properties){
        return veng::streq(properties.layerName,name);

    }

    bool IsLayerSupported(gsl::span<VkLayerProperties> layers,gsl::czstring name){
        return std::any_of(layers.begin(),layers.end()
                ,std::bind_front(LayerMatchesName,name)
        );
    }

    bool Graphics::AreaAllLayerSupported(gsl::span<gsl::czstring> layers) {
        std::vector<VkLayerProperties> supported_extensions = GetSupportedValidationLayers();

        return std::all_of(layers.begin(),layers.end(),std::bind_front(IsLayerSupported,supported_extensions));

    }




}