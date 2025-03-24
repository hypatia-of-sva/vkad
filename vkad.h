/*  vkad - a vulkan function loading utility library.
    Copyright (c) 2024-2025     Hypatia of Sva <hypatia.sva@posteo.eu>
    SPDX-License-Identifier: MIT

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
*/



#pragma once

/* only include vkad if the Vulkan headers are not included in another way, because we include them again, and they may have been included with prototypes */
#if !(defined(VKAD_H)) && !(defined(VK_VERSION_1_0))
#define VKAD_H

/* revision date */
#define VKAD_HEADER_REVISION 0x20250323

#ifdef __cplusplus
#define REINTERPRET_CAST(X,Y) reinterpret_cast<X>(Y)
#else
#define REINTERPRET_CAST(X,Y) ((X) Y)
#endif

#if defined(__cplusplus)
extern "C" {
#endif

/* give a better error message than "header not found" */
#ifdef VK_USE_PLATFORM_SCI
#error Nvidia Sci Platform only supported on Vulkan SC, not main Vulkan!
#endif

/* unconditionally excölude prototypes. */
#ifndef VK_NO_PROTOTYPES
#define VK_NO_PROTOTYPES
#endif

#include <vulkan/vulkan.h>

#if VK_HEADER_VERSION < 309
#error "Vulkan headers are out of date! Download at least 1.4.309."
#endif

/* define all platform pointers as void functions in case the headers do not get included; since they have to be convertible from that by a cast, the code should be compatible */
#ifndef VK_USE_PLATFORM_ANDROID_KHR
typedef PFN_vkVoidFunction PFN_vkCreateAndroidSurfaceKHR;
typedef PFN_vkVoidFunction PFN_vkGetAndroidHardwareBufferPropertiesANDROID;
typedef PFN_vkVoidFunction PFN_vkGetMemoryAndroidHardwareBufferANDROID;
#endif
#ifndef VK_USE_PLATFORM_FUCHSIA
typedef PFN_vkVoidFunction PFN_vkCreateImagePipeSurfaceFUCHSIA;
typedef PFN_vkVoidFunction PFN_vkGetMemoryZirconHandleFUCHSIA;
typedef PFN_vkVoidFunction PFN_vkGetMemoryZirconHandlePropertiesFUCHSIA;
typedef PFN_vkVoidFunction PFN_vkImportSemaphoreZirconHandleFUCHSIA;
typedef PFN_vkVoidFunction PFN_vkGetSemaphoreZirconHandleFUCHSIA;
typedef PFN_vkVoidFunction PFN_vkCreateBufferCollectionFUCHSIA;
typedef PFN_vkVoidFunction PFN_vkSetBufferCollectionImageConstraintsFUCHSIA;
typedef PFN_vkVoidFunction PFN_vkSetBufferCollectionBufferConstraintsFUCHSIA;
typedef PFN_vkVoidFunction PFN_vkDestroyBufferCollectionFUCHSIA;
typedef PFN_vkVoidFunction PFN_vkGetBufferCollectionPropertiesFUCHSIA;
#endif
#ifndef VK_USE_PLATFORM_IOS_MVK
typedef PFN_vkVoidFunction PFN_vkCreateIOSSurfaceMVK;
#endif
#ifndef VK_USE_PLATFORM_MACOS_MVK
typedef PFN_vkVoidFunction PFN_vkCreateMacOSSurfaceMVK;
#endif
#ifndef VK_USE_PLATFORM_METAL_EXT
typedef PFN_vkVoidFunction PFN_vkCreateMetalSurfaceEXT;
typedef PFN_vkVoidFunction PFN_vkExportMetalObjectsEXT;
typedef PFN_vkVoidFunction PFN_vkGetMemoryMetalHandleEXT;
typedef PFN_vkVoidFunction PFN_vkGetMemoryMetalHandlePropertiesEXT;
#endif
#ifndef VK_USE_PLATFORM_VI_NN
typedef PFN_vkVoidFunction PFN_vkCreateViSurfaceNN;
#endif
#ifndef VK_USE_PLATFORM_WAYLAND_KHR
typedef PFN_vkVoidFunction PFN_vkCreateWaylandSurfaceKHR;
typedef PFN_vkVoidFunction PFN_vkGetPhysicalDeviceWaylandPresentationSupportKHR;
#endif
#ifndef VK_USE_PLATFORM_WIN32_KHR
typedef PFN_vkVoidFunction PFN_vkCreateWin32SurfaceKHR;
typedef PFN_vkVoidFunction PFN_vkGetPhysicalDeviceWin32PresentationSupportKHR;
typedef PFN_vkVoidFunction PFN_vkGetPhysicalDeviceSurfacePresentModes2EXT;
typedef PFN_vkVoidFunction PFN_vkAcquireWinrtDisplayNV;
typedef PFN_vkVoidFunction PFN_vkGetWinrtDisplayNV;
typedef PFN_vkVoidFunction PFN_vkGetMemoryWin32HandleKHR;
typedef PFN_vkVoidFunction PFN_vkGetMemoryWin32HandlePropertiesKHR;
typedef PFN_vkVoidFunction PFN_vkImportSemaphoreWin32HandleKHR;
typedef PFN_vkVoidFunction PFN_vkGetSemaphoreWin32HandleKHR;
typedef PFN_vkVoidFunction PFN_vkImportFenceWin32HandleKHR;
typedef PFN_vkVoidFunction PFN_vkGetFenceWin32HandleKHR;
typedef PFN_vkVoidFunction PFN_vkGetMemoryWin32HandleNV;
typedef PFN_vkVoidFunction PFN_vkAcquireFullScreenExclusiveModeEXT;
typedef PFN_vkVoidFunction PFN_vkReleaseFullScreenExclusiveModeEXT;
typedef PFN_vkVoidFunction PFN_vkGetDeviceGroupSurfacePresentModes2EXT;
#endif
#ifndef VK_USE_PLATFORM_XCB_KHR
typedef PFN_vkVoidFunction PFN_vkCreateXcbSurfaceKHR;
typedef PFN_vkVoidFunction PFN_vkGetPhysicalDeviceXcbPresentationSupportKHR;
#endif
#ifndef VK_USE_PLATFORM_XLIB_KHR
typedef PFN_vkVoidFunction PFN_vkCreateXlibSurfaceKHR;
typedef PFN_vkVoidFunction PFN_vkGetPhysicalDeviceXlibPresentationSupportKHR;
#endif
#ifndef VK_USE_PLATFORM_DIRECTFB_EXT
typedef PFN_vkVoidFunction PFN_vkCreateDirectFBSurfaceEXT;
typedef PFN_vkVoidFunction PFN_vkGetPhysicalDeviceDirectFBPresentationSupportEXT;
#endif
#ifndef VK_USE_PLATFORM_XLIB_XRANDR_EXT
typedef PFN_vkVoidFunction PFN_vkAcquireXlibDisplayEXT;
typedef PFN_vkVoidFunction PFN_vkGetRandROutputDisplayEXT;
#endif
#ifndef VK_USE_PLATFORM_GGP
typedef PFN_vkVoidFunction PFN_vkCreateStreamDescriptorSurfaceGGP;
#endif
#ifndef VK_USE_PLATFORM_SCREEN_QNX
typedef PFN_vkVoidFunction PFN_vkCreateScreenSurfaceQNX;
typedef PFN_vkVoidFunction PFN_vkGetPhysicalDeviceScreenPresentationSupportQNX;
typedef PFN_vkVoidFunction PFN_vkGetScreenBufferPropertiesQNX;
#endif
#ifndef VK_ENABLE_BETA_EXTENSIONS
typedef PFN_vkVoidFunction PFN_vkCreateExecutionGraphPipelinesAMDX;
typedef PFN_vkVoidFunction PFN_vkGetExecutionGraphPipelineScratchSizeAMDX;
typedef PFN_vkVoidFunction PFN_vkGetExecutionGraphPipelineNodeIndexAMDX;
typedef PFN_vkVoidFunction PFN_vkCmdInitializeGraphScratchMemoryAMDX;
typedef PFN_vkVoidFunction PFN_vkCmdDispatchGraphAMDX;
typedef PFN_vkVoidFunction PFN_vkCmdDispatchGraphIndirectAMDX;
typedef PFN_vkVoidFunction PFN_vkCmdDispatchGraphIndirectCountAMDX;
#endif

typedef struct VkadGlobalFunctions {
    /* VK_VERSION_1_0 */
    PFN_vkEnumerateInstanceExtensionProperties                              EnumerateInstanceExtensionProperties                            ;
    PFN_vkEnumerateInstanceLayerProperties                                  EnumerateInstanceLayerProperties                                ;
    PFN_vkCreateInstance                                                    CreateInstance                                                  ;
    /* VK_VERSION_1_1 */                                                                                                                    
    PFN_vkEnumerateInstanceVersion                                          EnumerateInstanceVersion                                        ;
} VkadGlobalFunctions;                                                                                                                      
typedef struct VkadInstanceFunctions {                                                                                                      
    /* VK_VERSION_1_0 */                                                                                                                    
    PFN_vkDestroyInstance                                                   DestroyInstance                                                 ;
    PFN_vkEnumeratePhysicalDevices                                          EnumeratePhysicalDevices                                        ;
    PFN_vkGetPhysicalDeviceFeatures                                         GetPhysicalDeviceFeatures                                       ;
    PFN_vkGetPhysicalDeviceFormatProperties                                 GetPhysicalDeviceFormatProperties                               ;
    PFN_vkGetPhysicalDeviceImageFormatProperties                            GetPhysicalDeviceImageFormatProperties                          ;
    PFN_vkGetPhysicalDeviceProperties                                       GetPhysicalDeviceProperties                                     ;
    PFN_vkGetPhysicalDeviceQueueFamilyProperties                            GetPhysicalDeviceQueueFamilyProperties                          ;
    PFN_vkGetPhysicalDeviceMemoryProperties                                 GetPhysicalDeviceMemoryProperties                               ;
    PFN_vkEnumerateDeviceExtensionProperties                                EnumerateDeviceExtensionProperties                              ;
    PFN_vkEnumerateDeviceLayerProperties                                    EnumerateDeviceLayerProperties                                  ;
    PFN_vkGetPhysicalDeviceSparseImageFormatProperties                      GetPhysicalDeviceSparseImageFormatProperties                    ;
    PFN_vkCreateDevice                                                      CreateDevice                                                    ;
    PFN_vkGetDeviceProcAddr                                                 GetDeviceProcAddr                                               ;
    /* VK_VERSION_1_1 */                                                                                                                    
    PFN_vkEnumeratePhysicalDeviceGroups                                     EnumeratePhysicalDeviceGroups                                   ;
    PFN_vkGetPhysicalDeviceFeatures2                                        GetPhysicalDeviceFeatures2                                      ;
    PFN_vkGetPhysicalDeviceProperties2                                      GetPhysicalDeviceProperties2                                    ;
    PFN_vkGetPhysicalDeviceFormatProperties2                                GetPhysicalDeviceFormatProperties2                              ;
    PFN_vkGetPhysicalDeviceImageFormatProperties2                           GetPhysicalDeviceImageFormatProperties2                         ;
    PFN_vkGetPhysicalDeviceQueueFamilyProperties2                           GetPhysicalDeviceQueueFamilyProperties2                         ;
    PFN_vkGetPhysicalDeviceMemoryProperties2                                GetPhysicalDeviceMemoryProperties2                              ;
    PFN_vkGetPhysicalDeviceSparseImageFormatProperties2                     GetPhysicalDeviceSparseImageFormatProperties2                   ;
    PFN_vkGetPhysicalDeviceExternalBufferProperties                         GetPhysicalDeviceExternalBufferProperties                       ;
    PFN_vkGetPhysicalDeviceExternalFenceProperties                          GetPhysicalDeviceExternalFenceProperties                        ;
    PFN_vkGetPhysicalDeviceExternalSemaphoreProperties                      GetPhysicalDeviceExternalSemaphoreProperties                    ;
    /* VK_VERSION_1_3 */                                                    
    PFN_vkGetPhysicalDeviceToolProperties                                   GetPhysicalDeviceToolProperties                                 ;
    /* VK_KHR_surface spec_version 25  */                                                                                                   
    PFN_vkDestroySurfaceKHR                                                 DestroySurfaceKHR                                               ;
    PFN_vkGetPhysicalDeviceSurfaceSupportKHR                                GetPhysicalDeviceSurfaceSupportKHR                              ;
    PFN_vkGetPhysicalDeviceSurfaceCapabilitiesKHR                           GetPhysicalDeviceSurfaceCapabilitiesKHR                         ;
    PFN_vkGetPhysicalDeviceSurfaceFormatsKHR                                GetPhysicalDeviceSurfaceFormatsKHR                              ;
    PFN_vkGetPhysicalDeviceSurfacePresentModesKHR                           GetPhysicalDeviceSurfacePresentModesKHR                         ;
    /* VK_KHR_swapchain spec_version 70  */                                                                                                 
    PFN_vkGetPhysicalDevicePresentRectanglesKHR                             GetPhysicalDevicePresentRectanglesKHR                           ;
    /* VK_KHR_display spec_version 23  */                                                                                                   
    PFN_vkGetPhysicalDeviceDisplayPropertiesKHR                             GetPhysicalDeviceDisplayPropertiesKHR                           ;
    PFN_vkGetPhysicalDeviceDisplayPlanePropertiesKHR                        GetPhysicalDeviceDisplayPlanePropertiesKHR                      ;
    PFN_vkGetDisplayPlaneSupportedDisplaysKHR                               GetDisplayPlaneSupportedDisplaysKHR                             ;
    PFN_vkGetDisplayModePropertiesKHR                                       GetDisplayModePropertiesKHR                                     ;
    PFN_vkCreateDisplayModeKHR                                              CreateDisplayModeKHR                                            ;
    PFN_vkGetDisplayPlaneCapabilitiesKHR                                    GetDisplayPlaneCapabilitiesKHR                                  ;
    PFN_vkCreateDisplayPlaneSurfaceKHR                                      CreateDisplayPlaneSurfaceKHR                                    ;
    /* VK_KHR_video_queue spec_version 8 */                                                                                                 
    PFN_vkGetPhysicalDeviceVideoCapabilitiesKHR                             GetPhysicalDeviceVideoCapabilitiesKHR                           ;
    PFN_vkGetPhysicalDeviceVideoFormatPropertiesKHR                         GetPhysicalDeviceVideoFormatPropertiesKHR                       ;
    /* VK_KHR_get_physical_device_properties2 spec_version 2 */                                                                             
    PFN_vkGetPhysicalDeviceFeatures2KHR                                     GetPhysicalDeviceFeatures2KHR                                   ;
    PFN_vkGetPhysicalDeviceProperties2KHR                                   GetPhysicalDeviceProperties2KHR                                 ;
    PFN_vkGetPhysicalDeviceFormatProperties2KHR                             GetPhysicalDeviceFormatProperties2KHR                           ;
    PFN_vkGetPhysicalDeviceImageFormatProperties2KHR                        GetPhysicalDeviceImageFormatProperties2KHR                      ;
    PFN_vkGetPhysicalDeviceQueueFamilyProperties2KHR                        GetPhysicalDeviceQueueFamilyProperties2KHR                      ;
    PFN_vkGetPhysicalDeviceMemoryProperties2KHR                             GetPhysicalDeviceMemoryProperties2KHR                           ;
    PFN_vkGetPhysicalDeviceSparseImageFormatProperties2KHR                  GetPhysicalDeviceSparseImageFormatProperties2KHR                ;
    /* VK_KHR_device_group_creation spec_version 1 */
    PFN_vkEnumeratePhysicalDeviceGroupsKHR                                  EnumeratePhysicalDeviceGroupsKHR                                ;
    /* VK_KHR_external_memory_capabilities spec_version 1 */                                                                                
    PFN_vkGetPhysicalDeviceExternalBufferPropertiesKHR                      GetPhysicalDeviceExternalBufferPropertiesKHR                    ;
    /* VK_KHR_external_semaphore_capabilities spec_version 1 */                                                                             
    PFN_vkGetPhysicalDeviceExternalSemaphorePropertiesKHR                   GetPhysicalDeviceExternalSemaphorePropertiesKHR                 ;
    /* VK_KHR_external_fence_capabilities spec_version 1 */
    PFN_vkGetPhysicalDeviceExternalFencePropertiesKHR                       GetPhysicalDeviceExternalFencePropertiesKHR                     ;
    /* VK_KHR_performance_query spec_version 1 */
    PFN_vkEnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR     EnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR   ;
    PFN_vkGetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR             GetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR           ;
    /* VK_KHR_get_surface_capabilities2 spec_version 1 */
    PFN_vkGetPhysicalDeviceSurfaceCapabilities2KHR                          GetPhysicalDeviceSurfaceCapabilities2KHR                        ;
    PFN_vkGetPhysicalDeviceSurfaceFormats2KHR                               GetPhysicalDeviceSurfaceFormats2KHR                             ;
    /* VK_KHR_get_display_properties2 spec_version 1 */
    PFN_vkGetPhysicalDeviceDisplayProperties2KHR                            GetPhysicalDeviceDisplayProperties2KHR                          ;
    PFN_vkGetPhysicalDeviceDisplayPlaneProperties2KHR                       GetPhysicalDeviceDisplayPlaneProperties2KHR                     ;  
    PFN_vkGetDisplayModeProperties2KHR                                      GetDisplayModeProperties2KHR                                    ;
    PFN_vkGetDisplayPlaneCapabilities2KHR                                   GetDisplayPlaneCapabilities2KHR                                 ;
    /* VK_KHR_fragment_shading_rate spec_version 2 */
    PFN_vkGetPhysicalDeviceFragmentShadingRatesKHR                          GetPhysicalDeviceFragmentShadingRatesKHR                        ;
    /* VK_KHR_video_encode_queue spec_version 12 */
    PFN_vkGetPhysicalDeviceVideoEncodeQualityLevelPropertiesKHR             GetPhysicalDeviceVideoEncodeQualityLevelPropertiesKHR           ;
    /* VK_KHR_cooperative_matrix spec_version 2 */
    PFN_vkGetPhysicalDeviceCooperativeMatrixPropertiesKHR                   GetPhysicalDeviceCooperativeMatrixPropertiesKHR                 ;
    /* VK_KHR_calibrated_timestamps spec_version 1 */
    PFN_vkGetPhysicalDeviceCalibrateableTimeDomainsKHR                      GetPhysicalDeviceCalibrateableTimeDomainsKHR                    ;
    /* VK_EXT_debug_report spec_version 10 */
    PFN_vkCreateDebugReportCallbackEXT                                      CreateDebugReportCallbackEXT                                    ;
    PFN_vkDestroyDebugReportCallbackEXT                                     DestroyDebugReportCallbackEXT                                   ;
    PFN_vkDebugReportMessageEXT                                             DebugReportMessageEXT                                           ;
    /* VK_NV_external_memory_capabilities spec_version 1 */
    PFN_vkGetPhysicalDeviceExternalImageFormatPropertiesNV                  GetPhysicalDeviceExternalImageFormatPropertiesNV                ;
    /* VK_EXT_direct_mode_display spec_version 1 */
    PFN_vkReleaseDisplayEXT                                                 ReleaseDisplayEXT                                               ;
    /* VK_EXT_display_surface_counter spec_version 1 */
    PFN_vkGetPhysicalDeviceSurfaceCapabilities2EXT                          GetPhysicalDeviceSurfaceCapabilities2EXT                        ;
    /* VK_EXT_debug_utils spec_version 2 */
    PFN_vkCreateDebugUtilsMessengerEXT                                      CreateDebugUtilsMessengerEXT                                    ;
    PFN_vkDestroyDebugUtilsMessengerEXT                                     DestroyDebugUtilsMessengerEXT                                   ;
    PFN_vkSubmitDebugUtilsMessageEXT                                        SubmitDebugUtilsMessageEXT                                      ;
    /* VK_EXT_sample_locations spec_version 1 */
    PFN_vkGetPhysicalDeviceMultisamplePropertiesEXT                         GetPhysicalDeviceMultisamplePropertiesEXT                       ;
    /* VK_EXT_calibrated_timestamps spec_version 2 */
    PFN_vkGetPhysicalDeviceCalibrateableTimeDomainsEXT                      GetPhysicalDeviceCalibrateableTimeDomainsEXT                    ;
    /* VK_EXT_tooling_info spec_version 1 */
    PFN_vkGetPhysicalDeviceToolPropertiesEXT                                GetPhysicalDeviceToolPropertiesEXT                              ;
    /* VK_NV_cooperative_matrix spec_version 1 */
    PFN_vkGetPhysicalDeviceCooperativeMatrixPropertiesNV                    GetPhysicalDeviceCooperativeMatrixPropertiesNV                  ;
    /* VK_NV_coverage_reduction_mode spec_version 1 */
    PFN_vkGetPhysicalDeviceSupportedFramebufferMixedSamplesCombinationsNV   GetPhysicalDeviceSupportedFramebufferMixedSamplesCombinationsNV ;
    /* VK_EXT_headless_surface spec_version 1 */
    PFN_vkCreateHeadlessSurfaceEXT                                          CreateHeadlessSurfaceEXT                                        ;
    /* VK_EXT_acquire_drm_display spec_version 1 */
    PFN_vkAcquireDrmDisplayEXT                                              AcquireDrmDisplayEXT                                            ;
    PFN_vkGetDrmDisplayEXT                                                  GetDrmDisplayEXT                                                ;
    /* VK_NV_optical_flow spec_version 1 */
    PFN_vkGetPhysicalDeviceOpticalFlowImageFormatsNV                        GetPhysicalDeviceOpticalFlowImageFormatsNV                      ;
    /* VK_KHR_android_surface spec_version 6 */
    PFN_vkCreateAndroidSurfaceKHR                                           CreateAndroidSurfaceKHR                                         ;
    /* VK_FUCHSIA_imagepipe_surface spec_version 1 */
    PFN_vkCreateImagePipeSurfaceFUCHSIA                                     CreateImagePipeSurfaceFUCHSIA                                   ;
    /* VK_MVK_ios_surface spec_version 3 */
    PFN_vkCreateIOSSurfaceMVK                                               CreateIOSSurfaceMVK                                             ;
    /* VK_MVK_macos_surface spec_version 3 */
    PFN_vkCreateMacOSSurfaceMVK                                             CreateMacOSSurfaceMVK                                           ;
    /* VK_EXT_metal_surface spec_version 1 */
    PFN_vkCreateMetalSurfaceEXT                                             CreateMetalSurfaceEXT                                           ;
    /* VK_NN_vi_surface spec_version 1 */
    PFN_vkCreateViSurfaceNN                                                 CreateViSurfaceNN                                               ;
    /* VK_KHR_wayland_surface spec_version 6 */
    PFN_vkCreateWaylandSurfaceKHR                                           CreateWaylandSurfaceKHR                                         ;
    PFN_vkGetPhysicalDeviceWaylandPresentationSupportKHR                    GetPhysicalDeviceWaylandPresentationSupportKHR                  ;
    /* VK_KHR_win32_surface spec_version 6 */
    PFN_vkCreateWin32SurfaceKHR                                             CreateWin32SurfaceKHR                                           ;
    PFN_vkGetPhysicalDeviceWin32PresentationSupportKHR                      GetPhysicalDeviceWin32PresentationSupportKHR                    ;
    /* VK_EXT_full_screen_exclusive spec_version 4 */
    PFN_vkGetPhysicalDeviceSurfacePresentModes2EXT                          GetPhysicalDeviceSurfacePresentModes2EXT                        ;
    /* VK_NV_acquire_winrt_display spec_version 1 */
    PFN_vkAcquireWinrtDisplayNV                                             AcquireWinrtDisplayNV                                           ;
    PFN_vkGetWinrtDisplayNV                                                 GetWinrtDisplayNV                                               ;
    /* VK_KHR_xcb_surface spec_version 6 */
    PFN_vkCreateXcbSurfaceKHR                                               CreateXcbSurfaceKHR                                             ;
    PFN_vkGetPhysicalDeviceXcbPresentationSupportKHR                        GetPhysicalDeviceXcbPresentationSupportKHR                      ;
    /* VK_KHR_xlib_surface spec_version 6 */
    PFN_vkCreateXlibSurfaceKHR                                              CreateXlibSurfaceKHR                                            ;
    PFN_vkGetPhysicalDeviceXlibPresentationSupportKHR                       GetPhysicalDeviceXlibPresentationSupportKHR                     ;
    /* VK_EXT_directfb_surface spec_version 1 */
    PFN_vkCreateDirectFBSurfaceEXT                                          CreateDirectFBSurfaceEXT                                        ;
    PFN_vkGetPhysicalDeviceDirectFBPresentationSupportEXT                   GetPhysicalDeviceDirectFBPresentationSupportEXT                 ;
    /* VK_EXT_acquire_xlib_display spec_version 1 */
    PFN_vkAcquireXlibDisplayEXT                                             AcquireXlibDisplayEXT                                           ;
    PFN_vkGetRandROutputDisplayEXT                                          GetRandROutputDisplayEXT                                        ;
    /* VK_GGP_stream_descriptor_surface spec_version 1 */
    PFN_vkCreateStreamDescriptorSurfaceGGP                                  CreateStreamDescriptorSurfaceGGP                                ;
    /* VK_QNX_screen_surface spec_version 1 */
    PFN_vkCreateScreenSurfaceQNX                                            CreateScreenSurfaceQNX                                          ;
    PFN_vkGetPhysicalDeviceScreenPresentationSupportQNX                     GetPhysicalDeviceScreenPresentationSupportQNX                   ;
        /* Additions from 1.3.284 to 1.4.309: */
    /* VK_NV_cooperative_vector spec_version 4 */
    PFN_vkGetPhysicalDeviceCooperativeVectorPropertiesNV                    GetPhysicalDeviceCooperativeVectorPropertiesNV                  ;
    /* VK_NV_cooperative_matrix2 spec_version 1 */
    PFN_vkGetPhysicalDeviceCooperativeMatrixFlexibleDimensionsPropertiesNV  GetPhysicalDeviceCooperativeMatrixFlexibleDimensionsPropertiesNV;
} VkadInstanceFunctions;
typedef struct VkadDeviceFunctions {
    /* VK_VERSION_1_0 */
    PFN_vkDestroyDevice                                                     DestroyDevice                                                   ;
    PFN_vkGetDeviceQueue                                                    GetDeviceQueue                                                  ;
    PFN_vkQueueSubmit                                                       QueueSubmit                                                     ;
    PFN_vkQueueWaitIdle                                                     QueueWaitIdle                                                   ;
    PFN_vkDeviceWaitIdle                                                    DeviceWaitIdle                                                  ;
    PFN_vkAllocateMemory                                                    AllocateMemory                                                  ;
    PFN_vkFreeMemory                                                        FreeMemory                                                      ;
    PFN_vkMapMemory                                                         MapMemory                                                       ;
    PFN_vkUnmapMemory                                                       UnmapMemory                                                     ;
    PFN_vkFlushMappedMemoryRanges                                           FlushMappedMemoryRanges                                         ;
    PFN_vkInvalidateMappedMemoryRanges                                      InvalidateMappedMemoryRanges                                    ;
    PFN_vkGetDeviceMemoryCommitment                                         GetDeviceMemoryCommitment                                       ;
    PFN_vkBindBufferMemory                                                  BindBufferMemory                                                ;
    PFN_vkBindImageMemory                                                   BindImageMemory                                                 ;
    PFN_vkGetBufferMemoryRequirements                                       GetBufferMemoryRequirements                                     ;
    PFN_vkGetImageMemoryRequirements                                        GetImageMemoryRequirements                                      ;
    PFN_vkGetImageSparseMemoryRequirements                                  GetImageSparseMemoryRequirements                                ;
    PFN_vkQueueBindSparse                                                   QueueBindSparse                                                 ;
    PFN_vkCreateFence                                                       CreateFence                                                     ;
    PFN_vkDestroyFence                                                      DestroyFence                                                    ;
    PFN_vkResetFences                                                       ResetFences                                                     ;
    PFN_vkGetFenceStatus                                                    GetFenceStatus                                                  ;
    PFN_vkWaitForFences                                                     WaitForFences                                                   ;
    PFN_vkCreateSemaphore                                                   CreateSemaphore                                                 ;
    PFN_vkDestroySemaphore                                                  DestroySemaphore                                                ;
    PFN_vkCreateEvent                                                       CreateEvent                                                     ;
    PFN_vkDestroyEvent                                                      DestroyEvent                                                    ;
    PFN_vkGetEventStatus                                                    GetEventStatus                                                  ;
    PFN_vkSetEvent                                                          SetEvent                                                        ;
    PFN_vkResetEvent                                                        ResetEvent                                                      ;
    PFN_vkCreateQueryPool                                                   CreateQueryPool                                                 ;
    PFN_vkDestroyQueryPool                                                  DestroyQueryPool                                                ;
    PFN_vkGetQueryPoolResults                                               GetQueryPoolResults                                             ;
    PFN_vkCreateBuffer                                                      CreateBuffer                                                    ;
    PFN_vkDestroyBuffer                                                     DestroyBuffer                                                   ;
    PFN_vkCreateBufferView                                                  CreateBufferView                                                ;
    PFN_vkDestroyBufferView                                                 DestroyBufferView                                               ;
    PFN_vkCreateImage                                                       CreateImage                                                     ;
    PFN_vkDestroyImage                                                      DestroyImage                                                    ;
    PFN_vkGetImageSubresourceLayout                                         GetImageSubresourceLayout                                       ;
    PFN_vkCreateImageView                                                   CreateImageView                                                 ;
    PFN_vkDestroyImageView                                                  DestroyImageView                                                ;
    PFN_vkCreateShaderModule                                                CreateShaderModule                                              ;
    PFN_vkDestroyShaderModule                                               DestroyShaderModule                                             ;
    PFN_vkCreatePipelineCache                                               CreatePipelineCache                                             ;
    PFN_vkDestroyPipelineCache                                              DestroyPipelineCache                                            ;
    PFN_vkGetPipelineCacheData                                              GetPipelineCacheData                                            ;
    PFN_vkMergePipelineCaches                                               MergePipelineCaches                                             ;
    PFN_vkCreateGraphicsPipelines                                           CreateGraphicsPipelines                                         ;
    PFN_vkCreateComputePipelines                                            CreateComputePipelines                                          ;
    PFN_vkDestroyPipeline                                                   DestroyPipeline                                                 ;
    PFN_vkCreatePipelineLayout                                              CreatePipelineLayout                                            ;
    PFN_vkDestroyPipelineLayout                                             DestroyPipelineLayout                                           ;
    PFN_vkCreateSampler                                                     CreateSampler                                                   ;
    PFN_vkDestroySampler                                                    DestroySampler                                                  ;
    PFN_vkCreateDescriptorSetLayout                                         CreateDescriptorSetLayout                                       ;
    PFN_vkDestroyDescriptorSetLayout                                        DestroyDescriptorSetLayout                                      ;
    PFN_vkCreateDescriptorPool                                              CreateDescriptorPool                                            ;
    PFN_vkDestroyDescriptorPool                                             DestroyDescriptorPool                                           ;
    PFN_vkResetDescriptorPool                                               ResetDescriptorPool                                             ;
    PFN_vkAllocateDescriptorSets                                            AllocateDescriptorSets                                          ;
    PFN_vkFreeDescriptorSets                                                FreeDescriptorSets                                              ;
    PFN_vkUpdateDescriptorSets                                              UpdateDescriptorSets                                            ;
    PFN_vkCreateFramebuffer                                                 CreateFramebuffer                                               ;
    PFN_vkDestroyFramebuffer                                                DestroyFramebuffer                                              ;
    PFN_vkCreateRenderPass                                                  CreateRenderPass                                                ;
    PFN_vkDestroyRenderPass                                                 DestroyRenderPass                                               ;
    PFN_vkGetRenderAreaGranularity                                          GetRenderAreaGranularity                                        ;
    PFN_vkCreateCommandPool                                                 CreateCommandPool                                               ;
    PFN_vkDestroyCommandPool                                                DestroyCommandPool                                              ;
    PFN_vkResetCommandPool                                                  ResetCommandPool                                                ;
    PFN_vkAllocateCommandBuffers                                            AllocateCommandBuffers                                          ;
    PFN_vkFreeCommandBuffers                                                FreeCommandBuffers                                              ;
    PFN_vkBeginCommandBuffer                                                BeginCommandBuffer                                              ;
    PFN_vkEndCommandBuffer                                                  EndCommandBuffer                                                ;
    PFN_vkResetCommandBuffer                                                ResetCommandBuffer                                              ;
    PFN_vkCmdBindPipeline                                                   CmdBindPipeline                                                 ;
    PFN_vkCmdSetViewport                                                    CmdSetViewport                                                  ;
    PFN_vkCmdSetScissor                                                     CmdSetScissor                                                   ;
    PFN_vkCmdSetLineWidth                                                   CmdSetLineWidth                                                 ;
    PFN_vkCmdSetDepthBias                                                   CmdSetDepthBias                                                 ;
    PFN_vkCmdSetBlendConstants                                              CmdSetBlendConstants                                            ;
    PFN_vkCmdSetDepthBounds                                                 CmdSetDepthBounds                                               ;
    PFN_vkCmdSetStencilCompareMask                                          CmdSetStencilCompareMask                                        ;
    PFN_vkCmdSetStencilWriteMask                                            CmdSetStencilWriteMask                                          ;
    PFN_vkCmdSetStencilReference                                            CmdSetStencilReference                                          ;
    PFN_vkCmdBindDescriptorSets                                             CmdBindDescriptorSets                                           ;
    PFN_vkCmdBindIndexBuffer                                                CmdBindIndexBuffer                                              ;
    PFN_vkCmdBindVertexBuffers                                              CmdBindVertexBuffers                                            ;
    PFN_vkCmdDraw                                                           CmdDraw                                                         ;
    PFN_vkCmdDrawIndexed                                                    CmdDrawIndexed                                                  ;
    PFN_vkCmdDrawIndirect                                                   CmdDrawIndirect                                                 ;
    PFN_vkCmdDrawIndexedIndirect                                            CmdDrawIndexedIndirect                                          ;
    PFN_vkCmdDispatch                                                       CmdDispatch                                                     ;
    PFN_vkCmdDispatchIndirect                                               CmdDispatchIndirect                                             ;
    PFN_vkCmdCopyBuffer                                                     CmdCopyBuffer                                                   ;
    PFN_vkCmdCopyImage                                                      CmdCopyImage                                                    ;
    PFN_vkCmdBlitImage                                                      CmdBlitImage                                                    ;
    PFN_vkCmdCopyBufferToImage                                              CmdCopyBufferToImage                                            ;
    PFN_vkCmdCopyImageToBuffer                                              CmdCopyImageToBuffer                                            ;
    PFN_vkCmdUpdateBuffer                                                   CmdUpdateBuffer                                                 ;
    PFN_vkCmdFillBuffer                                                     CmdFillBuffer                                                   ;
    PFN_vkCmdClearColorImage                                                CmdClearColorImage                                              ;
    PFN_vkCmdClearDepthStencilImage                                         CmdClearDepthStencilImage                                       ;
    PFN_vkCmdClearAttachments                                               CmdClearAttachments                                             ;
    PFN_vkCmdResolveImage                                                   CmdResolveImage                                                 ;
    PFN_vkCmdSetEvent                                                       CmdSetEvent                                                     ;
    PFN_vkCmdResetEvent                                                     CmdResetEvent                                                   ;
    PFN_vkCmdWaitEvents                                                     CmdWaitEvents                                                   ;
    PFN_vkCmdPipelineBarrier                                                CmdPipelineBarrier                                              ;
    PFN_vkCmdBeginQuery                                                     CmdBeginQuery                                                   ;
    PFN_vkCmdEndQuery                                                       CmdEndQuery                                                     ;
    PFN_vkCmdResetQueryPool                                                 CmdResetQueryPool                                               ;
    PFN_vkCmdWriteTimestamp                                                 CmdWriteTimestamp                                               ;
    PFN_vkCmdCopyQueryPoolResults                                           CmdCopyQueryPoolResults                                         ;
    PFN_vkCmdPushConstants                                                  CmdPushConstants                                                ;
    PFN_vkCmdBeginRenderPass                                                CmdBeginRenderPass                                              ;
    PFN_vkCmdNextSubpass                                                    CmdNextSubpass                                                  ;
    PFN_vkCmdEndRenderPass                                                  CmdEndRenderPass                                                ;
    PFN_vkCmdExecuteCommands                                                CmdExecuteCommands                                              ;
    /* VK_VERSION_1_1 */
    PFN_vkBindBufferMemory2                                                 BindBufferMemory2                                               ;
    PFN_vkBindImageMemory2                                                  BindImageMemory2                                                ;
    PFN_vkGetDeviceGroupPeerMemoryFeatures                                  GetDeviceGroupPeerMemoryFeatures                                ;
    PFN_vkCmdSetDeviceMask                                                  CmdSetDeviceMask                                                ;
    PFN_vkCmdDispatchBase                                                   CmdDispatchBase                                                 ;
    PFN_vkGetImageMemoryRequirements2                                       GetImageMemoryRequirements2                                     ;
    PFN_vkGetBufferMemoryRequirements2                                      GetBufferMemoryRequirements2                                    ;
    PFN_vkGetImageSparseMemoryRequirements2                                 GetImageSparseMemoryRequirements2                               ;
    PFN_vkTrimCommandPool                                                   TrimCommandPool                                                 ;
    PFN_vkGetDeviceQueue2                                                   GetDeviceQueue2                                                 ;
    PFN_vkCreateSamplerYcbcrConversion                                      CreateSamplerYcbcrConversion                                    ;
    PFN_vkDestroySamplerYcbcrConversion                                     DestroySamplerYcbcrConversion                                   ;
    PFN_vkCreateDescriptorUpdateTemplate                                    CreateDescriptorUpdateTemplate                                  ;
    PFN_vkDestroyDescriptorUpdateTemplate                                   DestroyDescriptorUpdateTemplate                                 ;
    PFN_vkUpdateDescriptorSetWithTemplate                                   UpdateDescriptorSetWithTemplate                                 ;
    PFN_vkGetDescriptorSetLayoutSupport                                     GetDescriptorSetLayoutSupport                                   ;
    /* VK_VERSION_1_2 */
    PFN_vkCmdDrawIndirectCount                                              CmdDrawIndirectCount                                            ;
    PFN_vkCmdDrawIndexedIndirectCount                                       CmdDrawIndexedIndirectCount                                     ;
    PFN_vkCreateRenderPass2                                                 CreateRenderPass2                                               ;
    PFN_vkCmdBeginRenderPass2                                               CmdBeginRenderPass2                                             ;
    PFN_vkCmdNextSubpass2                                                   CmdNextSubpass2                                                 ;
    PFN_vkCmdEndRenderPass2                                                 CmdEndRenderPass2                                               ;
    PFN_vkResetQueryPool                                                    ResetQueryPool                                                  ;
    PFN_vkGetSemaphoreCounterValue                                          GetSemaphoreCounterValue                                        ;
    PFN_vkWaitSemaphores                                                    WaitSemaphores                                                  ;
    PFN_vkSignalSemaphore                                                   SignalSemaphore                                                 ;
    PFN_vkGetBufferDeviceAddress                                            GetBufferDeviceAddress                                          ;
    PFN_vkGetBufferOpaqueCaptureAddress                                     GetBufferOpaqueCaptureAddress                                   ;
    PFN_vkGetDeviceMemoryOpaqueCaptureAddress                               GetDeviceMemoryOpaqueCaptureAddress                             ;
    /* VK_VERSION_1_3 */
    PFN_vkCreatePrivateDataSlot                                             CreatePrivateDataSlot                                           ;
    PFN_vkDestroyPrivateDataSlot                                            DestroyPrivateDataSlot                                          ;
    PFN_vkSetPrivateData                                                    SetPrivateData                                                  ;
    PFN_vkGetPrivateData                                                    GetPrivateData                                                  ;
    PFN_vkCmdSetEvent2                                                      CmdSetEvent2                                                    ;
    PFN_vkCmdResetEvent2                                                    CmdResetEvent2                                                  ;
    PFN_vkCmdWaitEvents2                                                    CmdWaitEvents2                                                  ;
    PFN_vkCmdPipelineBarrier2                                               CmdPipelineBarrier2                                             ;
    PFN_vkCmdWriteTimestamp2                                                CmdWriteTimestamp2                                              ;
    PFN_vkQueueSubmit2                                                      QueueSubmit2                                                    ;
    PFN_vkCmdCopyBuffer2                                                    CmdCopyBuffer2                                                  ;
    PFN_vkCmdCopyImage2                                                     CmdCopyImage2                                                   ;
    PFN_vkCmdCopyBufferToImage2                                             CmdCopyBufferToImage2                                           ;
    PFN_vkCmdCopyImageToBuffer2                                             CmdCopyImageToBuffer2                                           ;
    PFN_vkCmdBlitImage2                                                     CmdBlitImage2                                                   ;
    PFN_vkCmdResolveImage2                                                  CmdResolveImage2                                                ;
    PFN_vkCmdBeginRendering                                                 CmdBeginRendering                                               ;
    PFN_vkCmdEndRendering                                                   CmdEndRendering                                                 ;
    PFN_vkCmdSetCullMode                                                    CmdSetCullMode                                                  ;
    PFN_vkCmdSetFrontFace                                                   CmdSetFrontFace                                                 ;
    PFN_vkCmdSetPrimitiveTopology                                           CmdSetPrimitiveTopology                                         ;
    PFN_vkCmdSetViewportWithCount                                           CmdSetViewportWithCount                                         ;
    PFN_vkCmdSetScissorWithCount                                            CmdSetScissorWithCount                                          ;
    PFN_vkCmdBindVertexBuffers2                                             CmdBindVertexBuffers2                                           ;
    PFN_vkCmdSetDepthTestEnable                                             CmdSetDepthTestEnable                                           ;
    PFN_vkCmdSetDepthWriteEnable                                            CmdSetDepthWriteEnable                                          ;
    PFN_vkCmdSetDepthCompareOp                                              CmdSetDepthCompareOp                                            ;
    PFN_vkCmdSetDepthBoundsTestEnable                                       CmdSetDepthBoundsTestEnable                                     ;
    PFN_vkCmdSetStencilTestEnable                                           CmdSetStencilTestEnable                                         ;
    PFN_vkCmdSetStencilOp                                                   CmdSetStencilOp                                                 ;
    PFN_vkCmdSetRasterizerDiscardEnable                                     CmdSetRasterizerDiscardEnable                                   ;
    PFN_vkCmdSetDepthBiasEnable                                             CmdSetDepthBiasEnable                                           ;
    PFN_vkCmdSetPrimitiveRestartEnable                                      CmdSetPrimitiveRestartEnable                                    ;
    PFN_vkGetDeviceBufferMemoryRequirements                                 GetDeviceBufferMemoryRequirements                               ;
    PFN_vkGetDeviceImageMemoryRequirements                                  GetDeviceImageMemoryRequirements                                ;
    PFN_vkGetDeviceImageSparseMemoryRequirements                            GetDeviceImageSparseMemoryRequirements                          ;
    /* VK_KHR_swapchain spec_version 70  */
    PFN_vkCreateSwapchainKHR                                                CreateSwapchainKHR                                              ;
    PFN_vkDestroySwapchainKHR                                               DestroySwapchainKHR                                             ;
    PFN_vkGetSwapchainImagesKHR                                             GetSwapchainImagesKHR                                           ;
    PFN_vkAcquireNextImageKHR                                               AcquireNextImageKHR                                             ;
    PFN_vkQueuePresentKHR                                                   QueuePresentKHR                                                 ;
    PFN_vkGetDeviceGroupPresentCapabilitiesKHR                              GetDeviceGroupPresentCapabilitiesKHR                            ;
    PFN_vkGetDeviceGroupSurfacePresentModesKHR                              GetDeviceGroupSurfacePresentModesKHR                            ;
    PFN_vkAcquireNextImage2KHR                                              AcquireNextImage2KHR                                            ;
    /* VK_KHR_display_swapchain spec_version 10  */
    PFN_vkCreateSharedSwapchainsKHR                                         CreateSharedSwapchainsKHR                                       ;
    /* VK_KHR_video_queue spec_version 8 */
    PFN_vkCreateVideoSessionKHR                                             CreateVideoSessionKHR                                           ;
    PFN_vkDestroyVideoSessionKHR                                            DestroyVideoSessionKHR                                          ;
    PFN_vkGetVideoSessionMemoryRequirementsKHR                              GetVideoSessionMemoryRequirementsKHR                            ;
    PFN_vkBindVideoSessionMemoryKHR                                         BindVideoSessionMemoryKHR                                       ;
    PFN_vkCreateVideoSessionParametersKHR                                   CreateVideoSessionParametersKHR                                 ;
    PFN_vkUpdateVideoSessionParametersKHR                                   UpdateVideoSessionParametersKHR                                 ;
    PFN_vkDestroyVideoSessionParametersKHR                                  DestroyVideoSessionParametersKHR                                ;
    PFN_vkCmdBeginVideoCodingKHR                                            CmdBeginVideoCodingKHR                                          ;
    PFN_vkCmdEndVideoCodingKHR                                              CmdEndVideoCodingKHR                                            ;
    PFN_vkCmdControlVideoCodingKHR                                          CmdControlVideoCodingKHR                                        ;
    /* VK_KHR_video_decode_queue spec_version 8 */
    PFN_vkCmdDecodeVideoKHR                                                 CmdDecodeVideoKHR                                               ;
    /* VK_KHR_dynamic_rendering spec_version 1 */
    PFN_vkCmdBeginRenderingKHR                                              CmdBeginRenderingKHR                                            ;
    PFN_vkCmdEndRenderingKHR                                                CmdEndRenderingKHR                                              ;
    /* VK_KHR_device_group spec_version 4 */
    PFN_vkGetDeviceGroupPeerMemoryFeaturesKHR                               GetDeviceGroupPeerMemoryFeaturesKHR                             ;
    PFN_vkCmdSetDeviceMaskKHR                                               CmdSetDeviceMaskKHR                                             ;
    PFN_vkCmdDispatchBaseKHR                                                CmdDispatchBaseKHR                                              ;
    /* VK_KHR_maintenance1 spec_version 2 */
    PFN_vkTrimCommandPoolKHR                                                TrimCommandPoolKHR                                              ;
    /* VK_KHR_external_memory_fd spec_version 1 */
    PFN_vkGetMemoryFdKHR                                                    GetMemoryFdKHR                                                  ;
    PFN_vkGetMemoryFdPropertiesKHR                                          GetMemoryFdPropertiesKHR                                        ;
    /* VK_KHR_external_semaphore_fd spec_version 1 */
    PFN_vkImportSemaphoreFdKHR                                              ImportSemaphoreFdKHR                                            ;
    PFN_vkGetSemaphoreFdKHR                                                 GetSemaphoreFdKHR                                               ;
    /* VK_KHR_push_descriptor spec_version 2 */
    PFN_vkCmdPushDescriptorSetKHR                                           CmdPushDescriptorSetKHR                                         ;
    PFN_vkCmdPushDescriptorSetWithTemplateKHR                               CmdPushDescriptorSetWithTemplateKHR                             ;
    /* VK_KHR_descriptor_update_template spec_version 1 */
    PFN_vkCreateDescriptorUpdateTemplateKHR                                 CreateDescriptorUpdateTemplateKHR                               ;
    PFN_vkDestroyDescriptorUpdateTemplateKHR                                DestroyDescriptorUpdateTemplateKHR                              ;
    PFN_vkUpdateDescriptorSetWithTemplateKHR                                UpdateDescriptorSetWithTemplateKHR                              ;
    /* VK_KHR_create_renderpass2 spec_version 1 */
    PFN_vkCreateRenderPass2KHR                                              CreateRenderPass2KHR                                            ;
    PFN_vkCmdBeginRenderPass2KHR                                            CmdBeginRenderPass2KHR                                          ;
    PFN_vkCmdNextSubpass2KHR                                                CmdNextSubpass2KHR                                              ;
    PFN_vkCmdEndRenderPass2KHR                                              CmdEndRenderPass2KHR                                            ;
    /* VK_KHR_shared_presentable_image spec_version 1 */
    PFN_vkGetSwapchainStatusKHR                                             GetSwapchainStatusKHR                                           ;
    /* VK_KHR_external_fence_fd spec_version 1 */
    PFN_vkImportFenceFdKHR                                                  ImportFenceFdKHR                                                ;
    PFN_vkGetFenceFdKHR                                                     GetFenceFdKHR                                                   ;
    /* VK_KHR_performance_query spec_version 1 */
    PFN_vkAcquireProfilingLockKHR                                           AcquireProfilingLockKHR                                         ;
    PFN_vkReleaseProfilingLockKHR                                           ReleaseProfilingLockKHR                                         ;
    /* VK_KHR_get_memory_requirements2 spec_version 1 */
    PFN_vkGetImageMemoryRequirements2KHR                                    GetImageMemoryRequirements2KHR                                  ;
    PFN_vkGetBufferMemoryRequirements2KHR                                   GetBufferMemoryRequirements2KHR                                 ;
    PFN_vkGetImageSparseMemoryRequirements2KHR                              GetImageSparseMemoryRequirements2KHR                            ;
    /* VK_KHR_sampler_ycbcr_conversion spec_version 14 */
    PFN_vkCreateSamplerYcbcrConversionKHR                                   CreateSamplerYcbcrConversionKHR                                 ;
    PFN_vkDestroySamplerYcbcrConversionKHR                                  DestroySamplerYcbcrConversionKHR                                ;
    /* VK_KHR_bind_memory2 spec_version 1 */
    PFN_vkBindBufferMemory2KHR                                              BindBufferMemory2KHR                                            ;
    PFN_vkBindImageMemory2KHR                                               BindImageMemory2KHR                                             ;
    /* VK_KHR_maintenance3 spec_version 1 */
    PFN_vkGetDescriptorSetLayoutSupportKHR                                  GetDescriptorSetLayoutSupportKHR                                ;
    /* VK_KHR_draw_indirect_count spec_version 1 */
    PFN_vkCmdDrawIndirectCountKHR                                           CmdDrawIndirectCountKHR                                         ;
    PFN_vkCmdDrawIndexedIndirectCountKHR                                    CmdDrawIndexedIndirectCountKHR                                  ;
    /* VK_KHR_timeline_semaphore spec_version 2 */
    PFN_vkGetSemaphoreCounterValueKHR                                       GetSemaphoreCounterValueKHR                                     ;
    PFN_vkWaitSemaphoresKHR                                                 WaitSemaphoresKHR                                               ;
    PFN_vkSignalSemaphoreKHR                                                SignalSemaphoreKHR                                              ;
    /* VK_KHR_fragment_shading_rate spec_version 2 */
    PFN_vkCmdSetFragmentShadingRateKHR                                      CmdSetFragmentShadingRateKHR                                    ;
    /* VK_KHR_dynamic_rendering_local_read spec_version 1 */
    PFN_vkCmdSetRenderingAttachmentLocationsKHR                             CmdSetRenderingAttachmentLocationsKHR                           ;
    PFN_vkCmdSetRenderingInputAttachmentIndicesKHR                          CmdSetRenderingInputAttachmentIndicesKHR                        ;
    /* VK_KHR_present_wait spec_version 1 */
    PFN_vkWaitForPresentKHR                                                 WaitForPresentKHR                                               ;
    /* VK_KHR_buffer_device_address spec_version 1 */
    PFN_vkGetBufferDeviceAddressKHR                                         GetBufferDeviceAddressKHR                                       ;
    PFN_vkGetBufferOpaqueCaptureAddressKHR                                  GetBufferOpaqueCaptureAddressKHR                                ;
    PFN_vkGetDeviceMemoryOpaqueCaptureAddressKHR                            GetDeviceMemoryOpaqueCaptureAddressKHR                          ;
    /* VK_KHR_deferred_host_operations spec_version 4 */
    PFN_vkCreateDeferredOperationKHR                                        CreateDeferredOperationKHR                                      ;
    PFN_vkDestroyDeferredOperationKHR                                       DestroyDeferredOperationKHR                                     ;
    PFN_vkGetDeferredOperationMaxConcurrencyKHR                             GetDeferredOperationMaxConcurrencyKHR                           ;
    PFN_vkGetDeferredOperationResultKHR                                     GetDeferredOperationResultKHR                                   ;
    PFN_vkDeferredOperationJoinKHR                                          DeferredOperationJoinKHR                                        ;
    /* VK_KHR_pipeline_executable_properties spec_version 1 */
    PFN_vkGetPipelineExecutablePropertiesKHR                                GetPipelineExecutablePropertiesKHR                              ;
    PFN_vkGetPipelineExecutableStatisticsKHR                                GetPipelineExecutableStatisticsKHR                              ;
    PFN_vkGetPipelineExecutableInternalRepresentationsKHR                   GetPipelineExecutableInternalRepresentationsKHR                 ;
    /* VK_KHR_map_memory2 spec_version 1 */
    PFN_vkMapMemory2KHR                                                     MapMemory2KHR                                                   ;
    PFN_vkUnmapMemory2KHR                                                   UnmapMemory2KHR                                                 ;
    /* VK_KHR_video_encode_queue spec_version 12 */
    PFN_vkGetEncodedVideoSessionParametersKHR                               GetEncodedVideoSessionParametersKHR                             ;
    PFN_vkCmdEncodeVideoKHR                                                 CmdEncodeVideoKHR                                               ;
    /* VK_KHR_synchronization2 spec_version 1 */
    PFN_vkCmdSetEvent2KHR                                                   CmdSetEvent2KHR                                                 ;
    PFN_vkCmdResetEvent2KHR                                                 CmdResetEvent2KHR                                               ;
    PFN_vkCmdWaitEvents2KHR                                                 CmdWaitEvents2KHR                                               ;
    PFN_vkCmdPipelineBarrier2KHR                                            CmdPipelineBarrier2KHR                                          ;
    PFN_vkCmdWriteTimestamp2KHR                                             CmdWriteTimestamp2KHR                                           ;
    PFN_vkQueueSubmit2KHR                                                   QueueSubmit2KHR                                                 ;
    PFN_vkCmdWriteBufferMarker2AMD                                          CmdWriteBufferMarker2AMD                                        ;
    PFN_vkGetQueueCheckpointData2NV                                         GetQueueCheckpointData2NV                                       ;
                /* NOTE: The function vkCmdWriteBufferMarker2AMD was moved into VK_AMD_buffer_marker and vkGetQueueCheckpointData2NV into VK_NV_device_diagnostic_checkpoints from 1.3.284 to 1.4.309;
                   they are kept here in their old position for the sake of preserving the memory layout of the old portion of the structs */
    /* VK_KHR_copy_commands2 spec_version 1 */
    PFN_vkCmdCopyBuffer2KHR                                                 CmdCopyBuffer2KHR                                               ;
    PFN_vkCmdCopyImage2KHR                                                  CmdCopyImage2KHR                                                ;
    PFN_vkCmdCopyBufferToImage2KHR                                          CmdCopyBufferToImage2KHR                                        ;
    PFN_vkCmdCopyImageToBuffer2KHR                                          CmdCopyImageToBuffer2KHR                                        ;
    PFN_vkCmdBlitImage2KHR                                                  CmdBlitImage2KHR                                                ;
    PFN_vkCmdResolveImage2KHR                                               CmdResolveImage2KHR                                             ;
    /* VK_KHR_ray_tracing_maintenance1 spec_version 1 */
    PFN_vkCmdTraceRaysIndirect2KHR                                          CmdTraceRaysIndirect2KHR                                        ;
    /* VK_KHR_maintenance4 spec_version 2 */
    PFN_vkGetDeviceBufferMemoryRequirementsKHR                              GetDeviceBufferMemoryRequirementsKHR                            ;
    PFN_vkGetDeviceImageMemoryRequirementsKHR                               GetDeviceImageMemoryRequirementsKHR                             ;
    PFN_vkGetDeviceImageSparseMemoryRequirementsKHR                         GetDeviceImageSparseMemoryRequirementsKHR                       ;
    /* VK_KHR_maintenance5 spec_version 1 */
    PFN_vkCmdBindIndexBuffer2KHR                                            CmdBindIndexBuffer2KHR                                          ;
    PFN_vkGetRenderingAreaGranularityKHR                                    GetRenderingAreaGranularityKHR                                  ;
    PFN_vkGetDeviceImageSubresourceLayoutKHR                                GetDeviceImageSubresourceLayoutKHR                              ;
    PFN_vkGetImageSubresourceLayout2KHR                                     GetImageSubresourceLayout2KHR                                   ;
    /* VK_KHR_line_rasterization spec_version 1 */
    PFN_vkCmdSetLineStippleKHR                                              CmdSetLineStippleKHR                                            ;
    /* VK_KHR_calibrated_timestamps spec_version 1 */
    PFN_vkGetCalibratedTimestampsKHR                                        GetCalibratedTimestampsKHR                                      ;
    /* VK_KHR_maintenance6 spec_version 1 */
    PFN_vkCmdBindDescriptorSets2KHR                                         CmdBindDescriptorSets2KHR                                       ;
    PFN_vkCmdPushConstants2KHR                                              CmdPushConstants2KHR                                            ;
    PFN_vkCmdPushDescriptorSet2KHR                                          CmdPushDescriptorSet2KHR                                        ;
    PFN_vkCmdPushDescriptorSetWithTemplate2KHR                              CmdPushDescriptorSetWithTemplate2KHR                            ;
    PFN_vkCmdSetDescriptorBufferOffsets2EXT                                 CmdSetDescriptorBufferOffsets2EXT                               ;
    PFN_vkCmdBindDescriptorBufferEmbeddedSamplers2EXT                       CmdBindDescriptorBufferEmbeddedSamplers2EXT                     ;
    /* VK_EXT_debug_marker spec_version 4 */
    PFN_vkDebugMarkerSetObjectTagEXT                                        DebugMarkerSetObjectTagEXT                                      ;
    PFN_vkDebugMarkerSetObjectNameEXT                                       DebugMarkerSetObjectNameEXT                                     ;
    PFN_vkCmdDebugMarkerBeginEXT                                            CmdDebugMarkerBeginEXT                                          ;
    PFN_vkCmdDebugMarkerEndEXT                                              CmdDebugMarkerEndEXT                                            ;
    PFN_vkCmdDebugMarkerInsertEXT                                           CmdDebugMarkerInsertEXT                                         ;
    /* VK_EXT_transform_feedback spec_version 1 */
    PFN_vkCmdBindTransformFeedbackBuffersEXT                                CmdBindTransformFeedbackBuffersEXT                              ;
    PFN_vkCmdBeginTransformFeedbackEXT                                      CmdBeginTransformFeedbackEXT                                    ;
    PFN_vkCmdEndTransformFeedbackEXT                                        CmdEndTransformFeedbackEXT                                      ;
    PFN_vkCmdBeginQueryIndexedEXT                                           CmdBeginQueryIndexedEXT                                         ;
    PFN_vkCmdEndQueryIndexedEXT                                             CmdEndQueryIndexedEXT                                           ;
    PFN_vkCmdDrawIndirectByteCountEXT                                       CmdDrawIndirectByteCountEXT                                     ;
    /* VK_NVX_binary_import spec_version 2 */
    PFN_vkCreateCuModuleNVX                                                 CreateCuModuleNVX                                               ;
    PFN_vkCreateCuFunctionNVX                                               CreateCuFunctionNVX                                             ;
    PFN_vkDestroyCuModuleNVX                                                DestroyCuModuleNVX                                              ;
    PFN_vkDestroyCuFunctionNVX                                              DestroyCuFunctionNVX                                            ;
    PFN_vkCmdCuLaunchKernelNVX                                              CmdCuLaunchKernelNVX                                            ;
    /* VK_NVX_image_view_handle spec_version 3 */
    PFN_vkGetImageViewHandleNVX                                             GetImageViewHandleNVX                                           ;
    PFN_vkGetImageViewAddressNVX                                            GetImageViewAddressNVX                                          ;
    /* VK_AMD_draw_indirect_count spec_version 2 */                         
    PFN_vkCmdDrawIndirectCountAMD                                           CmdDrawIndirectCountAMD                                         ;
    PFN_vkCmdDrawIndexedIndirectCountAMD                                    CmdDrawIndexedIndirectCountAMD                                  ;
    /* VK_AMD_shader_info spec_version 1 */                                 
    PFN_vkGetShaderInfoAMD                                                  GetShaderInfoAMD                                                ;
    /* VK_EXT_conditional_rendering spec_version 2 */                       
    PFN_vkCmdBeginConditionalRenderingEXT                                   CmdBeginConditionalRenderingEXT                                 ;
    PFN_vkCmdEndConditionalRenderingEXT                                     CmdEndConditionalRenderingEXT                                   ;
    /* VK_NV_clip_space_w_scaling spec_version 1 */                         
    PFN_vkCmdSetViewportWScalingNV                                          CmdSetViewportWScalingNV                                        ;
    /* VK_EXT_display_control spec_version 1 */                             
    PFN_vkDisplayPowerControlEXT                                            DisplayPowerControlEXT                                          ;
    PFN_vkRegisterDeviceEventEXT                                            RegisterDeviceEventEXT                                          ;
    PFN_vkRegisterDisplayEventEXT                                           RegisterDisplayEventEXT                                         ;
    PFN_vkGetSwapchainCounterEXT                                            GetSwapchainCounterEXT                                          ;
    /* VK_GOOGLE_display_timing spec_version 1 */                           
    PFN_vkGetRefreshCycleDurationGOOGLE                                     GetRefreshCycleDurationGOOGLE                                   ;
    PFN_vkGetPastPresentationTimingGOOGLE                                   GetPastPresentationTimingGOOGLE                                 ;
    /* VK_EXT_discard_rectangles spec_version 2 */                          
    PFN_vkCmdSetDiscardRectangleEXT                                         CmdSetDiscardRectangleEXT                                       ;
    PFN_vkCmdSetDiscardRectangleEnableEXT                                   CmdSetDiscardRectangleEnableEXT                                 ;
    PFN_vkCmdSetDiscardRectangleModeEXT                                     CmdSetDiscardRectangleModeEXT                                   ;
    /* VK_EXT_hdr_metadata spec_version 3 */
    PFN_vkSetHdrMetadataEXT                                                 SetHdrMetadataEXT                                               ;
    /* VK_EXT_debug_utils spec_version 2 */                                 
    PFN_vkSetDebugUtilsObjectNameEXT                                        SetDebugUtilsObjectNameEXT                                      ;
    PFN_vkSetDebugUtilsObjectTagEXT                                         SetDebugUtilsObjectTagEXT                                       ;
    PFN_vkQueueBeginDebugUtilsLabelEXT                                      QueueBeginDebugUtilsLabelEXT                                    ;
    PFN_vkQueueEndDebugUtilsLabelEXT                                        QueueEndDebugUtilsLabelEXT                                      ;
    PFN_vkQueueInsertDebugUtilsLabelEXT                                     QueueInsertDebugUtilsLabelEXT                                   ;
    PFN_vkCmdBeginDebugUtilsLabelEXT                                        CmdBeginDebugUtilsLabelEXT                                      ;
    PFN_vkCmdEndDebugUtilsLabelEXT                                          CmdEndDebugUtilsLabelEXT                                        ;
    PFN_vkCmdInsertDebugUtilsLabelEXT                                       CmdInsertDebugUtilsLabelEXT                                     ;
    /* VK_EXT_sample_locations spec_version 1 */                            
    PFN_vkCmdSetSampleLocationsEXT                                          CmdSetSampleLocationsEXT                                        ;
    /* VK_EXT_image_drm_format_modifier spec_version 2 */                   
    PFN_vkGetImageDrmFormatModifierPropertiesEXT                            GetImageDrmFormatModifierPropertiesEXT                          ;
    /* VK_EXT_validation_cache spec_version 1 */                            
    PFN_vkCreateValidationCacheEXT                                          CreateValidationCacheEXT                                        ;
    PFN_vkDestroyValidationCacheEXT                                         DestroyValidationCacheEXT                                       ;
    PFN_vkMergeValidationCachesEXT                                          MergeValidationCachesEXT                                        ;
    PFN_vkGetValidationCacheDataEXT                                         GetValidationCacheDataEXT                                       ;
    /* VK_NV_shading_rate_image spec_version 3 */                           
    PFN_vkCmdBindShadingRateImageNV                                         CmdBindShadingRateImageNV                                       ;
    PFN_vkCmdSetViewportShadingRatePaletteNV                                CmdSetViewportShadingRatePaletteNV                              ;
    PFN_vkCmdSetCoarseSampleOrderNV                                         CmdSetCoarseSampleOrderNV                                       ;
    /* VK_NV_ray_tracing spec_version 3 */                                  
    PFN_vkCreateAccelerationStructureNV                                     CreateAccelerationStructureNV                                   ;
    PFN_vkDestroyAccelerationStructureNV                                    DestroyAccelerationStructureNV                                  ;
    PFN_vkGetAccelerationStructureMemoryRequirementsNV                      GetAccelerationStructureMemoryRequirementsNV                    ;
    PFN_vkBindAccelerationStructureMemoryNV                                 BindAccelerationStructureMemoryNV                               ;
    PFN_vkCmdBuildAccelerationStructureNV                                   CmdBuildAccelerationStructureNV                                 ;
    PFN_vkCmdCopyAccelerationStructureNV                                    CmdCopyAccelerationStructureNV                                  ;
    PFN_vkCmdTraceRaysNV                                                    CmdTraceRaysNV                                                  ;
    PFN_vkCreateRayTracingPipelinesNV                                       CreateRayTracingPipelinesNV                                     ;
    PFN_vkGetRayTracingShaderGroupHandlesKHR                                GetRayTracingShaderGroupHandlesKHR                              ;
    PFN_vkGetRayTracingShaderGroupHandlesNV                                 GetRayTracingShaderGroupHandlesNV                               ;
    PFN_vkGetAccelerationStructureHandleNV                                  GetAccelerationStructureHandleNV                                ;
    PFN_vkCmdWriteAccelerationStructuresPropertiesNV                        CmdWriteAccelerationStructuresPropertiesNV                      ;
    PFN_vkCompileDeferredNV                                                 CompileDeferredNV                                               ;
    /* VK_EXT_external_memory_host spec_version 1 */                        
    PFN_vkGetMemoryHostPointerPropertiesEXT                                 GetMemoryHostPointerPropertiesEXT                               ;                                 
    /* VK_AMD_buffer_marker spec_version 1 */                               
    PFN_vkCmdWriteBufferMarkerAMD                                           CmdWriteBufferMarkerAMD                                         ;
    /* VK_EXT_calibrated_timestamps spec_version 2 */                       
    PFN_vkGetCalibratedTimestampsEXT                                        GetCalibratedTimestampsEXT                                      ;
    /* VK_NV_mesh_shader spec_version 1 */                                  
    PFN_vkCmdDrawMeshTasksNV                                                CmdDrawMeshTasksNV                                              ;
    PFN_vkCmdDrawMeshTasksIndirectNV                                        CmdDrawMeshTasksIndirectNV                                      ;
    PFN_vkCmdDrawMeshTasksIndirectCountNV                                   CmdDrawMeshTasksIndirectCountNV                                 ;
    /* VK_NV_scissor_exclusive spec_version 2 */                            
    PFN_vkCmdSetExclusiveScissorEnableNV                                    CmdSetExclusiveScissorEnableNV                                  ;
    PFN_vkCmdSetExclusiveScissorNV                                          CmdSetExclusiveScissorNV                                        ;
    /* VK_NV_device_diagnostic_checkpoints spec_version 2 */                
    PFN_vkCmdSetCheckpointNV                                                CmdSetCheckpointNV                                              ;
    PFN_vkGetQueueCheckpointDataNV                                          GetQueueCheckpointDataNV                                        ;
    /* VK_INTEL_performance_query spec_version 2 */                         
    PFN_vkInitializePerformanceApiINTEL                                     InitializePerformanceApiINTEL                                   ;
    PFN_vkUninitializePerformanceApiINTEL                                   UninitializePerformanceApiINTEL                                 ;
    PFN_vkCmdSetPerformanceMarkerINTEL                                      CmdSetPerformanceMarkerINTEL                                    ;
    PFN_vkCmdSetPerformanceStreamMarkerINTEL                                CmdSetPerformanceStreamMarkerINTEL                              ;
    PFN_vkCmdSetPerformanceOverrideINTEL                                    CmdSetPerformanceOverrideINTEL                                  ;
    PFN_vkAcquirePerformanceConfigurationINTEL                              AcquirePerformanceConfigurationINTEL                            ;
    PFN_vkReleasePerformanceConfigurationINTEL                              ReleasePerformanceConfigurationINTEL                            ;
    PFN_vkQueueSetPerformanceConfigurationINTEL                             QueueSetPerformanceConfigurationINTEL                           ;
    PFN_vkGetPerformanceParameterINTEL                                      GetPerformanceParameterINTEL                                    ;
    /* VK_AMD_display_native_hdr spec_version 1 */                          
    PFN_vkSetLocalDimmingAMD                                                SetLocalDimmingAMD                                              ;
    /* VK_EXT_buffer_device_address spec_version 2 */                       
    PFN_vkGetBufferDeviceAddressEXT                                         GetBufferDeviceAddressEXT                                       ;
    /* VK_EXT_line_rasterization spec_version 1 */                          
    PFN_vkCmdSetLineStippleEXT                                              CmdSetLineStippleEXT                                            ;
    /* VK_EXT_host_query_reset spec_version 1 */                            
    PFN_vkResetQueryPoolEXT                                                 ResetQueryPoolEXT                                               ;                                                 
    /* VK_EXT_extended_dynamic_state spec_version 1 */                      
    PFN_vkCmdSetCullModeEXT                                                 CmdSetCullModeEXT                                               ;
    PFN_vkCmdSetFrontFaceEXT                                                CmdSetFrontFaceEXT                                              ;
    PFN_vkCmdSetPrimitiveTopologyEXT                                        CmdSetPrimitiveTopologyEXT                                      ;
    PFN_vkCmdSetViewportWithCountEXT                                        CmdSetViewportWithCountEXT                                      ;
    PFN_vkCmdSetScissorWithCountEXT                                         CmdSetScissorWithCountEXT                                       ;
    PFN_vkCmdBindVertexBuffers2EXT                                          CmdBindVertexBuffers2EXT                                        ;
    PFN_vkCmdSetDepthTestEnableEXT                                          CmdSetDepthTestEnableEXT                                        ;
    PFN_vkCmdSetDepthWriteEnableEXT                                         CmdSetDepthWriteEnableEXT                                       ;
    PFN_vkCmdSetDepthCompareOpEXT                                           CmdSetDepthCompareOpEXT                                         ;
    PFN_vkCmdSetDepthBoundsTestEnableEXT                                    CmdSetDepthBoundsTestEnableEXT                                  ;
    PFN_vkCmdSetStencilTestEnableEXT                                        CmdSetStencilTestEnableEXT                                      ;
    PFN_vkCmdSetStencilOpEXT                                                CmdSetStencilOpEXT                                              ;
    /* VK_EXT_host_image_copy spec_version 1 */                             
    PFN_vkCopyMemoryToImageEXT                                              CopyMemoryToImageEXT                                            ;
    PFN_vkCopyImageToMemoryEXT                                              CopyImageToMemoryEXT                                            ;
    PFN_vkCopyImageToImageEXT                                               CopyImageToImageEXT                                             ;
    PFN_vkTransitionImageLayoutEXT                                          TransitionImageLayoutEXT                                        ;
    PFN_vkGetImageSubresourceLayout2EXT                                     GetImageSubresourceLayout2EXT                                   ;
    /* VK_EXT_swapchain_maintenance1 spec_version 1 */                      
    PFN_vkReleaseSwapchainImagesEXT                                         ReleaseSwapchainImagesEXT                                       ;
    /* VK_NV_device_generated_commands spec_version 3 */                    
    PFN_vkGetGeneratedCommandsMemoryRequirementsNV                          GetGeneratedCommandsMemoryRequirementsNV                        ;
    PFN_vkCmdPreprocessGeneratedCommandsNV                                  CmdPreprocessGeneratedCommandsNV                                ;
    PFN_vkCmdExecuteGeneratedCommandsNV                                     CmdExecuteGeneratedCommandsNV                                   ;
    PFN_vkCmdBindPipelineShaderGroupNV                                      CmdBindPipelineShaderGroupNV                                    ;
    PFN_vkCreateIndirectCommandsLayoutNV                                    CreateIndirectCommandsLayoutNV                                  ;
    PFN_vkDestroyIndirectCommandsLayoutNV                                   DestroyIndirectCommandsLayoutNV                                 ;
    /* VK_EXT_depth_bias_control spec_version 1 */                          
    PFN_vkCmdSetDepthBias2EXT                                               CmdSetDepthBias2EXT                                             ;
    /* VK_EXT_private_data spec_version 1 */                                
    PFN_vkCreatePrivateDataSlotEXT                                          CreatePrivateDataSlotEXT                                        ;
    PFN_vkDestroyPrivateDataSlotEXT                                         DestroyPrivateDataSlotEXT                                       ;
    PFN_vkSetPrivateDataEXT                                                 SetPrivateDataEXT                                               ;
    PFN_vkGetPrivateDataEXT                                                 GetPrivateDataEXT                                               ;
    /* VK_NV_cuda_kernel_launch spec_version 2 */                           
    PFN_vkCreateCudaModuleNV                                                CreateCudaModuleNV                                              ;
    PFN_vkGetCudaModuleCacheNV                                              GetCudaModuleCacheNV                                            ;
    PFN_vkCreateCudaFunctionNV                                              CreateCudaFunctionNV                                            ;
    PFN_vkDestroyCudaModuleNV                                               DestroyCudaModuleNV                                             ;
    PFN_vkDestroyCudaFunctionNV                                             DestroyCudaFunctionNV                                           ;
    PFN_vkCmdCudaLaunchKernelNV                                             CmdCudaLaunchKernelNV                                           ;
    /* VK_EXT_descriptor_buffer spec_version 1 */                           
    PFN_vkGetDescriptorSetLayoutSizeEXT                                     GetDescriptorSetLayoutSizeEXT                                   ;
    PFN_vkGetDescriptorSetLayoutBindingOffsetEXT                            GetDescriptorSetLayoutBindingOffsetEXT                          ;
    PFN_vkGetDescriptorEXT                                                  GetDescriptorEXT                                                ;
    PFN_vkCmdBindDescriptorBuffersEXT                                       CmdBindDescriptorBuffersEXT                                     ;
    PFN_vkCmdSetDescriptorBufferOffsetsEXT                                  CmdSetDescriptorBufferOffsetsEXT                                ;
    PFN_vkCmdBindDescriptorBufferEmbeddedSamplersEXT                        CmdBindDescriptorBufferEmbeddedSamplersEXT                      ;
    PFN_vkGetBufferOpaqueCaptureDescriptorDataEXT                           GetBufferOpaqueCaptureDescriptorDataEXT                         ;
    PFN_vkGetImageOpaqueCaptureDescriptorDataEXT                            GetImageOpaqueCaptureDescriptorDataEXT                          ;
    PFN_vkGetImageViewOpaqueCaptureDescriptorDataEXT                        GetImageViewOpaqueCaptureDescriptorDataEXT                      ;
    PFN_vkGetSamplerOpaqueCaptureDescriptorDataEXT                          GetSamplerOpaqueCaptureDescriptorDataEXT                        ;
    PFN_vkGetAccelerationStructureOpaqueCaptureDescriptorDataEXT            GetAccelerationStructureOpaqueCaptureDescriptorDataEXT          ;
    /* VK_NV_fragment_shading_rate_enums spec_version 1 */                  
    PFN_vkCmdSetFragmentShadingRateEnumNV                                   CmdSetFragmentShadingRateEnumNV                                 ;
    /* VK_EXT_device_fault spec_version 2 */                                
    PFN_vkGetDeviceFaultInfoEXT                                             GetDeviceFaultInfoEXT                                           ;
    /* VK_EXT_vertex_input_dynamic_state spec_version 2 */                  
    PFN_vkCmdSetVertexInputEXT                                              CmdSetVertexInputEXT                                            ;
    /* VK_HUAWEI_subpass_shading spec_version 3 */                          
    PFN_vkGetDeviceSubpassShadingMaxWorkgroupSizeHUAWEI                     GetDeviceSubpassShadingMaxWorkgroupSizeHUAWEI                   ;
    PFN_vkCmdSubpassShadingHUAWEI                                           CmdSubpassShadingHUAWEI                                         ;
    /* VK_HUAWEI_invocation_mask spec_version 1 */                          
    PFN_vkCmdBindInvocationMaskHUAWEI                                       CmdBindInvocationMaskHUAWEI                                     ;
    /* VK_NV_external_memory_rdma spec_version 1 */                         
    PFN_vkGetMemoryRemoteAddressNV                                          GetMemoryRemoteAddressNV                                        ;
    /* VK_EXT_pipeline_properties spec_version 1 */                         
    PFN_vkGetPipelinePropertiesEXT                                          GetPipelinePropertiesEXT                                        ;
    /* VK_EXT_extended_dynamic_state2 spec_version 1 */                     
    PFN_vkCmdSetPatchControlPointsEXT                                       CmdSetPatchControlPointsEXT                                     ;
    PFN_vkCmdSetRasterizerDiscardEnableEXT                                  CmdSetRasterizerDiscardEnableEXT                                ;
    PFN_vkCmdSetDepthBiasEnableEXT                                          CmdSetDepthBiasEnableEXT                                        ;
    PFN_vkCmdSetLogicOpEXT                                                  CmdSetLogicOpEXT                                                ;
    PFN_vkCmdSetPrimitiveRestartEnableEXT                                   CmdSetPrimitiveRestartEnableEXT                                 ;
    /* VK_EXT_color_write_enable spec_version 1 */                          
    PFN_vkCmdSetColorWriteEnableEXT                                         CmdSetColorWriteEnableEXT                                       ;
    /* VK_EXT_multi_draw spec_version 1 */                                  
    PFN_vkCmdDrawMultiEXT                                                   CmdDrawMultiEXT                                                 ;
    PFN_vkCmdDrawMultiIndexedEXT                                            CmdDrawMultiIndexedEXT                                          ;
    /* VK_EXT_opacity_micromap spec_version 2 */                            
    PFN_vkCreateMicromapEXT                                                 CreateMicromapEXT                                               ;
    PFN_vkDestroyMicromapEXT                                                DestroyMicromapEXT                                              ;
    PFN_vkCmdBuildMicromapsEXT                                              CmdBuildMicromapsEXT                                            ;
    PFN_vkBuildMicromapsEXT                                                 BuildMicromapsEXT                                               ;
    PFN_vkCopyMicromapEXT                                                   CopyMicromapEXT                                                 ;
    PFN_vkCopyMicromapToMemoryEXT                                           CopyMicromapToMemoryEXT                                         ;
    PFN_vkCopyMemoryToMicromapEXT                                           CopyMemoryToMicromapEXT                                         ;
    PFN_vkWriteMicromapsPropertiesEXT                                       WriteMicromapsPropertiesEXT                                     ;
    PFN_vkCmdCopyMicromapEXT                                                CmdCopyMicromapEXT                                              ;
    PFN_vkCmdCopyMicromapToMemoryEXT                                        CmdCopyMicromapToMemoryEXT                                      ;
    PFN_vkCmdCopyMemoryToMicromapEXT                                        CmdCopyMemoryToMicromapEXT                                      ;
    PFN_vkCmdWriteMicromapsPropertiesEXT                                    CmdWriteMicromapsPropertiesEXT                                  ;
    PFN_vkGetDeviceMicromapCompatibilityEXT                                 GetDeviceMicromapCompatibilityEXT                               ;
    PFN_vkGetMicromapBuildSizesEXT                                          GetMicromapBuildSizesEXT                                        ;
    /* VK_HUAWEI_cluster_culling_shader spec_version 3 */                   
    PFN_vkCmdDrawClusterHUAWEI                                              CmdDrawClusterHUAWEI                                            ;
    PFN_vkCmdDrawClusterIndirectHUAWEI                                      CmdDrawClusterIndirectHUAWEI                                    ;
    /* VK_EXT_pageable_device_local_memory spec_version 1 */                
    PFN_vkSetDeviceMemoryPriorityEXT                                        SetDeviceMemoryPriorityEXT                                      ;
    /* VK_VALVE_descriptor_set_host_mapping spec_version 1 */               
    PFN_vkGetDescriptorSetLayoutHostMappingInfoVALVE                        GetDescriptorSetLayoutHostMappingInfoVALVE                      ;
    PFN_vkGetDescriptorSetHostMappingVALVE                                  GetDescriptorSetHostMappingVALVE                                ;
    /* VK_NV_copy_memory_indirect spec_version 1 */                         
    PFN_vkCmdCopyMemoryIndirectNV                                           CmdCopyMemoryIndirectNV                                         ;
    PFN_vkCmdCopyMemoryToImageIndirectNV                                    CmdCopyMemoryToImageIndirectNV                                  ;
    /* VK_NV_memory_decompression spec_version 1 */                         
    PFN_vkCmdDecompressMemoryNV                                             CmdDecompressMemoryNV                                           ;
    PFN_vkCmdDecompressMemoryIndirectCountNV                                CmdDecompressMemoryIndirectCountNV                              ;
    /* VK_NV_device_generated_commands_compute spec_version 2 */            
    PFN_vkGetPipelineIndirectMemoryRequirementsNV                           GetPipelineIndirectMemoryRequirementsNV                         ;
    PFN_vkCmdUpdatePipelineIndirectBufferNV                                 CmdUpdatePipelineIndirectBufferNV                               ;
    PFN_vkGetPipelineIndirectDeviceAddressNV                                GetPipelineIndirectDeviceAddressNV                              ;
    /* VK_EXT_extended_dynamic_state3 spec_version 2 */                     
    PFN_vkCmdSetDepthClampEnableEXT                                         CmdSetDepthClampEnableEXT                                       ;
    PFN_vkCmdSetPolygonModeEXT                                              CmdSetPolygonModeEXT                                            ;
    PFN_vkCmdSetRasterizationSamplesEXT                                     CmdSetRasterizationSamplesEXT                                   ;
    PFN_vkCmdSetSampleMaskEXT                                               CmdSetSampleMaskEXT                                             ;
    PFN_vkCmdSetAlphaToCoverageEnableEXT                                    CmdSetAlphaToCoverageEnableEXT                                  ;
    PFN_vkCmdSetAlphaToOneEnableEXT                                         CmdSetAlphaToOneEnableEXT                                       ;
    PFN_vkCmdSetLogicOpEnableEXT                                            CmdSetLogicOpEnableEXT                                          ;
    PFN_vkCmdSetColorBlendEnableEXT                                         CmdSetColorBlendEnableEXT                                       ;
    PFN_vkCmdSetColorBlendEquationEXT                                       CmdSetColorBlendEquationEXT                                     ;
    PFN_vkCmdSetColorWriteMaskEXT                                           CmdSetColorWriteMaskEXT                                         ;
    PFN_vkCmdSetTessellationDomainOriginEXT                                 CmdSetTessellationDomainOriginEXT                               ;
    PFN_vkCmdSetRasterizationStreamEXT                                      CmdSetRasterizationStreamEXT                                    ;
    PFN_vkCmdSetConservativeRasterizationModeEXT                            CmdSetConservativeRasterizationModeEXT                          ;
    PFN_vkCmdSetExtraPrimitiveOverestimationSizeEXT                         CmdSetExtraPrimitiveOverestimationSizeEXT                       ;
    PFN_vkCmdSetDepthClipEnableEXT                                          CmdSetDepthClipEnableEXT                                        ;
    PFN_vkCmdSetSampleLocationsEnableEXT                                    CmdSetSampleLocationsEnableEXT                                  ;
    PFN_vkCmdSetColorBlendAdvancedEXT                                       CmdSetColorBlendAdvancedEXT                                     ;
    PFN_vkCmdSetProvokingVertexModeEXT                                      CmdSetProvokingVertexModeEXT                                    ;
    PFN_vkCmdSetLineRasterizationModeEXT                                    CmdSetLineRasterizationModeEXT                                  ;
    PFN_vkCmdSetLineStippleEnableEXT                                        CmdSetLineStippleEnableEXT                                      ;
    PFN_vkCmdSetDepthClipNegativeOneToOneEXT                                CmdSetDepthClipNegativeOneToOneEXT                              ;
    PFN_vkCmdSetViewportWScalingEnableNV                                    CmdSetViewportWScalingEnableNV                                  ;
    PFN_vkCmdSetViewportSwizzleNV                                           CmdSetViewportSwizzleNV                                         ;
    PFN_vkCmdSetCoverageToColorEnableNV                                     CmdSetCoverageToColorEnableNV                                   ;
    PFN_vkCmdSetCoverageToColorLocationNV                                   CmdSetCoverageToColorLocationNV                                 ;
    PFN_vkCmdSetCoverageModulationModeNV                                    CmdSetCoverageModulationModeNV                                  ;
    PFN_vkCmdSetCoverageModulationTableEnableNV                             CmdSetCoverageModulationTableEnableNV                           ;
    PFN_vkCmdSetCoverageModulationTableNV                                   CmdSetCoverageModulationTableNV                                 ;
    PFN_vkCmdSetShadingRateImageEnableNV                                    CmdSetShadingRateImageEnableNV                                  ;
    PFN_vkCmdSetRepresentativeFragmentTestEnableNV                          CmdSetRepresentativeFragmentTestEnableNV                        ;
    PFN_vkCmdSetCoverageReductionModeNV                                     CmdSetCoverageReductionModeNV                                   ;
    /* VK_EXT_shader_module_identifier spec_version 1 */                    
    PFN_vkGetShaderModuleIdentifierEXT                                      GetShaderModuleIdentifierEXT                                    ;
    PFN_vkGetShaderModuleCreateInfoIdentifierEXT                            GetShaderModuleCreateInfoIdentifierEXT                          ;
    /* VK_NV_optical_flow spec_version 1 */                                 
    PFN_vkCreateOpticalFlowSessionNV                                        CreateOpticalFlowSessionNV                                      ;
    PFN_vkDestroyOpticalFlowSessionNV                                       DestroyOpticalFlowSessionNV                                     ;
    PFN_vkBindOpticalFlowSessionImageNV                                     BindOpticalFlowSessionImageNV                                   ;
    PFN_vkCmdOpticalFlowExecuteNV                                           CmdOpticalFlowExecuteNV                                         ;
    /* VK_EXT_shader_object spec_version 1 */                               
    PFN_vkCreateShadersEXT                                                  CreateShadersEXT                                                ;
    PFN_vkDestroyShaderEXT                                                  DestroyShaderEXT                                                ;
    PFN_vkGetShaderBinaryDataEXT                                            GetShaderBinaryDataEXT                                          ;
    PFN_vkCmdBindShadersEXT                                                 CmdBindShadersEXT                                               ;
    /* VK_QCOM_tile_properties spec_version 1 */                            
    PFN_vkGetFramebufferTilePropertiesQCOM                                  GetFramebufferTilePropertiesQCOM                                ;
    PFN_vkGetDynamicRenderingTilePropertiesQCOM                             GetDynamicRenderingTilePropertiesQCOM                           ;
    /* VK_NV_low_latency2 spec_version 2 */                                 
    PFN_vkSetLatencySleepModeNV                                             SetLatencySleepModeNV                                           ;
    PFN_vkLatencySleepNV                                                    LatencySleepNV                                                  ;
    PFN_vkSetLatencyMarkerNV                                                SetLatencyMarkerNV                                              ;
    PFN_vkGetLatencyTimingsNV                                               GetLatencyTimingsNV                                             ;
    PFN_vkQueueNotifyOutOfBandNV                                            QueueNotifyOutOfBandNV                                          ;
    /* VK_EXT_attachment_feedback_loop_dynamic_state spec_version 1 */      
    PFN_vkCmdSetAttachmentFeedbackLoopEnableEXT                             CmdSetAttachmentFeedbackLoopEnableEXT                           ;
    /* VK_KHR_acceleration_structure spec_version 13 */                     
    PFN_vkCreateAccelerationStructureKHR                                    CreateAccelerationStructureKHR                                  ;
    PFN_vkDestroyAccelerationStructureKHR                                   DestroyAccelerationStructureKHR                                 ;
    PFN_vkCmdBuildAccelerationStructuresKHR                                 CmdBuildAccelerationStructuresKHR                               ;
    PFN_vkCmdBuildAccelerationStructuresIndirectKHR                         CmdBuildAccelerationStructuresIndirectKHR                       ;
    PFN_vkBuildAccelerationStructuresKHR                                    BuildAccelerationStructuresKHR                                  ;
    PFN_vkCopyAccelerationStructureKHR                                      CopyAccelerationStructureKHR                                    ;
    PFN_vkCopyAccelerationStructureToMemoryKHR                              CopyAccelerationStructureToMemoryKHR                            ;
    PFN_vkCopyMemoryToAccelerationStructureKHR                              CopyMemoryToAccelerationStructureKHR                            ;
    PFN_vkWriteAccelerationStructuresPropertiesKHR                          WriteAccelerationStructuresPropertiesKHR                        ;
    PFN_vkCmdCopyAccelerationStructureKHR                                   CmdCopyAccelerationStructureKHR                                 ;
    PFN_vkCmdCopyAccelerationStructureToMemoryKHR                           CmdCopyAccelerationStructureToMemoryKHR                         ;
    PFN_vkCmdCopyMemoryToAccelerationStructureKHR                           CmdCopyMemoryToAccelerationStructureKHR                         ;
    PFN_vkGetAccelerationStructureDeviceAddressKHR                          GetAccelerationStructureDeviceAddressKHR                        ;
    PFN_vkCmdWriteAccelerationStructuresPropertiesKHR                       CmdWriteAccelerationStructuresPropertiesKHR                     ;
    PFN_vkGetDeviceAccelerationStructureCompatibilityKHR                    GetDeviceAccelerationStructureCompatibilityKHR                  ;
    PFN_vkGetAccelerationStructureBuildSizesKHR                             GetAccelerationStructureBuildSizesKHR                           ;
    /* VK_KHR_ray_tracing_pipeline spec_version 1 */                        
    PFN_vkCmdTraceRaysKHR                                                   CmdTraceRaysKHR                                                 ;
    PFN_vkCreateRayTracingPipelinesKHR                                      CreateRayTracingPipelinesKHR                                    ;
    PFN_vkGetRayTracingCaptureReplayShaderGroupHandlesKHR                   GetRayTracingCaptureReplayShaderGroupHandlesKHR                 ;
    PFN_vkCmdTraceRaysIndirectKHR                                           CmdTraceRaysIndirectKHR                                         ;
    PFN_vkGetRayTracingShaderGroupStackSizeKHR                              GetRayTracingShaderGroupStackSizeKHR                            ;
    PFN_vkCmdSetRayTracingPipelineStackSizeKHR                              CmdSetRayTracingPipelineStackSizeKHR                            ;
    /* VK_EXT_mesh_shader spec_version 1 */                                 
    PFN_vkCmdDrawMeshTasksEXT                                               CmdDrawMeshTasksEXT                                             ;
    PFN_vkCmdDrawMeshTasksIndirectEXT                                       CmdDrawMeshTasksIndirectEXT                                     ;
    PFN_vkCmdDrawMeshTasksIndirectCountEXT                                  CmdDrawMeshTasksIndirectCountEXT                                ;
    /* VK_ANDROID_external_memory_android_hardware_buffer spec_version 5 */ 
    PFN_vkGetAndroidHardwareBufferPropertiesANDROID                         GetAndroidHardwareBufferPropertiesANDROID                       ;
    PFN_vkGetMemoryAndroidHardwareBufferANDROID                             GetMemoryAndroidHardwareBufferANDROID                           ;
    /* VK_FUCHSIA_external_memory spec_version 1 */                         
    PFN_vkGetMemoryZirconHandleFUCHSIA                                      GetMemoryZirconHandleFUCHSIA                                    ;
    PFN_vkGetMemoryZirconHandlePropertiesFUCHSIA                            GetMemoryZirconHandlePropertiesFUCHSIA                          ;
    /* VK_FUCHSIA_external_semaphore spec_version 1 */                      
    PFN_vkImportSemaphoreZirconHandleFUCHSIA                                ImportSemaphoreZirconHandleFUCHSIA                              ;
    PFN_vkGetSemaphoreZirconHandleFUCHSIA                                   GetSemaphoreZirconHandleFUCHSIA                                 ;
    /* VK_FUCHSIA_buffer_collection spec_version 2 */                       
    PFN_vkCreateBufferCollectionFUCHSIA                                     CreateBufferCollectionFUCHSIA                                   ;
    PFN_vkSetBufferCollectionImageConstraintsFUCHSIA                        SetBufferCollectionImageConstraintsFUCHSIA                      ;
    PFN_vkSetBufferCollectionBufferConstraintsFUCHSIA                       SetBufferCollectionBufferConstraintsFUCHSIA                     ;
    PFN_vkDestroyBufferCollectionFUCHSIA                                    DestroyBufferCollectionFUCHSIA                                  ;
    PFN_vkGetBufferCollectionPropertiesFUCHSIA                              GetBufferCollectionPropertiesFUCHSIA                            ;
    /* VK_EXT_metal_objects spec_version 2 */                               
    PFN_vkExportMetalObjectsEXT                                             ExportMetalObjectsEXT                                           ;
    /* VK_KHR_external_memory_win32 spec_version 1 */                       
    PFN_vkGetMemoryWin32HandleKHR                                           GetMemoryWin32HandleKHR                                         ;
    PFN_vkGetMemoryWin32HandlePropertiesKHR                                 GetMemoryWin32HandlePropertiesKHR                               ;
    /* VK_KHR_external_semaphore_win32 spec_version 1 */                    
    PFN_vkImportSemaphoreWin32HandleKHR                                     ImportSemaphoreWin32HandleKHR                                   ;
    PFN_vkGetSemaphoreWin32HandleKHR                                        GetSemaphoreWin32HandleKHR                                      ;
    /* VK_KHR_external_fence_win32 spec_version 1 */                        
    PFN_vkImportFenceWin32HandleKHR                                         ImportFenceWin32HandleKHR                                       ;
    PFN_vkGetFenceWin32HandleKHR                                            GetFenceWin32HandleKHR                                          ;
    /* VK_NV_external_memory_win32 spec_version 1 */                        
    PFN_vkGetMemoryWin32HandleNV                                            GetMemoryWin32HandleNV                                          ;
    /* VK_EXT_full_screen_exclusive spec_version 4 */                       
    PFN_vkAcquireFullScreenExclusiveModeEXT                                 AcquireFullScreenExclusiveModeEXT                               ;
    PFN_vkReleaseFullScreenExclusiveModeEXT                                 ReleaseFullScreenExclusiveModeEXT                               ;
    PFN_vkGetDeviceGroupSurfacePresentModes2EXT                             GetDeviceGroupSurfacePresentModes2EXT                           ;
    /* VK_QNX_external_memory_screen_buffer spec_version 1 */               
    PFN_vkGetScreenBufferPropertiesQNX                                      GetScreenBufferPropertiesQNX                                    ;
    /* VK_AMDX_shader_enqueue spec_version 2 */
    PFN_vkCreateExecutionGraphPipelinesAMDX                                 CreateExecutionGraphPipelinesAMDX                               ;
    PFN_vkGetExecutionGraphPipelineScratchSizeAMDX                          GetExecutionGraphPipelineScratchSizeAMDX                        ;
    PFN_vkGetExecutionGraphPipelineNodeIndexAMDX                            GetExecutionGraphPipelineNodeIndexAMDX                          ;
    PFN_vkCmdInitializeGraphScratchMemoryAMDX                               CmdInitializeGraphScratchMemoryAMDX                             ;
    PFN_vkCmdDispatchGraphAMDX                                              CmdDispatchGraphAMDX                                            ;
    PFN_vkCmdDispatchGraphIndirectAMDX                                      CmdDispatchGraphIndirectAMDX                                    ;
    PFN_vkCmdDispatchGraphIndirectCountAMDX                                 CmdDispatchGraphIndirectCountAMDX                               ;
        /* Additions from 1.3.284 to 1.4.309: */
    /* to VK_NVX_image_view_handle spec_version 3 */
    PFN_vkGetImageViewHandle64NVX                                           GetImageViewHandle64NVX                                         ;
    /* to VK_EXT_shader_object spec_version 1 */
    PFN_vkCmdSetDepthClampRangeEXT                                          CmdSetDepthClampRangeEXT                                        ;
    /* VK_VERSION_1_4 */
    PFN_vkCmdSetLineStipple                                                 CmdSetLineStipple                                               ;
    PFN_vkMapMemory2                                                        MapMemory2                                                      ;
    PFN_vkUnmapMemory2                                                      UnmapMemory2                                                    ;
    PFN_vkCmdBindIndexBuffer2                                               CmdBindIndexBuffer2                                             ;
    PFN_vkGetRenderingAreaGranularity                                       GetRenderingAreaGranularity                                     ;
    PFN_vkGetDeviceImageSubresourceLayout                                   GetDeviceImageSubresourceLayout                                 ;
    PFN_vkGetImageSubresourceLayout2                                        GetImageSubresourceLayout2                                      ;
    PFN_vkCmdPushDescriptorSet                                              CmdPushDescriptorSet                                            ;
    PFN_vkCmdPushDescriptorSetWithTemplate                                  CmdPushDescriptorSetWithTemplate                                ;
    PFN_vkCmdSetRenderingAttachmentLocations                                CmdSetRenderingAttachmentLocations                              ;
    PFN_vkCmdSetRenderingInputAttachmentIndices                             CmdSetRenderingInputAttachmentIndices                           ;
    PFN_vkCmdBindDescriptorSets2                                            CmdBindDescriptorSets2                                          ;
    PFN_vkCmdPushConstants2                                                 CmdPushConstants2                                               ;
    PFN_vkCmdPushDescriptorSet2                                             CmdPushDescriptorSet2                                           ;
    PFN_vkCmdPushDescriptorSetWithTemplate2                                 CmdPushDescriptorSetWithTemplate2                               ;
    PFN_vkCopyMemoryToImage                                                 CopyMemoryToImage                                               ;
    PFN_vkCopyImageToMemory                                                 CopyImageToMemory                                               ;
    PFN_vkCopyImageToImage                                                  CopyImageToImage                                                ;
    PFN_vkTransitionImageLayout                                             TransitionImageLayout                                           ;
    /* VK_KHR_pipeline_binary spec_version 1 */
    PFN_vkCreatePipelineBinariesKHR                                         CreatePipelineBinariesKHR                                       ;
    PFN_vkDestroyPipelineBinaryKHR                                          DestroyPipelineBinaryKHR                                        ;
    PFN_vkGetPipelineKeyKHR                                                 GetPipelineKeyKHR                                               ;
    PFN_vkGetPipelineBinaryDataKHR                                          GetPipelineBinaryDataKHR                                        ;
    PFN_vkReleaseCapturedPipelineDataKHR                                    ReleaseCapturedPipelineDataKHR                                  ;
    /* VK_AMD_anti_lag spec_version 1 */
    PFN_vkAntiLagUpdateAMD                                                  AntiLagUpdateAMD                                                ;
    /* VK_NV_cooperative_vector spec_version 4 */
    PFN_vkConvertCooperativeVectorMatrixNV                                  ConvertCooperativeVectorMatrixNV                                ;
    PFN_vkCmdConvertCooperativeVectorMatrixNV                               CmdConvertCooperativeVectorMatrixNV                             ;
    /* VK_NV_cluster_acceleration_structure spec_version 2 */
    PFN_vkGetClusterAccelerationStructureBuildSizesNV                       GetClusterAccelerationStructureBuildSizesNV                     ;
    PFN_vkCmdBuildClusterAccelerationStructureIndirectNV                    CmdBuildClusterAccelerationStructureIndirectNV                  ;
    /* VK_NV_partitioned_acceleration_structure spec_version 1 */
    PFN_vkGetPartitionedAccelerationStructuresBuildSizesNV                  GetPartitionedAccelerationStructuresBuildSizesNV                ;
    PFN_vkCmdBuildPartitionedAccelerationStructuresNV                       CmdBuildPartitionedAccelerationStructuresNV                     ;
    /* VK_EXT_device_generated_commands spec_version 1 */
    PFN_vkGetGeneratedCommandsMemoryRequirementsEXT                         GetGeneratedCommandsMemoryRequirementsEXT                       ;
    PFN_vkCmdPreprocessGeneratedCommandsEXT                                 CmdPreprocessGeneratedCommandsEXT                               ;
    PFN_vkCmdExecuteGeneratedCommandsEXT                                    CmdExecuteGeneratedCommandsEXT                                  ;
    PFN_vkCreateIndirectCommandsLayoutEXT                                   CreateIndirectCommandsLayoutEXT                                 ;
    PFN_vkDestroyIndirectCommandsLayoutEXT                                  DestroyIndirectCommandsLayoutEXT                                ;
    PFN_vkCreateIndirectExecutionSetEXT                                     CreateIndirectExecutionSetEXT                                   ;
    PFN_vkDestroyIndirectExecutionSetEXT                                    DestroyIndirectExecutionSetEXT                                  ;
    PFN_vkUpdateIndirectExecutionSetPipelineEXT                             UpdateIndirectExecutionSetPipelineEXT                           ;
    PFN_vkUpdateIndirectExecutionSetShaderEXT                               UpdateIndirectExecutionSetShaderEXT                             ;
    /* VK_EXT_external_memory_metal spec_version 1 */
    PFN_vkGetMemoryMetalHandleEXT                                           GetMemoryMetalHandleEXT                                         ;
    PFN_vkGetMemoryMetalHandlePropertiesEXT                                 GetMemoryMetalHandlePropertiesEXT                               ;
} VkadDeviceFunctions;
/* extensions without function pointers:
    VK_KHR_sampler_mirror_clamp_to_edge spec_version 3
    VK_KHR_video_encode_h264 spec_version 14
    VK_KHR_video_encode_h265 spec_version 14
    VK_KHR_video_decode_h264 spec_version 9
    VK_KHR_multiview spec_version 1
    VK_KHR_shader_draw_parameters spec_version 1
    VK_KHR_external_memory spec_version 1
    VK_KHR_external_semaphore spec_version 1
    VK_KHR_shader_float16_int8 spec_version 1
    VK_KHR_16bit_storage spec_version 1
    VK_KHR_incremental_present spec_version 2
    VK_KHR_imageless_framebuffer spec_version 1
    VK_KHR_external_fence spec_version 1
    VK_KHR_maintenance2 spec_version 1
    VK_KHR_variable_pointers spec_version 1
    VK_KHR_dedicated_allocation spec_version 3
    VK_KHR_storage_buffer_storage_class spec_version 1
    VK_KHR_relaxed_block_layout spec_version 1
    VK_KHR_image_format_list spec_version 1
    VK_KHR_shader_subgroup_extended_types spec_version 1
    VK_KHR_8bit_storage spec_version 1
    VK_KHR_shader_atomic_int64 spec_version 1
    VK_KHR_shader_clock spec_version 1
    VK_KHR_video_decode_h265 spec_version 8
    VK_KHR_global_priority spec_version 1
    VK_KHR_driver_properties spec_version 1
    VK_KHR_shader_float_controls spec_version 4
    VK_KHR_depth_stencil_resolve spec_version 1
    VK_KHR_swapchain_mutable_format spec_version 1
    VK_KHR_vulkan_memory_model spec_version 3
    VK_KHR_shader_terminate_invocation spec_version 1
    VK_KHR_shader_quad_control spec_version 1
    VK_KHR_spirv_1_4 spec_version 1
    VK_KHR_surface_protected_capabilities spec_version 1
    VK_KHR_separate_depth_stencil_layouts spec_version 1
    VK_KHR_uniform_buffer_standard_layout spec_version 1
    VK_KHR_shader_integer_dot_product spec_version 1
    VK_KHR_pipeline_library spec_version 1
    VK_KHR_shader_non_semantic_info spec_version 1
    VK_KHR_present_id spec_version 1
    VK_KHR_fragment_shader_barycentric spec_version 1
    VK_KHR_shader_subgroup_uniform_control_flow spec_version 1
    VK_KHR_zero_initialize_workgroup_memory spec_version 1
    VK_KHR_workgroup_memory_explicit_layout spec_version 1
    VK_KHR_format_feature_flags2 spec_version 2
    VK_KHR_portability_enumeration spec_version 1
    VK_KHR_shader_subgroup_rotate spec_version 2
    VK_KHR_shader_maximal_reconvergence spec_version 1
    VK_KHR_ray_tracing_position_fetch spec_version 1
    VK_KHR_video_decode_av1 spec_version 1
    VK_KHR_video_maintenance1 spec_version 1
    VK_KHR_vertex_attribute_divisor spec_version 1
    VK_KHR_load_store_op_none spec_version 1
    VK_KHR_shader_float_controls2 spec_version 1
    VK_KHR_index_type_uint8 spec_version 1
    VK_KHR_shader_expect_assume spec_version 1
    VK_NV_glsl_shader spec_version 1
    VK_EXT_depth_range_unrestricted spec_version 1
    VK_IMG_filter_cubic spec_version 1
    VK_AMD_rasterization_order spec_version 1
    VK_AMD_shader_trinary_minmax spec_version 1
    VK_AMD_shader_explicit_vertex_parameter spec_version 1
    VK_AMD_gcn_shader spec_version 1
    VK_NV_dedicated_allocation spec_version 1
    VK_AMD_negative_viewport_height spec_version 1
    VK_AMD_gpu_shader_half_float spec_version 2
    VK_AMD_shader_ballot spec_version 1
    VK_AMD_texture_gather_bias_lod spec_version 1
    VK_AMD_shader_image_load_store_lod spec_version 1
    VK_NV_corner_sampled_image spec_version 2
    VK_IMG_format_pvrtc spec_version 1
    VK_NV_external_memory spec_version 1
    VK_EXT_validation_flags spec_version 3
    VK_EXT_shader_subgroup_ballot spec_version 1
    VK_EXT_shader_subgroup_vote spec_version 1
    VK_EXT_texture_compression_astc_hdr spec_version 1
    VK_EXT_astc_decode_mode spec_version 1
    VK_EXT_pipeline_robustness spec_version 1
    VK_NV_sample_mask_override_coverage spec_version 1
    VK_NV_geometry_shader_passthrough spec_version 1
    VK_NV_viewport_array2 spec_version 1
    VK_NVX_multiview_per_view_attributes spec_version 1
    VK_NV_viewport_swizzle spec_version 1
    VK_EXT_conservative_rasterization spec_version 1
    VK_EXT_depth_clip_enable spec_version 1
    VK_EXT_swapchain_colorspace spec_version 5
    VK_IMG_relaxed_line_rasterization spec_version 1
    VK_EXT_external_memory_dma_buf spec_version 1
    VK_EXT_queue_family_foreign spec_version 1
    VK_EXT_sampler_filter_minmax spec_version 2
    VK_AMD_gpu_shader_int16 spec_version 2
    VK_AMD_mixed_attachment_samples spec_version 1
    VK_AMD_shader_fragment_mask spec_version 1
    VK_EXT_inline_uniform_block spec_version 1
    VK_EXT_shader_stencil_export spec_version 1
    VK_EXT_blend_operation_advanced spec_version 2
    VK_NV_fragment_coverage_to_color spec_version 1
    VK_NV_framebuffer_mixed_samples spec_version 1
    VK_NV_fill_rectangle spec_version 1
    VK_NV_shader_sm_builtins spec_version 1
    VK_EXT_post_depth_coverage spec_version 1
    VK_EXT_descriptor_indexing spec_version 2
    VK_EXT_shader_viewport_index_layer spec_version 1
    VK_NV_representative_fragment_test spec_version 2
    VK_EXT_filter_cubic spec_version 3
    VK_QCOM_render_pass_shader_resolve spec_version 4
    VK_EXT_global_priority spec_version 2
    VK_AMD_pipeline_compiler_control spec_version 1
    VK_AMD_shader_core_properties spec_version 2
    VK_AMD_memory_overallocation_behavior spec_version 1
    VK_EXT_vertex_attribute_divisor spec_version 3
    VK_EXT_pipeline_creation_feedback spec_version 1
    VK_NV_shader_subgroup_partitioned spec_version 1
    VK_NV_compute_shader_derivatives spec_version 1
    VK_NV_fragment_shader_barycentric spec_version 1
    VK_NV_shader_image_footprint spec_version 2
    VK_INTEL_shader_integer_functions2 spec_version 1
    VK_EXT_pci_bus_info spec_version 2
    VK_EXT_fragment_density_map spec_version 2
    VK_EXT_scalar_block_layout spec_version 1
    VK_GOOGLE_hlsl_functionality1 spec_version 1
    VK_GOOGLE_decorate_string spec_version 1
    VK_EXT_subgroup_size_control spec_version 2
    VK_AMD_shader_core_properties2 spec_version 1
    VK_AMD_device_coherent_memory spec_version 1
    VK_EXT_shader_image_atomic_int64 spec_version 1
    VK_EXT_memory_budget spec_version 1
    VK_EXT_memory_priority spec_version 1
    VK_NV_dedicated_allocation_image_aliasing spec_version 1
    VK_EXT_separate_stencil_usage spec_version 1
    VK_EXT_validation_features spec_version 6
    VK_EXT_fragment_shader_interlock spec_version 1
    VK_EXT_ycbcr_image_arrays spec_version 1
    VK_EXT_provoking_vertex spec_version 1
    VK_EXT_shader_atomic_float spec_version 1
    VK_EXT_index_type_uint8 spec_version 1
    VK_EXT_map_memory_placed spec_version 1
    VK_EXT_shader_atomic_float2 spec_version 1
    VK_EXT_surface_maintenance1 spec_version 1
    VK_EXT_shader_demote_to_helper_invocation spec_version 1
    VK_NV_inherited_viewport_scissor spec_version 1
    VK_EXT_texel_buffer_alignment spec_version 1
    VK_QCOM_render_pass_transform spec_version 4
    VK_EXT_device_memory_report spec_version 2
    VK_EXT_robustness2 spec_version 1
    VK_EXT_custom_border_color spec_version 12
    VK_GOOGLE_user_type spec_version 1
    VK_NV_present_barrier spec_version 1
    VK_EXT_pipeline_creation_cache_control spec_version 3
    VK_NV_device_diagnostics_config spec_version 2
    VK_QCOM_render_pass_store_ops spec_version 2
    VK_NV_low_latency spec_version 1
    VK_EXT_graphics_pipeline_library spec_version 1
    VK_AMD_shader_early_and_late_fragment_tests spec_version 1
    VK_NV_ray_tracing_motion_blur spec_version 1
    VK_EXT_ycbcr_2plane_444_formats spec_version 1
    VK_EXT_fragment_density_map2 spec_version 1
    VK_QCOM_rotated_copy_commands spec_version 2
    VK_EXT_image_robustness spec_version 1
    VK_EXT_image_compression_control spec_version 1
    VK_EXT_attachment_feedback_loop_layout spec_version 2
    VK_EXT_4444_formats spec_version 1
    VK_ARM_rasterization_order_attachment_access spec_version 1
    VK_EXT_rgba10x6_formats spec_version 1
    VK_VALVE_mutable_descriptor_type spec_version 1
    VK_EXT_physical_device_drm spec_version 1
    VK_EXT_device_address_binding_report spec_version 1
    VK_EXT_depth_clip_control spec_version 1
    VK_EXT_primitive_topology_list_restart spec_version 1
    VK_EXT_frame_boundary spec_version 1
    VK_EXT_multisampled_render_to_single_sampled spec_version 1
    VK_EXT_primitives_generated_query spec_version 1
    VK_EXT_global_priority_query spec_version 1
    VK_EXT_image_view_min_lod spec_version 1
    VK_EXT_image_2d_view_of_3d spec_version 1
    VK_EXT_shader_tile_image spec_version 1
    VK_EXT_load_store_op_none spec_version 1
    VK_EXT_border_color_swizzle spec_version 1
    VK_ARM_shader_core_properties spec_version 1
    VK_ARM_scheduling_controls spec_version 1
    VK_EXT_image_sliced_view_of_3d spec_version 1
    VK_EXT_depth_clamp_zero_one spec_version 1
    VK_EXT_non_seamless_cube_map spec_version 1
    VK_ARM_render_pass_striped spec_version 1
    VK_QCOM_fragment_density_map_offset spec_version 2
    VK_NV_linear_color_attachment spec_version 1
    VK_GOOGLE_surfaceless_query spec_version 2
    VK_EXT_image_compression_control_swapchain spec_version 1
    VK_QCOM_image_processing spec_version 1
    VK_EXT_nested_command_buffer spec_version 1
    VK_EXT_external_memory_acquire_unmodified spec_version 1
    VK_EXT_subpass_merge_feedback spec_version 2
    VK_LUNARG_direct_driver_loading spec_version 1
    VK_EXT_rasterization_order_attachment_access spec_version 1
    VK_EXT_legacy_dithering spec_version 2
    VK_EXT_pipeline_protected_access spec_version 1
    VK_SEC_amigo_profiling spec_version 1
    VK_QCOM_multiview_per_view_viewports spec_version 1
    VK_NV_ray_tracing_invocation_reorder spec_version 1
    VK_NV_extended_sparse_address_space spec_version 1
    VK_EXT_mutable_descriptor_type spec_version 1
    VK_EXT_legacy_vertex_attributes spec_version 1
    VK_EXT_layer_settings spec_version 2
    VK_ARM_shader_core_builtins spec_version 2
    VK_EXT_pipeline_library_group_handles spec_version 1
    VK_EXT_dynamic_rendering_unused_attachments spec_version 1
    VK_QCOM_multiview_per_view_render_areas spec_version 1
    VK_NV_per_stage_descriptor_set spec_version 1
    VK_QCOM_image_processing2 spec_version 1
    VK_QCOM_filter_cubic_weights spec_version 1
    VK_QCOM_ycbcr_degamma spec_version 1
    VK_QCOM_filter_cubic_clamp spec_version 1
    VK_MSFT_layered_driver spec_version 1
    VK_NV_descriptor_pool_overallocation spec_version 1
    VK_NV_raw_access_chains spec_version 1
    VK_NV_shader_atomic_float16_vector spec_version 1
    VK_NV_ray_tracing_validation spec_version 1
    VK_KHR_ray_query spec_version 1
    VK_ANDROID_external_format_resolve spec_version 1
    VK_KHR_win32_keyed_mutex spec_version 1
    VK_NV_win32_keyed_mutex spec_version 2
    VK_GGP_frame_token spec_version 1
    VK_KHR_portability_subset spec_version 1
    VK_NV_displacement_micromap spec_version 2
        Additions from 1.3.284 to 1.4.309:
    VK_KHR_compute_shader_derivatives spec_version 1
    VK_KHR_video_encode_av1 spec_version 1
    VK_KHR_video_encode_quantization_map spec_version 2
    VK_KHR_shader_relaxed_extended_instruction spec_version 1
    VK_KHR_maintenance7 spec_version 1
    VK_KHR_maintenance8 spec_version 1
    VK_KHR_video_maintenance2 spec_version 1
    VK_KHR_depth_clamp_zero_one spec_version 1
    VK_EXT_present_mode_fifo_latest_ready spec_version 1
    VK_NV_ray_tracing_linear_swept_spheres spec_version 1
    VK_NV_display_stereo spec_version 1
    VK_NV_command_buffer_inheritance spec_version 1
    VK_EXT_shader_replicated_composites spec_version 1
    VK_MESA_image_alignment_control spec_version 1
    VK_EXT_depth_clamp_control spec_version 1
    VK_HUAWEI_hdr_vivid spec_version 1
    VK_ARM_pipeline_opacity_micromap spec_version 1
    VK_EXT_vertex_attribute_robustness spec_version 1
    VK_NV_present_metering spec_version 1
*/

static void vkadLoadGlobalFunctions  (PFN_vkGetInstanceProcAddr loader, VkadGlobalFunctions* functions) {
    /* VK_VERSION_1_0 */
    functions[0].EnumerateInstanceExtensionProperties                              = REINTERPRET_CAST(PFN_vkEnumerateInstanceExtensionProperties                              , loader(NULL, "vkEnumerateInstanceExtensionProperties"                            )) ;
    functions[0].EnumerateInstanceLayerProperties                                  = REINTERPRET_CAST(PFN_vkEnumerateInstanceLayerProperties                                  , loader(NULL, "vkEnumerateInstanceLayerProperties"                                )) ;
    functions[0].CreateInstance                                                    = REINTERPRET_CAST(PFN_vkCreateInstance                                                    , loader(NULL, "vkCreateInstance"                                                  )) ;
    /* VK_VERSION_1_1 */                                                                                                     
    functions[0].EnumerateInstanceVersion                                          = REINTERPRET_CAST(PFN_vkEnumerateInstanceVersion                                          , loader(NULL, "vkEnumerateInstanceVersion"                                        )) ;
}
static void vkadLoadInstanceFunctions(PFN_vkGetInstanceProcAddr loader, VkInstance instance, VkadInstanceFunctions* functions) {
    /* VK_VERSION_1_0 */                                                                                                                    
    functions[0].DestroyInstance                                                   = REINTERPRET_CAST(PFN_vkDestroyInstance                                                   , loader(instance, "vkDestroyInstance"                                                 )) ;
    functions[0].EnumeratePhysicalDevices                                          = REINTERPRET_CAST(PFN_vkEnumeratePhysicalDevices                                          , loader(instance, "vkEnumeratePhysicalDevices"                                        )) ;
    functions[0].GetPhysicalDeviceFeatures                                         = REINTERPRET_CAST(PFN_vkGetPhysicalDeviceFeatures                                         , loader(instance, "vkGetPhysicalDeviceFeatures"                                       )) ;
    functions[0].GetPhysicalDeviceFormatProperties                                 = REINTERPRET_CAST(PFN_vkGetPhysicalDeviceFormatProperties                                 , loader(instance, "vkGetPhysicalDeviceFormatProperties"                               )) ;
    functions[0].GetPhysicalDeviceImageFormatProperties                            = REINTERPRET_CAST(PFN_vkGetPhysicalDeviceImageFormatProperties                            , loader(instance, "vkGetPhysicalDeviceImageFormatProperties"                          )) ;
    functions[0].GetPhysicalDeviceProperties                                       = REINTERPRET_CAST(PFN_vkGetPhysicalDeviceProperties                                       , loader(instance, "vkGetPhysicalDeviceProperties"                                     )) ;
    functions[0].GetPhysicalDeviceQueueFamilyProperties                            = REINTERPRET_CAST(PFN_vkGetPhysicalDeviceQueueFamilyProperties                            , loader(instance, "vkGetPhysicalDeviceQueueFamilyProperties"                          )) ;
    functions[0].GetPhysicalDeviceMemoryProperties                                 = REINTERPRET_CAST(PFN_vkGetPhysicalDeviceMemoryProperties                                 , loader(instance, "vkGetPhysicalDeviceMemoryProperties"                               )) ;
    functions[0].EnumerateDeviceExtensionProperties                                = REINTERPRET_CAST(PFN_vkEnumerateDeviceExtensionProperties                                , loader(instance, "vkEnumerateDeviceExtensionProperties"                              )) ;
    functions[0].EnumerateDeviceLayerProperties                                    = REINTERPRET_CAST(PFN_vkEnumerateDeviceLayerProperties                                    , loader(instance, "vkEnumerateDeviceLayerProperties"                                  )) ;
    functions[0].GetPhysicalDeviceSparseImageFormatProperties                      = REINTERPRET_CAST(PFN_vkGetPhysicalDeviceSparseImageFormatProperties                      , loader(instance, "vkGetPhysicalDeviceSparseImageFormatProperties"                    )) ;
    functions[0].CreateDevice                                                      = REINTERPRET_CAST(PFN_vkCreateDevice                                                      , loader(instance, "vkCreateDevice"                                                    )) ;
    functions[0].GetDeviceProcAddr                                                 = REINTERPRET_CAST(PFN_vkGetDeviceProcAddr                                                 , loader(instance, "vkGetDeviceProcAddr"                                               )) ;
    /* VK_VERSION_1_1 */                                                             
    functions[0].EnumeratePhysicalDeviceGroups                                     = REINTERPRET_CAST(PFN_vkEnumeratePhysicalDeviceGroups                                     , loader(instance, "vkEnumeratePhysicalDeviceGroups"                                   )) ;
    functions[0].GetPhysicalDeviceFeatures2                                        = REINTERPRET_CAST(PFN_vkGetPhysicalDeviceFeatures2                                        , loader(instance, "vkGetPhysicalDeviceFeatures2"                                      )) ;
    functions[0].GetPhysicalDeviceProperties2                                      = REINTERPRET_CAST(PFN_vkGetPhysicalDeviceProperties2                                      , loader(instance, "vkGetPhysicalDeviceProperties2"                                    )) ;
    functions[0].GetPhysicalDeviceFormatProperties2                                = REINTERPRET_CAST(PFN_vkGetPhysicalDeviceFormatProperties2                                , loader(instance, "vkGetPhysicalDeviceFormatProperties2"                              )) ;
    functions[0].GetPhysicalDeviceImageFormatProperties2                           = REINTERPRET_CAST(PFN_vkGetPhysicalDeviceImageFormatProperties2                           , loader(instance, "vkGetPhysicalDeviceImageFormatProperties2"                         )) ;
    functions[0].GetPhysicalDeviceQueueFamilyProperties2                           = REINTERPRET_CAST(PFN_vkGetPhysicalDeviceQueueFamilyProperties2                           , loader(instance, "vkGetPhysicalDeviceQueueFamilyProperties2"                         )) ;
    functions[0].GetPhysicalDeviceMemoryProperties2                                = REINTERPRET_CAST(PFN_vkGetPhysicalDeviceMemoryProperties2                                , loader(instance, "vkGetPhysicalDeviceMemoryProperties2"                              )) ;
    functions[0].GetPhysicalDeviceSparseImageFormatProperties2                     = REINTERPRET_CAST(PFN_vkGetPhysicalDeviceSparseImageFormatProperties2                     , loader(instance, "vkGetPhysicalDeviceSparseImageFormatProperties2"                   )) ;
    functions[0].GetPhysicalDeviceExternalBufferProperties                         = REINTERPRET_CAST(PFN_vkGetPhysicalDeviceExternalBufferProperties                         , loader(instance, "vkGetPhysicalDeviceExternalBufferProperties"                       )) ;
    functions[0].GetPhysicalDeviceExternalFenceProperties                          = REINTERPRET_CAST(PFN_vkGetPhysicalDeviceExternalFenceProperties                          , loader(instance, "vkGetPhysicalDeviceExternalFenceProperties"                        )) ;
    functions[0].GetPhysicalDeviceExternalSemaphoreProperties                      = REINTERPRET_CAST(PFN_vkGetPhysicalDeviceExternalSemaphoreProperties                      , loader(instance, "vkGetPhysicalDeviceExternalSemaphoreProperties"                    )) ;
    /* VK_VERSION_1_3 */                                                             
    functions[0].GetPhysicalDeviceToolProperties                                   = REINTERPRET_CAST(PFN_vkGetPhysicalDeviceToolProperties                                   , loader(instance, "vkGetPhysicalDeviceToolProperties"                                 )) ;
    /* VK_KHR_surface spec_version 25  */                                            
    functions[0].DestroySurfaceKHR                                                 = REINTERPRET_CAST(PFN_vkDestroySurfaceKHR                                                 , loader(instance, "vkDestroySurfaceKHR"                                               )) ;
    functions[0].GetPhysicalDeviceSurfaceSupportKHR                                = REINTERPRET_CAST(PFN_vkGetPhysicalDeviceSurfaceSupportKHR                                , loader(instance, "vkGetPhysicalDeviceSurfaceSupportKHR"                              )) ;
    functions[0].GetPhysicalDeviceSurfaceCapabilitiesKHR                           = REINTERPRET_CAST(PFN_vkGetPhysicalDeviceSurfaceCapabilitiesKHR                           , loader(instance, "vkGetPhysicalDeviceSurfaceCapabilitiesKHR"                         )) ;
    functions[0].GetPhysicalDeviceSurfaceFormatsKHR                                = REINTERPRET_CAST(PFN_vkGetPhysicalDeviceSurfaceFormatsKHR                                , loader(instance, "vkGetPhysicalDeviceSurfaceFormatsKHR"                              )) ;
    functions[0].GetPhysicalDeviceSurfacePresentModesKHR                           = REINTERPRET_CAST(PFN_vkGetPhysicalDeviceSurfacePresentModesKHR                           , loader(instance, "vkGetPhysicalDeviceSurfacePresentModesKHR"                         )) ;
    /* VK_KHR_swapchain spec_version 70  */                                          
    functions[0].GetPhysicalDevicePresentRectanglesKHR                             = REINTERPRET_CAST(PFN_vkGetPhysicalDevicePresentRectanglesKHR                             , loader(instance, "vkGetPhysicalDevicePresentRectanglesKHR"                           )) ;
    /* VK_KHR_display spec_version 23  */                                            
    functions[0].GetPhysicalDeviceDisplayPropertiesKHR                             = REINTERPRET_CAST(PFN_vkGetPhysicalDeviceDisplayPropertiesKHR                             , loader(instance, "vkGetPhysicalDeviceDisplayPropertiesKHR"                           )) ;
    functions[0].GetPhysicalDeviceDisplayPlanePropertiesKHR                        = REINTERPRET_CAST(PFN_vkGetPhysicalDeviceDisplayPlanePropertiesKHR                        , loader(instance, "vkGetPhysicalDeviceDisplayPlanePropertiesKHR"                      )) ;
    functions[0].GetDisplayPlaneSupportedDisplaysKHR                               = REINTERPRET_CAST(PFN_vkGetDisplayPlaneSupportedDisplaysKHR                               , loader(instance, "vkGetDisplayPlaneSupportedDisplaysKHR"                             )) ;
    functions[0].GetDisplayModePropertiesKHR                                       = REINTERPRET_CAST(PFN_vkGetDisplayModePropertiesKHR                                       , loader(instance, "vkGetDisplayModePropertiesKHR"                                     )) ;
    functions[0].CreateDisplayModeKHR                                              = REINTERPRET_CAST(PFN_vkCreateDisplayModeKHR                                              , loader(instance, "vkCreateDisplayModeKHR"                                            )) ;
    functions[0].GetDisplayPlaneCapabilitiesKHR                                    = REINTERPRET_CAST(PFN_vkGetDisplayPlaneCapabilitiesKHR                                    , loader(instance, "vkGetDisplayPlaneCapabilitiesKHR"                                  )) ;
    functions[0].CreateDisplayPlaneSurfaceKHR                                      = REINTERPRET_CAST(PFN_vkCreateDisplayPlaneSurfaceKHR                                      , loader(instance, "vkCreateDisplayPlaneSurfaceKHR"                                    )) ;
    /* VK_KHR_video_queue spec_version 8 */                                          
    functions[0].GetPhysicalDeviceVideoCapabilitiesKHR                             = REINTERPRET_CAST(PFN_vkGetPhysicalDeviceVideoCapabilitiesKHR                             , loader(instance, "vkGetPhysicalDeviceVideoCapabilitiesKHR"                           )) ;
    functions[0].GetPhysicalDeviceVideoFormatPropertiesKHR                         = REINTERPRET_CAST(PFN_vkGetPhysicalDeviceVideoFormatPropertiesKHR                         , loader(instance, "vkGetPhysicalDeviceVideoFormatPropertiesKHR"                       )) ;
    /* VK_KHR_get_physical_device_properties2 spec_version 2 */                      
    functions[0].GetPhysicalDeviceFeatures2KHR                                     = REINTERPRET_CAST(PFN_vkGetPhysicalDeviceFeatures2KHR                                     , loader(instance, "vkGetPhysicalDeviceFeatures2KHR"                                   )) ;
    functions[0].GetPhysicalDeviceProperties2KHR                                   = REINTERPRET_CAST(PFN_vkGetPhysicalDeviceProperties2KHR                                   , loader(instance, "vkGetPhysicalDeviceProperties2KHR"                                 )) ;
    functions[0].GetPhysicalDeviceFormatProperties2KHR                             = REINTERPRET_CAST(PFN_vkGetPhysicalDeviceFormatProperties2KHR                             , loader(instance, "vkGetPhysicalDeviceFormatProperties2KHR"                           )) ;
    functions[0].GetPhysicalDeviceImageFormatProperties2KHR                        = REINTERPRET_CAST(PFN_vkGetPhysicalDeviceImageFormatProperties2KHR                        , loader(instance, "vkGetPhysicalDeviceImageFormatProperties2KHR"                      )) ;
    functions[0].GetPhysicalDeviceQueueFamilyProperties2KHR                        = REINTERPRET_CAST(PFN_vkGetPhysicalDeviceQueueFamilyProperties2KHR                        , loader(instance, "vkGetPhysicalDeviceQueueFamilyProperties2KHR"                      )) ;
    functions[0].GetPhysicalDeviceMemoryProperties2KHR                             = REINTERPRET_CAST(PFN_vkGetPhysicalDeviceMemoryProperties2KHR                             , loader(instance, "vkGetPhysicalDeviceMemoryProperties2KHR"                           )) ;
    functions[0].GetPhysicalDeviceSparseImageFormatProperties2KHR                  = REINTERPRET_CAST(PFN_vkGetPhysicalDeviceSparseImageFormatProperties2KHR                  , loader(instance, "vkGetPhysicalDeviceSparseImageFormatProperties2KHR"                )) ;
    /* VK_KHR_device_group_creation spec_version 1 */                                
    functions[0].EnumeratePhysicalDeviceGroupsKHR                                  = REINTERPRET_CAST(PFN_vkEnumeratePhysicalDeviceGroupsKHR                                  , loader(instance, "vkEnumeratePhysicalDeviceGroupsKHR"                                )) ;
    /* VK_KHR_external_memory_capabilities spec_version 1 */                         
    functions[0].GetPhysicalDeviceExternalBufferPropertiesKHR                      = REINTERPRET_CAST(PFN_vkGetPhysicalDeviceExternalBufferPropertiesKHR                      , loader(instance, "vkGetPhysicalDeviceExternalBufferPropertiesKHR"                    )) ;
    /* VK_KHR_external_semaphore_capabilities spec_version 1 */                      
    functions[0].GetPhysicalDeviceExternalSemaphorePropertiesKHR                   = REINTERPRET_CAST(PFN_vkGetPhysicalDeviceExternalSemaphorePropertiesKHR                   , loader(instance, "vkGetPhysicalDeviceExternalSemaphorePropertiesKHR"                 )) ;
    /* VK_KHR_external_fence_capabilities spec_version 1 */                          
    functions[0].GetPhysicalDeviceExternalFencePropertiesKHR                       = REINTERPRET_CAST(PFN_vkGetPhysicalDeviceExternalFencePropertiesKHR                       , loader(instance, "vkGetPhysicalDeviceExternalFencePropertiesKHR"                     )) ;
    /* VK_KHR_performance_query spec_version 1 */                                    
    functions[0].EnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR     = REINTERPRET_CAST(PFN_vkEnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR     , loader(instance, "vkEnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR"   )) ;
    functions[0].GetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR             = REINTERPRET_CAST(PFN_vkGetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR             , loader(instance, "vkGetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR"           )) ;
    /* VK_KHR_get_surface_capabilities2 spec_version 1 */                            
    functions[0].GetPhysicalDeviceSurfaceCapabilities2KHR                          = REINTERPRET_CAST(PFN_vkGetPhysicalDeviceSurfaceCapabilities2KHR                          , loader(instance, "vkGetPhysicalDeviceSurfaceCapabilities2KHR"                        )) ;
    functions[0].GetPhysicalDeviceSurfaceFormats2KHR                               = REINTERPRET_CAST(PFN_vkGetPhysicalDeviceSurfaceFormats2KHR                               , loader(instance, "vkGetPhysicalDeviceSurfaceFormats2KHR"                             )) ;
    /* VK_KHR_get_display_properties2 spec_version 1 */                              
    functions[0].GetPhysicalDeviceDisplayProperties2KHR                            = REINTERPRET_CAST(PFN_vkGetPhysicalDeviceDisplayProperties2KHR                            , loader(instance, "vkGetPhysicalDeviceDisplayProperties2KHR"                          )) ;
    functions[0].GetPhysicalDeviceDisplayPlaneProperties2KHR                       = REINTERPRET_CAST(PFN_vkGetPhysicalDeviceDisplayPlaneProperties2KHR                       , loader(instance, "vkGetPhysicalDeviceDisplayPlaneProperties2KHR"                     )) ;  
    functions[0].GetDisplayModeProperties2KHR                                      = REINTERPRET_CAST(PFN_vkGetDisplayModeProperties2KHR                                      , loader(instance, "vkGetDisplayModeProperties2KHR"                                    )) ;
    functions[0].GetDisplayPlaneCapabilities2KHR                                   = REINTERPRET_CAST(PFN_vkGetDisplayPlaneCapabilities2KHR                                   , loader(instance, "vkGetDisplayPlaneCapabilities2KHR"                                 )) ;
    /* VK_KHR_fragment_shading_rate spec_version 2 */                                
    functions[0].GetPhysicalDeviceFragmentShadingRatesKHR                          = REINTERPRET_CAST(PFN_vkGetPhysicalDeviceFragmentShadingRatesKHR                          , loader(instance, "vkGetPhysicalDeviceFragmentShadingRatesKHR"                        )) ;
    /* VK_KHR_video_encode_queue spec_version 12 */                                  
    functions[0].GetPhysicalDeviceVideoEncodeQualityLevelPropertiesKHR             = REINTERPRET_CAST(PFN_vkGetPhysicalDeviceVideoEncodeQualityLevelPropertiesKHR             , loader(instance, "vkGetPhysicalDeviceVideoEncodeQualityLevelPropertiesKHR"           )) ;
    /* VK_KHR_cooperative_matrix spec_version 2 */                                   
    functions[0].GetPhysicalDeviceCooperativeMatrixPropertiesKHR                   = REINTERPRET_CAST(PFN_vkGetPhysicalDeviceCooperativeMatrixPropertiesKHR                   , loader(instance, "vkGetPhysicalDeviceCooperativeMatrixPropertiesKHR"                 )) ;
    /* VK_KHR_calibrated_timestamps spec_version 1 */                                
    functions[0].GetPhysicalDeviceCalibrateableTimeDomainsKHR                      = REINTERPRET_CAST(PFN_vkGetPhysicalDeviceCalibrateableTimeDomainsKHR                      , loader(instance, "vkGetPhysicalDeviceCalibrateableTimeDomainsKHR"                    )) ;
    /* VK_EXT_debug_report spec_version 10 */                                        
    functions[0].CreateDebugReportCallbackEXT                                      = REINTERPRET_CAST(PFN_vkCreateDebugReportCallbackEXT                                      , loader(instance, "vkCreateDebugReportCallbackEXT"                                    )) ;
    functions[0].DestroyDebugReportCallbackEXT                                     = REINTERPRET_CAST(PFN_vkDestroyDebugReportCallbackEXT                                     , loader(instance, "vkDestroyDebugReportCallbackEXT"                                   )) ;
    functions[0].DebugReportMessageEXT                                             = REINTERPRET_CAST(PFN_vkDebugReportMessageEXT                                             , loader(instance, "vkDebugReportMessageEXT"                                           )) ;
    /* VK_NV_external_memory_capabilities spec_version 1 */                          
    functions[0].GetPhysicalDeviceExternalImageFormatPropertiesNV                  = REINTERPRET_CAST(PFN_vkGetPhysicalDeviceExternalImageFormatPropertiesNV                  , loader(instance, "vkGetPhysicalDeviceExternalImageFormatPropertiesNV"                )) ;
    /* VK_EXT_direct_mode_display spec_version 1 */                                  
    functions[0].ReleaseDisplayEXT                                                 = REINTERPRET_CAST(PFN_vkReleaseDisplayEXT                                                 , loader(instance, "vkReleaseDisplayEXT"                                               )) ;
    /* VK_EXT_display_surface_counter spec_version 1 */                              
    functions[0].GetPhysicalDeviceSurfaceCapabilities2EXT                          = REINTERPRET_CAST(PFN_vkGetPhysicalDeviceSurfaceCapabilities2EXT                          , loader(instance, "vkGetPhysicalDeviceSurfaceCapabilities2EXT"                        )) ;
    /* VK_EXT_debug_utils spec_version 2 */                                          
    functions[0].CreateDebugUtilsMessengerEXT                                      = REINTERPRET_CAST(PFN_vkCreateDebugUtilsMessengerEXT                                      , loader(instance, "vkCreateDebugUtilsMessengerEXT"                                    )) ;
    functions[0].DestroyDebugUtilsMessengerEXT                                     = REINTERPRET_CAST(PFN_vkDestroyDebugUtilsMessengerEXT                                     , loader(instance, "vkDestroyDebugUtilsMessengerEXT"                                   )) ;
    functions[0].SubmitDebugUtilsMessageEXT                                        = REINTERPRET_CAST(PFN_vkSubmitDebugUtilsMessageEXT                                        , loader(instance, "vkSubmitDebugUtilsMessageEXT"                                      )) ;
    /* VK_EXT_sample_locations spec_version 1 */                                     
    functions[0].GetPhysicalDeviceMultisamplePropertiesEXT                         = REINTERPRET_CAST(PFN_vkGetPhysicalDeviceMultisamplePropertiesEXT                         , loader(instance, "vkGetPhysicalDeviceMultisamplePropertiesEXT"                       )) ;
    /* VK_EXT_calibrated_timestamps spec_version 2 */                                
    functions[0].GetPhysicalDeviceCalibrateableTimeDomainsEXT                      = REINTERPRET_CAST(PFN_vkGetPhysicalDeviceCalibrateableTimeDomainsEXT                      , loader(instance, "vkGetPhysicalDeviceCalibrateableTimeDomainsEXT"                    )) ;
    /* VK_EXT_tooling_info spec_version 1 */                                         
    functions[0].GetPhysicalDeviceToolPropertiesEXT                                = REINTERPRET_CAST(PFN_vkGetPhysicalDeviceToolPropertiesEXT                                , loader(instance, "vkGetPhysicalDeviceToolPropertiesEXT"                              )) ;
    /* VK_NV_cooperative_matrix spec_version 1 */                                    
    functions[0].GetPhysicalDeviceCooperativeMatrixPropertiesNV                    = REINTERPRET_CAST(PFN_vkGetPhysicalDeviceCooperativeMatrixPropertiesNV                    , loader(instance, "vkGetPhysicalDeviceCooperativeMatrixPropertiesNV"                  )) ;
    /* VK_NV_coverage_reduction_mode spec_version 1 */                               
    functions[0].GetPhysicalDeviceSupportedFramebufferMixedSamplesCombinationsNV   = REINTERPRET_CAST(PFN_vkGetPhysicalDeviceSupportedFramebufferMixedSamplesCombinationsNV   , loader(instance, "vkGetPhysicalDeviceSupportedFramebufferMixedSamplesCombinationsNV" )) ;
    /* VK_EXT_headless_surface spec_version 1 */                                     
    functions[0].CreateHeadlessSurfaceEXT                                          = REINTERPRET_CAST(PFN_vkCreateHeadlessSurfaceEXT                                          , loader(instance, "vkCreateHeadlessSurfaceEXT"                                        )) ;
    /* VK_EXT_acquire_drm_display spec_version 1 */                                  
    functions[0].AcquireDrmDisplayEXT                                              = REINTERPRET_CAST(PFN_vkAcquireDrmDisplayEXT                                              , loader(instance, "vkAcquireDrmDisplayEXT"                                            )) ;
    functions[0].GetDrmDisplayEXT                                                  = REINTERPRET_CAST(PFN_vkGetDrmDisplayEXT                                                  , loader(instance, "vkGetDrmDisplayEXT"                                                )) ;
    /* VK_NV_optical_flow spec_version 1 */                                          
    functions[0].GetPhysicalDeviceOpticalFlowImageFormatsNV                        = REINTERPRET_CAST(PFN_vkGetPhysicalDeviceOpticalFlowImageFormatsNV                        , loader(instance, "vkGetPhysicalDeviceOpticalFlowImageFormatsNV"                      )) ;
    /* VK_KHR_android_surface spec_version 6 */                                      
    functions[0].CreateAndroidSurfaceKHR                                           = REINTERPRET_CAST(PFN_vkCreateAndroidSurfaceKHR                                           , loader(instance, "vkCreateAndroidSurfaceKHR"                                         )) ;
    /* VK_FUCHSIA_imagepipe_surface spec_version 1 */                                
    functions[0].CreateImagePipeSurfaceFUCHSIA                                     = REINTERPRET_CAST(PFN_vkCreateImagePipeSurfaceFUCHSIA                                     , loader(instance, "vkCreateImagePipeSurfaceFUCHSIA"                                   )) ;
    /* VK_MVK_ios_surface spec_version 3 */                                          
    functions[0].CreateIOSSurfaceMVK                                               = REINTERPRET_CAST(PFN_vkCreateIOSSurfaceMVK                                               , loader(instance, "vkCreateIOSSurfaceMVK"                                             )) ;
    /* VK_MVK_macos_surface spec_version 3 */                                        
    functions[0].CreateMacOSSurfaceMVK                                             = REINTERPRET_CAST(PFN_vkCreateMacOSSurfaceMVK                                             , loader(instance, "vkCreateMacOSSurfaceMVK"                                           )) ;
    /* VK_EXT_metal_surface spec_version 1 */                                        
    functions[0].CreateMetalSurfaceEXT                                             = REINTERPRET_CAST(PFN_vkCreateMetalSurfaceEXT                                             , loader(instance, "vkCreateMetalSurfaceEXT"                                           )) ;
    /* VK_NN_vi_surface spec_version 1 */                                            
    functions[0].CreateViSurfaceNN                                                 = REINTERPRET_CAST(PFN_vkCreateViSurfaceNN                                                 , loader(instance, "vkCreateViSurfaceNN"                                               )) ;
    /* VK_KHR_wayland_surface spec_version 6 */                                      
    functions[0].CreateWaylandSurfaceKHR                                           = REINTERPRET_CAST(PFN_vkCreateWaylandSurfaceKHR                                           , loader(instance, "vkCreateWaylandSurfaceKHR"                                         )) ;
    functions[0].GetPhysicalDeviceWaylandPresentationSupportKHR                    = REINTERPRET_CAST(PFN_vkGetPhysicalDeviceWaylandPresentationSupportKHR                    , loader(instance, "vkGetPhysicalDeviceWaylandPresentationSupportKHR"                  )) ;
    /* VK_KHR_win32_surface spec_version 6 */                                        
    functions[0].CreateWin32SurfaceKHR                                             = REINTERPRET_CAST(PFN_vkCreateWin32SurfaceKHR                                             , loader(instance, "vkCreateWin32SurfaceKHR"                                           )) ;
    functions[0].GetPhysicalDeviceWin32PresentationSupportKHR                      = REINTERPRET_CAST(PFN_vkGetPhysicalDeviceWin32PresentationSupportKHR                      , loader(instance, "vkGetPhysicalDeviceWin32PresentationSupportKHR"                    )) ;
    /* VK_EXT_full_screen_exclusive spec_version 4 */                                
    functions[0].GetPhysicalDeviceSurfacePresentModes2EXT                          = REINTERPRET_CAST(PFN_vkGetPhysicalDeviceSurfacePresentModes2EXT                          , loader(instance, "vkGetPhysicalDeviceSurfacePresentModes2EXT"                        )) ;
    /* VK_NV_acquire_winrt_display spec_version 1 */                                 
    functions[0].AcquireWinrtDisplayNV                                             = REINTERPRET_CAST(PFN_vkAcquireWinrtDisplayNV                                             , loader(instance, "vkAcquireWinrtDisplayNV"                                           )) ;
    functions[0].GetWinrtDisplayNV                                                 = REINTERPRET_CAST(PFN_vkGetWinrtDisplayNV                                                 , loader(instance, "vkGetWinrtDisplayNV"                                               )) ;
    /* VK_KHR_xcb_surface spec_version 6 */                                          
    functions[0].CreateXcbSurfaceKHR                                               = REINTERPRET_CAST(PFN_vkCreateXcbSurfaceKHR                                               , loader(instance, "vkCreateXcbSurfaceKHR"                                             )) ;
    functions[0].GetPhysicalDeviceXcbPresentationSupportKHR                        = REINTERPRET_CAST(PFN_vkGetPhysicalDeviceXcbPresentationSupportKHR                        , loader(instance, "vkGetPhysicalDeviceXcbPresentationSupportKHR"                      )) ;
    /* VK_KHR_xlib_surface spec_version 6 */                                         
    functions[0].CreateXlibSurfaceKHR                                              = REINTERPRET_CAST(PFN_vkCreateXlibSurfaceKHR                                              , loader(instance, "vkCreateXlibSurfaceKHR"                                            )) ;
    functions[0].GetPhysicalDeviceXlibPresentationSupportKHR                       = REINTERPRET_CAST(PFN_vkGetPhysicalDeviceXlibPresentationSupportKHR                       , loader(instance, "vkGetPhysicalDeviceXlibPresentationSupportKHR"                     )) ;
    /* VK_EXT_directfb_surface spec_version 1 */                                     
    functions[0].CreateDirectFBSurfaceEXT                                          = REINTERPRET_CAST(PFN_vkCreateDirectFBSurfaceEXT                                          , loader(instance, "vkCreateDirectFBSurfaceEXT"                                        )) ;
    functions[0].GetPhysicalDeviceDirectFBPresentationSupportEXT                   = REINTERPRET_CAST(PFN_vkGetPhysicalDeviceDirectFBPresentationSupportEXT                   , loader(instance, "vkGetPhysicalDeviceDirectFBPresentationSupportEXT"                 )) ;
    /* VK_EXT_acquire_xlib_display spec_version 1 */                                 
    functions[0].AcquireXlibDisplayEXT                                             = REINTERPRET_CAST(PFN_vkAcquireXlibDisplayEXT                                             , loader(instance, "vkAcquireXlibDisplayEXT"                                           )) ;
    functions[0].GetRandROutputDisplayEXT                                          = REINTERPRET_CAST(PFN_vkGetRandROutputDisplayEXT                                          , loader(instance, "vkGetRandROutputDisplayEXT"                                        )) ;
    /* VK_GGP_stream_descriptor_surface spec_version 1 */                            
    functions[0].CreateStreamDescriptorSurfaceGGP                                  = REINTERPRET_CAST(PFN_vkCreateStreamDescriptorSurfaceGGP                                  , loader(instance, "vkCreateStreamDescriptorSurfaceGGP"                                )) ;
    /* VK_QNX_screen_surface spec_version 1 */                                       
    functions[0].CreateScreenSurfaceQNX                                            = REINTERPRET_CAST(PFN_vkCreateScreenSurfaceQNX                                            , loader(instance, "vkCreateScreenSurfaceQNX"                                          )) ;
    functions[0].GetPhysicalDeviceScreenPresentationSupportQNX                     = REINTERPRET_CAST(PFN_vkGetPhysicalDeviceScreenPresentationSupportQNX                     , loader(instance, "vkGetPhysicalDeviceScreenPresentationSupportQNX"                   )) ;
        /* Additions from 1.3.284 to 1.4.309: */
    /* VK_NV_cooperative_vector spec_version 4 */
    functions[0].GetPhysicalDeviceCooperativeVectorPropertiesNV                    = REINTERPRET_CAST(PFN_vkGetPhysicalDeviceCooperativeVectorPropertiesNV                    , loader(instance, "vkGetPhysicalDeviceCooperativeVectorPropertiesNV"                  )) ;
    /* VK_NV_cooperative_matrix2 spec_version 1 */
    functions[0].GetPhysicalDeviceCooperativeMatrixFlexibleDimensionsPropertiesNV  = REINTERPRET_CAST(PFN_vkGetPhysicalDeviceCooperativeMatrixFlexibleDimensionsPropertiesNV  , loader(instance, "vkGetPhysicalDeviceCooperativeMatrixFlexibleDimensionsPropertiesNV")) ;
}
static void vkadLoadDeviceFunctions  (PFN_vkGetDeviceProcAddr loader, VkDevice device, VkadDeviceFunctions* functions) {
    /* VK_VERSION_1_0 */
    functions[0].DestroyDevice                                                     = REINTERPRET_CAST(PFN_vkDestroyDevice                                                     , loader(device, "vkDestroyDevice"                                                 )) ;
    functions[0].GetDeviceQueue                                                    = REINTERPRET_CAST(PFN_vkGetDeviceQueue                                                    , loader(device, "vkGetDeviceQueue"                                                )) ;
    functions[0].QueueSubmit                                                       = REINTERPRET_CAST(PFN_vkQueueSubmit                                                       , loader(device, "vkQueueSubmit"                                                   )) ;
    functions[0].QueueWaitIdle                                                     = REINTERPRET_CAST(PFN_vkQueueWaitIdle                                                     , loader(device, "vkQueueWaitIdle"                                                 )) ;
    functions[0].DeviceWaitIdle                                                    = REINTERPRET_CAST(PFN_vkDeviceWaitIdle                                                    , loader(device, "vkDeviceWaitIdle"                                                )) ;
    functions[0].AllocateMemory                                                    = REINTERPRET_CAST(PFN_vkAllocateMemory                                                    , loader(device, "vkAllocateMemory"                                                )) ;
    functions[0].FreeMemory                                                        = REINTERPRET_CAST(PFN_vkFreeMemory                                                        , loader(device, "vkFreeMemory"                                                    )) ;
    functions[0].MapMemory                                                         = REINTERPRET_CAST(PFN_vkMapMemory                                                         , loader(device, "vkMapMemory"                                                     )) ;
    functions[0].UnmapMemory                                                       = REINTERPRET_CAST(PFN_vkUnmapMemory                                                       , loader(device, "vkUnmapMemory"                                                   )) ;
    functions[0].FlushMappedMemoryRanges                                           = REINTERPRET_CAST(PFN_vkFlushMappedMemoryRanges                                           , loader(device, "vkFlushMappedMemoryRanges"                                       )) ;
    functions[0].InvalidateMappedMemoryRanges                                      = REINTERPRET_CAST(PFN_vkInvalidateMappedMemoryRanges                                      , loader(device, "vkInvalidateMappedMemoryRanges"                                  )) ;
    functions[0].GetDeviceMemoryCommitment                                         = REINTERPRET_CAST(PFN_vkGetDeviceMemoryCommitment                                         , loader(device, "vkGetDeviceMemoryCommitment"                                     )) ;
    functions[0].BindBufferMemory                                                  = REINTERPRET_CAST(PFN_vkBindBufferMemory                                                  , loader(device, "vkBindBufferMemory"                                              )) ;
    functions[0].BindImageMemory                                                   = REINTERPRET_CAST(PFN_vkBindImageMemory                                                   , loader(device, "vkBindImageMemory"                                               )) ;
    functions[0].GetBufferMemoryRequirements                                       = REINTERPRET_CAST(PFN_vkGetBufferMemoryRequirements                                       , loader(device, "vkGetBufferMemoryRequirements"                                   )) ;
    functions[0].GetImageMemoryRequirements                                        = REINTERPRET_CAST(PFN_vkGetImageMemoryRequirements                                        , loader(device, "vkGetImageMemoryRequirements"                                    )) ;
    functions[0].GetImageSparseMemoryRequirements                                  = REINTERPRET_CAST(PFN_vkGetImageSparseMemoryRequirements                                  , loader(device, "vkGetImageSparseMemoryRequirements"                              )) ;
    functions[0].QueueBindSparse                                                   = REINTERPRET_CAST(PFN_vkQueueBindSparse                                                   , loader(device, "vkQueueBindSparse"                                               )) ;
    functions[0].CreateFence                                                       = REINTERPRET_CAST(PFN_vkCreateFence                                                       , loader(device, "vkCreateFence"                                                   )) ;
    functions[0].DestroyFence                                                      = REINTERPRET_CAST(PFN_vkDestroyFence                                                      , loader(device, "vkDestroyFence"                                                  )) ;
    functions[0].ResetFences                                                       = REINTERPRET_CAST(PFN_vkResetFences                                                       , loader(device, "vkResetFences"                                                   )) ;
    functions[0].GetFenceStatus                                                    = REINTERPRET_CAST(PFN_vkGetFenceStatus                                                    , loader(device, "vkGetFenceStatus"                                                )) ;
    functions[0].WaitForFences                                                     = REINTERPRET_CAST(PFN_vkWaitForFences                                                     , loader(device, "vkWaitForFences"                                                 )) ;
    functions[0].CreateSemaphore                                                   = REINTERPRET_CAST(PFN_vkCreateSemaphore                                                   , loader(device, "vkCreateSemaphore"                                               )) ;
    functions[0].DestroySemaphore                                                  = REINTERPRET_CAST(PFN_vkDestroySemaphore                                                  , loader(device, "vkDestroySemaphore"                                              )) ;
    functions[0].CreateEvent                                                       = REINTERPRET_CAST(PFN_vkCreateEvent                                                       , loader(device, "vkCreateEvent"                                                   )) ;
    functions[0].DestroyEvent                                                      = REINTERPRET_CAST(PFN_vkDestroyEvent                                                      , loader(device, "vkDestroyEvent"                                                  )) ;
    functions[0].GetEventStatus                                                    = REINTERPRET_CAST(PFN_vkGetEventStatus                                                    , loader(device, "vkGetEventStatus"                                                )) ;
    functions[0].SetEvent                                                          = REINTERPRET_CAST(PFN_vkSetEvent                                                          , loader(device, "vkSetEvent"                                                      )) ;
    functions[0].ResetEvent                                                        = REINTERPRET_CAST(PFN_vkResetEvent                                                        , loader(device, "vkResetEvent"                                                    )) ;
    functions[0].CreateQueryPool                                                   = REINTERPRET_CAST(PFN_vkCreateQueryPool                                                   , loader(device, "vkCreateQueryPool"                                               )) ;
    functions[0].DestroyQueryPool                                                  = REINTERPRET_CAST(PFN_vkDestroyQueryPool                                                  , loader(device, "vkDestroyQueryPool"                                              )) ;
    functions[0].GetQueryPoolResults                                               = REINTERPRET_CAST(PFN_vkGetQueryPoolResults                                               , loader(device, "vkGetQueryPoolResults"                                           )) ;
    functions[0].CreateBuffer                                                      = REINTERPRET_CAST(PFN_vkCreateBuffer                                                      , loader(device, "vkCreateBuffer"                                                  )) ;
    functions[0].DestroyBuffer                                                     = REINTERPRET_CAST(PFN_vkDestroyBuffer                                                     , loader(device, "vkDestroyBuffer"                                                 )) ;
    functions[0].CreateBufferView                                                  = REINTERPRET_CAST(PFN_vkCreateBufferView                                                  , loader(device, "vkCreateBufferView"                                              )) ;
    functions[0].DestroyBufferView                                                 = REINTERPRET_CAST(PFN_vkDestroyBufferView                                                 , loader(device, "vkDestroyBufferView"                                             )) ;
    functions[0].CreateImage                                                       = REINTERPRET_CAST(PFN_vkCreateImage                                                       , loader(device, "vkCreateImage"                                                   )) ;
    functions[0].DestroyImage                                                      = REINTERPRET_CAST(PFN_vkDestroyImage                                                      , loader(device, "vkDestroyImage"                                                  )) ;
    functions[0].GetImageSubresourceLayout                                         = REINTERPRET_CAST(PFN_vkGetImageSubresourceLayout                                         , loader(device, "vkGetImageSubresourceLayout"                                     )) ;
    functions[0].CreateImageView                                                   = REINTERPRET_CAST(PFN_vkCreateImageView                                                   , loader(device, "vkCreateImageView"                                               )) ;
    functions[0].DestroyImageView                                                  = REINTERPRET_CAST(PFN_vkDestroyImageView                                                  , loader(device, "vkDestroyImageView"                                              )) ;
    functions[0].CreateShaderModule                                                = REINTERPRET_CAST(PFN_vkCreateShaderModule                                                , loader(device, "vkCreateShaderModule"                                            )) ;
    functions[0].DestroyShaderModule                                               = REINTERPRET_CAST(PFN_vkDestroyShaderModule                                               , loader(device, "vkDestroyShaderModule"                                           )) ;
    functions[0].CreatePipelineCache                                               = REINTERPRET_CAST(PFN_vkCreatePipelineCache                                               , loader(device, "vkCreatePipelineCache"                                           )) ;
    functions[0].DestroyPipelineCache                                              = REINTERPRET_CAST(PFN_vkDestroyPipelineCache                                              , loader(device, "vkDestroyPipelineCache"                                          )) ;
    functions[0].GetPipelineCacheData                                              = REINTERPRET_CAST(PFN_vkGetPipelineCacheData                                              , loader(device, "vkGetPipelineCacheData"                                          )) ;
    functions[0].MergePipelineCaches                                               = REINTERPRET_CAST(PFN_vkMergePipelineCaches                                               , loader(device, "vkMergePipelineCaches"                                           )) ;
    functions[0].CreateGraphicsPipelines                                           = REINTERPRET_CAST(PFN_vkCreateGraphicsPipelines                                           , loader(device, "vkCreateGraphicsPipelines"                                       )) ;
    functions[0].CreateComputePipelines                                            = REINTERPRET_CAST(PFN_vkCreateComputePipelines                                            , loader(device, "vkCreateComputePipelines"                                        )) ;
    functions[0].DestroyPipeline                                                   = REINTERPRET_CAST(PFN_vkDestroyPipeline                                                   , loader(device, "vkDestroyPipeline"                                               )) ;
    functions[0].CreatePipelineLayout                                              = REINTERPRET_CAST(PFN_vkCreatePipelineLayout                                              , loader(device, "vkCreatePipelineLayout"                                          )) ;
    functions[0].DestroyPipelineLayout                                             = REINTERPRET_CAST(PFN_vkDestroyPipelineLayout                                             , loader(device, "vkDestroyPipelineLayout"                                         )) ;
    functions[0].CreateSampler                                                     = REINTERPRET_CAST(PFN_vkCreateSampler                                                     , loader(device, "vkCreateSampler"                                                 )) ;
    functions[0].DestroySampler                                                    = REINTERPRET_CAST(PFN_vkDestroySampler                                                    , loader(device, "vkDestroySampler"                                                )) ;
    functions[0].CreateDescriptorSetLayout                                         = REINTERPRET_CAST(PFN_vkCreateDescriptorSetLayout                                         , loader(device, "vkCreateDescriptorSetLayout"                                     )) ;
    functions[0].DestroyDescriptorSetLayout                                        = REINTERPRET_CAST(PFN_vkDestroyDescriptorSetLayout                                        , loader(device, "vkDestroyDescriptorSetLayout"                                    )) ;
    functions[0].CreateDescriptorPool                                              = REINTERPRET_CAST(PFN_vkCreateDescriptorPool                                              , loader(device, "vkCreateDescriptorPool"                                          )) ;
    functions[0].DestroyDescriptorPool                                             = REINTERPRET_CAST(PFN_vkDestroyDescriptorPool                                             , loader(device, "vkDestroyDescriptorPool"                                         )) ;
    functions[0].ResetDescriptorPool                                               = REINTERPRET_CAST(PFN_vkResetDescriptorPool                                               , loader(device, "vkResetDescriptorPool"                                           )) ;
    functions[0].AllocateDescriptorSets                                            = REINTERPRET_CAST(PFN_vkAllocateDescriptorSets                                            , loader(device, "vkAllocateDescriptorSets"                                        )) ;
    functions[0].FreeDescriptorSets                                                = REINTERPRET_CAST(PFN_vkFreeDescriptorSets                                                , loader(device, "vkFreeDescriptorSets"                                            )) ;
    functions[0].UpdateDescriptorSets                                              = REINTERPRET_CAST(PFN_vkUpdateDescriptorSets                                              , loader(device, "vkUpdateDescriptorSets"                                          )) ;
    functions[0].CreateFramebuffer                                                 = REINTERPRET_CAST(PFN_vkCreateFramebuffer                                                 , loader(device, "vkCreateFramebuffer"                                             )) ;
    functions[0].DestroyFramebuffer                                                = REINTERPRET_CAST(PFN_vkDestroyFramebuffer                                                , loader(device, "vkDestroyFramebuffer"                                            )) ;
    functions[0].CreateRenderPass                                                  = REINTERPRET_CAST(PFN_vkCreateRenderPass                                                  , loader(device, "vkCreateRenderPass"                                              )) ;
    functions[0].DestroyRenderPass                                                 = REINTERPRET_CAST(PFN_vkDestroyRenderPass                                                 , loader(device, "vkDestroyRenderPass"                                             )) ;
    functions[0].GetRenderAreaGranularity                                          = REINTERPRET_CAST(PFN_vkGetRenderAreaGranularity                                          , loader(device, "vkGetRenderAreaGranularity"                                      )) ;
    functions[0].CreateCommandPool                                                 = REINTERPRET_CAST(PFN_vkCreateCommandPool                                                 , loader(device, "vkCreateCommandPool"                                             )) ;
    functions[0].DestroyCommandPool                                                = REINTERPRET_CAST(PFN_vkDestroyCommandPool                                                , loader(device, "vkDestroyCommandPool"                                            )) ;
    functions[0].ResetCommandPool                                                  = REINTERPRET_CAST(PFN_vkResetCommandPool                                                  , loader(device, "vkResetCommandPool"                                              )) ;
    functions[0].AllocateCommandBuffers                                            = REINTERPRET_CAST(PFN_vkAllocateCommandBuffers                                            , loader(device, "vkAllocateCommandBuffers"                                        )) ;
    functions[0].FreeCommandBuffers                                                = REINTERPRET_CAST(PFN_vkFreeCommandBuffers                                                , loader(device, "vkFreeCommandBuffers"                                            )) ;
    functions[0].BeginCommandBuffer                                                = REINTERPRET_CAST(PFN_vkBeginCommandBuffer                                                , loader(device, "vkBeginCommandBuffer"                                            )) ;
    functions[0].EndCommandBuffer                                                  = REINTERPRET_CAST(PFN_vkEndCommandBuffer                                                  , loader(device, "vkEndCommandBuffer"                                              )) ;
    functions[0].ResetCommandBuffer                                                = REINTERPRET_CAST(PFN_vkResetCommandBuffer                                                , loader(device, "vkResetCommandBuffer"                                            )) ;
    functions[0].CmdBindPipeline                                                   = REINTERPRET_CAST(PFN_vkCmdBindPipeline                                                   , loader(device, "vkCmdBindPipeline"                                               )) ;
    functions[0].CmdSetViewport                                                    = REINTERPRET_CAST(PFN_vkCmdSetViewport                                                    , loader(device, "vkCmdSetViewport"                                                )) ;
    functions[0].CmdSetScissor                                                     = REINTERPRET_CAST(PFN_vkCmdSetScissor                                                     , loader(device, "vkCmdSetScissor"                                                 )) ;
    functions[0].CmdSetLineWidth                                                   = REINTERPRET_CAST(PFN_vkCmdSetLineWidth                                                   , loader(device, "vkCmdSetLineWidth"                                               )) ;
    functions[0].CmdSetDepthBias                                                   = REINTERPRET_CAST(PFN_vkCmdSetDepthBias                                                   , loader(device, "vkCmdSetDepthBias"                                               )) ;
    functions[0].CmdSetBlendConstants                                              = REINTERPRET_CAST(PFN_vkCmdSetBlendConstants                                              , loader(device, "vkCmdSetBlendConstants"                                          )) ;
    functions[0].CmdSetDepthBounds                                                 = REINTERPRET_CAST(PFN_vkCmdSetDepthBounds                                                 , loader(device, "vkCmdSetDepthBounds"                                             )) ;
    functions[0].CmdSetStencilCompareMask                                          = REINTERPRET_CAST(PFN_vkCmdSetStencilCompareMask                                          , loader(device, "vkCmdSetStencilCompareMask"                                      )) ;
    functions[0].CmdSetStencilWriteMask                                            = REINTERPRET_CAST(PFN_vkCmdSetStencilWriteMask                                            , loader(device, "vkCmdSetStencilWriteMask"                                        )) ;
    functions[0].CmdSetStencilReference                                            = REINTERPRET_CAST(PFN_vkCmdSetStencilReference                                            , loader(device, "vkCmdSetStencilReference"                                        )) ;
    functions[0].CmdBindDescriptorSets                                             = REINTERPRET_CAST(PFN_vkCmdBindDescriptorSets                                             , loader(device, "vkCmdBindDescriptorSets"                                         )) ;
    functions[0].CmdBindIndexBuffer                                                = REINTERPRET_CAST(PFN_vkCmdBindIndexBuffer                                                , loader(device, "vkCmdBindIndexBuffer"                                            )) ;
    functions[0].CmdBindVertexBuffers                                              = REINTERPRET_CAST(PFN_vkCmdBindVertexBuffers                                              , loader(device, "vkCmdBindVertexBuffers"                                          )) ;
    functions[0].CmdDraw                                                           = REINTERPRET_CAST(PFN_vkCmdDraw                                                           , loader(device, "vkCmdDraw"                                                       )) ;
    functions[0].CmdDrawIndexed                                                    = REINTERPRET_CAST(PFN_vkCmdDrawIndexed                                                    , loader(device, "vkCmdDrawIndexed"                                                )) ;
    functions[0].CmdDrawIndirect                                                   = REINTERPRET_CAST(PFN_vkCmdDrawIndirect                                                   , loader(device, "vkCmdDrawIndirect"                                               )) ;
    functions[0].CmdDrawIndexedIndirect                                            = REINTERPRET_CAST(PFN_vkCmdDrawIndexedIndirect                                            , loader(device, "vkCmdDrawIndexedIndirect"                                        )) ;
    functions[0].CmdDispatch                                                       = REINTERPRET_CAST(PFN_vkCmdDispatch                                                       , loader(device, "vkCmdDispatch"                                                   )) ;
    functions[0].CmdDispatchIndirect                                               = REINTERPRET_CAST(PFN_vkCmdDispatchIndirect                                               , loader(device, "vkCmdDispatchIndirect"                                           )) ;
    functions[0].CmdCopyBuffer                                                     = REINTERPRET_CAST(PFN_vkCmdCopyBuffer                                                     , loader(device, "vkCmdCopyBuffer"                                                 )) ;
    functions[0].CmdCopyImage                                                      = REINTERPRET_CAST(PFN_vkCmdCopyImage                                                      , loader(device, "vkCmdCopyImage"                                                  )) ;
    functions[0].CmdBlitImage                                                      = REINTERPRET_CAST(PFN_vkCmdBlitImage                                                      , loader(device, "vkCmdBlitImage"                                                  )) ;
    functions[0].CmdCopyBufferToImage                                              = REINTERPRET_CAST(PFN_vkCmdCopyBufferToImage                                              , loader(device, "vkCmdCopyBufferToImage"                                          )) ;
    functions[0].CmdCopyImageToBuffer                                              = REINTERPRET_CAST(PFN_vkCmdCopyImageToBuffer                                              , loader(device, "vkCmdCopyImageToBuffer"                                          )) ;
    functions[0].CmdUpdateBuffer                                                   = REINTERPRET_CAST(PFN_vkCmdUpdateBuffer                                                   , loader(device, "vkCmdUpdateBuffer"                                               )) ;
    functions[0].CmdFillBuffer                                                     = REINTERPRET_CAST(PFN_vkCmdFillBuffer                                                     , loader(device, "vkCmdFillBuffer"                                                 )) ;
    functions[0].CmdClearColorImage                                                = REINTERPRET_CAST(PFN_vkCmdClearColorImage                                                , loader(device, "vkCmdClearColorImage"                                            )) ;
    functions[0].CmdClearDepthStencilImage                                         = REINTERPRET_CAST(PFN_vkCmdClearDepthStencilImage                                         , loader(device, "vkCmdClearDepthStencilImage"                                     )) ;
    functions[0].CmdClearAttachments                                               = REINTERPRET_CAST(PFN_vkCmdClearAttachments                                               , loader(device, "vkCmdClearAttachments"                                           )) ;
    functions[0].CmdResolveImage                                                   = REINTERPRET_CAST(PFN_vkCmdResolveImage                                                   , loader(device, "vkCmdResolveImage"                                               )) ;
    functions[0].CmdSetEvent                                                       = REINTERPRET_CAST(PFN_vkCmdSetEvent                                                       , loader(device, "vkCmdSetEvent"                                                   )) ;
    functions[0].CmdResetEvent                                                     = REINTERPRET_CAST(PFN_vkCmdResetEvent                                                     , loader(device, "vkCmdResetEvent"                                                 )) ;
    functions[0].CmdWaitEvents                                                     = REINTERPRET_CAST(PFN_vkCmdWaitEvents                                                     , loader(device, "vkCmdWaitEvents"                                                 )) ;
    functions[0].CmdPipelineBarrier                                                = REINTERPRET_CAST(PFN_vkCmdPipelineBarrier                                                , loader(device, "vkCmdPipelineBarrier"                                            )) ;
    functions[0].CmdBeginQuery                                                     = REINTERPRET_CAST(PFN_vkCmdBeginQuery                                                     , loader(device, "vkCmdBeginQuery"                                                 )) ;
    functions[0].CmdEndQuery                                                       = REINTERPRET_CAST(PFN_vkCmdEndQuery                                                       , loader(device, "vkCmdEndQuery"                                                   )) ;
    functions[0].CmdResetQueryPool                                                 = REINTERPRET_CAST(PFN_vkCmdResetQueryPool                                                 , loader(device, "vkCmdResetQueryPool"                                             )) ;
    functions[0].CmdWriteTimestamp                                                 = REINTERPRET_CAST(PFN_vkCmdWriteTimestamp                                                 , loader(device, "vkCmdWriteTimestamp"                                             )) ;
    functions[0].CmdCopyQueryPoolResults                                           = REINTERPRET_CAST(PFN_vkCmdCopyQueryPoolResults                                           , loader(device, "vkCmdCopyQueryPoolResults"                                       )) ;
    functions[0].CmdPushConstants                                                  = REINTERPRET_CAST(PFN_vkCmdPushConstants                                                  , loader(device, "vkCmdPushConstants"                                              )) ;
    functions[0].CmdBeginRenderPass                                                = REINTERPRET_CAST(PFN_vkCmdBeginRenderPass                                                , loader(device, "vkCmdBeginRenderPass"                                            )) ;
    functions[0].CmdNextSubpass                                                    = REINTERPRET_CAST(PFN_vkCmdNextSubpass                                                    , loader(device, "vkCmdNextSubpass"                                                )) ;
    functions[0].CmdEndRenderPass                                                  = REINTERPRET_CAST(PFN_vkCmdEndRenderPass                                                  , loader(device, "vkCmdEndRenderPass"                                              )) ;
    functions[0].CmdExecuteCommands                                                = REINTERPRET_CAST(PFN_vkCmdExecuteCommands                                                , loader(device, "vkCmdExecuteCommands"                                            )) ;
    /* VK_VERSION_1_1 */                                                             
    functions[0].BindBufferMemory2                                                 = REINTERPRET_CAST(PFN_vkBindBufferMemory2                                                 , loader(device, "vkBindBufferMemory2"                                             )) ;
    functions[0].BindImageMemory2                                                  = REINTERPRET_CAST(PFN_vkBindImageMemory2                                                  , loader(device, "vkBindImageMemory2"                                              )) ;
    functions[0].GetDeviceGroupPeerMemoryFeatures                                  = REINTERPRET_CAST(PFN_vkGetDeviceGroupPeerMemoryFeatures                                  , loader(device, "vkGetDeviceGroupPeerMemoryFeatures"                              )) ;
    functions[0].CmdSetDeviceMask                                                  = REINTERPRET_CAST(PFN_vkCmdSetDeviceMask                                                  , loader(device, "vkCmdSetDeviceMask"                                              )) ;
    functions[0].CmdDispatchBase                                                   = REINTERPRET_CAST(PFN_vkCmdDispatchBase                                                   , loader(device, "vkCmdDispatchBase"                                               )) ;
    functions[0].GetImageMemoryRequirements2                                       = REINTERPRET_CAST(PFN_vkGetImageMemoryRequirements2                                       , loader(device, "vkGetImageMemoryRequirements2"                                   )) ;
    functions[0].GetBufferMemoryRequirements2                                      = REINTERPRET_CAST(PFN_vkGetBufferMemoryRequirements2                                      , loader(device, "vkGetBufferMemoryRequirements2"                                  )) ;
    functions[0].GetImageSparseMemoryRequirements2                                 = REINTERPRET_CAST(PFN_vkGetImageSparseMemoryRequirements2                                 , loader(device, "vkGetImageSparseMemoryRequirements2"                             )) ;
    functions[0].TrimCommandPool                                                   = REINTERPRET_CAST(PFN_vkTrimCommandPool                                                   , loader(device, "vkTrimCommandPool"                                               )) ;
    functions[0].GetDeviceQueue2                                                   = REINTERPRET_CAST(PFN_vkGetDeviceQueue2                                                   , loader(device, "vkGetDeviceQueue2"                                               )) ;
    functions[0].CreateSamplerYcbcrConversion                                      = REINTERPRET_CAST(PFN_vkCreateSamplerYcbcrConversion                                      , loader(device, "vkCreateSamplerYcbcrConversion"                                  )) ;
    functions[0].DestroySamplerYcbcrConversion                                     = REINTERPRET_CAST(PFN_vkDestroySamplerYcbcrConversion                                     , loader(device, "vkDestroySamplerYcbcrConversion"                                 )) ;
    functions[0].CreateDescriptorUpdateTemplate                                    = REINTERPRET_CAST(PFN_vkCreateDescriptorUpdateTemplate                                    , loader(device, "vkCreateDescriptorUpdateTemplate"                                )) ;
    functions[0].DestroyDescriptorUpdateTemplate                                   = REINTERPRET_CAST(PFN_vkDestroyDescriptorUpdateTemplate                                   , loader(device, "vkDestroyDescriptorUpdateTemplate"                               )) ;
    functions[0].UpdateDescriptorSetWithTemplate                                   = REINTERPRET_CAST(PFN_vkUpdateDescriptorSetWithTemplate                                   , loader(device, "vkUpdateDescriptorSetWithTemplate"                               )) ;
    functions[0].GetDescriptorSetLayoutSupport                                     = REINTERPRET_CAST(PFN_vkGetDescriptorSetLayoutSupport                                     , loader(device, "vkGetDescriptorSetLayoutSupport"                                 )) ;
    /* VK_VERSION_1_2 */                                                             
    functions[0].CmdDrawIndirectCount                                              = REINTERPRET_CAST(PFN_vkCmdDrawIndirectCount                                              , loader(device, "vkCmdDrawIndirectCount"                                          )) ;
    functions[0].CmdDrawIndexedIndirectCount                                       = REINTERPRET_CAST(PFN_vkCmdDrawIndexedIndirectCount                                       , loader(device, "vkCmdDrawIndexedIndirectCount"                                   )) ;
    functions[0].CreateRenderPass2                                                 = REINTERPRET_CAST(PFN_vkCreateRenderPass2                                                 , loader(device, "vkCreateRenderPass2"                                             )) ;
    functions[0].CmdBeginRenderPass2                                               = REINTERPRET_CAST(PFN_vkCmdBeginRenderPass2                                               , loader(device, "vkCmdBeginRenderPass2"                                           )) ;
    functions[0].CmdNextSubpass2                                                   = REINTERPRET_CAST(PFN_vkCmdNextSubpass2                                                   , loader(device, "vkCmdNextSubpass2"                                               )) ;
    functions[0].CmdEndRenderPass2                                                 = REINTERPRET_CAST(PFN_vkCmdEndRenderPass2                                                 , loader(device, "vkCmdEndRenderPass2"                                             )) ;
    functions[0].ResetQueryPool                                                    = REINTERPRET_CAST(PFN_vkResetQueryPool                                                    , loader(device, "vkResetQueryPool"                                                )) ;
    functions[0].GetSemaphoreCounterValue                                          = REINTERPRET_CAST(PFN_vkGetSemaphoreCounterValue                                          , loader(device, "vkGetSemaphoreCounterValue"                                      )) ;
    functions[0].WaitSemaphores                                                    = REINTERPRET_CAST(PFN_vkWaitSemaphores                                                    , loader(device, "vkWaitSemaphores"                                                )) ;
    functions[0].SignalSemaphore                                                   = REINTERPRET_CAST(PFN_vkSignalSemaphore                                                   , loader(device, "vkSignalSemaphore"                                               )) ;
    functions[0].GetBufferDeviceAddress                                            = REINTERPRET_CAST(PFN_vkGetBufferDeviceAddress                                            , loader(device, "vkGetBufferDeviceAddress"                                        )) ;
    functions[0].GetBufferOpaqueCaptureAddress                                     = REINTERPRET_CAST(PFN_vkGetBufferOpaqueCaptureAddress                                     , loader(device, "vkGetBufferOpaqueCaptureAddress"                                 )) ;
    functions[0].GetDeviceMemoryOpaqueCaptureAddress                               = REINTERPRET_CAST(PFN_vkGetDeviceMemoryOpaqueCaptureAddress                               , loader(device, "vkGetDeviceMemoryOpaqueCaptureAddress"                           )) ;
    /* VK_VERSION_1_3 */                                                             
    functions[0].CreatePrivateDataSlot                                             = REINTERPRET_CAST(PFN_vkCreatePrivateDataSlot                                             , loader(device, "vkCreatePrivateDataSlot"                                         )) ;
    functions[0].DestroyPrivateDataSlot                                            = REINTERPRET_CAST(PFN_vkDestroyPrivateDataSlot                                            , loader(device, "vkDestroyPrivateDataSlot"                                        )) ;
    functions[0].SetPrivateData                                                    = REINTERPRET_CAST(PFN_vkSetPrivateData                                                    , loader(device, "vkSetPrivateData"                                                )) ;
    functions[0].GetPrivateData                                                    = REINTERPRET_CAST(PFN_vkGetPrivateData                                                    , loader(device, "vkGetPrivateData"                                                )) ;
    functions[0].CmdSetEvent2                                                      = REINTERPRET_CAST(PFN_vkCmdSetEvent2                                                      , loader(device, "vkCmdSetEvent2"                                                  )) ;
    functions[0].CmdResetEvent2                                                    = REINTERPRET_CAST(PFN_vkCmdResetEvent2                                                    , loader(device, "vkCmdResetEvent2"                                                )) ;
    functions[0].CmdWaitEvents2                                                    = REINTERPRET_CAST(PFN_vkCmdWaitEvents2                                                    , loader(device, "vkCmdWaitEvents2"                                                )) ;
    functions[0].CmdPipelineBarrier2                                               = REINTERPRET_CAST(PFN_vkCmdPipelineBarrier2                                               , loader(device, "vkCmdPipelineBarrier2"                                           )) ;
    functions[0].CmdWriteTimestamp2                                                = REINTERPRET_CAST(PFN_vkCmdWriteTimestamp2                                                , loader(device, "vkCmdWriteTimestamp2"                                            )) ;
    functions[0].QueueSubmit2                                                      = REINTERPRET_CAST(PFN_vkQueueSubmit2                                                      , loader(device, "vkQueueSubmit2"                                                  )) ;
    functions[0].CmdCopyBuffer2                                                    = REINTERPRET_CAST(PFN_vkCmdCopyBuffer2                                                    , loader(device, "vkCmdCopyBuffer2"                                                )) ;
    functions[0].CmdCopyImage2                                                     = REINTERPRET_CAST(PFN_vkCmdCopyImage2                                                     , loader(device, "vkCmdCopyImage2"                                                 )) ;
    functions[0].CmdCopyBufferToImage2                                             = REINTERPRET_CAST(PFN_vkCmdCopyBufferToImage2                                             , loader(device, "vkCmdCopyBufferToImage2"                                         )) ;
    functions[0].CmdCopyImageToBuffer2                                             = REINTERPRET_CAST(PFN_vkCmdCopyImageToBuffer2                                             , loader(device, "vkCmdCopyImageToBuffer2"                                         )) ;
    functions[0].CmdBlitImage2                                                     = REINTERPRET_CAST(PFN_vkCmdBlitImage2                                                     , loader(device, "vkCmdBlitImage2"                                                 )) ;
    functions[0].CmdResolveImage2                                                  = REINTERPRET_CAST(PFN_vkCmdResolveImage2                                                  , loader(device, "vkCmdResolveImage2"                                              )) ;
    functions[0].CmdBeginRendering                                                 = REINTERPRET_CAST(PFN_vkCmdBeginRendering                                                 , loader(device, "vkCmdBeginRendering"                                             )) ;
    functions[0].CmdEndRendering                                                   = REINTERPRET_CAST(PFN_vkCmdEndRendering                                                   , loader(device, "vkCmdEndRendering"                                               )) ;
    functions[0].CmdSetCullMode                                                    = REINTERPRET_CAST(PFN_vkCmdSetCullMode                                                    , loader(device, "vkCmdSetCullMode"                                                )) ;
    functions[0].CmdSetFrontFace                                                   = REINTERPRET_CAST(PFN_vkCmdSetFrontFace                                                   , loader(device, "vkCmdSetFrontFace"                                               )) ;
    functions[0].CmdSetPrimitiveTopology                                           = REINTERPRET_CAST(PFN_vkCmdSetPrimitiveTopology                                           , loader(device, "vkCmdSetPrimitiveTopology"                                       )) ;
    functions[0].CmdSetViewportWithCount                                           = REINTERPRET_CAST(PFN_vkCmdSetViewportWithCount                                           , loader(device, "vkCmdSetViewportWithCount"                                       )) ;
    functions[0].CmdSetScissorWithCount                                            = REINTERPRET_CAST(PFN_vkCmdSetScissorWithCount                                            , loader(device, "vkCmdSetScissorWithCount"                                        )) ;
    functions[0].CmdBindVertexBuffers2                                             = REINTERPRET_CAST(PFN_vkCmdBindVertexBuffers2                                             , loader(device, "vkCmdBindVertexBuffers2"                                         )) ;
    functions[0].CmdSetDepthTestEnable                                             = REINTERPRET_CAST(PFN_vkCmdSetDepthTestEnable                                             , loader(device, "vkCmdSetDepthTestEnable"                                         )) ;
    functions[0].CmdSetDepthWriteEnable                                            = REINTERPRET_CAST(PFN_vkCmdSetDepthWriteEnable                                            , loader(device, "vkCmdSetDepthWriteEnable"                                        )) ;
    functions[0].CmdSetDepthCompareOp                                              = REINTERPRET_CAST(PFN_vkCmdSetDepthCompareOp                                              , loader(device, "vkCmdSetDepthCompareOp"                                          )) ;
    functions[0].CmdSetDepthBoundsTestEnable                                       = REINTERPRET_CAST(PFN_vkCmdSetDepthBoundsTestEnable                                       , loader(device, "vkCmdSetDepthBoundsTestEnable"                                   )) ;
    functions[0].CmdSetStencilTestEnable                                           = REINTERPRET_CAST(PFN_vkCmdSetStencilTestEnable                                           , loader(device, "vkCmdSetStencilTestEnable"                                       )) ;
    functions[0].CmdSetStencilOp                                                   = REINTERPRET_CAST(PFN_vkCmdSetStencilOp                                                   , loader(device, "vkCmdSetStencilOp"                                               )) ;
    functions[0].CmdSetRasterizerDiscardEnable                                     = REINTERPRET_CAST(PFN_vkCmdSetRasterizerDiscardEnable                                     , loader(device, "vkCmdSetRasterizerDiscardEnable"                                 )) ;
    functions[0].CmdSetDepthBiasEnable                                             = REINTERPRET_CAST(PFN_vkCmdSetDepthBiasEnable                                             , loader(device, "vkCmdSetDepthBiasEnable"                                         )) ;
    functions[0].CmdSetPrimitiveRestartEnable                                      = REINTERPRET_CAST(PFN_vkCmdSetPrimitiveRestartEnable                                      , loader(device, "vkCmdSetPrimitiveRestartEnable"                                  )) ;
    functions[0].GetDeviceBufferMemoryRequirements                                 = REINTERPRET_CAST(PFN_vkGetDeviceBufferMemoryRequirements                                 , loader(device, "vkGetDeviceBufferMemoryRequirements"                             )) ;
    functions[0].GetDeviceImageMemoryRequirements                                  = REINTERPRET_CAST(PFN_vkGetDeviceImageMemoryRequirements                                  , loader(device, "vkGetDeviceImageMemoryRequirements"                              )) ;
    functions[0].GetDeviceImageSparseMemoryRequirements                            = REINTERPRET_CAST(PFN_vkGetDeviceImageSparseMemoryRequirements                            , loader(device, "vkGetDeviceImageSparseMemoryRequirements"                        )) ;
    /* VK_KHR_swapchain spec_version 70  */                                          
    functions[0].CreateSwapchainKHR                                                = REINTERPRET_CAST(PFN_vkCreateSwapchainKHR                                                , loader(device, "vkCreateSwapchainKHR"                                            )) ;
    functions[0].DestroySwapchainKHR                                               = REINTERPRET_CAST(PFN_vkDestroySwapchainKHR                                               , loader(device, "vkDestroySwapchainKHR"                                           )) ;
    functions[0].GetSwapchainImagesKHR                                             = REINTERPRET_CAST(PFN_vkGetSwapchainImagesKHR                                             , loader(device, "vkGetSwapchainImagesKHR"                                         )) ;
    functions[0].AcquireNextImageKHR                                               = REINTERPRET_CAST(PFN_vkAcquireNextImageKHR                                               , loader(device, "vkAcquireNextImageKHR"                                           )) ;
    functions[0].QueuePresentKHR                                                   = REINTERPRET_CAST(PFN_vkQueuePresentKHR                                                   , loader(device, "vkQueuePresentKHR"                                               )) ;
    functions[0].GetDeviceGroupPresentCapabilitiesKHR                              = REINTERPRET_CAST(PFN_vkGetDeviceGroupPresentCapabilitiesKHR                              , loader(device, "vkGetDeviceGroupPresentCapabilitiesKHR"                          )) ;
    functions[0].GetDeviceGroupSurfacePresentModesKHR                              = REINTERPRET_CAST(PFN_vkGetDeviceGroupSurfacePresentModesKHR                              , loader(device, "vkGetDeviceGroupSurfacePresentModesKHR"                          )) ;
    functions[0].AcquireNextImage2KHR                                              = REINTERPRET_CAST(PFN_vkAcquireNextImage2KHR                                              , loader(device, "vkAcquireNextImage2KHR"                                          )) ;
    /* VK_KHR_display_swapchain spec_version 10  */                                  
    functions[0].CreateSharedSwapchainsKHR                                         = REINTERPRET_CAST(PFN_vkCreateSharedSwapchainsKHR                                         , loader(device, "vkCreateSharedSwapchainsKHR"                                     )) ;
    /* VK_KHR_video_queue spec_version 8 */                                          
    functions[0].CreateVideoSessionKHR                                             = REINTERPRET_CAST(PFN_vkCreateVideoSessionKHR                                             , loader(device, "vkCreateVideoSessionKHR"                                         )) ;
    functions[0].DestroyVideoSessionKHR                                            = REINTERPRET_CAST(PFN_vkDestroyVideoSessionKHR                                            , loader(device, "vkDestroyVideoSessionKHR"                                        )) ;
    functions[0].GetVideoSessionMemoryRequirementsKHR                              = REINTERPRET_CAST(PFN_vkGetVideoSessionMemoryRequirementsKHR                              , loader(device, "vkGetVideoSessionMemoryRequirementsKHR"                          )) ;
    functions[0].BindVideoSessionMemoryKHR                                         = REINTERPRET_CAST(PFN_vkBindVideoSessionMemoryKHR                                         , loader(device, "vkBindVideoSessionMemoryKHR"                                     )) ;
    functions[0].CreateVideoSessionParametersKHR                                   = REINTERPRET_CAST(PFN_vkCreateVideoSessionParametersKHR                                   , loader(device, "vkCreateVideoSessionParametersKHR"                               )) ;
    functions[0].UpdateVideoSessionParametersKHR                                   = REINTERPRET_CAST(PFN_vkUpdateVideoSessionParametersKHR                                   , loader(device, "vkUpdateVideoSessionParametersKHR"                               )) ;
    functions[0].DestroyVideoSessionParametersKHR                                  = REINTERPRET_CAST(PFN_vkDestroyVideoSessionParametersKHR                                  , loader(device, "vkDestroyVideoSessionParametersKHR"                              )) ;
    functions[0].CmdBeginVideoCodingKHR                                            = REINTERPRET_CAST(PFN_vkCmdBeginVideoCodingKHR                                            , loader(device, "vkCmdBeginVideoCodingKHR"                                        )) ;
    functions[0].CmdEndVideoCodingKHR                                              = REINTERPRET_CAST(PFN_vkCmdEndVideoCodingKHR                                              , loader(device, "vkCmdEndVideoCodingKHR"                                          )) ;
    functions[0].CmdControlVideoCodingKHR                                          = REINTERPRET_CAST(PFN_vkCmdControlVideoCodingKHR                                          , loader(device, "vkCmdControlVideoCodingKHR"                                      )) ;
    /* VK_KHR_video_decode_queue spec_version 8 */                                   
    functions[0].CmdDecodeVideoKHR                                                 = REINTERPRET_CAST(PFN_vkCmdDecodeVideoKHR                                                 , loader(device, "vkCmdDecodeVideoKHR"                                             )) ;
    /* VK_KHR_dynamic_rendering spec_version 1 */                                    
    functions[0].CmdBeginRenderingKHR                                              = REINTERPRET_CAST(PFN_vkCmdBeginRenderingKHR                                              , loader(device, "vkCmdBeginRenderingKHR"                                          )) ;
    functions[0].CmdEndRenderingKHR                                                = REINTERPRET_CAST(PFN_vkCmdEndRenderingKHR                                                , loader(device, "vkCmdEndRenderingKHR"                                            )) ;
    /* VK_KHR_device_group spec_version 4 */                                         
    functions[0].GetDeviceGroupPeerMemoryFeaturesKHR                               = REINTERPRET_CAST(PFN_vkGetDeviceGroupPeerMemoryFeaturesKHR                               , loader(device, "vkGetDeviceGroupPeerMemoryFeaturesKHR"                           )) ;
    functions[0].CmdSetDeviceMaskKHR                                               = REINTERPRET_CAST(PFN_vkCmdSetDeviceMaskKHR                                               , loader(device, "vkCmdSetDeviceMaskKHR"                                           )) ;
    functions[0].CmdDispatchBaseKHR                                                = REINTERPRET_CAST(PFN_vkCmdDispatchBaseKHR                                                , loader(device, "vkCmdDispatchBaseKHR"                                            )) ;
    /* VK_KHR_maintenance1 spec_version 2 */                                         
    functions[0].TrimCommandPoolKHR                                                = REINTERPRET_CAST(PFN_vkTrimCommandPoolKHR                                                , loader(device, "vkTrimCommandPoolKHR"                                            )) ;
    /* VK_KHR_external_memory_fd spec_version 1 */                                   
    functions[0].GetMemoryFdKHR                                                    = REINTERPRET_CAST(PFN_vkGetMemoryFdKHR                                                    , loader(device, "vkGetMemoryFdKHR"                                                )) ;
    functions[0].GetMemoryFdPropertiesKHR                                          = REINTERPRET_CAST(PFN_vkGetMemoryFdPropertiesKHR                                          , loader(device, "vkGetMemoryFdPropertiesKHR"                                      )) ;
    /* VK_KHR_external_semaphore_fd spec_version 1 */                                
    functions[0].ImportSemaphoreFdKHR                                              = REINTERPRET_CAST(PFN_vkImportSemaphoreFdKHR                                              , loader(device, "vkImportSemaphoreFdKHR"                                          )) ;
    functions[0].GetSemaphoreFdKHR                                                 = REINTERPRET_CAST(PFN_vkGetSemaphoreFdKHR                                                 , loader(device, "vkGetSemaphoreFdKHR"                                             )) ;
    /* VK_KHR_push_descriptor spec_version 2 */                                      
    functions[0].CmdPushDescriptorSetKHR                                           = REINTERPRET_CAST(PFN_vkCmdPushDescriptorSetKHR                                           , loader(device, "vkCmdPushDescriptorSetKHR"                                       )) ;
    functions[0].CmdPushDescriptorSetWithTemplateKHR                               = REINTERPRET_CAST(PFN_vkCmdPushDescriptorSetWithTemplateKHR                               , loader(device, "vkCmdPushDescriptorSetWithTemplateKHR"                           )) ;
    /* VK_KHR_descriptor_update_template spec_version 1 */                           
    functions[0].CreateDescriptorUpdateTemplateKHR                                 = REINTERPRET_CAST(PFN_vkCreateDescriptorUpdateTemplateKHR                                 , loader(device, "vkCreateDescriptorUpdateTemplateKHR"                             )) ;
    functions[0].DestroyDescriptorUpdateTemplateKHR                                = REINTERPRET_CAST(PFN_vkDestroyDescriptorUpdateTemplateKHR                                , loader(device, "vkDestroyDescriptorUpdateTemplateKHR"                            )) ;
    functions[0].UpdateDescriptorSetWithTemplateKHR                                = REINTERPRET_CAST(PFN_vkUpdateDescriptorSetWithTemplateKHR                                , loader(device, "vkUpdateDescriptorSetWithTemplateKHR"                            )) ;
    /* VK_KHR_create_renderpass2 spec_version 1 */                                   
    functions[0].CreateRenderPass2KHR                                              = REINTERPRET_CAST(PFN_vkCreateRenderPass2KHR                                              , loader(device, "vkCreateRenderPass2KHR"                                          )) ;
    functions[0].CmdBeginRenderPass2KHR                                            = REINTERPRET_CAST(PFN_vkCmdBeginRenderPass2KHR                                            , loader(device, "vkCmdBeginRenderPass2KHR"                                        )) ;
    functions[0].CmdNextSubpass2KHR                                                = REINTERPRET_CAST(PFN_vkCmdNextSubpass2KHR                                                , loader(device, "vkCmdNextSubpass2KHR"                                            )) ;
    functions[0].CmdEndRenderPass2KHR                                              = REINTERPRET_CAST(PFN_vkCmdEndRenderPass2KHR                                              , loader(device, "vkCmdEndRenderPass2KHR"                                          )) ;
    /* VK_KHR_shared_presentable_image spec_version 1 */                             
    functions[0].GetSwapchainStatusKHR                                             = REINTERPRET_CAST(PFN_vkGetSwapchainStatusKHR                                             , loader(device, "vkGetSwapchainStatusKHR"                                         )) ;
    /* VK_KHR_external_fence_fd spec_version 1 */                                    
    functions[0].ImportFenceFdKHR                                                  = REINTERPRET_CAST(PFN_vkImportFenceFdKHR                                                  , loader(device, "vkImportFenceFdKHR"                                              )) ;
    functions[0].GetFenceFdKHR                                                     = REINTERPRET_CAST(PFN_vkGetFenceFdKHR                                                     , loader(device, "vkGetFenceFdKHR"                                                 )) ;
    /* VK_KHR_performance_query spec_version 1 */                                    
    functions[0].AcquireProfilingLockKHR                                           = REINTERPRET_CAST(PFN_vkAcquireProfilingLockKHR                                           , loader(device, "vkAcquireProfilingLockKHR"                                       )) ;
    functions[0].ReleaseProfilingLockKHR                                           = REINTERPRET_CAST(PFN_vkReleaseProfilingLockKHR                                           , loader(device, "vkReleaseProfilingLockKHR"                                       )) ;
    /* VK_KHR_get_memory_requirements2 spec_version 1 */                             
    functions[0].GetImageMemoryRequirements2KHR                                    = REINTERPRET_CAST(PFN_vkGetImageMemoryRequirements2KHR                                    , loader(device, "vkGetImageMemoryRequirements2KHR"                                )) ;
    functions[0].GetBufferMemoryRequirements2KHR                                   = REINTERPRET_CAST(PFN_vkGetBufferMemoryRequirements2KHR                                   , loader(device, "vkGetBufferMemoryRequirements2KHR"                               )) ;
    functions[0].GetImageSparseMemoryRequirements2KHR                              = REINTERPRET_CAST(PFN_vkGetImageSparseMemoryRequirements2KHR                              , loader(device, "vkGetImageSparseMemoryRequirements2KHR"                          )) ;
    /* VK_KHR_sampler_ycbcr_conversion spec_version 14 */                            
    functions[0].CreateSamplerYcbcrConversionKHR                                   = REINTERPRET_CAST(PFN_vkCreateSamplerYcbcrConversionKHR                                   , loader(device, "vkCreateSamplerYcbcrConversionKHR"                               )) ;
    functions[0].DestroySamplerYcbcrConversionKHR                                  = REINTERPRET_CAST(PFN_vkDestroySamplerYcbcrConversionKHR                                  , loader(device, "vkDestroySamplerYcbcrConversionKHR"                              )) ;
    /* VK_KHR_bind_memory2 spec_version 1 */                                         
    functions[0].BindBufferMemory2KHR                                              = REINTERPRET_CAST(PFN_vkBindBufferMemory2KHR                                              , loader(device, "vkBindBufferMemory2KHR"                                          )) ;
    functions[0].BindImageMemory2KHR                                               = REINTERPRET_CAST(PFN_vkBindImageMemory2KHR                                               , loader(device, "vkBindImageMemory2KHR"                                           )) ;
    /* VK_KHR_maintenance3 spec_version 1 */                                         
    functions[0].GetDescriptorSetLayoutSupportKHR                                  = REINTERPRET_CAST(PFN_vkGetDescriptorSetLayoutSupportKHR                                  , loader(device, "vkGetDescriptorSetLayoutSupportKHR"                              )) ;
    /* VK_KHR_draw_indirect_count spec_version 1 */                                  
    functions[0].CmdDrawIndirectCountKHR                                           = REINTERPRET_CAST(PFN_vkCmdDrawIndirectCountKHR                                           , loader(device, "vkCmdDrawIndirectCountKHR"                                       )) ;
    functions[0].CmdDrawIndexedIndirectCountKHR                                    = REINTERPRET_CAST(PFN_vkCmdDrawIndexedIndirectCountKHR                                    , loader(device, "vkCmdDrawIndexedIndirectCountKHR"                                )) ;
    /* VK_KHR_timeline_semaphore spec_version 2 */                                   
    functions[0].GetSemaphoreCounterValueKHR                                       = REINTERPRET_CAST(PFN_vkGetSemaphoreCounterValueKHR                                       , loader(device, "vkGetSemaphoreCounterValueKHR"                                   )) ;
    functions[0].WaitSemaphoresKHR                                                 = REINTERPRET_CAST(PFN_vkWaitSemaphoresKHR                                                 , loader(device, "vkWaitSemaphoresKHR"                                             )) ;
    functions[0].SignalSemaphoreKHR                                                = REINTERPRET_CAST(PFN_vkSignalSemaphoreKHR                                                , loader(device, "vkSignalSemaphoreKHR"                                            )) ;
    /* VK_KHR_fragment_shading_rate spec_version 2 */                                
    functions[0].CmdSetFragmentShadingRateKHR                                      = REINTERPRET_CAST(PFN_vkCmdSetFragmentShadingRateKHR                                      , loader(device, "vkCmdSetFragmentShadingRateKHR"                                  )) ;
    /* VK_KHR_dynamic_rendering_local_read spec_version 1 */                         
    functions[0].CmdSetRenderingAttachmentLocationsKHR                             = REINTERPRET_CAST(PFN_vkCmdSetRenderingAttachmentLocationsKHR                             , loader(device, "vkCmdSetRenderingAttachmentLocationsKHR"                         )) ;
    functions[0].CmdSetRenderingInputAttachmentIndicesKHR                          = REINTERPRET_CAST(PFN_vkCmdSetRenderingInputAttachmentIndicesKHR                          , loader(device, "vkCmdSetRenderingInputAttachmentIndicesKHR"                      )) ;
    /* VK_KHR_present_wait spec_version 1 */                                         
    functions[0].WaitForPresentKHR                                                 = REINTERPRET_CAST(PFN_vkWaitForPresentKHR                                                 , loader(device, "vkWaitForPresentKHR"                                             )) ;
    /* VK_KHR_buffer_device_address spec_version 1 */                                
    functions[0].GetBufferDeviceAddressKHR                                         = REINTERPRET_CAST(PFN_vkGetBufferDeviceAddressKHR                                         , loader(device, "vkGetBufferDeviceAddressKHR"                                     )) ;
    functions[0].GetBufferOpaqueCaptureAddressKHR                                  = REINTERPRET_CAST(PFN_vkGetBufferOpaqueCaptureAddressKHR                                  , loader(device, "vkGetBufferOpaqueCaptureAddressKHR"                              )) ;
    functions[0].GetDeviceMemoryOpaqueCaptureAddressKHR                            = REINTERPRET_CAST(PFN_vkGetDeviceMemoryOpaqueCaptureAddressKHR                            , loader(device, "vkGetDeviceMemoryOpaqueCaptureAddressKHR"                        )) ;
    /* VK_KHR_deferred_host_operations spec_version 4 */                             
    functions[0].CreateDeferredOperationKHR                                        = REINTERPRET_CAST(PFN_vkCreateDeferredOperationKHR                                        , loader(device, "vkCreateDeferredOperationKHR"                                    )) ;
    functions[0].DestroyDeferredOperationKHR                                       = REINTERPRET_CAST(PFN_vkDestroyDeferredOperationKHR                                       , loader(device, "vkDestroyDeferredOperationKHR"                                   )) ;
    functions[0].GetDeferredOperationMaxConcurrencyKHR                             = REINTERPRET_CAST(PFN_vkGetDeferredOperationMaxConcurrencyKHR                             , loader(device, "vkGetDeferredOperationMaxConcurrencyKHR"                         )) ;
    functions[0].GetDeferredOperationResultKHR                                     = REINTERPRET_CAST(PFN_vkGetDeferredOperationResultKHR                                     , loader(device, "vkGetDeferredOperationResultKHR"                                 )) ;
    functions[0].DeferredOperationJoinKHR                                          = REINTERPRET_CAST(PFN_vkDeferredOperationJoinKHR                                          , loader(device, "vkDeferredOperationJoinKHR"                                      )) ;
    /* VK_KHR_pipeline_executable_properties spec_version 1 */                       
    functions[0].GetPipelineExecutablePropertiesKHR                                = REINTERPRET_CAST(PFN_vkGetPipelineExecutablePropertiesKHR                                , loader(device, "vkGetPipelineExecutablePropertiesKHR"                            )) ;
    functions[0].GetPipelineExecutableStatisticsKHR                                = REINTERPRET_CAST(PFN_vkGetPipelineExecutableStatisticsKHR                                , loader(device, "vkGetPipelineExecutableStatisticsKHR"                            )) ;
    functions[0].GetPipelineExecutableInternalRepresentationsKHR                   = REINTERPRET_CAST(PFN_vkGetPipelineExecutableInternalRepresentationsKHR                   , loader(device, "vkGetPipelineExecutableInternalRepresentationsKHR"               )) ;
    /* VK_KHR_map_memory2 spec_version 1 */                                          
    functions[0].MapMemory2KHR                                                     = REINTERPRET_CAST(PFN_vkMapMemory2KHR                                                     , loader(device, "vkMapMemory2KHR"                                                 )) ;
    functions[0].UnmapMemory2KHR                                                   = REINTERPRET_CAST(PFN_vkUnmapMemory2KHR                                                   , loader(device, "vkUnmapMemory2KHR"                                               )) ;
    /* VK_KHR_video_encode_queue spec_version 12 */                                  
    functions[0].GetEncodedVideoSessionParametersKHR                               = REINTERPRET_CAST(PFN_vkGetEncodedVideoSessionParametersKHR                               , loader(device, "vkGetEncodedVideoSessionParametersKHR"                           )) ;
    functions[0].CmdEncodeVideoKHR                                                 = REINTERPRET_CAST(PFN_vkCmdEncodeVideoKHR                                                 , loader(device, "vkCmdEncodeVideoKHR"                                             )) ;
    /* VK_KHR_synchronization2 spec_version 1 */
    functions[0].CmdSetEvent2KHR                                                   = REINTERPRET_CAST(PFN_vkCmdSetEvent2KHR                                                   , loader(device, "vkCmdSetEvent2KHR"                                               )) ;
    functions[0].CmdResetEvent2KHR                                                 = REINTERPRET_CAST(PFN_vkCmdResetEvent2KHR                                                 , loader(device, "vkCmdResetEvent2KHR"                                             )) ;
    functions[0].CmdWaitEvents2KHR                                                 = REINTERPRET_CAST(PFN_vkCmdWaitEvents2KHR                                                 , loader(device, "vkCmdWaitEvents2KHR"                                             )) ;
    functions[0].CmdPipelineBarrier2KHR                                            = REINTERPRET_CAST(PFN_vkCmdPipelineBarrier2KHR                                            , loader(device, "vkCmdPipelineBarrier2KHR"                                        )) ;
    functions[0].CmdWriteTimestamp2KHR                                             = REINTERPRET_CAST(PFN_vkCmdWriteTimestamp2KHR                                             , loader(device, "vkCmdWriteTimestamp2KHR"                                         )) ;
    functions[0].QueueSubmit2KHR                                                   = REINTERPRET_CAST(PFN_vkQueueSubmit2KHR                                                   , loader(device, "vkQueueSubmit2KHR"                                               )) ;
    functions[0].CmdWriteBufferMarker2AMD                                          = REINTERPRET_CAST(PFN_vkCmdWriteBufferMarker2AMD                                          , loader(device, "vkCmdWriteBufferMarker2AMD"                                      )) ;
    functions[0].GetQueueCheckpointData2NV                                         = REINTERPRET_CAST(PFN_vkGetQueueCheckpointData2NV                                         , loader(device, "vkGetQueueCheckpointData2NV"                                     )) ;
                /* NOTE: The function vkCmdWriteBufferMarker2AMD was moved into VK_AMD_buffer_marker and vkGetQueueCheckpointData2NV into VK_NV_device_diagnostic_checkpoints from 1.3.284 to 1.4.309;
                   they are kept here in their old position for the sake of preserving the memory layout of the old portion of the structs */
    /* VK_KHR_copy_commands2 spec_version 1 */                                       
    functions[0].CmdCopyBuffer2KHR                                                 = REINTERPRET_CAST(PFN_vkCmdCopyBuffer2KHR                                                 , loader(device, "vkCmdCopyBuffer2KHR"                                             )) ;
    functions[0].CmdCopyImage2KHR                                                  = REINTERPRET_CAST(PFN_vkCmdCopyImage2KHR                                                  , loader(device, "vkCmdCopyImage2KHR"                                              )) ;
    functions[0].CmdCopyBufferToImage2KHR                                          = REINTERPRET_CAST(PFN_vkCmdCopyBufferToImage2KHR                                          , loader(device, "vkCmdCopyBufferToImage2KHR"                                      )) ;
    functions[0].CmdCopyImageToBuffer2KHR                                          = REINTERPRET_CAST(PFN_vkCmdCopyImageToBuffer2KHR                                          , loader(device, "vkCmdCopyImageToBuffer2KHR"                                      )) ;
    functions[0].CmdBlitImage2KHR                                                  = REINTERPRET_CAST(PFN_vkCmdBlitImage2KHR                                                  , loader(device, "vkCmdBlitImage2KHR"                                              )) ;
    functions[0].CmdResolveImage2KHR                                               = REINTERPRET_CAST(PFN_vkCmdResolveImage2KHR                                               , loader(device, "vkCmdResolveImage2KHR"                                           )) ;
    /* VK_KHR_ray_tracing_maintenance1 spec_version 1 */                             
    functions[0].CmdTraceRaysIndirect2KHR                                          = REINTERPRET_CAST(PFN_vkCmdTraceRaysIndirect2KHR                                          , loader(device, "vkCmdTraceRaysIndirect2KHR"                                      )) ;
    /* VK_KHR_maintenance4 spec_version 2 */                                         
    functions[0].GetDeviceBufferMemoryRequirementsKHR                              = REINTERPRET_CAST(PFN_vkGetDeviceBufferMemoryRequirementsKHR                              , loader(device, "vkGetDeviceBufferMemoryRequirementsKHR"                          )) ;
    functions[0].GetDeviceImageMemoryRequirementsKHR                               = REINTERPRET_CAST(PFN_vkGetDeviceImageMemoryRequirementsKHR                               , loader(device, "vkGetDeviceImageMemoryRequirementsKHR"                           )) ;
    functions[0].GetDeviceImageSparseMemoryRequirementsKHR                         = REINTERPRET_CAST(PFN_vkGetDeviceImageSparseMemoryRequirementsKHR                         , loader(device, "vkGetDeviceImageSparseMemoryRequirementsKHR"                     )) ;
    /* VK_KHR_maintenance5 spec_version 1 */                                         
    functions[0].CmdBindIndexBuffer2KHR                                            = REINTERPRET_CAST(PFN_vkCmdBindIndexBuffer2KHR                                            , loader(device, "vkCmdBindIndexBuffer2KHR"                                        )) ;
    functions[0].GetRenderingAreaGranularityKHR                                    = REINTERPRET_CAST(PFN_vkGetRenderingAreaGranularityKHR                                    , loader(device, "vkGetRenderingAreaGranularityKHR"                                )) ;
    functions[0].GetDeviceImageSubresourceLayoutKHR                                = REINTERPRET_CAST(PFN_vkGetDeviceImageSubresourceLayoutKHR                                , loader(device, "vkGetDeviceImageSubresourceLayoutKHR"                            )) ;
    functions[0].GetImageSubresourceLayout2KHR                                     = REINTERPRET_CAST(PFN_vkGetImageSubresourceLayout2KHR                                     , loader(device, "vkGetImageSubresourceLayout2KHR"                                 )) ;
    /* VK_KHR_line_rasterization spec_version 1 */                                   
    functions[0].CmdSetLineStippleKHR                                              = REINTERPRET_CAST(PFN_vkCmdSetLineStippleKHR                                              , loader(device, "vkCmdSetLineStippleKHR"                                          )) ;
    /* VK_KHR_calibrated_timestamps spec_version 1 */                                
    functions[0].GetCalibratedTimestampsKHR                                        = REINTERPRET_CAST(PFN_vkGetCalibratedTimestampsKHR                                        , loader(device, "vkGetCalibratedTimestampsKHR"                                    )) ;
    /* VK_KHR_maintenance6 spec_version 1 */                                         
    functions[0].CmdBindDescriptorSets2KHR                                         = REINTERPRET_CAST(PFN_vkCmdBindDescriptorSets2KHR                                         , loader(device, "vkCmdBindDescriptorSets2KHR"                                     )) ;
    functions[0].CmdPushConstants2KHR                                              = REINTERPRET_CAST(PFN_vkCmdPushConstants2KHR                                              , loader(device, "vkCmdPushConstants2KHR"                                          )) ;
    functions[0].CmdPushDescriptorSet2KHR                                          = REINTERPRET_CAST(PFN_vkCmdPushDescriptorSet2KHR                                          , loader(device, "vkCmdPushDescriptorSet2KHR"                                      )) ;
    functions[0].CmdPushDescriptorSetWithTemplate2KHR                              = REINTERPRET_CAST(PFN_vkCmdPushDescriptorSetWithTemplate2KHR                              , loader(device, "vkCmdPushDescriptorSetWithTemplate2KHR"                          )) ;
    functions[0].CmdSetDescriptorBufferOffsets2EXT                                 = REINTERPRET_CAST(PFN_vkCmdSetDescriptorBufferOffsets2EXT                                 , loader(device, "vkCmdSetDescriptorBufferOffsets2EXT"                             )) ;
    functions[0].CmdBindDescriptorBufferEmbeddedSamplers2EXT                       = REINTERPRET_CAST(PFN_vkCmdBindDescriptorBufferEmbeddedSamplers2EXT                       , loader(device, "vkCmdBindDescriptorBufferEmbeddedSamplers2EXT"                   )) ;
    /* VK_EXT_debug_marker spec_version 4 */                                         
    functions[0].DebugMarkerSetObjectTagEXT                                        = REINTERPRET_CAST(PFN_vkDebugMarkerSetObjectTagEXT                                        , loader(device, "vkDebugMarkerSetObjectTagEXT"                                    )) ;
    functions[0].DebugMarkerSetObjectNameEXT                                       = REINTERPRET_CAST(PFN_vkDebugMarkerSetObjectNameEXT                                       , loader(device, "vkDebugMarkerSetObjectNameEXT"                                   )) ;
    functions[0].CmdDebugMarkerBeginEXT                                            = REINTERPRET_CAST(PFN_vkCmdDebugMarkerBeginEXT                                            , loader(device, "vkCmdDebugMarkerBeginEXT"                                        )) ;
    functions[0].CmdDebugMarkerEndEXT                                              = REINTERPRET_CAST(PFN_vkCmdDebugMarkerEndEXT                                              , loader(device, "vkCmdDebugMarkerEndEXT"                                          )) ;
    functions[0].CmdDebugMarkerInsertEXT                                           = REINTERPRET_CAST(PFN_vkCmdDebugMarkerInsertEXT                                           , loader(device, "vkCmdDebugMarkerInsertEXT"                                       )) ;
    /* VK_EXT_transform_feedback spec_version 1 */                                   
    functions[0].CmdBindTransformFeedbackBuffersEXT                                = REINTERPRET_CAST(PFN_vkCmdBindTransformFeedbackBuffersEXT                                , loader(device, "vkCmdBindTransformFeedbackBuffersEXT"                            )) ;
    functions[0].CmdBeginTransformFeedbackEXT                                      = REINTERPRET_CAST(PFN_vkCmdBeginTransformFeedbackEXT                                      , loader(device, "vkCmdBeginTransformFeedbackEXT"                                  )) ;
    functions[0].CmdEndTransformFeedbackEXT                                        = REINTERPRET_CAST(PFN_vkCmdEndTransformFeedbackEXT                                        , loader(device, "vkCmdEndTransformFeedbackEXT"                                    )) ;
    functions[0].CmdBeginQueryIndexedEXT                                           = REINTERPRET_CAST(PFN_vkCmdBeginQueryIndexedEXT                                           , loader(device, "vkCmdBeginQueryIndexedEXT"                                       )) ;
    functions[0].CmdEndQueryIndexedEXT                                             = REINTERPRET_CAST(PFN_vkCmdEndQueryIndexedEXT                                             , loader(device, "vkCmdEndQueryIndexedEXT"                                         )) ;
    functions[0].CmdDrawIndirectByteCountEXT                                       = REINTERPRET_CAST(PFN_vkCmdDrawIndirectByteCountEXT                                       , loader(device, "vkCmdDrawIndirectByteCountEXT"                                   )) ;
    /* VK_NVX_binary_import spec_version 2 */
    functions[0].CreateCuModuleNVX                                                 = REINTERPRET_CAST(PFN_vkCreateCuModuleNVX                                                 , loader(device, "vkCreateCuModuleNVX"                                             )) ;
    functions[0].CreateCuFunctionNVX                                               = REINTERPRET_CAST(PFN_vkCreateCuFunctionNVX                                               , loader(device, "vkCreateCuFunctionNVX"                                           )) ;
    functions[0].DestroyCuModuleNVX                                                = REINTERPRET_CAST(PFN_vkDestroyCuModuleNVX                                                , loader(device, "vkDestroyCuModuleNVX"                                            )) ;
    functions[0].DestroyCuFunctionNVX                                              = REINTERPRET_CAST(PFN_vkDestroyCuFunctionNVX                                              , loader(device, "vkDestroyCuFunctionNVX"                                          )) ;
    functions[0].CmdCuLaunchKernelNVX                                              = REINTERPRET_CAST(PFN_vkCmdCuLaunchKernelNVX                                              , loader(device, "vkCmdCuLaunchKernelNVX"                                          )) ;
    /* VK_NVX_image_view_handle spec_version 3 */
    functions[0].GetImageViewHandleNVX                                             = REINTERPRET_CAST(PFN_vkGetImageViewHandleNVX                                             , loader(device, "vkGetImageViewHandleNVX"                                         )) ;
    functions[0].GetImageViewAddressNVX                                            = REINTERPRET_CAST(PFN_vkGetImageViewAddressNVX                                            , loader(device, "vkGetImageViewAddressNVX"                                        )) ;
    /* VK_AMD_draw_indirect_count spec_version 2 */                                  
    functions[0].CmdDrawIndirectCountAMD                                           = REINTERPRET_CAST(PFN_vkCmdDrawIndirectCountAMD                                           , loader(device, "vkCmdDrawIndirectCountAMD"                                       )) ;
    functions[0].CmdDrawIndexedIndirectCountAMD                                    = REINTERPRET_CAST(PFN_vkCmdDrawIndexedIndirectCountAMD                                    , loader(device, "vkCmdDrawIndexedIndirectCountAMD"                                )) ;
    /* VK_AMD_shader_info spec_version 1 */                                          
    functions[0].GetShaderInfoAMD                                                  = REINTERPRET_CAST(PFN_vkGetShaderInfoAMD                                                  , loader(device, "vkGetShaderInfoAMD"                                              )) ;
    /* VK_EXT_conditional_rendering spec_version 2 */                                
    functions[0].CmdBeginConditionalRenderingEXT                                   = REINTERPRET_CAST(PFN_vkCmdBeginConditionalRenderingEXT                                   , loader(device, "vkCmdBeginConditionalRenderingEXT"                               )) ;
    functions[0].CmdEndConditionalRenderingEXT                                     = REINTERPRET_CAST(PFN_vkCmdEndConditionalRenderingEXT                                     , loader(device, "vkCmdEndConditionalRenderingEXT"                                 )) ;
    /* VK_NV_clip_space_w_scaling spec_version 1 */                                  
    functions[0].CmdSetViewportWScalingNV                                          = REINTERPRET_CAST(PFN_vkCmdSetViewportWScalingNV                                          , loader(device, "vkCmdSetViewportWScalingNV"                                      )) ;
    /* VK_EXT_display_control spec_version 1 */                                      
    functions[0].DisplayPowerControlEXT                                            = REINTERPRET_CAST(PFN_vkDisplayPowerControlEXT                                            , loader(device, "vkDisplayPowerControlEXT"                                        )) ;
    functions[0].RegisterDeviceEventEXT                                            = REINTERPRET_CAST(PFN_vkRegisterDeviceEventEXT                                            , loader(device, "vkRegisterDeviceEventEXT"                                        )) ;
    functions[0].RegisterDisplayEventEXT                                           = REINTERPRET_CAST(PFN_vkRegisterDisplayEventEXT                                           , loader(device, "vkRegisterDisplayEventEXT"                                       )) ;
    functions[0].GetSwapchainCounterEXT                                            = REINTERPRET_CAST(PFN_vkGetSwapchainCounterEXT                                            , loader(device, "vkGetSwapchainCounterEXT"                                        )) ;
    /* VK_GOOGLE_display_timing spec_version 1 */                                    
    functions[0].GetRefreshCycleDurationGOOGLE                                     = REINTERPRET_CAST(PFN_vkGetRefreshCycleDurationGOOGLE                                     , loader(device, "vkGetRefreshCycleDurationGOOGLE"                                 )) ;
    functions[0].GetPastPresentationTimingGOOGLE                                   = REINTERPRET_CAST(PFN_vkGetPastPresentationTimingGOOGLE                                   , loader(device, "vkGetPastPresentationTimingGOOGLE"                               )) ;
    /* VK_EXT_discard_rectangles spec_version 2 */                                   
    functions[0].CmdSetDiscardRectangleEXT                                         = REINTERPRET_CAST(PFN_vkCmdSetDiscardRectangleEXT                                         , loader(device, "vkCmdSetDiscardRectangleEXT"                                     )) ;
    functions[0].CmdSetDiscardRectangleEnableEXT                                   = REINTERPRET_CAST(PFN_vkCmdSetDiscardRectangleEnableEXT                                   , loader(device, "vkCmdSetDiscardRectangleEnableEXT"                               )) ;
    functions[0].CmdSetDiscardRectangleModeEXT                                     = REINTERPRET_CAST(PFN_vkCmdSetDiscardRectangleModeEXT                                     , loader(device, "vkCmdSetDiscardRectangleModeEXT"                                 )) ;
    /* VK_EXT_hdr_metadata spec_version 3 */
    functions[0].SetHdrMetadataEXT                                                 = REINTERPRET_CAST(PFN_vkSetHdrMetadataEXT                                                 , loader(device, "vkSetHdrMetadataEXT"                                             )) ;
    /* VK_EXT_debug_utils spec_version 2 */                                          
    functions[0].SetDebugUtilsObjectNameEXT                                        = REINTERPRET_CAST(PFN_vkSetDebugUtilsObjectNameEXT                                        , loader(device, "vkSetDebugUtilsObjectNameEXT"                                    )) ;
    functions[0].SetDebugUtilsObjectTagEXT                                         = REINTERPRET_CAST(PFN_vkSetDebugUtilsObjectTagEXT                                         , loader(device, "vkSetDebugUtilsObjectTagEXT"                                     )) ;
    functions[0].QueueBeginDebugUtilsLabelEXT                                      = REINTERPRET_CAST(PFN_vkQueueBeginDebugUtilsLabelEXT                                      , loader(device, "vkQueueBeginDebugUtilsLabelEXT"                                  )) ;
    functions[0].QueueEndDebugUtilsLabelEXT                                        = REINTERPRET_CAST(PFN_vkQueueEndDebugUtilsLabelEXT                                        , loader(device, "vkQueueEndDebugUtilsLabelEXT"                                    )) ;
    functions[0].QueueInsertDebugUtilsLabelEXT                                     = REINTERPRET_CAST(PFN_vkQueueInsertDebugUtilsLabelEXT                                     , loader(device, "vkQueueInsertDebugUtilsLabelEXT"                                 )) ;
    functions[0].CmdBeginDebugUtilsLabelEXT                                        = REINTERPRET_CAST(PFN_vkCmdBeginDebugUtilsLabelEXT                                        , loader(device, "vkCmdBeginDebugUtilsLabelEXT"                                    )) ;
    functions[0].CmdEndDebugUtilsLabelEXT                                          = REINTERPRET_CAST(PFN_vkCmdEndDebugUtilsLabelEXT                                          , loader(device, "vkCmdEndDebugUtilsLabelEXT"                                      )) ;
    functions[0].CmdInsertDebugUtilsLabelEXT                                       = REINTERPRET_CAST(PFN_vkCmdInsertDebugUtilsLabelEXT                                       , loader(device, "vkCmdInsertDebugUtilsLabelEXT"                                   )) ;
    /* VK_EXT_sample_locations spec_version 1 */                                     
    functions[0].CmdSetSampleLocationsEXT                                          = REINTERPRET_CAST(PFN_vkCmdSetSampleLocationsEXT                                          , loader(device, "vkCmdSetSampleLocationsEXT"                                      )) ;
    /* VK_EXT_image_drm_format_modifier spec_version 2 */                            
    functions[0].GetImageDrmFormatModifierPropertiesEXT                            = REINTERPRET_CAST(PFN_vkGetImageDrmFormatModifierPropertiesEXT                            , loader(device, "vkGetImageDrmFormatModifierPropertiesEXT"                        )) ;
    /* VK_EXT_validation_cache spec_version 1 */                                     
    functions[0].CreateValidationCacheEXT                                          = REINTERPRET_CAST(PFN_vkCreateValidationCacheEXT                                          , loader(device, "vkCreateValidationCacheEXT"                                      )) ;
    functions[0].DestroyValidationCacheEXT                                         = REINTERPRET_CAST(PFN_vkDestroyValidationCacheEXT                                         , loader(device, "vkDestroyValidationCacheEXT"                                     )) ;
    functions[0].MergeValidationCachesEXT                                          = REINTERPRET_CAST(PFN_vkMergeValidationCachesEXT                                          , loader(device, "vkMergeValidationCachesEXT"                                      )) ;
    functions[0].GetValidationCacheDataEXT                                         = REINTERPRET_CAST(PFN_vkGetValidationCacheDataEXT                                         , loader(device, "vkGetValidationCacheDataEXT"                                     )) ;
    /* VK_NV_shading_rate_image spec_version 3 */                                    
    functions[0].CmdBindShadingRateImageNV                                         = REINTERPRET_CAST(PFN_vkCmdBindShadingRateImageNV                                         , loader(device, "vkCmdBindShadingRateImageNV"                                     )) ;
    functions[0].CmdSetViewportShadingRatePaletteNV                                = REINTERPRET_CAST(PFN_vkCmdSetViewportShadingRatePaletteNV                                , loader(device, "vkCmdSetViewportShadingRatePaletteNV"                            )) ;
    functions[0].CmdSetCoarseSampleOrderNV                                         = REINTERPRET_CAST(PFN_vkCmdSetCoarseSampleOrderNV                                         , loader(device, "vkCmdSetCoarseSampleOrderNV"                                     )) ;
    /* VK_NV_ray_tracing spec_version 3 */                                           
    functions[0].CreateAccelerationStructureNV                                     = REINTERPRET_CAST(PFN_vkCreateAccelerationStructureNV                                     , loader(device, "vkCreateAccelerationStructureNV"                                 )) ;
    functions[0].DestroyAccelerationStructureNV                                    = REINTERPRET_CAST(PFN_vkDestroyAccelerationStructureNV                                    , loader(device, "vkDestroyAccelerationStructureNV"                                )) ;
    functions[0].GetAccelerationStructureMemoryRequirementsNV                      = REINTERPRET_CAST(PFN_vkGetAccelerationStructureMemoryRequirementsNV                      , loader(device, "vkGetAccelerationStructureMemoryRequirementsNV"                  )) ;
    functions[0].BindAccelerationStructureMemoryNV                                 = REINTERPRET_CAST(PFN_vkBindAccelerationStructureMemoryNV                                 , loader(device, "vkBindAccelerationStructureMemoryNV"                             )) ;
    functions[0].CmdBuildAccelerationStructureNV                                   = REINTERPRET_CAST(PFN_vkCmdBuildAccelerationStructureNV                                   , loader(device, "vkCmdBuildAccelerationStructureNV"                               )) ;
    functions[0].CmdCopyAccelerationStructureNV                                    = REINTERPRET_CAST(PFN_vkCmdCopyAccelerationStructureNV                                    , loader(device, "vkCmdCopyAccelerationStructureNV"                                )) ;
    functions[0].CmdTraceRaysNV                                                    = REINTERPRET_CAST(PFN_vkCmdTraceRaysNV                                                    , loader(device, "vkCmdTraceRaysNV"                                                )) ;
    functions[0].CreateRayTracingPipelinesNV                                       = REINTERPRET_CAST(PFN_vkCreateRayTracingPipelinesNV                                       , loader(device, "vkCreateRayTracingPipelinesNV"                                   )) ;
    functions[0].GetRayTracingShaderGroupHandlesKHR                                = REINTERPRET_CAST(PFN_vkGetRayTracingShaderGroupHandlesKHR                                , loader(device, "vkGetRayTracingShaderGroupHandlesKHR"                            )) ;
    functions[0].GetRayTracingShaderGroupHandlesNV                                 = REINTERPRET_CAST(PFN_vkGetRayTracingShaderGroupHandlesNV                                 , loader(device, "vkGetRayTracingShaderGroupHandlesNV"                             )) ;
    functions[0].GetAccelerationStructureHandleNV                                  = REINTERPRET_CAST(PFN_vkGetAccelerationStructureHandleNV                                  , loader(device, "vkGetAccelerationStructureHandleNV"                              )) ;
    functions[0].CmdWriteAccelerationStructuresPropertiesNV                        = REINTERPRET_CAST(PFN_vkCmdWriteAccelerationStructuresPropertiesNV                        , loader(device, "vkCmdWriteAccelerationStructuresPropertiesNV"                    )) ;
    functions[0].CompileDeferredNV                                                 = REINTERPRET_CAST(PFN_vkCompileDeferredNV                                                 , loader(device, "vkCompileDeferredNV"                                             )) ;
    /* VK_EXT_external_memory_host spec_version 1 */                                 
    functions[0].GetMemoryHostPointerPropertiesEXT                                 = REINTERPRET_CAST(PFN_vkGetMemoryHostPointerPropertiesEXT                                 , loader(device, "vkGetMemoryHostPointerPropertiesEXT"                             )) ;  
    /* VK_AMD_buffer_marker spec_version 1 */                                        
    functions[0].CmdWriteBufferMarkerAMD                                           = REINTERPRET_CAST(PFN_vkCmdWriteBufferMarkerAMD                                           , loader(device, "vkCmdWriteBufferMarkerAMD"                                       )) ;
    /* VK_EXT_calibrated_timestamps spec_version 2 */                                
    functions[0].GetCalibratedTimestampsEXT                                        = REINTERPRET_CAST(PFN_vkGetCalibratedTimestampsEXT                                        , loader(device, "vkGetCalibratedTimestampsEXT"                                    )) ;
    /* VK_NV_mesh_shader spec_version 1 */                                           
    functions[0].CmdDrawMeshTasksNV                                                = REINTERPRET_CAST(PFN_vkCmdDrawMeshTasksNV                                                , loader(device, "vkCmdDrawMeshTasksNV"                                            )) ;
    functions[0].CmdDrawMeshTasksIndirectNV                                        = REINTERPRET_CAST(PFN_vkCmdDrawMeshTasksIndirectNV                                        , loader(device, "vkCmdDrawMeshTasksIndirectNV"                                    )) ;
    functions[0].CmdDrawMeshTasksIndirectCountNV                                   = REINTERPRET_CAST(PFN_vkCmdDrawMeshTasksIndirectCountNV                                   , loader(device, "vkCmdDrawMeshTasksIndirectCountNV"                               )) ;
    /* VK_NV_scissor_exclusive spec_version 2 */                                     
    functions[0].CmdSetExclusiveScissorEnableNV                                    = REINTERPRET_CAST(PFN_vkCmdSetExclusiveScissorEnableNV                                    , loader(device, "vkCmdSetExclusiveScissorEnableNV"                                )) ;
    functions[0].CmdSetExclusiveScissorNV                                          = REINTERPRET_CAST(PFN_vkCmdSetExclusiveScissorNV                                          , loader(device, "vkCmdSetExclusiveScissorNV"                                      )) ;
    /* VK_NV_device_diagnostic_checkpoints spec_version 2 */                         
    functions[0].CmdSetCheckpointNV                                                = REINTERPRET_CAST(PFN_vkCmdSetCheckpointNV                                                , loader(device, "vkCmdSetCheckpointNV"                                            )) ;
    functions[0].GetQueueCheckpointDataNV                                          = REINTERPRET_CAST(PFN_vkGetQueueCheckpointDataNV                                          , loader(device, "vkGetQueueCheckpointDataNV"                                      )) ;
    /* VK_INTEL_performance_query spec_version 2 */                                  
    functions[0].InitializePerformanceApiINTEL                                     = REINTERPRET_CAST(PFN_vkInitializePerformanceApiINTEL                                     , loader(device, "vkInitializePerformanceApiINTEL"                                 )) ;
    functions[0].UninitializePerformanceApiINTEL                                   = REINTERPRET_CAST(PFN_vkUninitializePerformanceApiINTEL                                   , loader(device, "vkUninitializePerformanceApiINTEL"                               )) ;
    functions[0].CmdSetPerformanceMarkerINTEL                                      = REINTERPRET_CAST(PFN_vkCmdSetPerformanceMarkerINTEL                                      , loader(device, "vkCmdSetPerformanceMarkerINTEL"                                  )) ;
    functions[0].CmdSetPerformanceStreamMarkerINTEL                                = REINTERPRET_CAST(PFN_vkCmdSetPerformanceStreamMarkerINTEL                                , loader(device, "vkCmdSetPerformanceStreamMarkerINTEL"                            )) ;
    functions[0].CmdSetPerformanceOverrideINTEL                                    = REINTERPRET_CAST(PFN_vkCmdSetPerformanceOverrideINTEL                                    , loader(device, "vkCmdSetPerformanceOverrideINTEL"                                )) ;
    functions[0].AcquirePerformanceConfigurationINTEL                              = REINTERPRET_CAST(PFN_vkAcquirePerformanceConfigurationINTEL                              , loader(device, "vkAcquirePerformanceConfigurationINTEL"                          )) ;
    functions[0].ReleasePerformanceConfigurationINTEL                              = REINTERPRET_CAST(PFN_vkReleasePerformanceConfigurationINTEL                              , loader(device, "vkReleasePerformanceConfigurationINTEL"                          )) ;
    functions[0].QueueSetPerformanceConfigurationINTEL                             = REINTERPRET_CAST(PFN_vkQueueSetPerformanceConfigurationINTEL                             , loader(device, "vkQueueSetPerformanceConfigurationINTEL"                         )) ;
    functions[0].GetPerformanceParameterINTEL                                      = REINTERPRET_CAST(PFN_vkGetPerformanceParameterINTEL                                      , loader(device, "vkGetPerformanceParameterINTEL"                                  )) ;
    /* VK_AMD_display_native_hdr spec_version 1 */                                   
    functions[0].SetLocalDimmingAMD                                                = REINTERPRET_CAST(PFN_vkSetLocalDimmingAMD                                                , loader(device, "vkSetLocalDimmingAMD"                                            )) ;
    /* VK_EXT_buffer_device_address spec_version 2 */                                
    functions[0].GetBufferDeviceAddressEXT                                         = REINTERPRET_CAST(PFN_vkGetBufferDeviceAddressEXT                                         , loader(device, "vkGetBufferDeviceAddressEXT"                                     )) ;
    /* VK_EXT_line_rasterization spec_version 1 */                                   
    functions[0].CmdSetLineStippleEXT                                              = REINTERPRET_CAST(PFN_vkCmdSetLineStippleEXT                                              , loader(device, "vkCmdSetLineStippleEXT"                                          )) ;
    /* VK_EXT_host_query_reset spec_version 1 */                                     
    functions[0].ResetQueryPoolEXT                                                 = REINTERPRET_CAST(PFN_vkResetQueryPoolEXT                                                 , loader(device, "vkResetQueryPoolEXT"                                             )) ;  
    /* VK_EXT_extended_dynamic_state spec_version 1 */                               
    functions[0].CmdSetCullModeEXT                                                 = REINTERPRET_CAST(PFN_vkCmdSetCullModeEXT                                                 , loader(device, "vkCmdSetCullModeEXT"                                             )) ;
    functions[0].CmdSetFrontFaceEXT                                                = REINTERPRET_CAST(PFN_vkCmdSetFrontFaceEXT                                                , loader(device, "vkCmdSetFrontFaceEXT"                                            )) ;
    functions[0].CmdSetPrimitiveTopologyEXT                                        = REINTERPRET_CAST(PFN_vkCmdSetPrimitiveTopologyEXT                                        , loader(device, "vkCmdSetPrimitiveTopologyEXT"                                    )) ;
    functions[0].CmdSetViewportWithCountEXT                                        = REINTERPRET_CAST(PFN_vkCmdSetViewportWithCountEXT                                        , loader(device, "vkCmdSetViewportWithCountEXT"                                    )) ;
    functions[0].CmdSetScissorWithCountEXT                                         = REINTERPRET_CAST(PFN_vkCmdSetScissorWithCountEXT                                         , loader(device, "vkCmdSetScissorWithCountEXT"                                     )) ;
    functions[0].CmdBindVertexBuffers2EXT                                          = REINTERPRET_CAST(PFN_vkCmdBindVertexBuffers2EXT                                          , loader(device, "vkCmdBindVertexBuffers2EXT"                                      )) ;
    functions[0].CmdSetDepthTestEnableEXT                                          = REINTERPRET_CAST(PFN_vkCmdSetDepthTestEnableEXT                                          , loader(device, "vkCmdSetDepthTestEnableEXT"                                      )) ;
    functions[0].CmdSetDepthWriteEnableEXT                                         = REINTERPRET_CAST(PFN_vkCmdSetDepthWriteEnableEXT                                         , loader(device, "vkCmdSetDepthWriteEnableEXT"                                     )) ;
    functions[0].CmdSetDepthCompareOpEXT                                           = REINTERPRET_CAST(PFN_vkCmdSetDepthCompareOpEXT                                           , loader(device, "vkCmdSetDepthCompareOpEXT"                                       )) ;
    functions[0].CmdSetDepthBoundsTestEnableEXT                                    = REINTERPRET_CAST(PFN_vkCmdSetDepthBoundsTestEnableEXT                                    , loader(device, "vkCmdSetDepthBoundsTestEnableEXT"                                )) ;
    functions[0].CmdSetStencilTestEnableEXT                                        = REINTERPRET_CAST(PFN_vkCmdSetStencilTestEnableEXT                                        , loader(device, "vkCmdSetStencilTestEnableEXT"                                    )) ;
    functions[0].CmdSetStencilOpEXT                                                = REINTERPRET_CAST(PFN_vkCmdSetStencilOpEXT                                                , loader(device, "vkCmdSetStencilOpEXT"                                            )) ;
    /* VK_EXT_host_image_copy spec_version 1 */                                      
    functions[0].CopyMemoryToImageEXT                                              = REINTERPRET_CAST(PFN_vkCopyMemoryToImageEXT                                              , loader(device, "vkCopyMemoryToImageEXT"                                          )) ;
    functions[0].CopyImageToMemoryEXT                                              = REINTERPRET_CAST(PFN_vkCopyImageToMemoryEXT                                              , loader(device, "vkCopyImageToMemoryEXT"                                          )) ;
    functions[0].CopyImageToImageEXT                                               = REINTERPRET_CAST(PFN_vkCopyImageToImageEXT                                               , loader(device, "vkCopyImageToImageEXT"                                           )) ;
    functions[0].TransitionImageLayoutEXT                                          = REINTERPRET_CAST(PFN_vkTransitionImageLayoutEXT                                          , loader(device, "vkTransitionImageLayoutEXT"                                      )) ;
    functions[0].GetImageSubresourceLayout2EXT                                     = REINTERPRET_CAST(PFN_vkGetImageSubresourceLayout2EXT                                     , loader(device, "vkGetImageSubresourceLayout2EXT"                                 )) ;
    /* VK_EXT_swapchain_maintenance1 spec_version 1 */                               
    functions[0].ReleaseSwapchainImagesEXT                                         = REINTERPRET_CAST(PFN_vkReleaseSwapchainImagesEXT                                         , loader(device, "vkReleaseSwapchainImagesEXT"                                     )) ;
    /* VK_NV_device_generated_commands spec_version 3 */                             
    functions[0].GetGeneratedCommandsMemoryRequirementsNV                          = REINTERPRET_CAST(PFN_vkGetGeneratedCommandsMemoryRequirementsNV                          , loader(device, "vkGetGeneratedCommandsMemoryRequirementsNV"                      )) ;
    functions[0].CmdPreprocessGeneratedCommandsNV                                  = REINTERPRET_CAST(PFN_vkCmdPreprocessGeneratedCommandsNV                                  , loader(device, "vkCmdPreprocessGeneratedCommandsNV"                              )) ;
    functions[0].CmdExecuteGeneratedCommandsNV                                     = REINTERPRET_CAST(PFN_vkCmdExecuteGeneratedCommandsNV                                     , loader(device, "vkCmdExecuteGeneratedCommandsNV"                                 )) ;
    functions[0].CmdBindPipelineShaderGroupNV                                      = REINTERPRET_CAST(PFN_vkCmdBindPipelineShaderGroupNV                                      , loader(device, "vkCmdBindPipelineShaderGroupNV"                                  )) ;
    functions[0].CreateIndirectCommandsLayoutNV                                    = REINTERPRET_CAST(PFN_vkCreateIndirectCommandsLayoutNV                                    , loader(device, "vkCreateIndirectCommandsLayoutNV"                                )) ;
    functions[0].DestroyIndirectCommandsLayoutNV                                   = REINTERPRET_CAST(PFN_vkDestroyIndirectCommandsLayoutNV                                   , loader(device, "vkDestroyIndirectCommandsLayoutNV"                               )) ;
    /* VK_EXT_depth_bias_control spec_version 1 */                                   
    functions[0].CmdSetDepthBias2EXT                                               = REINTERPRET_CAST(PFN_vkCmdSetDepthBias2EXT                                               , loader(device, "vkCmdSetDepthBias2EXT"                                           )) ;
    /* VK_EXT_private_data spec_version 1 */                                         
    functions[0].CreatePrivateDataSlotEXT                                          = REINTERPRET_CAST(PFN_vkCreatePrivateDataSlotEXT                                          , loader(device, "vkCreatePrivateDataSlotEXT"                                      )) ;
    functions[0].DestroyPrivateDataSlotEXT                                         = REINTERPRET_CAST(PFN_vkDestroyPrivateDataSlotEXT                                         , loader(device, "vkDestroyPrivateDataSlotEXT"                                     )) ;
    functions[0].SetPrivateDataEXT                                                 = REINTERPRET_CAST(PFN_vkSetPrivateDataEXT                                                 , loader(device, "vkSetPrivateDataEXT"                                             )) ;
    functions[0].GetPrivateDataEXT                                                 = REINTERPRET_CAST(PFN_vkGetPrivateDataEXT                                                 , loader(device, "vkGetPrivateDataEXT"                                             )) ;
    /* VK_NV_cuda_kernel_launch spec_version 2 */                                    
    functions[0].CreateCudaModuleNV                                                = REINTERPRET_CAST(PFN_vkCreateCudaModuleNV                                                , loader(device, "vkCreateCudaModuleNV"                                            )) ;
    functions[0].GetCudaModuleCacheNV                                              = REINTERPRET_CAST(PFN_vkGetCudaModuleCacheNV                                              , loader(device, "vkGetCudaModuleCacheNV"                                          )) ;
    functions[0].CreateCudaFunctionNV                                              = REINTERPRET_CAST(PFN_vkCreateCudaFunctionNV                                              , loader(device, "vkCreateCudaFunctionNV"                                          )) ;
    functions[0].DestroyCudaModuleNV                                               = REINTERPRET_CAST(PFN_vkDestroyCudaModuleNV                                               , loader(device, "vkDestroyCudaModuleNV"                                           )) ;
    functions[0].DestroyCudaFunctionNV                                             = REINTERPRET_CAST(PFN_vkDestroyCudaFunctionNV                                             , loader(device, "vkDestroyCudaFunctionNV"                                         )) ;
    functions[0].CmdCudaLaunchKernelNV                                             = REINTERPRET_CAST(PFN_vkCmdCudaLaunchKernelNV                                             , loader(device, "vkCmdCudaLaunchKernelNV"                                         )) ;
    /* VK_EXT_descriptor_buffer spec_version 1 */                                    
    functions[0].GetDescriptorSetLayoutSizeEXT                                     = REINTERPRET_CAST(PFN_vkGetDescriptorSetLayoutSizeEXT                                     , loader(device, "vkGetDescriptorSetLayoutSizeEXT"                                 )) ;
    functions[0].GetDescriptorSetLayoutBindingOffsetEXT                            = REINTERPRET_CAST(PFN_vkGetDescriptorSetLayoutBindingOffsetEXT                            , loader(device, "vkGetDescriptorSetLayoutBindingOffsetEXT"                        )) ;
    functions[0].GetDescriptorEXT                                                  = REINTERPRET_CAST(PFN_vkGetDescriptorEXT                                                  , loader(device, "vkGetDescriptorEXT"                                              )) ;
    functions[0].CmdBindDescriptorBuffersEXT                                       = REINTERPRET_CAST(PFN_vkCmdBindDescriptorBuffersEXT                                       , loader(device, "vkCmdBindDescriptorBuffersEXT"                                   )) ;
    functions[0].CmdSetDescriptorBufferOffsetsEXT                                  = REINTERPRET_CAST(PFN_vkCmdSetDescriptorBufferOffsetsEXT                                  , loader(device, "vkCmdSetDescriptorBufferOffsetsEXT"                              )) ;
    functions[0].CmdBindDescriptorBufferEmbeddedSamplersEXT                        = REINTERPRET_CAST(PFN_vkCmdBindDescriptorBufferEmbeddedSamplersEXT                        , loader(device, "vkCmdBindDescriptorBufferEmbeddedSamplersEXT"                    )) ;
    functions[0].GetBufferOpaqueCaptureDescriptorDataEXT                           = REINTERPRET_CAST(PFN_vkGetBufferOpaqueCaptureDescriptorDataEXT                           , loader(device, "vkGetBufferOpaqueCaptureDescriptorDataEXT"                       )) ;
    functions[0].GetImageOpaqueCaptureDescriptorDataEXT                            = REINTERPRET_CAST(PFN_vkGetImageOpaqueCaptureDescriptorDataEXT                            , loader(device, "vkGetImageOpaqueCaptureDescriptorDataEXT"                        )) ;
    functions[0].GetImageViewOpaqueCaptureDescriptorDataEXT                        = REINTERPRET_CAST(PFN_vkGetImageViewOpaqueCaptureDescriptorDataEXT                        , loader(device, "vkGetImageViewOpaqueCaptureDescriptorDataEXT"                    )) ;
    functions[0].GetSamplerOpaqueCaptureDescriptorDataEXT                          = REINTERPRET_CAST(PFN_vkGetSamplerOpaqueCaptureDescriptorDataEXT                          , loader(device, "vkGetSamplerOpaqueCaptureDescriptorDataEXT"                      )) ;
    functions[0].GetAccelerationStructureOpaqueCaptureDescriptorDataEXT            = REINTERPRET_CAST(PFN_vkGetAccelerationStructureOpaqueCaptureDescriptorDataEXT            , loader(device, "vkGetAccelerationStructureOpaqueCaptureDescriptorDataEXT"        )) ;
    /* VK_NV_fragment_shading_rate_enums spec_version 1 */                           
    functions[0].CmdSetFragmentShadingRateEnumNV                                   = REINTERPRET_CAST(PFN_vkCmdSetFragmentShadingRateEnumNV                                   , loader(device, "vkCmdSetFragmentShadingRateEnumNV"                               )) ;
    /* VK_EXT_device_fault spec_version 2 */                                         
    functions[0].GetDeviceFaultInfoEXT                                             = REINTERPRET_CAST(PFN_vkGetDeviceFaultInfoEXT                                             , loader(device, "vkGetDeviceFaultInfoEXT"                                         )) ;
    /* VK_EXT_vertex_input_dynamic_state spec_version 2 */                           
    functions[0].CmdSetVertexInputEXT                                              = REINTERPRET_CAST(PFN_vkCmdSetVertexInputEXT                                              , loader(device, "vkCmdSetVertexInputEXT"                                          )) ;
    /* VK_HUAWEI_subpass_shading spec_version 3 */                                   
    functions[0].GetDeviceSubpassShadingMaxWorkgroupSizeHUAWEI                     = REINTERPRET_CAST(PFN_vkGetDeviceSubpassShadingMaxWorkgroupSizeHUAWEI                     , loader(device, "vkGetDeviceSubpassShadingMaxWorkgroupSizeHUAWEI"                 )) ;
    functions[0].CmdSubpassShadingHUAWEI                                           = REINTERPRET_CAST(PFN_vkCmdSubpassShadingHUAWEI                                           , loader(device, "vkCmdSubpassShadingHUAWEI"                                       )) ;
    /* VK_HUAWEI_invocation_mask spec_version 1 */                                   
    functions[0].CmdBindInvocationMaskHUAWEI                                       = REINTERPRET_CAST(PFN_vkCmdBindInvocationMaskHUAWEI                                       , loader(device, "vkCmdBindInvocationMaskHUAWEI"                                   )) ;
    /* VK_NV_external_memory_rdma spec_version 1 */                                  
    functions[0].GetMemoryRemoteAddressNV                                          = REINTERPRET_CAST(PFN_vkGetMemoryRemoteAddressNV                                          , loader(device, "vkGetMemoryRemoteAddressNV"                                      )) ;
    /* VK_EXT_pipeline_properties spec_version 1 */                                  
    functions[0].GetPipelinePropertiesEXT                                          = REINTERPRET_CAST(PFN_vkGetPipelinePropertiesEXT                                          , loader(device, "vkGetPipelinePropertiesEXT"                                      )) ;
    /* VK_EXT_extended_dynamic_state2 spec_version 1 */                              
    functions[0].CmdSetPatchControlPointsEXT                                       = REINTERPRET_CAST(PFN_vkCmdSetPatchControlPointsEXT                                       , loader(device, "vkCmdSetPatchControlPointsEXT"                                   )) ;
    functions[0].CmdSetRasterizerDiscardEnableEXT                                  = REINTERPRET_CAST(PFN_vkCmdSetRasterizerDiscardEnableEXT                                  , loader(device, "vkCmdSetRasterizerDiscardEnableEXT"                              )) ;
    functions[0].CmdSetDepthBiasEnableEXT                                          = REINTERPRET_CAST(PFN_vkCmdSetDepthBiasEnableEXT                                          , loader(device, "vkCmdSetDepthBiasEnableEXT"                                      )) ;
    functions[0].CmdSetLogicOpEXT                                                  = REINTERPRET_CAST(PFN_vkCmdSetLogicOpEXT                                                  , loader(device, "vkCmdSetLogicOpEXT"                                              )) ;
    functions[0].CmdSetPrimitiveRestartEnableEXT                                   = REINTERPRET_CAST(PFN_vkCmdSetPrimitiveRestartEnableEXT                                   , loader(device, "vkCmdSetPrimitiveRestartEnableEXT"                               )) ;
    /* VK_EXT_color_write_enable spec_version 1 */                                   
    functions[0].CmdSetColorWriteEnableEXT                                         = REINTERPRET_CAST(PFN_vkCmdSetColorWriteEnableEXT                                         , loader(device, "vkCmdSetColorWriteEnableEXT"                                     )) ;
    /* VK_EXT_multi_draw spec_version 1 */                                           
    functions[0].CmdDrawMultiEXT                                                   = REINTERPRET_CAST(PFN_vkCmdDrawMultiEXT                                                   , loader(device, "vkCmdDrawMultiEXT"                                               )) ;
    functions[0].CmdDrawMultiIndexedEXT                                            = REINTERPRET_CAST(PFN_vkCmdDrawMultiIndexedEXT                                            , loader(device, "vkCmdDrawMultiIndexedEXT"                                        )) ;
    /* VK_EXT_opacity_micromap spec_version 2 */                                     
    functions[0].CreateMicromapEXT                                                 = REINTERPRET_CAST(PFN_vkCreateMicromapEXT                                                 , loader(device, "vkCreateMicromapEXT"                                             )) ;
    functions[0].DestroyMicromapEXT                                                = REINTERPRET_CAST(PFN_vkDestroyMicromapEXT                                                , loader(device, "vkDestroyMicromapEXT"                                            )) ;
    functions[0].CmdBuildMicromapsEXT                                              = REINTERPRET_CAST(PFN_vkCmdBuildMicromapsEXT                                              , loader(device, "vkCmdBuildMicromapsEXT"                                          )) ;
    functions[0].BuildMicromapsEXT                                                 = REINTERPRET_CAST(PFN_vkBuildMicromapsEXT                                                 , loader(device, "vkBuildMicromapsEXT"                                             )) ;
    functions[0].CopyMicromapEXT                                                   = REINTERPRET_CAST(PFN_vkCopyMicromapEXT                                                   , loader(device, "vkCopyMicromapEXT"                                               )) ;
    functions[0].CopyMicromapToMemoryEXT                                           = REINTERPRET_CAST(PFN_vkCopyMicromapToMemoryEXT                                           , loader(device, "vkCopyMicromapToMemoryEXT"                                       )) ;
    functions[0].CopyMemoryToMicromapEXT                                           = REINTERPRET_CAST(PFN_vkCopyMemoryToMicromapEXT                                           , loader(device, "vkCopyMemoryToMicromapEXT"                                       )) ;
    functions[0].WriteMicromapsPropertiesEXT                                       = REINTERPRET_CAST(PFN_vkWriteMicromapsPropertiesEXT                                       , loader(device, "vkWriteMicromapsPropertiesEXT"                                   )) ;
    functions[0].CmdCopyMicromapEXT                                                = REINTERPRET_CAST(PFN_vkCmdCopyMicromapEXT                                                , loader(device, "vkCmdCopyMicromapEXT"                                            )) ;
    functions[0].CmdCopyMicromapToMemoryEXT                                        = REINTERPRET_CAST(PFN_vkCmdCopyMicromapToMemoryEXT                                        , loader(device, "vkCmdCopyMicromapToMemoryEXT"                                    )) ;
    functions[0].CmdCopyMemoryToMicromapEXT                                        = REINTERPRET_CAST(PFN_vkCmdCopyMemoryToMicromapEXT                                        , loader(device, "vkCmdCopyMemoryToMicromapEXT"                                    )) ;
    functions[0].CmdWriteMicromapsPropertiesEXT                                    = REINTERPRET_CAST(PFN_vkCmdWriteMicromapsPropertiesEXT                                    , loader(device, "vkCmdWriteMicromapsPropertiesEXT"                                )) ;
    functions[0].GetDeviceMicromapCompatibilityEXT                                 = REINTERPRET_CAST(PFN_vkGetDeviceMicromapCompatibilityEXT                                 , loader(device, "vkGetDeviceMicromapCompatibilityEXT"                             )) ;
    functions[0].GetMicromapBuildSizesEXT                                          = REINTERPRET_CAST(PFN_vkGetMicromapBuildSizesEXT                                          , loader(device, "vkGetMicromapBuildSizesEXT"                                      )) ;
    /* VK_HUAWEI_cluster_culling_shader spec_version 3 */                            
    functions[0].CmdDrawClusterHUAWEI                                              = REINTERPRET_CAST(PFN_vkCmdDrawClusterHUAWEI                                              , loader(device, "vkCmdDrawClusterHUAWEI"                                          )) ;
    functions[0].CmdDrawClusterIndirectHUAWEI                                      = REINTERPRET_CAST(PFN_vkCmdDrawClusterIndirectHUAWEI                                      , loader(device, "vkCmdDrawClusterIndirectHUAWEI"                                  )) ;
    /* VK_EXT_pageable_device_local_memory spec_version 1 */                         
    functions[0].SetDeviceMemoryPriorityEXT                                        = REINTERPRET_CAST(PFN_vkSetDeviceMemoryPriorityEXT                                        , loader(device, "vkSetDeviceMemoryPriorityEXT"                                    )) ;
    /* VK_VALVE_descriptor_set_host_mapping spec_version 1 */                        
    functions[0].GetDescriptorSetLayoutHostMappingInfoVALVE                        = REINTERPRET_CAST(PFN_vkGetDescriptorSetLayoutHostMappingInfoVALVE                        , loader(device, "vkGetDescriptorSetLayoutHostMappingInfoVALVE"                    )) ;
    functions[0].GetDescriptorSetHostMappingVALVE                                  = REINTERPRET_CAST(PFN_vkGetDescriptorSetHostMappingVALVE                                  , loader(device, "vkGetDescriptorSetHostMappingVALVE"                              )) ;
    /* VK_NV_copy_memory_indirect spec_version 1 */                                  
    functions[0].CmdCopyMemoryIndirectNV                                           = REINTERPRET_CAST(PFN_vkCmdCopyMemoryIndirectNV                                           , loader(device, "vkCmdCopyMemoryIndirectNV"                                       )) ;
    functions[0].CmdCopyMemoryToImageIndirectNV                                    = REINTERPRET_CAST(PFN_vkCmdCopyMemoryToImageIndirectNV                                    , loader(device, "vkCmdCopyMemoryToImageIndirectNV"                                )) ;
    /* VK_NV_memory_decompression spec_version 1 */                                  
    functions[0].CmdDecompressMemoryNV                                             = REINTERPRET_CAST(PFN_vkCmdDecompressMemoryNV                                             , loader(device, "vkCmdDecompressMemoryNV"                                         )) ;
    functions[0].CmdDecompressMemoryIndirectCountNV                                = REINTERPRET_CAST(PFN_vkCmdDecompressMemoryIndirectCountNV                                , loader(device, "vkCmdDecompressMemoryIndirectCountNV"                            )) ;
    /* VK_NV_device_generated_commands_compute spec_version 2 */                     
    functions[0].GetPipelineIndirectMemoryRequirementsNV                           = REINTERPRET_CAST(PFN_vkGetPipelineIndirectMemoryRequirementsNV                           , loader(device, "vkGetPipelineIndirectMemoryRequirementsNV"                       )) ;
    functions[0].CmdUpdatePipelineIndirectBufferNV                                 = REINTERPRET_CAST(PFN_vkCmdUpdatePipelineIndirectBufferNV                                 , loader(device, "vkCmdUpdatePipelineIndirectBufferNV"                             )) ;
    functions[0].GetPipelineIndirectDeviceAddressNV                                = REINTERPRET_CAST(PFN_vkGetPipelineIndirectDeviceAddressNV                                , loader(device, "vkGetPipelineIndirectDeviceAddressNV"                            )) ;
    /* VK_EXT_extended_dynamic_state3 spec_version 2 */                              
    functions[0].CmdSetDepthClampEnableEXT                                         = REINTERPRET_CAST(PFN_vkCmdSetDepthClampEnableEXT                                         , loader(device, "vkCmdSetDepthClampEnableEXT"                                     )) ;
    functions[0].CmdSetPolygonModeEXT                                              = REINTERPRET_CAST(PFN_vkCmdSetPolygonModeEXT                                              , loader(device, "vkCmdSetPolygonModeEXT"                                          )) ;
    functions[0].CmdSetRasterizationSamplesEXT                                     = REINTERPRET_CAST(PFN_vkCmdSetRasterizationSamplesEXT                                     , loader(device, "vkCmdSetRasterizationSamplesEXT"                                 )) ;
    functions[0].CmdSetSampleMaskEXT                                               = REINTERPRET_CAST(PFN_vkCmdSetSampleMaskEXT                                               , loader(device, "vkCmdSetSampleMaskEXT"                                           )) ;
    functions[0].CmdSetAlphaToCoverageEnableEXT                                    = REINTERPRET_CAST(PFN_vkCmdSetAlphaToCoverageEnableEXT                                    , loader(device, "vkCmdSetAlphaToCoverageEnableEXT"                                )) ;
    functions[0].CmdSetAlphaToOneEnableEXT                                         = REINTERPRET_CAST(PFN_vkCmdSetAlphaToOneEnableEXT                                         , loader(device, "vkCmdSetAlphaToOneEnableEXT"                                     )) ;
    functions[0].CmdSetLogicOpEnableEXT                                            = REINTERPRET_CAST(PFN_vkCmdSetLogicOpEnableEXT                                            , loader(device, "vkCmdSetLogicOpEnableEXT"                                        )) ;
    functions[0].CmdSetColorBlendEnableEXT                                         = REINTERPRET_CAST(PFN_vkCmdSetColorBlendEnableEXT                                         , loader(device, "vkCmdSetColorBlendEnableEXT"                                     )) ;
    functions[0].CmdSetColorBlendEquationEXT                                       = REINTERPRET_CAST(PFN_vkCmdSetColorBlendEquationEXT                                       , loader(device, "vkCmdSetColorBlendEquationEXT"                                   )) ;
    functions[0].CmdSetColorWriteMaskEXT                                           = REINTERPRET_CAST(PFN_vkCmdSetColorWriteMaskEXT                                           , loader(device, "vkCmdSetColorWriteMaskEXT"                                       )) ;
    functions[0].CmdSetTessellationDomainOriginEXT                                 = REINTERPRET_CAST(PFN_vkCmdSetTessellationDomainOriginEXT                                 , loader(device, "vkCmdSetTessellationDomainOriginEXT"                             )) ;
    functions[0].CmdSetRasterizationStreamEXT                                      = REINTERPRET_CAST(PFN_vkCmdSetRasterizationStreamEXT                                      , loader(device, "vkCmdSetRasterizationStreamEXT"                                  )) ;
    functions[0].CmdSetConservativeRasterizationModeEXT                            = REINTERPRET_CAST(PFN_vkCmdSetConservativeRasterizationModeEXT                            , loader(device, "vkCmdSetConservativeRasterizationModeEXT"                        )) ;
    functions[0].CmdSetExtraPrimitiveOverestimationSizeEXT                         = REINTERPRET_CAST(PFN_vkCmdSetExtraPrimitiveOverestimationSizeEXT                         , loader(device, "vkCmdSetExtraPrimitiveOverestimationSizeEXT"                     )) ;
    functions[0].CmdSetDepthClipEnableEXT                                          = REINTERPRET_CAST(PFN_vkCmdSetDepthClipEnableEXT                                          , loader(device, "vkCmdSetDepthClipEnableEXT"                                      )) ;
    functions[0].CmdSetSampleLocationsEnableEXT                                    = REINTERPRET_CAST(PFN_vkCmdSetSampleLocationsEnableEXT                                    , loader(device, "vkCmdSetSampleLocationsEnableEXT"                                )) ;
    functions[0].CmdSetColorBlendAdvancedEXT                                       = REINTERPRET_CAST(PFN_vkCmdSetColorBlendAdvancedEXT                                       , loader(device, "vkCmdSetColorBlendAdvancedEXT"                                   )) ;
    functions[0].CmdSetProvokingVertexModeEXT                                      = REINTERPRET_CAST(PFN_vkCmdSetProvokingVertexModeEXT                                      , loader(device, "vkCmdSetProvokingVertexModeEXT"                                  )) ;
    functions[0].CmdSetLineRasterizationModeEXT                                    = REINTERPRET_CAST(PFN_vkCmdSetLineRasterizationModeEXT                                    , loader(device, "vkCmdSetLineRasterizationModeEXT"                                )) ;
    functions[0].CmdSetLineStippleEnableEXT                                        = REINTERPRET_CAST(PFN_vkCmdSetLineStippleEnableEXT                                        , loader(device, "vkCmdSetLineStippleEnableEXT"                                    )) ;
    functions[0].CmdSetDepthClipNegativeOneToOneEXT                                = REINTERPRET_CAST(PFN_vkCmdSetDepthClipNegativeOneToOneEXT                                , loader(device, "vkCmdSetDepthClipNegativeOneToOneEXT"                            )) ;
    functions[0].CmdSetViewportWScalingEnableNV                                    = REINTERPRET_CAST(PFN_vkCmdSetViewportWScalingEnableNV                                    , loader(device, "vkCmdSetViewportWScalingEnableNV"                                )) ;
    functions[0].CmdSetViewportSwizzleNV                                           = REINTERPRET_CAST(PFN_vkCmdSetViewportSwizzleNV                                           , loader(device, "vkCmdSetViewportSwizzleNV"                                       )) ;
    functions[0].CmdSetCoverageToColorEnableNV                                     = REINTERPRET_CAST(PFN_vkCmdSetCoverageToColorEnableNV                                     , loader(device, "vkCmdSetCoverageToColorEnableNV"                                 )) ;
    functions[0].CmdSetCoverageToColorLocationNV                                   = REINTERPRET_CAST(PFN_vkCmdSetCoverageToColorLocationNV                                   , loader(device, "vkCmdSetCoverageToColorLocationNV"                               )) ;
    functions[0].CmdSetCoverageModulationModeNV                                    = REINTERPRET_CAST(PFN_vkCmdSetCoverageModulationModeNV                                    , loader(device, "vkCmdSetCoverageModulationModeNV"                                )) ;
    functions[0].CmdSetCoverageModulationTableEnableNV                             = REINTERPRET_CAST(PFN_vkCmdSetCoverageModulationTableEnableNV                             , loader(device, "vkCmdSetCoverageModulationTableEnableNV"                         )) ;
    functions[0].CmdSetCoverageModulationTableNV                                   = REINTERPRET_CAST(PFN_vkCmdSetCoverageModulationTableNV                                   , loader(device, "vkCmdSetCoverageModulationTableNV"                               )) ;
    functions[0].CmdSetShadingRateImageEnableNV                                    = REINTERPRET_CAST(PFN_vkCmdSetShadingRateImageEnableNV                                    , loader(device, "vkCmdSetShadingRateImageEnableNV"                                )) ;
    functions[0].CmdSetRepresentativeFragmentTestEnableNV                          = REINTERPRET_CAST(PFN_vkCmdSetRepresentativeFragmentTestEnableNV                          , loader(device, "vkCmdSetRepresentativeFragmentTestEnableNV"                      )) ;
    functions[0].CmdSetCoverageReductionModeNV                                     = REINTERPRET_CAST(PFN_vkCmdSetCoverageReductionModeNV                                     , loader(device, "vkCmdSetCoverageReductionModeNV"                                 )) ;
    /* VK_EXT_shader_module_identifier spec_version 1 */                             
    functions[0].GetShaderModuleIdentifierEXT                                      = REINTERPRET_CAST(PFN_vkGetShaderModuleIdentifierEXT                                      , loader(device, "vkGetShaderModuleIdentifierEXT"                                  )) ;
    functions[0].GetShaderModuleCreateInfoIdentifierEXT                            = REINTERPRET_CAST(PFN_vkGetShaderModuleCreateInfoIdentifierEXT                            , loader(device, "vkGetShaderModuleCreateInfoIdentifierEXT"                        )) ;
    /* VK_NV_optical_flow spec_version 1 */                                          
    functions[0].CreateOpticalFlowSessionNV                                        = REINTERPRET_CAST(PFN_vkCreateOpticalFlowSessionNV                                        , loader(device, "vkCreateOpticalFlowSessionNV"                                    )) ;
    functions[0].DestroyOpticalFlowSessionNV                                       = REINTERPRET_CAST(PFN_vkDestroyOpticalFlowSessionNV                                       , loader(device, "vkDestroyOpticalFlowSessionNV"                                   )) ;
    functions[0].BindOpticalFlowSessionImageNV                                     = REINTERPRET_CAST(PFN_vkBindOpticalFlowSessionImageNV                                     , loader(device, "vkBindOpticalFlowSessionImageNV"                                 )) ;
    functions[0].CmdOpticalFlowExecuteNV                                           = REINTERPRET_CAST(PFN_vkCmdOpticalFlowExecuteNV                                           , loader(device, "vkCmdOpticalFlowExecuteNV"                                       )) ;
    /* VK_EXT_shader_object spec_version 1 */                                        
    functions[0].CreateShadersEXT                                                  = REINTERPRET_CAST(PFN_vkCreateShadersEXT                                                  , loader(device, "vkCreateShadersEXT"                                              )) ;
    functions[0].DestroyShaderEXT                                                  = REINTERPRET_CAST(PFN_vkDestroyShaderEXT                                                  , loader(device, "vkDestroyShaderEXT"                                              )) ;
    functions[0].GetShaderBinaryDataEXT                                            = REINTERPRET_CAST(PFN_vkGetShaderBinaryDataEXT                                            , loader(device, "vkGetShaderBinaryDataEXT"                                        )) ;
    functions[0].CmdBindShadersEXT                                                 = REINTERPRET_CAST(PFN_vkCmdBindShadersEXT                                                 , loader(device, "vkCmdBindShadersEXT"                                             )) ;
    /* VK_QCOM_tile_properties spec_version 1 */                                     
    functions[0].GetFramebufferTilePropertiesQCOM                                  = REINTERPRET_CAST(PFN_vkGetFramebufferTilePropertiesQCOM                                  , loader(device, "vkGetFramebufferTilePropertiesQCOM"                              )) ;
    functions[0].GetDynamicRenderingTilePropertiesQCOM                             = REINTERPRET_CAST(PFN_vkGetDynamicRenderingTilePropertiesQCOM                             , loader(device, "vkGetDynamicRenderingTilePropertiesQCOM"                         )) ;
    /* VK_NV_low_latency2 spec_version 2 */                                          
    functions[0].SetLatencySleepModeNV                                             = REINTERPRET_CAST(PFN_vkSetLatencySleepModeNV                                             , loader(device, "vkSetLatencySleepModeNV"                                         )) ;
    functions[0].LatencySleepNV                                                    = REINTERPRET_CAST(PFN_vkLatencySleepNV                                                    , loader(device, "vkLatencySleepNV"                                                )) ;
    functions[0].SetLatencyMarkerNV                                                = REINTERPRET_CAST(PFN_vkSetLatencyMarkerNV                                                , loader(device, "vkSetLatencyMarkerNV"                                            )) ;
    functions[0].GetLatencyTimingsNV                                               = REINTERPRET_CAST(PFN_vkGetLatencyTimingsNV                                               , loader(device, "vkGetLatencyTimingsNV"                                           )) ;
    functions[0].QueueNotifyOutOfBandNV                                            = REINTERPRET_CAST(PFN_vkQueueNotifyOutOfBandNV                                            , loader(device, "vkQueueNotifyOutOfBandNV"                                        )) ;
    /* VK_EXT_attachment_feedback_loop_dynamic_state spec_version 1 */               
    functions[0].CmdSetAttachmentFeedbackLoopEnableEXT                             = REINTERPRET_CAST(PFN_vkCmdSetAttachmentFeedbackLoopEnableEXT                             , loader(device, "vkCmdSetAttachmentFeedbackLoopEnableEXT"                         )) ;
    /* VK_KHR_acceleration_structure spec_version 13 */                              
    functions[0].CreateAccelerationStructureKHR                                    = REINTERPRET_CAST(PFN_vkCreateAccelerationStructureKHR                                    , loader(device, "vkCreateAccelerationStructureKHR"                                )) ;
    functions[0].DestroyAccelerationStructureKHR                                   = REINTERPRET_CAST(PFN_vkDestroyAccelerationStructureKHR                                   , loader(device, "vkDestroyAccelerationStructureKHR"                               )) ;
    functions[0].CmdBuildAccelerationStructuresKHR                                 = REINTERPRET_CAST(PFN_vkCmdBuildAccelerationStructuresKHR                                 , loader(device, "vkCmdBuildAccelerationStructuresKHR"                             )) ;
    functions[0].CmdBuildAccelerationStructuresIndirectKHR                         = REINTERPRET_CAST(PFN_vkCmdBuildAccelerationStructuresIndirectKHR                         , loader(device, "vkCmdBuildAccelerationStructuresIndirectKHR"                     )) ;
    functions[0].BuildAccelerationStructuresKHR                                    = REINTERPRET_CAST(PFN_vkBuildAccelerationStructuresKHR                                    , loader(device, "vkBuildAccelerationStructuresKHR"                                )) ;
    functions[0].CopyAccelerationStructureKHR                                      = REINTERPRET_CAST(PFN_vkCopyAccelerationStructureKHR                                      , loader(device, "vkCopyAccelerationStructureKHR"                                  )) ;
    functions[0].CopyAccelerationStructureToMemoryKHR                              = REINTERPRET_CAST(PFN_vkCopyAccelerationStructureToMemoryKHR                              , loader(device, "vkCopyAccelerationStructureToMemoryKHR"                          )) ;
    functions[0].CopyMemoryToAccelerationStructureKHR                              = REINTERPRET_CAST(PFN_vkCopyMemoryToAccelerationStructureKHR                              , loader(device, "vkCopyMemoryToAccelerationStructureKHR"                          )) ;
    functions[0].WriteAccelerationStructuresPropertiesKHR                          = REINTERPRET_CAST(PFN_vkWriteAccelerationStructuresPropertiesKHR                          , loader(device, "vkWriteAccelerationStructuresPropertiesKHR"                      )) ;
    functions[0].CmdCopyAccelerationStructureKHR                                   = REINTERPRET_CAST(PFN_vkCmdCopyAccelerationStructureKHR                                   , loader(device, "vkCmdCopyAccelerationStructureKHR"                               )) ;
    functions[0].CmdCopyAccelerationStructureToMemoryKHR                           = REINTERPRET_CAST(PFN_vkCmdCopyAccelerationStructureToMemoryKHR                           , loader(device, "vkCmdCopyAccelerationStructureToMemoryKHR"                       )) ;
    functions[0].CmdCopyMemoryToAccelerationStructureKHR                           = REINTERPRET_CAST(PFN_vkCmdCopyMemoryToAccelerationStructureKHR                           , loader(device, "vkCmdCopyMemoryToAccelerationStructureKHR"                       )) ;
    functions[0].GetAccelerationStructureDeviceAddressKHR                          = REINTERPRET_CAST(PFN_vkGetAccelerationStructureDeviceAddressKHR                          , loader(device, "vkGetAccelerationStructureDeviceAddressKHR"                      )) ;
    functions[0].CmdWriteAccelerationStructuresPropertiesKHR                       = REINTERPRET_CAST(PFN_vkCmdWriteAccelerationStructuresPropertiesKHR                       , loader(device, "vkCmdWriteAccelerationStructuresPropertiesKHR"                   )) ;
    functions[0].GetDeviceAccelerationStructureCompatibilityKHR                    = REINTERPRET_CAST(PFN_vkGetDeviceAccelerationStructureCompatibilityKHR                    , loader(device, "vkGetDeviceAccelerationStructureCompatibilityKHR"                )) ;
    functions[0].GetAccelerationStructureBuildSizesKHR                             = REINTERPRET_CAST(PFN_vkGetAccelerationStructureBuildSizesKHR                             , loader(device, "vkGetAccelerationStructureBuildSizesKHR"                         )) ;
    /* VK_KHR_ray_tracing_pipeline spec_version 1 */                                 
    functions[0].CmdTraceRaysKHR                                                   = REINTERPRET_CAST(PFN_vkCmdTraceRaysKHR                                                   , loader(device, "vkCmdTraceRaysKHR"                                               )) ;
    functions[0].CreateRayTracingPipelinesKHR                                      = REINTERPRET_CAST(PFN_vkCreateRayTracingPipelinesKHR                                      , loader(device, "vkCreateRayTracingPipelinesKHR"                                  )) ;
    functions[0].GetRayTracingCaptureReplayShaderGroupHandlesKHR                   = REINTERPRET_CAST(PFN_vkGetRayTracingCaptureReplayShaderGroupHandlesKHR                   , loader(device, "vkGetRayTracingCaptureReplayShaderGroupHandlesKHR"               )) ;
    functions[0].CmdTraceRaysIndirectKHR                                           = REINTERPRET_CAST(PFN_vkCmdTraceRaysIndirectKHR                                           , loader(device, "vkCmdTraceRaysIndirectKHR"                                       )) ;
    functions[0].GetRayTracingShaderGroupStackSizeKHR                              = REINTERPRET_CAST(PFN_vkGetRayTracingShaderGroupStackSizeKHR                              , loader(device, "vkGetRayTracingShaderGroupStackSizeKHR"                          )) ;
    functions[0].CmdSetRayTracingPipelineStackSizeKHR                              = REINTERPRET_CAST(PFN_vkCmdSetRayTracingPipelineStackSizeKHR                              , loader(device, "vkCmdSetRayTracingPipelineStackSizeKHR"                          )) ;
    /* VK_EXT_mesh_shader spec_version 1 */                                          
    functions[0].CmdDrawMeshTasksEXT                                               = REINTERPRET_CAST(PFN_vkCmdDrawMeshTasksEXT                                               , loader(device, "vkCmdDrawMeshTasksEXT"                                           )) ;
    functions[0].CmdDrawMeshTasksIndirectEXT                                       = REINTERPRET_CAST(PFN_vkCmdDrawMeshTasksIndirectEXT                                       , loader(device, "vkCmdDrawMeshTasksIndirectEXT"                                   )) ;
    functions[0].CmdDrawMeshTasksIndirectCountEXT                                  = REINTERPRET_CAST(PFN_vkCmdDrawMeshTasksIndirectCountEXT                                  , loader(device, "vkCmdDrawMeshTasksIndirectCountEXT"                              )) ;
    /* VK_ANDROID_external_memory_android_hardware_buffer spec_version 5 */          
    functions[0].GetAndroidHardwareBufferPropertiesANDROID                         = REINTERPRET_CAST(PFN_vkGetAndroidHardwareBufferPropertiesANDROID                         , loader(device, "vkGetAndroidHardwareBufferPropertiesANDROID"                     )) ;
    functions[0].GetMemoryAndroidHardwareBufferANDROID                             = REINTERPRET_CAST(PFN_vkGetMemoryAndroidHardwareBufferANDROID                             , loader(device, "vkGetMemoryAndroidHardwareBufferANDROID"                         )) ;
    /* VK_FUCHSIA_external_memory spec_version 1 */                                  
    functions[0].GetMemoryZirconHandleFUCHSIA                                      = REINTERPRET_CAST(PFN_vkGetMemoryZirconHandleFUCHSIA                                      , loader(device, "vkGetMemoryZirconHandleFUCHSIA"                                  )) ;
    functions[0].GetMemoryZirconHandlePropertiesFUCHSIA                            = REINTERPRET_CAST(PFN_vkGetMemoryZirconHandlePropertiesFUCHSIA                            , loader(device, "vkGetMemoryZirconHandlePropertiesFUCHSIA"                        )) ;
    /* VK_FUCHSIA_external_semaphore spec_version 1 */                               
    functions[0].ImportSemaphoreZirconHandleFUCHSIA                                = REINTERPRET_CAST(PFN_vkImportSemaphoreZirconHandleFUCHSIA                                , loader(device, "vkImportSemaphoreZirconHandleFUCHSIA"                            )) ;
    functions[0].GetSemaphoreZirconHandleFUCHSIA                                   = REINTERPRET_CAST(PFN_vkGetSemaphoreZirconHandleFUCHSIA                                   , loader(device, "vkGetSemaphoreZirconHandleFUCHSIA"                               )) ;
    /* VK_FUCHSIA_buffer_collection spec_version 2 */                                
    functions[0].CreateBufferCollectionFUCHSIA                                     = REINTERPRET_CAST(PFN_vkCreateBufferCollectionFUCHSIA                                     , loader(device, "vkCreateBufferCollectionFUCHSIA"                                 )) ;
    functions[0].SetBufferCollectionImageConstraintsFUCHSIA                        = REINTERPRET_CAST(PFN_vkSetBufferCollectionImageConstraintsFUCHSIA                        , loader(device, "vkSetBufferCollectionImageConstraintsFUCHSIA"                    )) ;
    functions[0].SetBufferCollectionBufferConstraintsFUCHSIA                       = REINTERPRET_CAST(PFN_vkSetBufferCollectionBufferConstraintsFUCHSIA                       , loader(device, "vkSetBufferCollectionBufferConstraintsFUCHSIA"                   )) ;
    functions[0].DestroyBufferCollectionFUCHSIA                                    = REINTERPRET_CAST(PFN_vkDestroyBufferCollectionFUCHSIA                                    , loader(device, "vkDestroyBufferCollectionFUCHSIA"                                )) ;
    functions[0].GetBufferCollectionPropertiesFUCHSIA                              = REINTERPRET_CAST(PFN_vkGetBufferCollectionPropertiesFUCHSIA                              , loader(device, "vkGetBufferCollectionPropertiesFUCHSIA"                          )) ;
    /* VK_EXT_metal_objects spec_version 2 */                                        
    functions[0].ExportMetalObjectsEXT                                             = REINTERPRET_CAST(PFN_vkExportMetalObjectsEXT                                             , loader(device, "vkExportMetalObjectsEXT"                                         )) ;
    /* VK_KHR_external_memory_win32 spec_version 1 */                                
    functions[0].GetMemoryWin32HandleKHR                                           = REINTERPRET_CAST(PFN_vkGetMemoryWin32HandleKHR                                           , loader(device, "vkGetMemoryWin32HandleKHR"                                       )) ;
    functions[0].GetMemoryWin32HandlePropertiesKHR                                 = REINTERPRET_CAST(PFN_vkGetMemoryWin32HandlePropertiesKHR                                 , loader(device, "vkGetMemoryWin32HandlePropertiesKHR"                             )) ;
    /* VK_KHR_external_semaphore_win32 spec_version 1 */                             
    functions[0].ImportSemaphoreWin32HandleKHR                                     = REINTERPRET_CAST(PFN_vkImportSemaphoreWin32HandleKHR                                     , loader(device, "vkImportSemaphoreWin32HandleKHR"                                 )) ;
    functions[0].GetSemaphoreWin32HandleKHR                                        = REINTERPRET_CAST(PFN_vkGetSemaphoreWin32HandleKHR                                        , loader(device, "vkGetSemaphoreWin32HandleKHR"                                    )) ;
    /* VK_KHR_external_fence_win32 spec_version 1 */                                 
    functions[0].ImportFenceWin32HandleKHR                                         = REINTERPRET_CAST(PFN_vkImportFenceWin32HandleKHR                                         , loader(device, "vkImportFenceWin32HandleKHR"                                     )) ;
    functions[0].GetFenceWin32HandleKHR                                            = REINTERPRET_CAST(PFN_vkGetFenceWin32HandleKHR                                            , loader(device, "vkGetFenceWin32HandleKHR"                                        )) ;
    /* VK_NV_external_memory_win32 spec_version 1 */                                 
    functions[0].GetMemoryWin32HandleNV                                            = REINTERPRET_CAST(PFN_vkGetMemoryWin32HandleNV                                            , loader(device, "vkGetMemoryWin32HandleNV"                                        )) ;
    /* VK_EXT_full_screen_exclusive spec_version 4 */                                
    functions[0].AcquireFullScreenExclusiveModeEXT                                 = REINTERPRET_CAST(PFN_vkAcquireFullScreenExclusiveModeEXT                                 , loader(device, "vkAcquireFullScreenExclusiveModeEXT"                             )) ;
    functions[0].ReleaseFullScreenExclusiveModeEXT                                 = REINTERPRET_CAST(PFN_vkReleaseFullScreenExclusiveModeEXT                                 , loader(device, "vkReleaseFullScreenExclusiveModeEXT"                             )) ;
    functions[0].GetDeviceGroupSurfacePresentModes2EXT                             = REINTERPRET_CAST(PFN_vkGetDeviceGroupSurfacePresentModes2EXT                             , loader(device, "vkGetDeviceGroupSurfacePresentModes2EXT"                         )) ;
    /* VK_QNX_external_memory_screen_buffer spec_version 1 */                        
    functions[0].GetScreenBufferPropertiesQNX                                      = REINTERPRET_CAST(PFN_vkGetScreenBufferPropertiesQNX                                      , loader(device, "vkGetScreenBufferPropertiesQNX"                                  )) ;
    /* VK_AMDX_shader_enqueue spec_version 2 */
    functions[0].CreateExecutionGraphPipelinesAMDX                                 = REINTERPRET_CAST(PFN_vkCreateExecutionGraphPipelinesAMDX                                 , loader(device, "vkCreateExecutionGraphPipelinesAMDX"                             )) ;
    functions[0].GetExecutionGraphPipelineScratchSizeAMDX                          = REINTERPRET_CAST(PFN_vkGetExecutionGraphPipelineScratchSizeAMDX                          , loader(device, "vkGetExecutionGraphPipelineScratchSizeAMDX"                      )) ;
    functions[0].GetExecutionGraphPipelineNodeIndexAMDX                            = REINTERPRET_CAST(PFN_vkGetExecutionGraphPipelineNodeIndexAMDX                            , loader(device, "vkGetExecutionGraphPipelineNodeIndexAMDX"                        )) ;
    functions[0].CmdInitializeGraphScratchMemoryAMDX                               = REINTERPRET_CAST(PFN_vkCmdInitializeGraphScratchMemoryAMDX                               , loader(device, "vkCmdInitializeGraphScratchMemoryAMDX"                           )) ;
    functions[0].CmdDispatchGraphAMDX                                              = REINTERPRET_CAST(PFN_vkCmdDispatchGraphAMDX                                              , loader(device, "vkCmdDispatchGraphAMDX"                                          )) ;
    functions[0].CmdDispatchGraphIndirectAMDX                                      = REINTERPRET_CAST(PFN_vkCmdDispatchGraphIndirectAMDX                                      , loader(device, "vkCmdDispatchGraphIndirectAMDX"                                  )) ;
    functions[0].CmdDispatchGraphIndirectCountAMDX                                 = REINTERPRET_CAST(PFN_vkCmdDispatchGraphIndirectCountAMDX                                 , loader(device, "vkCmdDispatchGraphIndirectCountAMDX"                             )) ;
        /* Additions from 1.3.284 to 1.4.309: */
    /* to VK_NVX_image_view_handle spec_version 3 */
    functions[0].GetImageViewHandle64NVX                                           = REINTERPRET_CAST(PFN_vkGetImageViewHandle64NVX                                           , loader(device, "vkGetImageViewHandle64NVX"                                       )) ;
    /* to VK_EXT_shader_object spec_version 1 */
    functions[0].CmdSetDepthClampRangeEXT                                          = REINTERPRET_CAST(PFN_vkCmdSetDepthClampRangeEXT                                          , loader(device, "vkCmdSetDepthClampRangeEXT"                                      )) ;
    /* VK_VERSION_1_4 */
    functions[0].CmdSetLineStipple                                                 = REINTERPRET_CAST(PFN_vkCmdSetLineStipple                                                 , loader(device, "vkCmdSetLineStipple"                                             )) ;
    functions[0].MapMemory2                                                        = REINTERPRET_CAST(PFN_vkMapMemory2                                                        , loader(device, "vkMapMemory2"                                                    )) ;
    functions[0].UnmapMemory2                                                      = REINTERPRET_CAST(PFN_vkUnmapMemory2                                                      , loader(device, "vkUnmapMemory2"                                                  )) ;
    functions[0].CmdBindIndexBuffer2                                               = REINTERPRET_CAST(PFN_vkCmdBindIndexBuffer2                                               , loader(device, "vkCmdBindIndexBuffer2"                                           )) ;
    functions[0].GetRenderingAreaGranularity                                       = REINTERPRET_CAST(PFN_vkGetRenderingAreaGranularity                                       , loader(device, "vkGetRenderingAreaGranularity"                                   )) ;
    functions[0].GetDeviceImageSubresourceLayout                                   = REINTERPRET_CAST(PFN_vkGetDeviceImageSubresourceLayout                                   , loader(device, "vkGetDeviceImageSubresourceLayout"                               )) ;
    functions[0].GetImageSubresourceLayout2                                        = REINTERPRET_CAST(PFN_vkGetImageSubresourceLayout2                                        , loader(device, "vkGetImageSubresourceLayout2"                                    )) ;
    functions[0].CmdPushDescriptorSet                                              = REINTERPRET_CAST(PFN_vkCmdPushDescriptorSet                                              , loader(device, "vkCmdPushDescriptorSet"                                          )) ;
    functions[0].CmdPushDescriptorSetWithTemplate                                  = REINTERPRET_CAST(PFN_vkCmdPushDescriptorSetWithTemplate                                  , loader(device, "vkCmdPushDescriptorSetWithTemplate"                              )) ;
    functions[0].CmdSetRenderingAttachmentLocations                                = REINTERPRET_CAST(PFN_vkCmdSetRenderingAttachmentLocations                                , loader(device, "vkCmdSetRenderingAttachmentLocations"                            )) ;
    functions[0].CmdSetRenderingInputAttachmentIndices                             = REINTERPRET_CAST(PFN_vkCmdSetRenderingInputAttachmentIndices                             , loader(device, "vkCmdSetRenderingInputAttachmentIndices"                         )) ;
    functions[0].CmdBindDescriptorSets2                                            = REINTERPRET_CAST(PFN_vkCmdBindDescriptorSets2                                            , loader(device, "vkCmdBindDescriptorSets2"                                        )) ;
    functions[0].CmdPushConstants2                                                 = REINTERPRET_CAST(PFN_vkCmdPushConstants2                                                 , loader(device, "vkCmdPushConstants2"                                             )) ;
    functions[0].CmdPushDescriptorSet2                                             = REINTERPRET_CAST(PFN_vkCmdPushDescriptorSet2                                             , loader(device, "vkCmdPushDescriptorSet2"                                         )) ;
    functions[0].CmdPushDescriptorSetWithTemplate2                                 = REINTERPRET_CAST(PFN_vkCmdPushDescriptorSetWithTemplate2                                 , loader(device, "vkCmdPushDescriptorSetWithTemplate2"                             )) ;
    functions[0].CopyMemoryToImage                                                 = REINTERPRET_CAST(PFN_vkCopyMemoryToImage                                                 , loader(device, "vkCopyMemoryToImage"                                             )) ;
    functions[0].CopyImageToMemory                                                 = REINTERPRET_CAST(PFN_vkCopyImageToMemory                                                 , loader(device, "vkCopyImageToMemory"                                             )) ;
    functions[0].CopyImageToImage                                                  = REINTERPRET_CAST(PFN_vkCopyImageToImage                                                  , loader(device, "vkCopyImageToImage"                                              )) ;
    functions[0].TransitionImageLayout                                             = REINTERPRET_CAST(PFN_vkTransitionImageLayout                                             , loader(device, "vkTransitionImageLayout"                                         )) ;
    /* VK_KHR_pipeline_binary spec_version 1 */
    functions[0].CreatePipelineBinariesKHR                                         = REINTERPRET_CAST(PFN_vkCreatePipelineBinariesKHR                                         , loader(device, "vkCreatePipelineBinariesKHR"                                     )) ;
    functions[0].DestroyPipelineBinaryKHR                                          = REINTERPRET_CAST(PFN_vkDestroyPipelineBinaryKHR                                          , loader(device, "vkDestroyPipelineBinaryKHR"                                      )) ;
    functions[0].GetPipelineKeyKHR                                                 = REINTERPRET_CAST(PFN_vkGetPipelineKeyKHR                                                 , loader(device, "vkGetPipelineKeyKHR"                                             )) ;
    functions[0].GetPipelineBinaryDataKHR                                          = REINTERPRET_CAST(PFN_vkGetPipelineBinaryDataKHR                                          , loader(device, "vkGetPipelineBinaryDataKHR"                                      )) ;
    functions[0].ReleaseCapturedPipelineDataKHR                                    = REINTERPRET_CAST(PFN_vkReleaseCapturedPipelineDataKHR                                    , loader(device, "vkReleaseCapturedPipelineDataKHR"                                )) ;
    /* VK_AMD_anti_lag spec_version 1 */
    functions[0].AntiLagUpdateAMD                                                  = REINTERPRET_CAST(PFN_vkAntiLagUpdateAMD                                                  , loader(device, "vkAntiLagUpdateAMD"                                              )) ;
    /* VK_NV_cooperative_vector spec_version 4 */
    functions[0].ConvertCooperativeVectorMatrixNV                                  = REINTERPRET_CAST(PFN_vkConvertCooperativeVectorMatrixNV                                  , loader(device, "vkConvertCooperativeVectorMatrixNV"                              )) ;
    functions[0].CmdConvertCooperativeVectorMatrixNV                               = REINTERPRET_CAST(PFN_vkCmdConvertCooperativeVectorMatrixNV                               , loader(device, "vkCmdConvertCooperativeVectorMatrixNV"                           )) ;
    /* VK_NV_cluster_acceleration_structure spec_version 2 */
    functions[0].GetClusterAccelerationStructureBuildSizesNV                       = REINTERPRET_CAST(PFN_vkGetClusterAccelerationStructureBuildSizesNV                       , loader(device, "vkGetClusterAccelerationStructureBuildSizesNV"                   )) ;
    functions[0].CmdBuildClusterAccelerationStructureIndirectNV                    = REINTERPRET_CAST(PFN_vkCmdBuildClusterAccelerationStructureIndirectNV                    , loader(device, "vkCmdBuildClusterAccelerationStructureIndirectNV"                )) ;
    /* VK_NV_partitioned_acceleration_structure spec_version 1 */
    functions[0].GetPartitionedAccelerationStructuresBuildSizesNV                  = REINTERPRET_CAST(PFN_vkGetPartitionedAccelerationStructuresBuildSizesNV                  , loader(device, "vkGetPartitionedAccelerationStructuresBuildSizesNV"              )) ;
    functions[0].CmdBuildPartitionedAccelerationStructuresNV                       = REINTERPRET_CAST(PFN_vkCmdBuildPartitionedAccelerationStructuresNV                       , loader(device, "vkCmdBuildPartitionedAccelerationStructuresNV"                   )) ;
    /* VK_EXT_device_generated_commands spec_version 1 */
    functions[0].GetGeneratedCommandsMemoryRequirementsEXT                         = REINTERPRET_CAST(PFN_vkGetGeneratedCommandsMemoryRequirementsEXT                         , loader(device, "vkGetGeneratedCommandsMemoryRequirementsEXT"                     )) ;
    functions[0].CmdPreprocessGeneratedCommandsEXT                                 = REINTERPRET_CAST(PFN_vkCmdPreprocessGeneratedCommandsEXT                                 , loader(device, "vkCmdPreprocessGeneratedCommandsEXT"                             )) ;
    functions[0].CmdExecuteGeneratedCommandsEXT                                    = REINTERPRET_CAST(PFN_vkCmdExecuteGeneratedCommandsEXT                                    , loader(device, "vkCmdExecuteGeneratedCommandsEXT"                                )) ;
    functions[0].CreateIndirectCommandsLayoutEXT                                   = REINTERPRET_CAST(PFN_vkCreateIndirectCommandsLayoutEXT                                   , loader(device, "vkCreateIndirectCommandsLayoutEXT"                               )) ;
    functions[0].DestroyIndirectCommandsLayoutEXT                                  = REINTERPRET_CAST(PFN_vkDestroyIndirectCommandsLayoutEXT                                  , loader(device, "vkDestroyIndirectCommandsLayoutEXT"                              )) ;
    functions[0].CreateIndirectExecutionSetEXT                                     = REINTERPRET_CAST(PFN_vkCreateIndirectExecutionSetEXT                                     , loader(device, "vkCreateIndirectExecutionSetEXT"                                 )) ;
    functions[0].DestroyIndirectExecutionSetEXT                                    = REINTERPRET_CAST(PFN_vkDestroyIndirectExecutionSetEXT                                    , loader(device, "vkDestroyIndirectExecutionSetEXT"                                )) ;
    functions[0].UpdateIndirectExecutionSetPipelineEXT                             = REINTERPRET_CAST(PFN_vkUpdateIndirectExecutionSetPipelineEXT                             , loader(device, "vkUpdateIndirectExecutionSetPipelineEXT"                         )) ;
    functions[0].UpdateIndirectExecutionSetShaderEXT                               = REINTERPRET_CAST(PFN_vkUpdateIndirectExecutionSetShaderEXT                               , loader(device, "vkUpdateIndirectExecutionSetShaderEXT"                           )) ;
    /* VK_EXT_external_memory_metal spec_version 1 */
    functions[0].GetMemoryMetalHandleEXT                                           = REINTERPRET_CAST(PFN_vkGetMemoryMetalHandleEXT                                           , loader(device, "vkGetMemoryMetalHandleEXT"                                       )) ;
    functions[0].GetMemoryMetalHandlePropertiesEXT                                 = REINTERPRET_CAST(PFN_vkGetMemoryMetalHandlePropertiesEXT                                 , loader(device, "vkGetMemoryMetalHandlePropertiesEXT"                             )) ;
}

#ifndef VKAD_NO_GLOBAL_SYMBOLS
/* global functions */
        /* VK_VERSION_1_0 */
#define vkEnumerateInstanceExtensionProperties                              VKAD_USER_GLOBAL.EnumerateInstanceExtensionProperties                           
#define vkEnumerateInstanceLayerProperties                                  VKAD_USER_GLOBAL.EnumerateInstanceLayerProperties                               
#define vkCreateInstance                                                    VKAD_USER_GLOBAL.CreateInstance                                                 
        /* VK_VERSION_1_1 */                                                                                                                 
#define vkEnumerateInstanceVersion                                          VKAD_USER_GLOBAL.EnumerateInstanceVersion                                      


/* instance functions */                                                                                              
        /* VK_VERSION_1_0 */                                                                                                                    
#define vkDestroyInstance                                                   VKAD_USER_INSTANCE.DestroyInstance                                         
#define vkEnumeratePhysicalDevices                                          VKAD_USER_INSTANCE.EnumeratePhysicalDevices                                
#define vkGetPhysicalDeviceFeatures                                         VKAD_USER_INSTANCE.GetPhysicalDeviceFeatures                               
#define vkGetPhysicalDeviceFormatProperties                                 VKAD_USER_INSTANCE.GetPhysicalDeviceFormatProperties                       
#define vkGetPhysicalDeviceImageFormatProperties                            VKAD_USER_INSTANCE.GetPhysicalDeviceImageFormatProperties                  
#define vkGetPhysicalDeviceProperties                                       VKAD_USER_INSTANCE.GetPhysicalDeviceProperties                             
#define vkGetPhysicalDeviceQueueFamilyProperties                            VKAD_USER_INSTANCE.GetPhysicalDeviceQueueFamilyProperties                  
#define vkGetPhysicalDeviceMemoryProperties                                 VKAD_USER_INSTANCE.GetPhysicalDeviceMemoryProperties                       
#define vkEnumerateDeviceExtensionProperties                                VKAD_USER_INSTANCE.EnumerateDeviceExtensionProperties                      
#define vkEnumerateDeviceLayerProperties                                    VKAD_USER_INSTANCE.EnumerateDeviceLayerProperties                          
#define vkGetPhysicalDeviceSparseImageFormatProperties                      VKAD_USER_INSTANCE.GetPhysicalDeviceSparseImageFormatProperties            
#define vkCreateDevice                                                      VKAD_USER_INSTANCE.CreateDevice                                            
#define vkGetDeviceProcAddr                                                 VKAD_USER_INSTANCE.GetDeviceProcAddr                                       
        /* VK_VERSION_1_1 */                                                                                 
#define vkEnumeratePhysicalDeviceGroups                                     VKAD_USER_INSTANCE.EnumeratePhysicalDeviceGroups                           
#define vkGetPhysicalDeviceFeatures2                                        VKAD_USER_INSTANCE.GetPhysicalDeviceFeatures2                              
#define vkGetPhysicalDeviceProperties2                                      VKAD_USER_INSTANCE.GetPhysicalDeviceProperties2                            
#define vkGetPhysicalDeviceFormatProperties2                                VKAD_USER_INSTANCE.GetPhysicalDeviceFormatProperties2                      
#define vkGetPhysicalDeviceImageFormatProperties2                           VKAD_USER_INSTANCE.GetPhysicalDeviceImageFormatProperties2                 
#define vkGetPhysicalDeviceQueueFamilyProperties2                           VKAD_USER_INSTANCE.GetPhysicalDeviceQueueFamilyProperties2                 
#define vkGetPhysicalDeviceMemoryProperties2                                VKAD_USER_INSTANCE.GetPhysicalDeviceMemoryProperties2                      
#define vkGetPhysicalDeviceSparseImageFormatProperties2                     VKAD_USER_INSTANCE.GetPhysicalDeviceSparseImageFormatProperties2           
#define vkGetPhysicalDeviceExternalBufferProperties                         VKAD_USER_INSTANCE.GetPhysicalDeviceExternalBufferProperties               
#define vkGetPhysicalDeviceExternalFenceProperties                          VKAD_USER_INSTANCE.GetPhysicalDeviceExternalFenceProperties                
#define vkGetPhysicalDeviceExternalSemaphoreProperties                      VKAD_USER_INSTANCE.GetPhysicalDeviceExternalSemaphoreProperties            
        /* VK_VERSION_1_3 */                                                
#define vkGetPhysicalDeviceToolProperties                                   VKAD_USER_INSTANCE.GetPhysicalDeviceToolProperties                         
        /* VK_KHR_surface spec_version 25  */                               
#define vkDestroySurfaceKHR                                                 VKAD_USER_INSTANCE.DestroySurfaceKHR                                       
#define vkGetPhysicalDeviceSurfaceSupportKHR                                VKAD_USER_INSTANCE.GetPhysicalDeviceSurfaceSupportKHR                      
#define vkGetPhysicalDeviceSurfaceCapabilitiesKHR                           VKAD_USER_INSTANCE.GetPhysicalDeviceSurfaceCapabilitiesKHR                 
#define vkGetPhysicalDeviceSurfaceFormatsKHR                                VKAD_USER_INSTANCE.GetPhysicalDeviceSurfaceFormatsKHR                      
#define vkGetPhysicalDeviceSurfacePresentModesKHR                           VKAD_USER_INSTANCE.GetPhysicalDeviceSurfacePresentModesKHR                      
        /* VK_KHR_swapchain spec_version 70  */                             
#define vkGetPhysicalDevicePresentRectanglesKHR                             VKAD_USER_INSTANCE.GetPhysicalDevicePresentRectanglesKHR                        
        /* VK_KHR_display spec_version 23  */                               
#define vkGetPhysicalDeviceDisplayPropertiesKHR                             VKAD_USER_INSTANCE.GetPhysicalDeviceDisplayPropertiesKHR                        
#define vkGetPhysicalDeviceDisplayPlanePropertiesKHR                        VKAD_USER_INSTANCE.GetPhysicalDeviceDisplayPlanePropertiesKHR                   
#define vkGetDisplayPlaneSupportedDisplaysKHR                               VKAD_USER_INSTANCE.GetDisplayPlaneSupportedDisplaysKHR                          
#define vkGetDisplayModePropertiesKHR                                       VKAD_USER_INSTANCE.GetDisplayModePropertiesKHR                                  
#define vkCreateDisplayModeKHR                                              VKAD_USER_INSTANCE.CreateDisplayModeKHR                                         
#define vkGetDisplayPlaneCapabilitiesKHR                                    VKAD_USER_INSTANCE.GetDisplayPlaneCapabilitiesKHR                               
#define vkCreateDisplayPlaneSurfaceKHR                                      VKAD_USER_INSTANCE.CreateDisplayPlaneSurfaceKHR                                 
        /* VK_KHR_video_queue spec_version 8 */                             
#define vkGetPhysicalDeviceVideoCapabilitiesKHR                             VKAD_USER_INSTANCE.GetPhysicalDeviceVideoCapabilitiesKHR                        
#define vkGetPhysicalDeviceVideoFormatPropertiesKHR                         VKAD_USER_INSTANCE.GetPhysicalDeviceVideoFormatPropertiesKHR                    
        /* VK_KHR_get_physical_device_properties2 spec_version 2 */         
#define vkGetPhysicalDeviceFeatures2KHR                                     VKAD_USER_INSTANCE.GetPhysicalDeviceFeatures2KHR                                
#define vkGetPhysicalDeviceProperties2KHR                                   VKAD_USER_INSTANCE.GetPhysicalDeviceProperties2KHR                              
#define vkGetPhysicalDeviceFormatProperties2KHR                             VKAD_USER_INSTANCE.GetPhysicalDeviceFormatProperties2KHR                        
#define vkGetPhysicalDeviceImageFormatProperties2KHR                        VKAD_USER_INSTANCE.GetPhysicalDeviceImageFormatProperties2KHR                   
#define vkGetPhysicalDeviceQueueFamilyProperties2KHR                        VKAD_USER_INSTANCE.GetPhysicalDeviceQueueFamilyProperties2KHR                   
#define vkGetPhysicalDeviceMemoryProperties2KHR                             VKAD_USER_INSTANCE.GetPhysicalDeviceMemoryProperties2KHR                        
#define vkGetPhysicalDeviceSparseImageFormatProperties2KHR                  VKAD_USER_INSTANCE.GetPhysicalDeviceSparseImageFormatProperties2KHR             
        /* VK_KHR_device_group_creation spec_version 1 */                   
#define vkEnumeratePhysicalDeviceGroupsKHR                                  VKAD_USER_INSTANCE.EnumeratePhysicalDeviceGroupsKHR                             
        /* VK_KHR_external_memory_capabilities spec_version 1 */            
#define vkGetPhysicalDeviceExternalBufferPropertiesKHR                      VKAD_USER_INSTANCE.GetPhysicalDeviceExternalBufferPropertiesKHR                 
        /* VK_KHR_external_semaphore_capabilities spec_version 1 */         
#define vkGetPhysicalDeviceExternalSemaphorePropertiesKHR                   VKAD_USER_INSTANCE.GetPhysicalDeviceExternalSemaphorePropertiesKHR              
        /* VK_KHR_external_fence_capabilities spec_version 1 */             
#define vkGetPhysicalDeviceExternalFencePropertiesKHR                       VKAD_USER_INSTANCE.GetPhysicalDeviceExternalFencePropertiesKHR                  
        /* VK_KHR_performance_query spec_version 1 */                       
#define vkEnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR     VKAD_USER_INSTANCE.EnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR
#define vkGetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR             VKAD_USER_INSTANCE.GetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR        
        /* VK_KHR_get_surface_capabilities2 spec_version 1 */               
#define vkGetPhysicalDeviceSurfaceCapabilities2KHR                          VKAD_USER_INSTANCE.GetPhysicalDeviceSurfaceCapabilities2KHR                
#define vkGetPhysicalDeviceSurfaceFormats2KHR                               VKAD_USER_INSTANCE.GetPhysicalDeviceSurfaceFormats2KHR                     
        /* VK_KHR_get_display_properties2 spec_version 1 */                 
#define vkGetPhysicalDeviceDisplayProperties2KHR                            VKAD_USER_INSTANCE.GetPhysicalDeviceDisplayProperties2KHR                  
#define vkGetPhysicalDeviceDisplayPlaneProperties2KHR                       VKAD_USER_INSTANCE.GetPhysicalDeviceDisplayPlaneProperties2KHR               
#define vkGetDisplayModeProperties2KHR                                      VKAD_USER_INSTANCE.GetDisplayModeProperties2KHR                            
#define vkGetDisplayPlaneCapabilities2KHR                                   VKAD_USER_INSTANCE.GetDisplayPlaneCapabilities2KHR                         
        /* VK_KHR_fragment_shading_rate spec_version 2 */                   
#define vkGetPhysicalDeviceFragmentShadingRatesKHR                          VKAD_USER_INSTANCE.GetPhysicalDeviceFragmentShadingRatesKHR                
        /* VK_KHR_video_encode_queue spec_version 12 */                     
#define vkGetPhysicalDeviceVideoEncodeQualityLevelPropertiesKHR             VKAD_USER_INSTANCE.GetPhysicalDeviceVideoEncodeQualityLevelPropertiesKHR   
        /* VK_KHR_cooperative_matrix spec_version 2 */                      
#define vkGetPhysicalDeviceCooperativeMatrixPropertiesKHR                   VKAD_USER_INSTANCE.GetPhysicalDeviceCooperativeMatrixPropertiesKHR         
        /* VK_KHR_calibrated_timestamps spec_version 1 */                   
#define vkGetPhysicalDeviceCalibrateableTimeDomainsKHR                      VKAD_USER_INSTANCE.GetPhysicalDeviceCalibrateableTimeDomainsKHR            
        /* VK_EXT_debug_report spec_version 10 */                           
#define vkCreateDebugReportCallbackEXT                                      VKAD_USER_INSTANCE.CreateDebugReportCallbackEXT                            
#define vkDestroyDebugReportCallbackEXT                                     VKAD_USER_INSTANCE.DestroyDebugReportCallbackEXT                           
#define vkDebugReportMessageEXT                                             VKAD_USER_INSTANCE.DebugReportMessageEXT                                   
        /* VK_NV_external_memory_capabilities spec_version 1 */             
#define vkGetPhysicalDeviceExternalImageFormatPropertiesNV                  VKAD_USER_INSTANCE.GetPhysicalDeviceExternalImageFormatPropertiesNV        
        /* VK_EXT_direct_mode_display spec_version 1 */                     
#define vkReleaseDisplayEXT                                                 VKAD_USER_INSTANCE.ReleaseDisplayEXT                                       
        /* VK_EXT_display_surface_counter spec_version 1 */                 
#define vkGetPhysicalDeviceSurfaceCapabilities2EXT                          VKAD_USER_INSTANCE.GetPhysicalDeviceSurfaceCapabilities2EXT                
        /* VK_EXT_debug_utils spec_version 2 */                             
#define vkCreateDebugUtilsMessengerEXT                                      VKAD_USER_INSTANCE.CreateDebugUtilsMessengerEXT                            
#define vkDestroyDebugUtilsMessengerEXT                                     VKAD_USER_INSTANCE.DestroyDebugUtilsMessengerEXT                           
#define vkSubmitDebugUtilsMessageEXT                                        VKAD_USER_INSTANCE.SubmitDebugUtilsMessageEXT                              
        /* VK_EXT_sample_locations spec_version 1 */                        
#define vkGetPhysicalDeviceMultisamplePropertiesEXT                         VKAD_USER_INSTANCE.GetPhysicalDeviceMultisamplePropertiesEXT               
        /* VK_EXT_calibrated_timestamps spec_version 2 */                   
#define vkGetPhysicalDeviceCalibrateableTimeDomainsEXT                      VKAD_USER_INSTANCE.GetPhysicalDeviceCalibrateableTimeDomainsEXT            
        /* VK_EXT_tooling_info spec_version 1 */                            
#define vkGetPhysicalDeviceToolPropertiesEXT                                VKAD_USER_INSTANCE.GetPhysicalDeviceToolPropertiesEXT                      
        /* VK_NV_cooperative_matrix spec_version 1 */                       
#define vkGetPhysicalDeviceCooperativeMatrixPropertiesNV                    VKAD_USER_INSTANCE.GetPhysicalDeviceCooperativeMatrixPropertiesNV          
        /* VK_NV_coverage_reduction_mode spec_version 1 */                  
#define vkGetPhysicalDeviceSupportedFramebufferMixedSamplesCombinationsNV   VKAD_USER_INSTANCE.GetPhysicalDeviceSupportedFramebufferMixedSamplesCombinationsNV
        /* VK_EXT_headless_surface spec_version 1 */                        
#define vkCreateHeadlessSurfaceEXT                                          VKAD_USER_INSTANCE.CreateHeadlessSurfaceEXT                                       
        /* VK_EXT_acquire_drm_display spec_version 1 */                     
#define vkAcquireDrmDisplayEXT                                              VKAD_USER_INSTANCE.AcquireDrmDisplayEXT                                  
#define vkGetDrmDisplayEXT                                                  VKAD_USER_INSTANCE.GetDrmDisplayEXT                                      
        /* VK_NV_optical_flow spec_version 1 */                             
#define vkGetPhysicalDeviceOpticalFlowImageFormatsNV                        VKAD_USER_INSTANCE.GetPhysicalDeviceOpticalFlowImageFormatsNV            
        /* VK_KHR_android_surface spec_version 6 */                         
#define vkCreateAndroidSurfaceKHR                                           VKAD_USER_INSTANCE.CreateAndroidSurfaceKHR                               
        /* VK_FUCHSIA_imagepipe_surface spec_version 1 */                   
#define vkCreateImagePipeSurfaceFUCHSIA                                     VKAD_USER_INSTANCE.CreateImagePipeSurfaceFUCHSIA                         
        /* VK_MVK_ios_surface spec_version 3 */                             
#define vkCreateIOSSurfaceMVK                                               VKAD_USER_INSTANCE.CreateIOSSurfaceMVK                                   
        /* VK_MVK_macos_surface spec_version 3 */                           
#define vkCreateMacOSSurfaceMVK                                             VKAD_USER_INSTANCE.CreateMacOSSurfaceMVK                                 
        /* VK_EXT_metal_surface spec_version 1 */                           
#define vkCreateMetalSurfaceEXT                                             VKAD_USER_INSTANCE.CreateMetalSurfaceEXT                                 
        /* VK_NN_vi_surface spec_version 1 */                               
#define vkCreateViSurfaceNN                                                 VKAD_USER_INSTANCE.CreateViSurfaceNN                                     
        /* VK_KHR_wayland_surface spec_version 6 */                         
#define vkCreateWaylandSurfaceKHR                                           VKAD_USER_INSTANCE.CreateWaylandSurfaceKHR                               
#define vkGetPhysicalDeviceWaylandPresentationSupportKHR                    VKAD_USER_INSTANCE.GetPhysicalDeviceWaylandPresentationSupportKHR        
        /* VK_KHR_win32_surface spec_version 6 */                           
#define vkCreateWin32SurfaceKHR                                             VKAD_USER_INSTANCE.CreateWin32SurfaceKHR                                 
#define vkGetPhysicalDeviceWin32PresentationSupportKHR                      VKAD_USER_INSTANCE.GetPhysicalDeviceWin32PresentationSupportKHR          
        /* VK_EXT_full_screen_exclusive spec_version 4 */                   
#define vkGetPhysicalDeviceSurfacePresentModes2EXT                          VKAD_USER_INSTANCE.GetPhysicalDeviceSurfacePresentModes2EXT              
        /* VK_NV_acquire_winrt_display spec_version 1 */                    
#define vkAcquireWinrtDisplayNV                                             VKAD_USER_INSTANCE.AcquireWinrtDisplayNV                                 
#define vkGetWinrtDisplayNV                                                 VKAD_USER_INSTANCE.GetWinrtDisplayNV                                     
        /* VK_KHR_xcb_surface spec_version 6 */                             
#define vkCreateXcbSurfaceKHR                                               VKAD_USER_INSTANCE.CreateXcbSurfaceKHR                                   
#define vkGetPhysicalDeviceXcbPresentationSupportKHR                        VKAD_USER_INSTANCE.GetPhysicalDeviceXcbPresentationSupportKHR            
        /* VK_KHR_xlib_surface spec_version 6 */                            
#define vkCreateXlibSurfaceKHR                                              VKAD_USER_INSTANCE.CreateXlibSurfaceKHR                                  
#define vkGetPhysicalDeviceXlibPresentationSupportKHR                       VKAD_USER_INSTANCE.GetPhysicalDeviceXlibPresentationSupportKHR           
        /* VK_EXT_directfb_surface spec_version 1 */                        
#define vkCreateDirectFBSurfaceEXT                                          VKAD_USER_INSTANCE.CreateDirectFBSurfaceEXT                              
#define vkGetPhysicalDeviceDirectFBPresentationSupportEXT                   VKAD_USER_INSTANCE.GetPhysicalDeviceDirectFBPresentationSupportEXT       
        /* VK_EXT_acquire_xlib_display spec_version 1 */                    
#define vkAcquireXlibDisplayEXT                                             VKAD_USER_INSTANCE.AcquireXlibDisplayEXT                                 
#define vkGetRandROutputDisplayEXT                                          VKAD_USER_INSTANCE.GetRandROutputDisplayEXT                              
        /* VK_GGP_stream_descriptor_surface spec_version 1 */               
#define vkCreateStreamDescriptorSurfaceGGP                                  VKAD_USER_INSTANCE.CreateStreamDescriptorSurfaceGGP                      
        /* VK_QNX_screen_surface spec_version 1 */                          
#define vkCreateScreenSurfaceQNX                                            VKAD_USER_INSTANCE.CreateScreenSurfaceQNX                                
#define vkGetPhysicalDeviceScreenPresentationSupportQNX                     VKAD_USER_INSTANCE.GetPhysicalDeviceScreenPresentationSupportQNX         
        /* Additions from 1.3.284 to 1.4.309: */
        /* VK_NV_cooperative_vector spec_version 4 */
#define vkGetPhysicalDeviceCooperativeVectorPropertiesNV                    VKAD_USER_INSTANCE.GetPhysicalDeviceCooperativeVectorPropertiesNV
        /* VK_NV_cooperative_matrix2 spec_version 1 */
#define vkGetPhysicalDeviceCooperativeMatrixFlexibleDimensionsPropertiesNV  VKAD_USER_INSTANCE.GetPhysicalDeviceCooperativeMatrixFlexibleDimensionsPropertiesNV


/* device functions */    
        /* VK_VERSION_1_0 */
#define vkDestroyDevice                                                     VKAD_USER_DEVICE.DestroyDevice                                              
#define vkGetDeviceQueue                                                    VKAD_USER_DEVICE.GetDeviceQueue                                             
#define vkQueueSubmit                                                       VKAD_USER_DEVICE.QueueSubmit                                                
#define vkQueueWaitIdle                                                     VKAD_USER_DEVICE.QueueWaitIdle                                              
#define vkDeviceWaitIdle                                                    VKAD_USER_DEVICE.DeviceWaitIdle                                             
#define vkAllocateMemory                                                    VKAD_USER_DEVICE.AllocateMemory                                             
#define vkFreeMemory                                                        VKAD_USER_DEVICE.FreeMemory                                                 
#define vkMapMemory                                                         VKAD_USER_DEVICE.MapMemory                                                  
#define vkUnmapMemory                                                       VKAD_USER_DEVICE.UnmapMemory                                                
#define vkFlushMappedMemoryRanges                                           VKAD_USER_DEVICE.FlushMappedMemoryRanges                                    
#define vkInvalidateMappedMemoryRanges                                      VKAD_USER_DEVICE.InvalidateMappedMemoryRanges                               
#define vkGetDeviceMemoryCommitment                                         VKAD_USER_DEVICE.GetDeviceMemoryCommitment                                  
#define vkBindBufferMemory                                                  VKAD_USER_DEVICE.BindBufferMemory                                           
#define vkBindImageMemory                                                   VKAD_USER_DEVICE.BindImageMemory                                            
#define vkGetBufferMemoryRequirements                                       VKAD_USER_DEVICE.GetBufferMemoryRequirements                                
#define vkGetImageMemoryRequirements                                        VKAD_USER_DEVICE.GetImageMemoryRequirements                                 
#define vkGetImageSparseMemoryRequirements                                  VKAD_USER_DEVICE.GetImageSparseMemoryRequirements                           
#define vkQueueBindSparse                                                   VKAD_USER_DEVICE.QueueBindSparse                                            
#define vkCreateFence                                                       VKAD_USER_DEVICE.CreateFence                                                
#define vkDestroyFence                                                      VKAD_USER_DEVICE.DestroyFence                                               
#define vkResetFences                                                       VKAD_USER_DEVICE.ResetFences                                                
#define vkGetFenceStatus                                                    VKAD_USER_DEVICE.GetFenceStatus                                             
#define vkWaitForFences                                                     VKAD_USER_DEVICE.WaitForFences                                              
#define vkCreateSemaphore                                                   VKAD_USER_DEVICE.CreateSemaphore                                            
#define vkDestroySemaphore                                                  VKAD_USER_DEVICE.DestroySemaphore                                           
#define vkCreateEvent                                                       VKAD_USER_DEVICE.CreateEvent                                                
#define vkDestroyEvent                                                      VKAD_USER_DEVICE.DestroyEvent                                               
#define vkGetEventStatus                                                    VKAD_USER_DEVICE.GetEventStatus                                             
#define vkSetEvent                                                          VKAD_USER_DEVICE.SetEvent                                                   
#define vkResetEvent                                                        VKAD_USER_DEVICE.ResetEvent                                                 
#define vkCreateQueryPool                                                   VKAD_USER_DEVICE.CreateQueryPool                                            
#define vkDestroyQueryPool                                                  VKAD_USER_DEVICE.DestroyQueryPool                                           
#define vkGetQueryPoolResults                                               VKAD_USER_DEVICE.GetQueryPoolResults                                        
#define vkCreateBuffer                                                      VKAD_USER_DEVICE.CreateBuffer                                               
#define vkDestroyBuffer                                                     VKAD_USER_DEVICE.DestroyBuffer                                              
#define vkCreateBufferView                                                  VKAD_USER_DEVICE.CreateBufferView                                           
#define vkDestroyBufferView                                                 VKAD_USER_DEVICE.DestroyBufferView                                          
#define vkCreateImage                                                       VKAD_USER_DEVICE.CreateImage                                                
#define vkDestroyImage                                                      VKAD_USER_DEVICE.DestroyImage                                               
#define vkGetImageSubresourceLayout                                         VKAD_USER_DEVICE.GetImageSubresourceLayout                                  
#define vkCreateImageView                                                   VKAD_USER_DEVICE.CreateImageView                                            
#define vkDestroyImageView                                                  VKAD_USER_DEVICE.DestroyImageView                                           
#define vkCreateShaderModule                                                VKAD_USER_DEVICE.CreateShaderModule                                         
#define vkDestroyShaderModule                                               VKAD_USER_DEVICE.DestroyShaderModule                                        
#define vkCreatePipelineCache                                               VKAD_USER_DEVICE.CreatePipelineCache                                        
#define vkDestroyPipelineCache                                              VKAD_USER_DEVICE.DestroyPipelineCache                                       
#define vkGetPipelineCacheData                                              VKAD_USER_DEVICE.GetPipelineCacheData                                       
#define vkMergePipelineCaches                                               VKAD_USER_DEVICE.MergePipelineCaches                                        
#define vkCreateGraphicsPipelines                                           VKAD_USER_DEVICE.CreateGraphicsPipelines                                    
#define vkCreateComputePipelines                                            VKAD_USER_DEVICE.CreateComputePipelines                                     
#define vkDestroyPipeline                                                   VKAD_USER_DEVICE.DestroyPipeline                                            
#define vkCreatePipelineLayout                                              VKAD_USER_DEVICE.CreatePipelineLayout                                       
#define vkDestroyPipelineLayout                                             VKAD_USER_DEVICE.DestroyPipelineLayout                                      
#define vkCreateSampler                                                     VKAD_USER_DEVICE.CreateSampler                                              
#define vkDestroySampler                                                    VKAD_USER_DEVICE.DestroySampler                                             
#define vkCreateDescriptorSetLayout                                         VKAD_USER_DEVICE.CreateDescriptorSetLayout                                  
#define vkDestroyDescriptorSetLayout                                        VKAD_USER_DEVICE.DestroyDescriptorSetLayout                                 
#define vkCreateDescriptorPool                                              VKAD_USER_DEVICE.CreateDescriptorPool                                       
#define vkDestroyDescriptorPool                                             VKAD_USER_DEVICE.DestroyDescriptorPool                                      
#define vkResetDescriptorPool                                               VKAD_USER_DEVICE.ResetDescriptorPool                                        
#define vkAllocateDescriptorSets                                            VKAD_USER_DEVICE.AllocateDescriptorSets                                     
#define vkFreeDescriptorSets                                                VKAD_USER_DEVICE.FreeDescriptorSets                                         
#define vkUpdateDescriptorSets                                              VKAD_USER_DEVICE.UpdateDescriptorSets                                       
#define vkCreateFramebuffer                                                 VKAD_USER_DEVICE.CreateFramebuffer                                          
#define vkDestroyFramebuffer                                                VKAD_USER_DEVICE.DestroyFramebuffer                                         
#define vkCreateRenderPass                                                  VKAD_USER_DEVICE.CreateRenderPass                                           
#define vkDestroyRenderPass                                                 VKAD_USER_DEVICE.DestroyRenderPass                                          
#define vkGetRenderAreaGranularity                                          VKAD_USER_DEVICE.GetRenderAreaGranularity                                   
#define vkCreateCommandPool                                                 VKAD_USER_DEVICE.CreateCommandPool                                          
#define vkDestroyCommandPool                                                VKAD_USER_DEVICE.DestroyCommandPool                                         
#define vkResetCommandPool                                                  VKAD_USER_DEVICE.ResetCommandPool                                           
#define vkAllocateCommandBuffers                                            VKAD_USER_DEVICE.AllocateCommandBuffers                                     
#define vkFreeCommandBuffers                                                VKAD_USER_DEVICE.FreeCommandBuffers                                         
#define vkBeginCommandBuffer                                                VKAD_USER_DEVICE.BeginCommandBuffer                                         
#define vkEndCommandBuffer                                                  VKAD_USER_DEVICE.EndCommandBuffer                                           
#define vkResetCommandBuffer                                                VKAD_USER_DEVICE.ResetCommandBuffer                                         
#define vkCmdBindPipeline                                                   VKAD_USER_DEVICE.CmdBindPipeline                                            
#define vkCmdSetViewport                                                    VKAD_USER_DEVICE.CmdSetViewport                                             
#define vkCmdSetScissor                                                     VKAD_USER_DEVICE.CmdSetScissor                                              
#define vkCmdSetLineWidth                                                   VKAD_USER_DEVICE.CmdSetLineWidth                                            
#define vkCmdSetDepthBias                                                   VKAD_USER_DEVICE.CmdSetDepthBias                                            
#define vkCmdSetBlendConstants                                              VKAD_USER_DEVICE.CmdSetBlendConstants                                       
#define vkCmdSetDepthBounds                                                 VKAD_USER_DEVICE.CmdSetDepthBounds                                          
#define vkCmdSetStencilCompareMask                                          VKAD_USER_DEVICE.CmdSetStencilCompareMask                                   
#define vkCmdSetStencilWriteMask                                            VKAD_USER_DEVICE.CmdSetStencilWriteMask                                     
#define vkCmdSetStencilReference                                            VKAD_USER_DEVICE.CmdSetStencilReference                                     
#define vkCmdBindDescriptorSets                                             VKAD_USER_DEVICE.CmdBindDescriptorSets                                      
#define vkCmdBindIndexBuffer                                                VKAD_USER_DEVICE.CmdBindIndexBuffer                                         
#define vkCmdBindVertexBuffers                                              VKAD_USER_DEVICE.CmdBindVertexBuffers                                       
#define vkCmdDraw                                                           VKAD_USER_DEVICE.CmdDraw                                                    
#define vkCmdDrawIndexed                                                    VKAD_USER_DEVICE.CmdDrawIndexed                                             
#define vkCmdDrawIndirect                                                   VKAD_USER_DEVICE.CmdDrawIndirect                                            
#define vkCmdDrawIndexedIndirect                                            VKAD_USER_DEVICE.CmdDrawIndexedIndirect                                     
#define vkCmdDispatch                                                       VKAD_USER_DEVICE.CmdDispatch                                                
#define vkCmdDispatchIndirect                                               VKAD_USER_DEVICE.CmdDispatchIndirect                                        
#define vkCmdCopyBuffer                                                     VKAD_USER_DEVICE.CmdCopyBuffer                                              
#define vkCmdCopyImage                                                      VKAD_USER_DEVICE.CmdCopyImage                                               
#define vkCmdBlitImage                                                      VKAD_USER_DEVICE.CmdBlitImage                                               
#define vkCmdCopyBufferToImage                                              VKAD_USER_DEVICE.CmdCopyBufferToImage                                       
#define vkCmdCopyImageToBuffer                                              VKAD_USER_DEVICE.CmdCopyImageToBuffer                                       
#define vkCmdUpdateBuffer                                                   VKAD_USER_DEVICE.CmdUpdateBuffer                                            
#define vkCmdFillBuffer                                                     VKAD_USER_DEVICE.CmdFillBuffer                                              
#define vkCmdClearColorImage                                                VKAD_USER_DEVICE.CmdClearColorImage                                         
#define vkCmdClearDepthStencilImage                                         VKAD_USER_DEVICE.CmdClearDepthStencilImage                                  
#define vkCmdClearAttachments                                               VKAD_USER_DEVICE.CmdClearAttachments                                        
#define vkCmdResolveImage                                                   VKAD_USER_DEVICE.CmdResolveImage                                            
#define vkCmdSetEvent                                                       VKAD_USER_DEVICE.CmdSetEvent                                                
#define vkCmdResetEvent                                                     VKAD_USER_DEVICE.CmdResetEvent                                              
#define vkCmdWaitEvents                                                     VKAD_USER_DEVICE.CmdWaitEvents                                              
#define vkCmdPipelineBarrier                                                VKAD_USER_DEVICE.CmdPipelineBarrier                                         
#define vkCmdBeginQuery                                                     VKAD_USER_DEVICE.CmdBeginQuery                                              
#define vkCmdEndQuery                                                       VKAD_USER_DEVICE.CmdEndQuery                                                
#define vkCmdResetQueryPool                                                 VKAD_USER_DEVICE.CmdResetQueryPool                                          
#define vkCmdWriteTimestamp                                                 VKAD_USER_DEVICE.CmdWriteTimestamp                                          
#define vkCmdCopyQueryPoolResults                                           VKAD_USER_DEVICE.CmdCopyQueryPoolResults                                    
#define vkCmdPushConstants                                                  VKAD_USER_DEVICE.CmdPushConstants                                           
#define vkCmdBeginRenderPass                                                VKAD_USER_DEVICE.CmdBeginRenderPass                                         
#define vkCmdNextSubpass                                                    VKAD_USER_DEVICE.CmdNextSubpass                                             
#define vkCmdEndRenderPass                                                  VKAD_USER_DEVICE.CmdEndRenderPass                                           
#define vkCmdExecuteCommands                                                VKAD_USER_DEVICE.CmdExecuteCommands                                         
        /* VK_VERSION_1_1 */                                                
#define vkBindBufferMemory2                                                 VKAD_USER_DEVICE.BindBufferMemory2                                          
#define vkBindImageMemory2                                                  VKAD_USER_DEVICE.BindImageMemory2                                           
#define vkGetDeviceGroupPeerMemoryFeatures                                  VKAD_USER_DEVICE.GetDeviceGroupPeerMemoryFeatures                           
#define vkCmdSetDeviceMask                                                  VKAD_USER_DEVICE.CmdSetDeviceMask                                           
#define vkCmdDispatchBase                                                   VKAD_USER_DEVICE.CmdDispatchBase                                            
#define vkGetImageMemoryRequirements2                                       VKAD_USER_DEVICE.GetImageMemoryRequirements2                                
#define vkGetBufferMemoryRequirements2                                      VKAD_USER_DEVICE.GetBufferMemoryRequirements2                               
#define vkGetImageSparseMemoryRequirements2                                 VKAD_USER_DEVICE.GetImageSparseMemoryRequirements2                          
#define vkTrimCommandPool                                                   VKAD_USER_DEVICE.TrimCommandPool                                            
#define vkGetDeviceQueue2                                                   VKAD_USER_DEVICE.GetDeviceQueue2                                            
#define vkCreateSamplerYcbcrConversion                                      VKAD_USER_DEVICE.CreateSamplerYcbcrConversion                               
#define vkDestroySamplerYcbcrConversion                                     VKAD_USER_DEVICE.DestroySamplerYcbcrConversion                              
#define vkCreateDescriptorUpdateTemplate                                    VKAD_USER_DEVICE.CreateDescriptorUpdateTemplate                             
#define vkDestroyDescriptorUpdateTemplate                                   VKAD_USER_DEVICE.DestroyDescriptorUpdateTemplate                            
#define vkUpdateDescriptorSetWithTemplate                                   VKAD_USER_DEVICE.UpdateDescriptorSetWithTemplate                            
#define vkGetDescriptorSetLayoutSupport                                     VKAD_USER_DEVICE.GetDescriptorSetLayoutSupport                              
        /* VK_VERSION_1_2 */                                                
#define vkCmdDrawIndirectCount                                              VKAD_USER_DEVICE.CmdDrawIndirectCount                                       
#define vkCmdDrawIndexedIndirectCount                                       VKAD_USER_DEVICE.CmdDrawIndexedIndirectCount                                
#define vkCreateRenderPass2                                                 VKAD_USER_DEVICE.CreateRenderPass2                                          
#define vkCmdBeginRenderPass2                                               VKAD_USER_DEVICE.CmdBeginRenderPass2                                        
#define vkCmdNextSubpass2                                                   VKAD_USER_DEVICE.CmdNextSubpass2                                            
#define vkCmdEndRenderPass2                                                 VKAD_USER_DEVICE.CmdEndRenderPass2                                          
#define vkResetQueryPool                                                    VKAD_USER_DEVICE.ResetQueryPool                                             
#define vkGetSemaphoreCounterValue                                          VKAD_USER_DEVICE.GetSemaphoreCounterValue                                   
#define vkWaitSemaphores                                                    VKAD_USER_DEVICE.WaitSemaphores                                             
#define vkSignalSemaphore                                                   VKAD_USER_DEVICE.SignalSemaphore                                            
#define vkGetBufferDeviceAddress                                            VKAD_USER_DEVICE.GetBufferDeviceAddress                                     
#define vkGetBufferOpaqueCaptureAddress                                     VKAD_USER_DEVICE.GetBufferOpaqueCaptureAddress                              
#define vkGetDeviceMemoryOpaqueCaptureAddress                               VKAD_USER_DEVICE.GetDeviceMemoryOpaqueCaptureAddress                        
        /* VK_VERSION_1_3 */                                                
#define vkCreatePrivateDataSlot                                             VKAD_USER_DEVICE.CreatePrivateDataSlot                                      
#define vkDestroyPrivateDataSlot                                            VKAD_USER_DEVICE.DestroyPrivateDataSlot                                     
#define vkSetPrivateData                                                    VKAD_USER_DEVICE.SetPrivateData                                             
#define vkGetPrivateData                                                    VKAD_USER_DEVICE.GetPrivateData                                             
#define vkCmdSetEvent2                                                      VKAD_USER_DEVICE.CmdSetEvent2                                               
#define vkCmdResetEvent2                                                    VKAD_USER_DEVICE.CmdResetEvent2                                             
#define vkCmdWaitEvents2                                                    VKAD_USER_DEVICE.CmdWaitEvents2                                             
#define vkCmdPipelineBarrier2                                               VKAD_USER_DEVICE.CmdPipelineBarrier2                                        
#define vkCmdWriteTimestamp2                                                VKAD_USER_DEVICE.CmdWriteTimestamp2                                         
#define vkQueueSubmit2                                                      VKAD_USER_DEVICE.QueueSubmit2                                               
#define vkCmdCopyBuffer2                                                    VKAD_USER_DEVICE.CmdCopyBuffer2                                             
#define vkCmdCopyImage2                                                     VKAD_USER_DEVICE.CmdCopyImage2                                              
#define vkCmdCopyBufferToImage2                                             VKAD_USER_DEVICE.CmdCopyBufferToImage2                                      
#define vkCmdCopyImageToBuffer2                                             VKAD_USER_DEVICE.CmdCopyImageToBuffer2                                      
#define vkCmdBlitImage2                                                     VKAD_USER_DEVICE.CmdBlitImage2                                              
#define vkCmdResolveImage2                                                  VKAD_USER_DEVICE.CmdResolveImage2                                           
#define vkCmdBeginRendering                                                 VKAD_USER_DEVICE.CmdBeginRendering                                          
#define vkCmdEndRendering                                                   VKAD_USER_DEVICE.CmdEndRendering                                            
#define vkCmdSetCullMode                                                    VKAD_USER_DEVICE.CmdSetCullMode                                             
#define vkCmdSetFrontFace                                                   VKAD_USER_DEVICE.CmdSetFrontFace                                            
#define vkCmdSetPrimitiveTopology                                           VKAD_USER_DEVICE.CmdSetPrimitiveTopology                                    
#define vkCmdSetViewportWithCount                                           VKAD_USER_DEVICE.CmdSetViewportWithCount                                    
#define vkCmdSetScissorWithCount                                            VKAD_USER_DEVICE.CmdSetScissorWithCount                                     
#define vkCmdBindVertexBuffers2                                             VKAD_USER_DEVICE.CmdBindVertexBuffers2                                      
#define vkCmdSetDepthTestEnable                                             VKAD_USER_DEVICE.CmdSetDepthTestEnable                                      
#define vkCmdSetDepthWriteEnable                                            VKAD_USER_DEVICE.CmdSetDepthWriteEnable                                     
#define vkCmdSetDepthCompareOp                                              VKAD_USER_DEVICE.CmdSetDepthCompareOp                                       
#define vkCmdSetDepthBoundsTestEnable                                       VKAD_USER_DEVICE.CmdSetDepthBoundsTestEnable                                
#define vkCmdSetStencilTestEnable                                           VKAD_USER_DEVICE.CmdSetStencilTestEnable                                    
#define vkCmdSetStencilOp                                                   VKAD_USER_DEVICE.CmdSetStencilOp                                            
#define vkCmdSetRasterizerDiscardEnable                                     VKAD_USER_DEVICE.CmdSetRasterizerDiscardEnable                              
#define vkCmdSetDepthBiasEnable                                             VKAD_USER_DEVICE.CmdSetDepthBiasEnable                                      
#define vkCmdSetPrimitiveRestartEnable                                      VKAD_USER_DEVICE.CmdSetPrimitiveRestartEnable                               
#define vkGetDeviceBufferMemoryRequirements                                 VKAD_USER_DEVICE.GetDeviceBufferMemoryRequirements                          
#define vkGetDeviceImageMemoryRequirements                                  VKAD_USER_DEVICE.GetDeviceImageMemoryRequirements                           
#define vkGetDeviceImageSparseMemoryRequirements                            VKAD_USER_DEVICE.GetDeviceImageSparseMemoryRequirements                     
        /* VK_KHR_swapchain spec_version 70  */                             
#define vkCreateSwapchainKHR                                                VKAD_USER_DEVICE.CreateSwapchainKHR                                         
#define vkDestroySwapchainKHR                                               VKAD_USER_DEVICE.DestroySwapchainKHR                                        
#define vkGetSwapchainImagesKHR                                             VKAD_USER_DEVICE.GetSwapchainImagesKHR                                      
#define vkAcquireNextImageKHR                                               VKAD_USER_DEVICE.AcquireNextImageKHR                                        
#define vkQueuePresentKHR                                                   VKAD_USER_DEVICE.QueuePresentKHR                                            
#define vkGetDeviceGroupPresentCapabilitiesKHR                              VKAD_USER_DEVICE.GetDeviceGroupPresentCapabilitiesKHR                       
#define vkGetDeviceGroupSurfacePresentModesKHR                              VKAD_USER_DEVICE.GetDeviceGroupSurfacePresentModesKHR                       
#define vkAcquireNextImage2KHR                                              VKAD_USER_DEVICE.AcquireNextImage2KHR                                       
        /* VK_KHR_display_swapchain spec_version 10  */                     
#define vkCreateSharedSwapchainsKHR                                         VKAD_USER_DEVICE.CreateSharedSwapchainsKHR                                  
        /* VK_KHR_video_queue spec_version 8 */                             
#define vkCreateVideoSessionKHR                                             VKAD_USER_DEVICE.CreateVideoSessionKHR                                      
#define vkDestroyVideoSessionKHR                                            VKAD_USER_DEVICE.DestroyVideoSessionKHR                                     
#define vkGetVideoSessionMemoryRequirementsKHR                              VKAD_USER_DEVICE.GetVideoSessionMemoryRequirementsKHR                       
#define vkBindVideoSessionMemoryKHR                                         VKAD_USER_DEVICE.BindVideoSessionMemoryKHR                                  
#define vkCreateVideoSessionParametersKHR                                   VKAD_USER_DEVICE.CreateVideoSessionParametersKHR                            
#define vkUpdateVideoSessionParametersKHR                                   VKAD_USER_DEVICE.UpdateVideoSessionParametersKHR                            
#define vkDestroyVideoSessionParametersKHR                                  VKAD_USER_DEVICE.DestroyVideoSessionParametersKHR                           
#define vkCmdBeginVideoCodingKHR                                            VKAD_USER_DEVICE.CmdBeginVideoCodingKHR                                     
#define vkCmdEndVideoCodingKHR                                              VKAD_USER_DEVICE.CmdEndVideoCodingKHR                                       
#define vkCmdControlVideoCodingKHR                                          VKAD_USER_DEVICE.CmdControlVideoCodingKHR                                   
        /* VK_KHR_video_decode_queue spec_version 8 */                      
#define vkCmdDecodeVideoKHR                                                 VKAD_USER_DEVICE.CmdDecodeVideoKHR                                          
        /* VK_KHR_dynamic_rendering spec_version 1 */                       
#define vkCmdBeginRenderingKHR                                              VKAD_USER_DEVICE.CmdBeginRenderingKHR                                       
#define vkCmdEndRenderingKHR                                                VKAD_USER_DEVICE.CmdEndRenderingKHR                                         
        /* VK_KHR_device_group spec_version 4 */                            
#define vkGetDeviceGroupPeerMemoryFeaturesKHR                               VKAD_USER_DEVICE.GetDeviceGroupPeerMemoryFeaturesKHR                        
#define vkCmdSetDeviceMaskKHR                                               VKAD_USER_DEVICE.CmdSetDeviceMaskKHR                                        
#define vkCmdDispatchBaseKHR                                                VKAD_USER_DEVICE.CmdDispatchBaseKHR                                         
        /* VK_KHR_maintenance1 spec_version 2 */                            
#define vkTrimCommandPoolKHR                                                VKAD_USER_DEVICE.TrimCommandPoolKHR                                         
        /* VK_KHR_external_memory_fd spec_version 1 */                      
#define vkGetMemoryFdKHR                                                    VKAD_USER_DEVICE.GetMemoryFdKHR                                             
#define vkGetMemoryFdPropertiesKHR                                          VKAD_USER_DEVICE.GetMemoryFdPropertiesKHR                                   
        /* VK_KHR_external_semaphore_fd spec_version 1 */                   
#define vkImportSemaphoreFdKHR                                              VKAD_USER_DEVICE.ImportSemaphoreFdKHR                                       
#define vkGetSemaphoreFdKHR                                                 VKAD_USER_DEVICE.GetSemaphoreFdKHR                                          
        /* VK_KHR_push_descriptor spec_version 2 */                         
#define vkCmdPushDescriptorSetKHR                                           VKAD_USER_DEVICE.CmdPushDescriptorSetKHR                                    
#define vkCmdPushDescriptorSetWithTemplateKHR                               VKAD_USER_DEVICE.CmdPushDescriptorSetWithTemplateKHR                        
        /* VK_KHR_descriptor_update_template spec_version 1 */              
#define vkCreateDescriptorUpdateTemplateKHR                                 VKAD_USER_DEVICE.CreateDescriptorUpdateTemplateKHR                          
#define vkDestroyDescriptorUpdateTemplateKHR                                VKAD_USER_DEVICE.DestroyDescriptorUpdateTemplateKHR                         
#define vkUpdateDescriptorSetWithTemplateKHR                                VKAD_USER_DEVICE.UpdateDescriptorSetWithTemplateKHR                         
        /* VK_KHR_create_renderpass2 spec_version 1 */                      
#define vkCreateRenderPass2KHR                                              VKAD_USER_DEVICE.CreateRenderPass2KHR                                       
#define vkCmdBeginRenderPass2KHR                                            VKAD_USER_DEVICE.CmdBeginRenderPass2KHR                                     
#define vkCmdNextSubpass2KHR                                                VKAD_USER_DEVICE.CmdNextSubpass2KHR                                         
#define vkCmdEndRenderPass2KHR                                              VKAD_USER_DEVICE.CmdEndRenderPass2KHR                                       
        /* VK_KHR_shared_presentable_image spec_version 1 */                
#define vkGetSwapchainStatusKHR                                             VKAD_USER_DEVICE.GetSwapchainStatusKHR                                      
        /* VK_KHR_external_fence_fd spec_version 1 */                       
#define vkImportFenceFdKHR                                                  VKAD_USER_DEVICE.ImportFenceFdKHR                                           
#define vkGetFenceFdKHR                                                     VKAD_USER_DEVICE.GetFenceFdKHR                                              
        /* VK_KHR_performance_query spec_version 1 */                       
#define vkAcquireProfilingLockKHR                                           VKAD_USER_DEVICE.AcquireProfilingLockKHR                                    
#define vkReleaseProfilingLockKHR                                           VKAD_USER_DEVICE.ReleaseProfilingLockKHR                                    
        /* VK_KHR_get_memory_requirements2 spec_version 1 */                
#define vkGetImageMemoryRequirements2KHR                                    VKAD_USER_DEVICE.GetImageMemoryRequirements2KHR                             
#define vkGetBufferMemoryRequirements2KHR                                   VKAD_USER_DEVICE.GetBufferMemoryRequirements2KHR                            
#define vkGetImageSparseMemoryRequirements2KHR                              VKAD_USER_DEVICE.GetImageSparseMemoryRequirements2KHR                       
        /* VK_KHR_sampler_ycbcr_conversion spec_version 14 */               
#define vkCreateSamplerYcbcrConversionKHR                                   VKAD_USER_DEVICE.CreateSamplerYcbcrConversionKHR                            
#define vkDestroySamplerYcbcrConversionKHR                                  VKAD_USER_DEVICE.DestroySamplerYcbcrConversionKHR                           
        /* VK_KHR_bind_memory2 spec_version 1 */                            
#define vkBindBufferMemory2KHR                                              VKAD_USER_DEVICE.BindBufferMemory2KHR                                       
#define vkBindImageMemory2KHR                                               VKAD_USER_DEVICE.BindImageMemory2KHR                                        
        /* VK_KHR_maintenance3 spec_version 1 */                            
#define vkGetDescriptorSetLayoutSupportKHR                                  VKAD_USER_DEVICE.GetDescriptorSetLayoutSupportKHR                           
        /* VK_KHR_draw_indirect_count spec_version 1 */                     
#define vkCmdDrawIndirectCountKHR                                           VKAD_USER_DEVICE.CmdDrawIndirectCountKHR                                    
#define vkCmdDrawIndexedIndirectCountKHR                                    VKAD_USER_DEVICE.CmdDrawIndexedIndirectCountKHR                             
        /* VK_KHR_timeline_semaphore spec_version 2 */                      
#define vkGetSemaphoreCounterValueKHR                                       VKAD_USER_DEVICE.GetSemaphoreCounterValueKHR                                
#define vkWaitSemaphoresKHR                                                 VKAD_USER_DEVICE.WaitSemaphoresKHR                                          
#define vkSignalSemaphoreKHR                                                VKAD_USER_DEVICE.SignalSemaphoreKHR                                         
        /* VK_KHR_fragment_shading_rate spec_version 2 */                   
#define vkCmdSetFragmentShadingRateKHR                                      VKAD_USER_DEVICE.CmdSetFragmentShadingRateKHR                               
        /* VK_KHR_dynamic_rendering_local_read spec_version 1 */            
#define vkCmdSetRenderingAttachmentLocationsKHR                             VKAD_USER_DEVICE.CmdSetRenderingAttachmentLocationsKHR                      
#define vkCmdSetRenderingInputAttachmentIndicesKHR                          VKAD_USER_DEVICE.CmdSetRenderingInputAttachmentIndicesKHR                   
        /* VK_KHR_present_wait spec_version 1 */                            
#define vkWaitForPresentKHR                                                 VKAD_USER_DEVICE.WaitForPresentKHR                                          
        /* VK_KHR_buffer_device_address spec_version 1 */                   
#define vkGetBufferDeviceAddressKHR                                         VKAD_USER_DEVICE.GetBufferDeviceAddressKHR                                  
#define vkGetBufferOpaqueCaptureAddressKHR                                  VKAD_USER_DEVICE.GetBufferOpaqueCaptureAddressKHR                          
#define vkGetDeviceMemoryOpaqueCaptureAddressKHR                            VKAD_USER_DEVICE.GetDeviceMemoryOpaqueCaptureAddressKHR                    
        /* VK_KHR_deferred_host_operations spec_version 4 */                
#define vkCreateDeferredOperationKHR                                        VKAD_USER_DEVICE.CreateDeferredOperationKHR                                
#define vkDestroyDeferredOperationKHR                                       VKAD_USER_DEVICE.DestroyDeferredOperationKHR                               
#define vkGetDeferredOperationMaxConcurrencyKHR                             VKAD_USER_DEVICE.GetDeferredOperationMaxConcurrencyKHR                     
#define vkGetDeferredOperationResultKHR                                     VKAD_USER_DEVICE.GetDeferredOperationResultKHR                             
#define vkDeferredOperationJoinKHR                                          VKAD_USER_DEVICE.DeferredOperationJoinKHR                                  
        /* VK_KHR_pipeline_executable_properties spec_version 1 */          
#define vkGetPipelineExecutablePropertiesKHR                                VKAD_USER_DEVICE.GetPipelineExecutablePropertiesKHR                        
#define vkGetPipelineExecutableStatisticsKHR                                VKAD_USER_DEVICE.GetPipelineExecutableStatisticsKHR                        
#define vkGetPipelineExecutableInternalRepresentationsKHR                   VKAD_USER_DEVICE.GetPipelineExecutableInternalRepresentationsKHR           
        /* VK_KHR_map_memory2 spec_version 1 */                             
#define vkMapMemory2KHR                                                     VKAD_USER_DEVICE.MapMemory2KHR                                             
#define vkUnmapMemory2KHR                                                   VKAD_USER_DEVICE.UnmapMemory2KHR                                           
        /* VK_KHR_video_encode_queue spec_version 12 */                     
#define vkGetEncodedVideoSessionParametersKHR                               VKAD_USER_DEVICE.GetEncodedVideoSessionParametersKHR                       
#define vkCmdEncodeVideoKHR                                                 VKAD_USER_DEVICE.CmdEncodeVideoKHR                                         
        /* VK_KHR_synchronization2 spec_version 1 */                        
#define vkCmdSetEvent2KHR                                                   VKAD_USER_DEVICE.CmdSetEvent2KHR                                           
#define vkCmdResetEvent2KHR                                                 VKAD_USER_DEVICE.CmdResetEvent2KHR                                         
#define vkCmdWaitEvents2KHR                                                 VKAD_USER_DEVICE.CmdWaitEvents2KHR                                         
#define vkCmdPipelineBarrier2KHR                                            VKAD_USER_DEVICE.CmdPipelineBarrier2KHR                                    
#define vkCmdWriteTimestamp2KHR                                             VKAD_USER_DEVICE.CmdWriteTimestamp2KHR                                     
#define vkQueueSubmit2KHR                                                   VKAD_USER_DEVICE.QueueSubmit2KHR                                           
#define vkCmdWriteBufferMarker2AMD                                          VKAD_USER_DEVICE.CmdWriteBufferMarker2AMD                                  
#define vkGetQueueCheckpointData2NV                                         VKAD_USER_DEVICE.GetQueueCheckpointData2NV                                 
                /* NOTE: The function vkCmdWriteBufferMarker2AMD was moved into VK_AMD_buffer_marker and vkGetQueueCheckpointData2NV into VK_NV_device_diagnostic_checkpoints from 1.3.284 to 1.4.309;
                   they are kept here in their old position for the sake of preserving the memory layout of the old portion of the structs */
        /* VK_KHR_copy_commands2 spec_version 1 */                          
#define vkCmdCopyBuffer2KHR                                                 VKAD_USER_DEVICE.CmdCopyBuffer2KHR                                         
#define vkCmdCopyImage2KHR                                                  VKAD_USER_DEVICE.CmdCopyImage2KHR                                          
#define vkCmdCopyBufferToImage2KHR                                          VKAD_USER_DEVICE.CmdCopyBufferToImage2KHR                                  
#define vkCmdCopyImageToBuffer2KHR                                          VKAD_USER_DEVICE.CmdCopyImageToBuffer2KHR                                  
#define vkCmdBlitImage2KHR                                                  VKAD_USER_DEVICE.CmdBlitImage2KHR                                          
#define vkCmdResolveImage2KHR                                               VKAD_USER_DEVICE.CmdResolveImage2KHR                                       
        /* VK_KHR_ray_tracing_maintenance1 spec_version 1 */                
#define vkCmdTraceRaysIndirect2KHR                                          VKAD_USER_DEVICE.CmdTraceRaysIndirect2KHR                                  
        /* VK_KHR_maintenance4 spec_version 2 */                            
#define vkGetDeviceBufferMemoryRequirementsKHR                              VKAD_USER_DEVICE.GetDeviceBufferMemoryRequirementsKHR                      
#define vkGetDeviceImageMemoryRequirementsKHR                               VKAD_USER_DEVICE.GetDeviceImageMemoryRequirementsKHR                       
#define vkGetDeviceImageSparseMemoryRequirementsKHR                         VKAD_USER_DEVICE.GetDeviceImageSparseMemoryRequirementsKHR                 
        /* VK_KHR_maintenance5 spec_version 1 */                            
#define vkCmdBindIndexBuffer2KHR                                            VKAD_USER_DEVICE.CmdBindIndexBuffer2KHR                                    
#define vkGetRenderingAreaGranularityKHR                                    VKAD_USER_DEVICE.GetRenderingAreaGranularityKHR                            
#define vkGetDeviceImageSubresourceLayoutKHR                                VKAD_USER_DEVICE.GetDeviceImageSubresourceLayoutKHR                        
#define vkGetImageSubresourceLayout2KHR                                     VKAD_USER_DEVICE.GetImageSubresourceLayout2KHR                             
        /* VK_KHR_line_rasterization spec_version 1 */                      
#define vkCmdSetLineStippleKHR                                              VKAD_USER_DEVICE.CmdSetLineStippleKHR                                      
        /* VK_KHR_calibrated_timestamps spec_version 1 */                   
#define vkGetCalibratedTimestampsKHR                                        VKAD_USER_DEVICE.GetCalibratedTimestampsKHR                                
        /* VK_KHR_maintenance6 spec_version 1 */                            
#define vkCmdBindDescriptorSets2KHR                                         VKAD_USER_DEVICE.CmdBindDescriptorSets2KHR                                 
#define vkCmdPushConstants2KHR                                              VKAD_USER_DEVICE.CmdPushConstants2KHR                                      
#define vkCmdPushDescriptorSet2KHR                                          VKAD_USER_DEVICE.CmdPushDescriptorSet2KHR                                  
#define vkCmdPushDescriptorSetWithTemplate2KHR                              VKAD_USER_DEVICE.CmdPushDescriptorSetWithTemplate2KHR                      
#define vkCmdSetDescriptorBufferOffsets2EXT                                 VKAD_USER_DEVICE.CmdSetDescriptorBufferOffsets2EXT                         
#define vkCmdBindDescriptorBufferEmbeddedSamplers2EXT                       VKAD_USER_DEVICE.CmdBindDescriptorBufferEmbeddedSamplers2EXT               
        /* VK_EXT_debug_marker spec_version 4 */                            
#define vkDebugMarkerSetObjectTagEXT                                        VKAD_USER_DEVICE.DebugMarkerSetObjectTagEXT                                
#define vkDebugMarkerSetObjectNameEXT                                       VKAD_USER_DEVICE.DebugMarkerSetObjectNameEXT                               
#define vkCmdDebugMarkerBeginEXT                                            VKAD_USER_DEVICE.CmdDebugMarkerBeginEXT                                    
#define vkCmdDebugMarkerEndEXT                                              VKAD_USER_DEVICE.CmdDebugMarkerEndEXT                                      
#define vkCmdDebugMarkerInsertEXT                                           VKAD_USER_DEVICE.CmdDebugMarkerInsertEXT                                   
        /* VK_EXT_transform_feedback spec_version 1 */                      
#define vkCmdBindTransformFeedbackBuffersEXT                                VKAD_USER_DEVICE.CmdBindTransformFeedbackBuffersEXT                        
#define vkCmdBeginTransformFeedbackEXT                                      VKAD_USER_DEVICE.CmdBeginTransformFeedbackEXT                              
#define vkCmdEndTransformFeedbackEXT                                        VKAD_USER_DEVICE.CmdEndTransformFeedbackEXT                                
#define vkCmdBeginQueryIndexedEXT                                           VKAD_USER_DEVICE.CmdBeginQueryIndexedEXT                                   
#define vkCmdEndQueryIndexedEXT                                             VKAD_USER_DEVICE.CmdEndQueryIndexedEXT                                     
#define vkCmdDrawIndirectByteCountEXT                                       VKAD_USER_DEVICE.CmdDrawIndirectByteCountEXT                               
        /* VK_NVX_binary_import spec_version 2 */
#define vkCreateCuModuleNVX                                                 VKAD_USER_DEVICE.CreateCuModuleNVX                                         
#define vkCreateCuFunctionNVX                                               VKAD_USER_DEVICE.CreateCuFunctionNVX                                       
#define vkDestroyCuModuleNVX                                                VKAD_USER_DEVICE.DestroyCuModuleNVX                                        
#define vkDestroyCuFunctionNVX                                              VKAD_USER_DEVICE.DestroyCuFunctionNVX                                      
#define vkCmdCuLaunchKernelNVX                                              VKAD_USER_DEVICE.CmdCuLaunchKernelNVX                                      
        /* VK_NVX_image_view_handle spec_version 3 */
#define vkGetImageViewHandleNVX                                             VKAD_USER_DEVICE.GetImageViewHandleNVX                                     
#define vkGetImageViewAddressNVX                                            VKAD_USER_DEVICE.GetImageViewAddressNVX                                    
        /* VK_AMD_draw_indirect_count spec_version 2 */                     
#define vkCmdDrawIndirectCountAMD                                           VKAD_USER_DEVICE.CmdDrawIndirectCountAMD                                   
#define vkCmdDrawIndexedIndirectCountAMD                                    VKAD_USER_DEVICE.CmdDrawIndexedIndirectCountAMD                            
        /* VK_AMD_shader_info spec_version 1 */                             
#define vkGetShaderInfoAMD                                                  VKAD_USER_DEVICE.GetShaderInfoAMD                                          
        /* VK_EXT_conditional_rendering spec_version 2 */                   
#define vkCmdBeginConditionalRenderingEXT                                   VKAD_USER_DEVICE.CmdBeginConditionalRenderingEXT                           
#define vkCmdEndConditionalRenderingEXT                                     VKAD_USER_DEVICE.CmdEndConditionalRenderingEXT                             
        /* VK_NV_clip_space_w_scaling spec_version 1 */                     
#define vkCmdSetViewportWScalingNV                                          VKAD_USER_DEVICE.CmdSetViewportWScalingNV                                  
        /* VK_EXT_display_control spec_version 1 */                         
#define vkDisplayPowerControlEXT                                            VKAD_USER_DEVICE.DisplayPowerControlEXT                                    
#define vkRegisterDeviceEventEXT                                            VKAD_USER_DEVICE.RegisterDeviceEventEXT                                    
#define vkRegisterDisplayEventEXT                                           VKAD_USER_DEVICE.RegisterDisplayEventEXT                                   
#define vkGetSwapchainCounterEXT                                            VKAD_USER_DEVICE.GetSwapchainCounterEXT                                    
        /* VK_GOOGLE_display_timing spec_version 1 */                       
#define vkGetRefreshCycleDurationGOOGLE                                     VKAD_USER_DEVICE.GetRefreshCycleDurationGOOGLE                             
#define vkGetPastPresentationTimingGOOGLE                                   VKAD_USER_DEVICE.GetPastPresentationTimingGOOGLE                           
        /* VK_EXT_discard_rectangles spec_version 2 */                      
#define vkCmdSetDiscardRectangleEXT                                         VKAD_USER_DEVICE.CmdSetDiscardRectangleEXT                                 
#define vkCmdSetDiscardRectangleEnableEXT                                   VKAD_USER_DEVICE.CmdSetDiscardRectangleEnableEXT                           
#define vkCmdSetDiscardRectangleModeEXT                                     VKAD_USER_DEVICE.CmdSetDiscardRectangleModeEXT                             
        /* VK_EXT_hdr_metadata spec_version 3 */
#define vkSetHdrMetadataEXT                                                 VKAD_USER_DEVICE.SetHdrMetadataEXT                                         
        /* VK_EXT_debug_utils spec_version 2 */                             
#define vkSetDebugUtilsObjectNameEXT                                        VKAD_USER_DEVICE.SetDebugUtilsObjectNameEXT                                
#define vkSetDebugUtilsObjectTagEXT                                         VKAD_USER_DEVICE.SetDebugUtilsObjectTagEXT                                 
#define vkQueueBeginDebugUtilsLabelEXT                                      VKAD_USER_DEVICE.QueueBeginDebugUtilsLabelEXT                              
#define vkQueueEndDebugUtilsLabelEXT                                        VKAD_USER_DEVICE.QueueEndDebugUtilsLabelEXT                                
#define vkQueueInsertDebugUtilsLabelEXT                                     VKAD_USER_DEVICE.QueueInsertDebugUtilsLabelEXT                             
#define vkCmdBeginDebugUtilsLabelEXT                                        VKAD_USER_DEVICE.CmdBeginDebugUtilsLabelEXT                                
#define vkCmdEndDebugUtilsLabelEXT                                          VKAD_USER_DEVICE.CmdEndDebugUtilsLabelEXT                                  
#define vkCmdInsertDebugUtilsLabelEXT                                       VKAD_USER_DEVICE.CmdInsertDebugUtilsLabelEXT                               
        /* VK_EXT_sample_locations spec_version 1 */                        
#define vkCmdSetSampleLocationsEXT                                          VKAD_USER_DEVICE.CmdSetSampleLocationsEXT                                  
        /* VK_EXT_image_drm_format_modifier spec_version 2 */               
#define vkGetImageDrmFormatModifierPropertiesEXT                            VKAD_USER_DEVICE.GetImageDrmFormatModifierPropertiesEXT                    
        /* VK_EXT_validation_cache spec_version 1 */                        
#define vkCreateValidationCacheEXT                                          VKAD_USER_DEVICE.CreateValidationCacheEXT                                  
#define vkDestroyValidationCacheEXT                                         VKAD_USER_DEVICE.DestroyValidationCacheEXT                                 
#define vkMergeValidationCachesEXT                                          VKAD_USER_DEVICE.MergeValidationCachesEXT                                  
#define vkGetValidationCacheDataEXT                                         VKAD_USER_DEVICE.GetValidationCacheDataEXT                                 
        /* VK_NV_shading_rate_image spec_version 3 */                       
#define vkCmdBindShadingRateImageNV                                         VKAD_USER_DEVICE.CmdBindShadingRateImageNV                                 
#define vkCmdSetViewportShadingRatePaletteNV                                VKAD_USER_DEVICE.CmdSetViewportShadingRatePaletteNV                        
#define vkCmdSetCoarseSampleOrderNV                                         VKAD_USER_DEVICE.CmdSetCoarseSampleOrderNV                                 
        /* VK_NV_ray_tracing spec_version 3 */                              
#define vkCreateAccelerationStructureNV                                     VKAD_USER_DEVICE.CreateAccelerationStructureNV                             
#define vkDestroyAccelerationStructureNV                                    VKAD_USER_DEVICE.DestroyAccelerationStructureNV                            
#define vkGetAccelerationStructureMemoryRequirementsNV                      VKAD_USER_DEVICE.GetAccelerationStructureMemoryRequirementsNV            
#define vkBindAccelerationStructureMemoryNV                                 VKAD_USER_DEVICE.BindAccelerationStructureMemoryNV                       
#define vkCmdBuildAccelerationStructureNV                                   VKAD_USER_DEVICE.CmdBuildAccelerationStructureNV                         
#define vkCmdCopyAccelerationStructureNV                                    VKAD_USER_DEVICE.CmdCopyAccelerationStructureNV                          
#define vkCmdTraceRaysNV                                                    VKAD_USER_DEVICE.CmdTraceRaysNV                                          
#define vkCreateRayTracingPipelinesNV                                       VKAD_USER_DEVICE.CreateRayTracingPipelinesNV                             
#define vkGetRayTracingShaderGroupHandlesKHR                                VKAD_USER_DEVICE.GetRayTracingShaderGroupHandlesKHR                      
#define vkGetRayTracingShaderGroupHandlesNV                                 VKAD_USER_DEVICE.GetRayTracingShaderGroupHandlesNV                       
#define vkGetAccelerationStructureHandleNV                                  VKAD_USER_DEVICE.GetAccelerationStructureHandleNV                        
#define vkCmdWriteAccelerationStructuresPropertiesNV                        VKAD_USER_DEVICE.CmdWriteAccelerationStructuresPropertiesNV              
#define vkCompileDeferredNV                                                 VKAD_USER_DEVICE.CompileDeferredNV                                       
        /* VK_EXT_external_memory_host spec_version 1 */                    
#define vkGetMemoryHostPointerPropertiesEXT                                 VKAD_USER_DEVICE.GetMemoryHostPointerPropertiesEXT                                             
        /* VK_AMD_buffer_marker spec_version 1 */                           
#define vkCmdWriteBufferMarkerAMD                                           VKAD_USER_DEVICE.CmdWriteBufferMarkerAMD                                 
        /* VK_EXT_calibrated_timestamps spec_version 2 */                   
#define vkGetCalibratedTimestampsEXT                                        VKAD_USER_DEVICE.GetCalibratedTimestampsEXT                              
        /* VK_NV_mesh_shader spec_version 1 */                              
#define vkCmdDrawMeshTasksNV                                                VKAD_USER_DEVICE.CmdDrawMeshTasksNV                                      
#define vkCmdDrawMeshTasksIndirectNV                                        VKAD_USER_DEVICE.CmdDrawMeshTasksIndirectNV                              
#define vkCmdDrawMeshTasksIndirectCountNV                                   VKAD_USER_DEVICE.CmdDrawMeshTasksIndirectCountNV                         
        /* VK_NV_scissor_exclusive spec_version 2 */                        
#define vkCmdSetExclusiveScissorEnableNV                                    VKAD_USER_DEVICE.CmdSetExclusiveScissorEnableNV                          
#define vkCmdSetExclusiveScissorNV                                          VKAD_USER_DEVICE.CmdSetExclusiveScissorNV                                
        /* VK_NV_device_diagnostic_checkpoints spec_version 2 */            
#define vkCmdSetCheckpointNV                                                VKAD_USER_DEVICE.CmdSetCheckpointNV                                      
#define vkGetQueueCheckpointDataNV                                          VKAD_USER_DEVICE.GetQueueCheckpointDataNV                                
        /* VK_INTEL_performance_query spec_version 2 */                     
#define vkInitializePerformanceApiINTEL                                     VKAD_USER_DEVICE.InitializePerformanceApiINTEL                           
#define vkUninitializePerformanceApiINTEL                                   VKAD_USER_DEVICE.UninitializePerformanceApiINTEL                         
#define vkCmdSetPerformanceMarkerINTEL                                      VKAD_USER_DEVICE.CmdSetPerformanceMarkerINTEL                            
#define vkCmdSetPerformanceStreamMarkerINTEL                                VKAD_USER_DEVICE.CmdSetPerformanceStreamMarkerINTEL                      
#define vkCmdSetPerformanceOverrideINTEL                                    VKAD_USER_DEVICE.CmdSetPerformanceOverrideINTEL                          
#define vkAcquirePerformanceConfigurationINTEL                              VKAD_USER_DEVICE.AcquirePerformanceConfigurationINTEL                    
#define vkReleasePerformanceConfigurationINTEL                              VKAD_USER_DEVICE.ReleasePerformanceConfigurationINTEL                    
#define vkQueueSetPerformanceConfigurationINTEL                             VKAD_USER_DEVICE.QueueSetPerformanceConfigurationINTEL                   
#define vkGetPerformanceParameterINTEL                                      VKAD_USER_DEVICE.GetPerformanceParameterINTEL                            
        /* VK_AMD_display_native_hdr spec_version 1 */                      
#define vkSetLocalDimmingAMD                                                VKAD_USER_DEVICE.SetLocalDimmingAMD                                      
        /* VK_EXT_buffer_device_address spec_version 2 */                   
#define vkGetBufferDeviceAddressEXT                                         VKAD_USER_DEVICE.GetBufferDeviceAddressEXT                               
        /* VK_EXT_line_rasterization spec_version 1 */                      
#define vkCmdSetLineStippleEXT                                              VKAD_USER_DEVICE.CmdSetLineStippleEXT                                    
        /* VK_EXT_host_query_reset spec_version 1 */                        
#define vkResetQueryPoolEXT                                                 VKAD_USER_DEVICE.ResetQueryPoolEXT                                                                             
        /* VK_EXT_extended_dynamic_state spec_version 1 */                  
#define vkCmdSetCullModeEXT                                                 VKAD_USER_DEVICE.CmdSetCullModeEXT                                       
#define vkCmdSetFrontFaceEXT                                                VKAD_USER_DEVICE.CmdSetFrontFaceEXT                                        
#define vkCmdSetPrimitiveTopologyEXT                                        VKAD_USER_DEVICE.CmdSetPrimitiveTopologyEXT                                
#define vkCmdSetViewportWithCountEXT                                        VKAD_USER_DEVICE.CmdSetViewportWithCountEXT                                
#define vkCmdSetScissorWithCountEXT                                         VKAD_USER_DEVICE.CmdSetScissorWithCountEXT                                 
#define vkCmdBindVertexBuffers2EXT                                          VKAD_USER_DEVICE.CmdBindVertexBuffers2EXT                                  
#define vkCmdSetDepthTestEnableEXT                                          VKAD_USER_DEVICE.CmdSetDepthTestEnableEXT                                  
#define vkCmdSetDepthWriteEnableEXT                                         VKAD_USER_DEVICE.CmdSetDepthWriteEnableEXT                                 
#define vkCmdSetDepthCompareOpEXT                                           VKAD_USER_DEVICE.CmdSetDepthCompareOpEXT                                   
#define vkCmdSetDepthBoundsTestEnableEXT                                    VKAD_USER_DEVICE.CmdSetDepthBoundsTestEnableEXT                            
#define vkCmdSetStencilTestEnableEXT                                        VKAD_USER_DEVICE.CmdSetStencilTestEnableEXT                                
#define vkCmdSetStencilOpEXT                                                VKAD_USER_DEVICE.CmdSetStencilOpEXT                                        
        /* VK_EXT_host_image_copy spec_version 1 */                         
#define vkCopyMemoryToImageEXT                                              VKAD_USER_DEVICE.CopyMemoryToImageEXT                                      
#define vkCopyImageToMemoryEXT                                              VKAD_USER_DEVICE.CopyImageToMemoryEXT                                      
#define vkCopyImageToImageEXT                                               VKAD_USER_DEVICE.CopyImageToImageEXT                                       
#define vkTransitionImageLayoutEXT                                          VKAD_USER_DEVICE.TransitionImageLayoutEXT                                  
#define vkGetImageSubresourceLayout2EXT                                     VKAD_USER_DEVICE.GetImageSubresourceLayout2EXT                             
        /* VK_EXT_swapchain_maintenance1 spec_version 1 */                  
#define vkReleaseSwapchainImagesEXT                                         VKAD_USER_DEVICE.ReleaseSwapchainImagesEXT                                 
        /* VK_NV_device_generated_commands spec_version 3 */                
#define vkGetGeneratedCommandsMemoryRequirementsNV                          VKAD_USER_DEVICE.GetGeneratedCommandsMemoryRequirementsNV                  
#define vkCmdPreprocessGeneratedCommandsNV                                  VKAD_USER_DEVICE.CmdPreprocessGeneratedCommandsNV                          
#define vkCmdExecuteGeneratedCommandsNV                                     VKAD_USER_DEVICE.CmdExecuteGeneratedCommandsNV                             
#define vkCmdBindPipelineShaderGroupNV                                      VKAD_USER_DEVICE.CmdBindPipelineShaderGroupNV                              
#define vkCreateIndirectCommandsLayoutNV                                    VKAD_USER_DEVICE.CreateIndirectCommandsLayoutNV                            
#define vkDestroyIndirectCommandsLayoutNV                                   VKAD_USER_DEVICE.DestroyIndirectCommandsLayoutNV                           
        /* VK_EXT_depth_bias_control spec_version 1 */                      
#define vkCmdSetDepthBias2EXT                                               VKAD_USER_DEVICE.CmdSetDepthBias2EXT                                       
        /* VK_EXT_private_data spec_version 1 */                            
#define vkCreatePrivateDataSlotEXT                                          VKAD_USER_DEVICE.CreatePrivateDataSlotEXT                                  
#define vkDestroyPrivateDataSlotEXT                                         VKAD_USER_DEVICE.DestroyPrivateDataSlotEXT                                 
#define vkSetPrivateDataEXT                                                 VKAD_USER_DEVICE.SetPrivateDataEXT                                         
#define vkGetPrivateDataEXT                                                 VKAD_USER_DEVICE.GetPrivateDataEXT                                         
        /* VK_NV_cuda_kernel_launch spec_version 2 */                       
#define vkCreateCudaModuleNV                                                VKAD_USER_DEVICE.CreateCudaModuleNV                                        
#define vkGetCudaModuleCacheNV                                              VKAD_USER_DEVICE.GetCudaModuleCacheNV                                      
#define vkCreateCudaFunctionNV                                              VKAD_USER_DEVICE.CreateCudaFunctionNV                                      
#define vkDestroyCudaModuleNV                                               VKAD_USER_DEVICE.DestroyCudaModuleNV                                       
#define vkDestroyCudaFunctionNV                                             VKAD_USER_DEVICE.DestroyCudaFunctionNV                                     
#define vkCmdCudaLaunchKernelNV                                             VKAD_USER_DEVICE.CmdCudaLaunchKernelNV                                     
        /* VK_EXT_descriptor_buffer spec_version 1 */                       
#define vkGetDescriptorSetLayoutSizeEXT                                     VKAD_USER_DEVICE.GetDescriptorSetLayoutSizeEXT                             
#define vkGetDescriptorSetLayoutBindingOffsetEXT                            VKAD_USER_DEVICE.GetDescriptorSetLayoutBindingOffsetEXT                      
#define vkGetDescriptorEXT                                                  VKAD_USER_DEVICE.GetDescriptorEXT                                            
#define vkCmdBindDescriptorBuffersEXT                                       VKAD_USER_DEVICE.CmdBindDescriptorBuffersEXT                                 
#define vkCmdSetDescriptorBufferOffsetsEXT                                  VKAD_USER_DEVICE.CmdSetDescriptorBufferOffsetsEXT                            
#define vkCmdBindDescriptorBufferEmbeddedSamplersEXT                        VKAD_USER_DEVICE.CmdBindDescriptorBufferEmbeddedSamplersEXT                  
#define vkGetBufferOpaqueCaptureDescriptorDataEXT                           VKAD_USER_DEVICE.GetBufferOpaqueCaptureDescriptorDataEXT                     
#define vkGetImageOpaqueCaptureDescriptorDataEXT                            VKAD_USER_DEVICE.GetImageOpaqueCaptureDescriptorDataEXT                      
#define vkGetImageViewOpaqueCaptureDescriptorDataEXT                        VKAD_USER_DEVICE.GetImageViewOpaqueCaptureDescriptorDataEXT                  
#define vkGetSamplerOpaqueCaptureDescriptorDataEXT                          VKAD_USER_DEVICE.GetSamplerOpaqueCaptureDescriptorDataEXT                    
#define vkGetAccelerationStructureOpaqueCaptureDescriptorDataEXT            VKAD_USER_DEVICE.GetAccelerationStructureOpaqueCaptureDescriptorDataEXT      
        /* VK_NV_fragment_shading_rate_enums spec_version 1 */              
#define vkCmdSetFragmentShadingRateEnumNV                                   VKAD_USER_DEVICE.CmdSetFragmentShadingRateEnumNV                             
        /* VK_EXT_device_fault spec_version 2 */                            
#define vkGetDeviceFaultInfoEXT                                             VKAD_USER_DEVICE.GetDeviceFaultInfoEXT                                       
        /* VK_EXT_vertex_input_dynamic_state spec_version 2 */              
#define vkCmdSetVertexInputEXT                                              VKAD_USER_DEVICE.CmdSetVertexInputEXT                                        
        /* VK_HUAWEI_subpass_shading spec_version 3 */                      
#define vkGetDeviceSubpassShadingMaxWorkgroupSizeHUAWEI                     VKAD_USER_DEVICE.GetDeviceSubpassShadingMaxWorkgroupSizeHUAWEI               
#define vkCmdSubpassShadingHUAWEI                                           VKAD_USER_DEVICE.CmdSubpassShadingHUAWEI                                     
        /* VK_HUAWEI_invocation_mask spec_version 1 */                      
#define vkCmdBindInvocationMaskHUAWEI                                       VKAD_USER_DEVICE.CmdBindInvocationMaskHUAWEI                                 
        /* VK_NV_external_memory_rdma spec_version 1 */                     
#define vkGetMemoryRemoteAddressNV                                          VKAD_USER_DEVICE.GetMemoryRemoteAddressNV                                    
        /* VK_EXT_pipeline_properties spec_version 1 */                     
#define vkGetPipelinePropertiesEXT                                          VKAD_USER_DEVICE.GetPipelinePropertiesEXT                                    
        /* VK_EXT_extended_dynamic_state2 spec_version 1 */                 
#define vkCmdSetPatchControlPointsEXT                                       VKAD_USER_DEVICE.CmdSetPatchControlPointsEXT                                 
#define vkCmdSetRasterizerDiscardEnableEXT                                  VKAD_USER_DEVICE.CmdSetRasterizerDiscardEnableEXT                            
#define vkCmdSetDepthBiasEnableEXT                                          VKAD_USER_DEVICE.CmdSetDepthBiasEnableEXT                                    
#define vkCmdSetLogicOpEXT                                                  VKAD_USER_DEVICE.CmdSetLogicOpEXT                                            
#define vkCmdSetPrimitiveRestartEnableEXT                                   VKAD_USER_DEVICE.CmdSetPrimitiveRestartEnableEXT                             
        /* VK_EXT_color_write_enable spec_version 1 */                      
#define vkCmdSetColorWriteEnableEXT                                         VKAD_USER_DEVICE.CmdSetColorWriteEnableEXT                                   
        /* VK_EXT_multi_draw spec_version 1 */                              
#define vkCmdDrawMultiEXT                                                   VKAD_USER_DEVICE.CmdDrawMultiEXT                                             
#define vkCmdDrawMultiIndexedEXT                                            VKAD_USER_DEVICE.CmdDrawMultiIndexedEXT                                      
        /* VK_EXT_opacity_micromap spec_version 2 */                        
#define vkCreateMicromapEXT                                                 VKAD_USER_DEVICE.CreateMicromapEXT                                           
#define vkDestroyMicromapEXT                                                VKAD_USER_DEVICE.DestroyMicromapEXT                                          
#define vkCmdBuildMicromapsEXT                                              VKAD_USER_DEVICE.CmdBuildMicromapsEXT                                        
#define vkBuildMicromapsEXT                                                 VKAD_USER_DEVICE.BuildMicromapsEXT                                           
#define vkCopyMicromapEXT                                                   VKAD_USER_DEVICE.CopyMicromapEXT                                             
#define vkCopyMicromapToMemoryEXT                                           VKAD_USER_DEVICE.CopyMicromapToMemoryEXT                                     
#define vkCopyMemoryToMicromapEXT                                           VKAD_USER_DEVICE.CopyMemoryToMicromapEXT                                     
#define vkWriteMicromapsPropertiesEXT                                       VKAD_USER_DEVICE.WriteMicromapsPropertiesEXT                                 
#define vkCmdCopyMicromapEXT                                                VKAD_USER_DEVICE.CmdCopyMicromapEXT                                          
#define vkCmdCopyMicromapToMemoryEXT                                        VKAD_USER_DEVICE.CmdCopyMicromapToMemoryEXT                                
#define vkCmdCopyMemoryToMicromapEXT                                        VKAD_USER_DEVICE.CmdCopyMemoryToMicromapEXT                                
#define vkCmdWriteMicromapsPropertiesEXT                                    VKAD_USER_DEVICE.CmdWriteMicromapsPropertiesEXT                            
#define vkGetDeviceMicromapCompatibilityEXT                                 VKAD_USER_DEVICE.GetDeviceMicromapCompatibilityEXT                         
#define vkGetMicromapBuildSizesEXT                                          VKAD_USER_DEVICE.GetMicromapBuildSizesEXT                                  
        /* VK_HUAWEI_cluster_culling_shader spec_version 3 */               
#define vkCmdDrawClusterHUAWEI                                              VKAD_USER_DEVICE.CmdDrawClusterHUAWEI                                      
#define vkCmdDrawClusterIndirectHUAWEI                                      VKAD_USER_DEVICE.CmdDrawClusterIndirectHUAWEI                              
        /* VK_EXT_pageable_device_local_memory spec_version 1 */            
#define vkSetDeviceMemoryPriorityEXT                                        VKAD_USER_DEVICE.SetDeviceMemoryPriorityEXT                                
        /* VK_VALVE_descriptor_set_host_mapping spec_version 1 */           
#define vkGetDescriptorSetLayoutHostMappingInfoVALVE                        VKAD_USER_DEVICE.GetDescriptorSetLayoutHostMappingInfoVALVE                
#define vkGetDescriptorSetHostMappingVALVE                                  VKAD_USER_DEVICE.GetDescriptorSetHostMappingVALVE                          
        /* VK_NV_copy_memory_indirect spec_version 1 */                     
#define vkCmdCopyMemoryIndirectNV                                           VKAD_USER_DEVICE.CmdCopyMemoryIndirectNV                                   
#define vkCmdCopyMemoryToImageIndirectNV                                    VKAD_USER_DEVICE.CmdCopyMemoryToImageIndirectNV                            
        /* VK_NV_memory_decompression spec_version 1 */                     
#define vkCmdDecompressMemoryNV                                             VKAD_USER_DEVICE.CmdDecompressMemoryNV                                     
#define vkCmdDecompressMemoryIndirectCountNV                                VKAD_USER_DEVICE.CmdDecompressMemoryIndirectCountNV                        
        /* VK_NV_device_generated_commands_compute spec_version 2 */        
#define vkGetPipelineIndirectMemoryRequirementsNV                           VKAD_USER_DEVICE.GetPipelineIndirectMemoryRequirementsNV                   
#define vkCmdUpdatePipelineIndirectBufferNV                                 VKAD_USER_DEVICE.CmdUpdatePipelineIndirectBufferNV                         
#define vkGetPipelineIndirectDeviceAddressNV                                VKAD_USER_DEVICE.GetPipelineIndirectDeviceAddressNV                        
        /* VK_EXT_extended_dynamic_state3 spec_version 2 */                 
#define vkCmdSetDepthClampEnableEXT                                         VKAD_USER_DEVICE.CmdSetDepthClampEnableEXT                                 
#define vkCmdSetPolygonModeEXT                                              VKAD_USER_DEVICE.CmdSetPolygonModeEXT                                      
#define vkCmdSetRasterizationSamplesEXT                                     VKAD_USER_DEVICE.CmdSetRasterizationSamplesEXT                             
#define vkCmdSetSampleMaskEXT                                               VKAD_USER_DEVICE.CmdSetSampleMaskEXT                                       
#define vkCmdSetAlphaToCoverageEnableEXT                                    VKAD_USER_DEVICE.CmdSetAlphaToCoverageEnableEXT                            
#define vkCmdSetAlphaToOneEnableEXT                                         VKAD_USER_DEVICE.CmdSetAlphaToOneEnableEXT                                 
#define vkCmdSetLogicOpEnableEXT                                            VKAD_USER_DEVICE.CmdSetLogicOpEnableEXT                                    
#define vkCmdSetColorBlendEnableEXT                                         VKAD_USER_DEVICE.CmdSetColorBlendEnableEXT                                 
#define vkCmdSetColorBlendEquationEXT                                       VKAD_USER_DEVICE.CmdSetColorBlendEquationEXT                               
#define vkCmdSetColorWriteMaskEXT                                           VKAD_USER_DEVICE.CmdSetColorWriteMaskEXT                                   
#define vkCmdSetTessellationDomainOriginEXT                                 VKAD_USER_DEVICE.CmdSetTessellationDomainOriginEXT                         
#define vkCmdSetRasterizationStreamEXT                                      VKAD_USER_DEVICE.CmdSetRasterizationStreamEXT                              
#define vkCmdSetConservativeRasterizationModeEXT                            VKAD_USER_DEVICE.CmdSetConservativeRasterizationModeEXT                    
#define vkCmdSetExtraPrimitiveOverestimationSizeEXT                         VKAD_USER_DEVICE.CmdSetExtraPrimitiveOverestimationSizeEXT                 
#define vkCmdSetDepthClipEnableEXT                                          VKAD_USER_DEVICE.CmdSetDepthClipEnableEXT                                  
#define vkCmdSetSampleLocationsEnableEXT                                    VKAD_USER_DEVICE.CmdSetSampleLocationsEnableEXT                            
#define vkCmdSetColorBlendAdvancedEXT                                       VKAD_USER_DEVICE.CmdSetColorBlendAdvancedEXT                               
#define vkCmdSetProvokingVertexModeEXT                                      VKAD_USER_DEVICE.CmdSetProvokingVertexModeEXT                              
#define vkCmdSetLineRasterizationModeEXT                                    VKAD_USER_DEVICE.CmdSetLineRasterizationModeEXT                            
#define vkCmdSetLineStippleEnableEXT                                        VKAD_USER_DEVICE.CmdSetLineStippleEnableEXT                                
#define vkCmdSetDepthClipNegativeOneToOneEXT                                VKAD_USER_DEVICE.CmdSetDepthClipNegativeOneToOneEXT                        
#define vkCmdSetViewportWScalingEnableNV                                    VKAD_USER_DEVICE.CmdSetViewportWScalingEnableNV                            
#define vkCmdSetViewportSwizzleNV                                           VKAD_USER_DEVICE.CmdSetViewportSwizzleNV                                   
#define vkCmdSetCoverageToColorEnableNV                                     VKAD_USER_DEVICE.CmdSetCoverageToColorEnableNV                             
#define vkCmdSetCoverageToColorLocationNV                                   VKAD_USER_DEVICE.CmdSetCoverageToColorLocationNV                           
#define vkCmdSetCoverageModulationModeNV                                    VKAD_USER_DEVICE.CmdSetCoverageModulationModeNV                            
#define vkCmdSetCoverageModulationTableEnableNV                             VKAD_USER_DEVICE.CmdSetCoverageModulationTableEnableNV                     
#define vkCmdSetCoverageModulationTableNV                                   VKAD_USER_DEVICE.CmdSetCoverageModulationTableNV                           
#define vkCmdSetShadingRateImageEnableNV                                    VKAD_USER_DEVICE.CmdSetShadingRateImageEnableNV                            
#define vkCmdSetRepresentativeFragmentTestEnableNV                          VKAD_USER_DEVICE.CmdSetRepresentativeFragmentTestEnableNV                  
#define vkCmdSetCoverageReductionModeNV                                     VKAD_USER_DEVICE.CmdSetCoverageReductionModeNV                             
        /* VK_EXT_shader_module_identifier spec_version 1 */                
#define vkGetShaderModuleIdentifierEXT                                      VKAD_USER_DEVICE.GetShaderModuleIdentifierEXT                              
#define vkGetShaderModuleCreateInfoIdentifierEXT                            VKAD_USER_DEVICE.GetShaderModuleCreateInfoIdentifierEXT                    
        /* VK_NV_optical_flow spec_version 1 */                             
#define vkCreateOpticalFlowSessionNV                                        VKAD_USER_DEVICE.CreateOpticalFlowSessionNV                                
#define vkDestroyOpticalFlowSessionNV                                       VKAD_USER_DEVICE.DestroyOpticalFlowSessionNV                               
#define vkBindOpticalFlowSessionImageNV                                     VKAD_USER_DEVICE.BindOpticalFlowSessionImageNV                             
#define vkCmdOpticalFlowExecuteNV                                           VKAD_USER_DEVICE.CmdOpticalFlowExecuteNV                                   
        /* VK_EXT_shader_object spec_version 1 */                           
#define vkCreateShadersEXT                                                  VKAD_USER_DEVICE.CreateShadersEXT                                          
#define vkDestroyShaderEXT                                                  VKAD_USER_DEVICE.DestroyShaderEXT                                          
#define vkGetShaderBinaryDataEXT                                            VKAD_USER_DEVICE.GetShaderBinaryDataEXT                                    
#define vkCmdBindShadersEXT                                                 VKAD_USER_DEVICE.CmdBindShadersEXT                                         
        /* VK_QCOM_tile_properties spec_version 1 */                        
#define vkGetFramebufferTilePropertiesQCOM                                  VKAD_USER_DEVICE.GetFramebufferTilePropertiesQCOM                          
#define vkGetDynamicRenderingTilePropertiesQCOM                             VKAD_USER_DEVICE.GetDynamicRenderingTilePropertiesQCOM                     
        /* VK_NV_low_latency2 spec_version 2 */                             
#define vkSetLatencySleepModeNV                                             VKAD_USER_DEVICE.SetLatencySleepModeNV                                     
#define vkLatencySleepNV                                                    VKAD_USER_DEVICE.LatencySleepNV                                            
#define vkSetLatencyMarkerNV                                                VKAD_USER_DEVICE.SetLatencyMarkerNV                                        
#define vkGetLatencyTimingsNV                                               VKAD_USER_DEVICE.GetLatencyTimingsNV                                       
#define vkQueueNotifyOutOfBandNV                                            VKAD_USER_DEVICE.QueueNotifyOutOfBandNV                                    
        /* VK_EXT_attachment_feedback_loop_dynamic_state spec_version 1 */  
#define vkCmdSetAttachmentFeedbackLoopEnableEXT                             VKAD_USER_DEVICE.CmdSetAttachmentFeedbackLoopEnableEXT                     
        /* VK_KHR_acceleration_structure spec_version 13 */                 
#define vkCreateAccelerationStructureKHR                                    VKAD_USER_DEVICE.CreateAccelerationStructureKHR                            
#define vkDestroyAccelerationStructureKHR                                   VKAD_USER_DEVICE.DestroyAccelerationStructureKHR                           
#define vkCmdBuildAccelerationStructuresKHR                                 VKAD_USER_DEVICE.CmdBuildAccelerationStructuresKHR                         
#define vkCmdBuildAccelerationStructuresIndirectKHR                         VKAD_USER_DEVICE.CmdBuildAccelerationStructuresIndirectKHR                 
#define vkBuildAccelerationStructuresKHR                                    VKAD_USER_DEVICE.BuildAccelerationStructuresKHR                            
#define vkCopyAccelerationStructureKHR                                      VKAD_USER_DEVICE.CopyAccelerationStructureKHR                              
#define vkCopyAccelerationStructureToMemoryKHR                              VKAD_USER_DEVICE.CopyAccelerationStructureToMemoryKHR                      
#define vkCopyMemoryToAccelerationStructureKHR                              VKAD_USER_DEVICE.CopyMemoryToAccelerationStructureKHR                      
#define vkWriteAccelerationStructuresPropertiesKHR                          VKAD_USER_DEVICE.WriteAccelerationStructuresPropertiesKHR                  
#define vkCmdCopyAccelerationStructureKHR                                   VKAD_USER_DEVICE.CmdCopyAccelerationStructureKHR                           
#define vkCmdCopyAccelerationStructureToMemoryKHR                           VKAD_USER_DEVICE.CmdCopyAccelerationStructureToMemoryKHR                   
#define vkCmdCopyMemoryToAccelerationStructureKHR                           VKAD_USER_DEVICE.CmdCopyMemoryToAccelerationStructureKHR                   
#define vkGetAccelerationStructureDeviceAddressKHR                          VKAD_USER_DEVICE.GetAccelerationStructureDeviceAddressKHR                  
#define vkCmdWriteAccelerationStructuresPropertiesKHR                       VKAD_USER_DEVICE.CmdWriteAccelerationStructuresPropertiesKHR               
#define vkGetDeviceAccelerationStructureCompatibilityKHR                    VKAD_USER_DEVICE.GetDeviceAccelerationStructureCompatibilityKHR            
#define vkGetAccelerationStructureBuildSizesKHR                             VKAD_USER_DEVICE.GetAccelerationStructureBuildSizesKHR                     
        /* VK_KHR_ray_tracing_pipeline spec_version 1 */                    
#define vkCmdTraceRaysKHR                                                   VKAD_USER_DEVICE.CmdTraceRaysKHR                                           
#define vkCreateRayTracingPipelinesKHR                                      VKAD_USER_DEVICE.CreateRayTracingPipelinesKHR                              
#define vkGetRayTracingCaptureReplayShaderGroupHandlesKHR                   VKAD_USER_DEVICE.GetRayTracingCaptureReplayShaderGroupHandlesKHR           
#define vkCmdTraceRaysIndirectKHR                                           VKAD_USER_DEVICE.CmdTraceRaysIndirectKHR                                   
#define vkGetRayTracingShaderGroupStackSizeKHR                              VKAD_USER_DEVICE.GetRayTracingShaderGroupStackSizeKHR                      
#define vkCmdSetRayTracingPipelineStackSizeKHR                              VKAD_USER_DEVICE.CmdSetRayTracingPipelineStackSizeKHR                      
        /* VK_EXT_mesh_shader spec_version 1 */                             
#define vkCmdDrawMeshTasksEXT                                               VKAD_USER_DEVICE.CmdDrawMeshTasksEXT                                       
#define vkCmdDrawMeshTasksIndirectEXT                                       VKAD_USER_DEVICE.CmdDrawMeshTasksIndirectEXT                               
#define vkCmdDrawMeshTasksIndirectCountEXT                                  VKAD_USER_DEVICE.CmdDrawMeshTasksIndirectCountEXT                          
        /* VK_ANDROID_external_memory_android_hardware_buffer spec_version 5VKAD_USER_DEVICE. */ 
#define vkGetAndroidHardwareBufferPropertiesANDROID                         VKAD_USER_DEVICE.GetAndroidHardwareBufferPropertiesANDROID                 
#define vkGetMemoryAndroidHardwareBufferANDROID                             VKAD_USER_DEVICE.GetMemoryAndroidHardwareBufferANDROID                     
        /* VK_FUCHSIA_external_memory spec_version 1 */                     
#define vkGetMemoryZirconHandleFUCHSIA                                      VKAD_USER_DEVICE.GetMemoryZirconHandleFUCHSIA                              
#define vkGetMemoryZirconHandlePropertiesFUCHSIA                            VKAD_USER_DEVICE.GetMemoryZirconHandlePropertiesFUCHSIA                    
        /* VK_FUCHSIA_external_semaphore spec_version 1 */                  
#define vkImportSemaphoreZirconHandleFUCHSIA                                VKAD_USER_DEVICE.ImportSemaphoreZirconHandleFUCHSIA                        
#define vkGetSemaphoreZirconHandleFUCHSIA                                   VKAD_USER_DEVICE.GetSemaphoreZirconHandleFUCHSIA                           
        /* VK_FUCHSIA_buffer_collection spec_version 2 */                   
#define vkCreateBufferCollectionFUCHSIA                                     VKAD_USER_DEVICE.CreateBufferCollectionFUCHSIA                             
#define vkSetBufferCollectionImageConstraintsFUCHSIA                        VKAD_USER_DEVICE.SetBufferCollectionImageConstraintsFUCHSIA                
#define vkSetBufferCollectionBufferConstraintsFUCHSIA                       VKAD_USER_DEVICE.SetBufferCollectionBufferConstraintsFUCHSIA               
#define vkDestroyBufferCollectionFUCHSIA                                    VKAD_USER_DEVICE.DestroyBufferCollectionFUCHSIA                            
#define vkGetBufferCollectionPropertiesFUCHSIA                              VKAD_USER_DEVICE.GetBufferCollectionPropertiesFUCHSIA                      
        /* VK_EXT_metal_objects spec_version 2 */                           
#define vkExportMetalObjectsEXT                                             VKAD_USER_DEVICE.ExportMetalObjectsEXT                                     
        /* VK_KHR_external_memory_win32 spec_version 1 */                   
#define vkGetMemoryWin32HandleKHR                                           VKAD_USER_DEVICE.GetMemoryWin32HandleKHR                                   
#define vkGetMemoryWin32HandlePropertiesKHR                                 VKAD_USER_DEVICE.GetMemoryWin32HandlePropertiesKHR                         
        /* VK_KHR_external_semaphore_win32 spec_version 1 */                
#define vkImportSemaphoreWin32HandleKHR                                     VKAD_USER_DEVICE.ImportSemaphoreWin32HandleKHR                             
#define vkGetSemaphoreWin32HandleKHR                                        VKAD_USER_DEVICE.GetSemaphoreWin32HandleKHR                                
        /* VK_KHR_external_fence_win32 spec_version 1 */                    
#define vkImportFenceWin32HandleKHR                                         VKAD_USER_DEVICE.ImportFenceWin32HandleKHR                                 
#define vkGetFenceWin32HandleKHR                                            VKAD_USER_DEVICE.GetFenceWin32HandleKHR                                    
        /* VK_NV_external_memory_win32 spec_version 1 */                    
#define vkGetMemoryWin32HandleNV                                            VKAD_USER_DEVICE.GetMemoryWin32HandleNV                                    
        /* VK_EXT_full_screen_exclusive spec_version 4 */                   
#define vkAcquireFullScreenExclusiveModeEXT                                 VKAD_USER_DEVICE.AcquireFullScreenExclusiveModeEXT                         
#define vkReleaseFullScreenExclusiveModeEXT                                 VKAD_USER_DEVICE.ReleaseFullScreenExclusiveModeEXT                         
#define vkGetDeviceGroupSurfacePresentModes2EXT                             VKAD_USER_DEVICE.GetDeviceGroupSurfacePresentModes2EXT                     
        /* VK_QNX_external_memory_screen_buffer spec_version 1 */           
#define vkGetScreenBufferPropertiesQNX                                      VKAD_USER_DEVICE.GetScreenBufferPropertiesQNX                              
        /* VK_AMDX_shader_enqueue spec_version 2 */
#define vkCreateExecutionGraphPipelinesAMDX                                 VKAD_USER_DEVICE.CreateExecutionGraphPipelinesAMDX                         
#define vkGetExecutionGraphPipelineScratchSizeAMDX                          VKAD_USER_DEVICE.GetExecutionGraphPipelineScratchSizeAMDX                  
#define vkGetExecutionGraphPipelineNodeIndexAMDX                            VKAD_USER_DEVICE.GetExecutionGraphPipelineNodeIndexAMDX                    
#define vkCmdInitializeGraphScratchMemoryAMDX                               VKAD_USER_DEVICE.CmdInitializeGraphScratchMemoryAMDX                       
#define vkCmdDispatchGraphAMDX                                              VKAD_USER_DEVICE.CmdDispatchGraphAMDX                                      
#define vkCmdDispatchGraphIndirectAMDX                                      VKAD_USER_DEVICE.CmdDispatchGraphIndirectAMDX                               
#define vkCmdDispatchGraphIndirectCountAMDX                                 VKAD_USER_DEVICE.CmdDispatchGraphIndirectCountAMDX
                /* Additions from 1.3.284 to 1.4.309: */
        /* to VK_NVX_image_view_handle spec_version 3 */
#define vkGetImageViewHandle64NVX                                           VKAD_USER_DEVICE.GetImageViewHandle64NVX
        /* to VK_EXT_shader_object spec_version 1 */
#define vkCmdSetDepthClampRangeEXT                                          VKAD_USER_DEVICE.CmdSetDepthClampRangeEXT
        /* VK_VERSION_1_4 */
#define vkCmdSetLineStipple                                                 VKAD_USER_DEVICE.CmdSetLineStipple
#define vkMapMemory2                                                        VKAD_USER_DEVICE.MapMemory2
#define vkUnmapMemory2                                                      VKAD_USER_DEVICE.UnmapMemory2
#define vkCmdBindIndexBuffer2                                               VKAD_USER_DEVICE.CmdBindIndexBuffer2
#define vkGetRenderingAreaGranularity                                       VKAD_USER_DEVICE.GetRenderingAreaGranularity
#define vkGetDeviceImageSubresourceLayout                                   VKAD_USER_DEVICE.GetDeviceImageSubresourceLayout
#define vkGetImageSubresourceLayout2                                        VKAD_USER_DEVICE.GetImageSubresourceLayout2
#define vkCmdPushDescriptorSet                                              VKAD_USER_DEVICE.CmdPushDescriptorSet
#define vkCmdPushDescriptorSetWithTemplate                                  VKAD_USER_DEVICE.CmdPushDescriptorSetWithTemplate
#define vkCmdSetRenderingAttachmentLocations                                VKAD_USER_DEVICE.CmdSetRenderingAttachmentLocations
#define vkCmdSetRenderingInputAttachmentIndices                             VKAD_USER_DEVICE.CmdSetRenderingInputAttachmentIndices
#define vkCmdBindDescriptorSets2                                            VKAD_USER_DEVICE.CmdBindDescriptorSets2
#define vkCmdPushConstants2                                                 VKAD_USER_DEVICE.CmdPushConstants2
#define vkCmdPushDescriptorSet2                                             VKAD_USER_DEVICE.CmdPushDescriptorSet2
#define vkCmdPushDescriptorSetWithTemplate2                                 VKAD_USER_DEVICE.CmdPushDescriptorSetWithTemplate2
#define vkCopyMemoryToImage                                                 VKAD_USER_DEVICE.CopyMemoryToImage
#define vkCopyImageToMemory                                                 VKAD_USER_DEVICE.CopyImageToMemory
#define vkCopyImageToImage                                                  VKAD_USER_DEVICE.CopyImageToImage
#define vkTransitionImageLayout                                             VKAD_USER_DEVICE.TransitionImageLayout
        /* VK_KHR_pipeline_binary spec_version 1 */
#define vkCreatePipelineBinariesKHR                                         VKAD_USER_DEVICE.CreatePipelineBinariesKHR
#define vkDestroyPipelineBinaryKHR                                          VKAD_USER_DEVICE.DestroyPipelineBinaryKHR
#define vkGetPipelineKeyKHR                                                 VKAD_USER_DEVICE.GetPipelineKeyKHR
#define vkGetPipelineBinaryDataKHR                                          VKAD_USER_DEVICE.GetPipelineBinaryDataKHR
#define vkReleaseCapturedPipelineDataKHR                                    VKAD_USER_DEVICE.ReleaseCapturedPipelineDataKHR
        /* VK_AMD_anti_lag spec_version 1 */
#define vkAntiLagUpdateAMD                                                  VKAD_USER_DEVICE.AntiLagUpdateAMD
        /* VK_NV_cooperative_vector spec_version 4 */
#define vkConvertCooperativeVectorMatrixNV                                  VKAD_USER_DEVICE.ConvertCooperativeVectorMatrixNV
#define vkCmdConvertCooperativeVectorMatrixNV                               VKAD_USER_DEVICE.CmdConvertCooperativeVectorMatrixNV
        /* VK_NV_cluster_acceleration_structure spec_version 2 */
#define vkGetClusterAccelerationStructureBuildSizesNV                       VKAD_USER_DEVICE.GetClusterAccelerationStructureBuildSizesNV
#define vkCmdBuildClusterAccelerationStructureIndirectNV                    VKAD_USER_DEVICE.CmdBuildClusterAccelerationStructureIndirectNV
        /* VK_NV_partitioned_acceleration_structure spec_version 1 */
#define vkGetPartitionedAccelerationStructuresBuildSizesNV                  VKAD_USER_DEVICE.GetPartitionedAccelerationStructuresBuildSizesNV
#define vkCmdBuildPartitionedAccelerationStructuresNV                       VKAD_USER_DEVICE.CmdBuildPartitionedAccelerationStructuresNV
        /* VK_EXT_device_generated_commands spec_version 1 */
#define vkGetGeneratedCommandsMemoryRequirementsEXT                         VKAD_USER_DEVICE.GetGeneratedCommandsMemoryRequirementsEXT
#define vkCmdPreprocessGeneratedCommandsEXT                                 VKAD_USER_DEVICE.CmdPreprocessGeneratedCommandsEXT
#define vkCmdExecuteGeneratedCommandsEXT                                    VKAD_USER_DEVICE.CmdExecuteGeneratedCommandsEXT
#define vkCreateIndirectCommandsLayoutEXT                                   VKAD_USER_DEVICE.CreateIndirectCommandsLayoutEXT
#define vkDestroyIndirectCommandsLayoutEXT                                  VKAD_USER_DEVICE.DestroyIndirectCommandsLayoutEXT
#define vkCreateIndirectExecutionSetEXT                                     VKAD_USER_DEVICE.CreateIndirectExecutionSetEXT
#define vkDestroyIndirectExecutionSetEXT                                    VKAD_USER_DEVICE.DestroyIndirectExecutionSetEXT
#define vkUpdateIndirectExecutionSetPipelineEXT                             VKAD_USER_DEVICE.UpdateIndirectExecutionSetPipelineEXT
#define vkUpdateIndirectExecutionSetShaderEXT                               VKAD_USER_DEVICE.UpdateIndirectExecutionSetShaderEXT
        /* VK_EXT_external_memory_metal spec_version 1 */
#define vkGetMemoryMetalHandleEXT                                           VKAD_USER_DEVICE.GetMemoryMetalHandleEXT
#define vkGetMemoryMetalHandlePropertiesEXT                                 VKAD_USER_DEVICE.GetMemoryMetalHandlePropertiesEXT
    

#endif


#if defined(__cplusplus)
} /* extern "C" */
#endif

#endif        /* VKAD_H */
