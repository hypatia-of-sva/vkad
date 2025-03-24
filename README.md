# vkad - a vulkan function loading utility library.

Based on the Vulkan Headers 1.4.309.

Vkad offers three types and functions and utility macros for the use of Vulkan function loading.

Vkad should be included instead of `vulkan.h`. It will include it, and expects to find it under the path `<vulkan/vulkan.h>`.
`VK_USE_PLATFORM_`* macros should be defined before the inclusion of vkad, unsupported ones will give error messages (notably `VK_USE_PLATFORM_SCI`).

Vkad defines three struct types: `VkadGlobalFunctions`, `VkadInstanceFunctions`, and `VkadDeviceFunctions`, each with a corresponding function:
```c
void vkadLoadGlobalFunctions  (PFN_vkGetInstanceProcAddr loader, VkadGlobalFunctions* functions);
void vkadLoadInstanceFunctions(PFN_vkGetInstanceProcAddr loader, VkInstance instance, VkadInstanceFunctions* functions);
void vkadLoadDeviceFunctions  (PFN_vkGetDeviceProcAddr loader, VkDevice device, VkadDeviceFunctions* functions);
```
The struct will contain function pointers with member names equivalent to the functions of the appropriate access level, but with the `vk` prefix removes (for example. `VkadDeviceFunctions` has a member `CreateCommandPool` of type `PFN_vkCreateCommandPool`, loaded by `vkadLoadDeviceFunctions` to point to `vkCreateCommandPool`). The function will load all of those pointers, including the platform pointers. Pointers of platforms not included with the macros will be loaded anyway for having a fixed size of these structs, but the type of these members will be `PFN_vkVoidFunction` instead of the correct function pointer type. This means that the type definition, althought not the size, of these structure types can differ when vkad is included in different files with inconsistent platform macros. However, all vkad functions are defined with `static`, so there should be no linking issue, merely an issue of inconsistent type definitions when compiling in the same step. (This is to assist linking general purpose libraries with platform specific ones, if they are compiled seperately.)

By default, vkad defines cnvenience macros, so that if you set:
```c
#define VKAD_USER_GLOBAL   my_vkadGlobalFunctions
#define VKAD_USER_INSTANCE my_vkadInstanceFunctions
#define VKAD_USER_DEVICE   my_vkadDeviceFunctions
```
with `my_vkadGlobalFunctions`, `my_vkadInstanceFunctions` and `my_vkadDeviceFunctions` pointing to a struct of the indicated type somewhere, then a call to `vkCreateCommandPool` will in fact be resolved to `my_vkadDeviceFunctions.CreateCommandPool`. If this macro resolution is not desired, and the user wants to create an alternative resolution to these shorter named symbols, all of these definitions can be suppressed by defining `VKAD_NO_GLOBAL_SYMBOLS`.
