


#define VK_NO_PROTOTYPES
#include <vulkan/vulkan.h>

#if VK_HEADER_VERSION < 238
#error "Vulkan headers are out of date! Download at least 1.3.238."
#endif



//globally dispatched functions
//VK_VERSION_1_0
PFN_vkGetInstanceProcAddr                  vkGetInstanceProcAddr;
PFN_vkEnumerateInstanceExtensionProperties vkEnumerateInstanceExtensionProperties;
PFN_vkEnumerateInstanceLayerProperties     vkEnumerateInstanceLayerProperties;
PFN_vkCreateInstance                       vkCreateInstance;
//VK_VERSION_1_1
PFN_vkEnumerateInstanceVersion             vkEnumerateInstanceVersion;


//VkInstance dispatched functions
//VK_VERSION_1_0
PFN_vkDestroyInstance                      vkDestroyInstance;
PFN_vkEnumeratePhysicalDevices             vkEnumeratePhysicalDevices;
//VK_VERSION_1_1
PFN_vkEnumeratePhysicalDeviceGroups        vkEnumeratePhysicalDeviceGroups;
//VK_KHR_surface
PFN_vkDestroySurfaceKHR                    vkDestroySurfaceKHR;
//VK_KHR_display
PFN_vkCreateDisplayPlaneSurfaceKHR         vkCreateDisplayPlaneSurfaceKHR;
//VK_KHR_device_group_creation
PFN_vkEnumeratePhysicalDeviceGroupsKHR     vkEnumeratePhysicalDeviceGroupsKHR;
//VK_EXT_debug_report
PFN_vkCreateDebugReportCallbackEXT         vkCreateDebugReportCallbackEXT;
PFN_vkDestroyDebugReportCallbackEXT        vkDestroyDebugReportCallbackEXT;
PFN_vkDebugReportMessageEXT                vkDebugReportMessageEXT;
//VK_EXT_debug_utils
PFN_vkCreateDebugUtilsMessengerEXT         vkCreateDebugUtilsMessengerEXT;
PFN_vkDestroyDebugUtilsMessengerEXT        vkDestroyDebugUtilsMessengerEXT;
PFN_vkSubmitDebugUtilsMessageEXT           vkSubmitDebugUtilsMessageEXT;
//VK_EXT_headless_surface
PFN_vkCreateHeadlessSurfaceEXT             vkCreateHeadlessSurfaceEXT;
#ifdef VK_USE_PLATFORM_ANDROID_KHR
//VK_KHR_android_surface
PFN_vkCreateAndroidSurfaceKHR vkCreateAndroidSurfaceKHR;
#endif
#ifdef VK_USE_PLATFORM_FUCHSIA
//VK_FUCHSIA_imagepipe_surface
PFN_vkCreateImagePipeSurfaceFUCHSIA vkCreateImagePipeSurfaceFUCHSIA;
#endif
#ifdef VK_USE_PLATFORM_IOS_MVK
//VK_MVK_ios_surface
PFN_vkCreateIOSSurfaceMVK vkCreateIOSSurfaceMVK;
#endif
#ifdef VK_USE_PLATFORM_MACOS_MVK
//VK_MVK_macos_surface
PFN_vkCreateMacOSSurfaceMVK vkCreateMacOSSurfaceMVK;
#endif
#ifdef VK_USE_PLATFORM_METAL_EXT
//VK_EXT_metal_surface
PFN_vkCreateMetalSurfaceEXT vkCreateMetalSurfaceEXT;
#endif
#ifdef VK_USE_PLATFORM_VI_NN
//VK_NN_vi_surface
PFN_vkCreateViSurfaceNN vkCreateViSurfaceNN;
#endif
#ifdef VK_USE_PLATFORM_WAYLAND_KHR
//VK_KHR_wayland_surface
PFN_vkCreateWaylandSurfaceKHR vkCreateWaylandSurfaceKHR;
#endif
#ifdef VK_USE_PLATFORM_WIN32_KHR
//VK_KHR_win32_surface
PFN_vkCreateWin32SurfaceKHR vkCreateWin32SurfaceKHR;
#endif
#ifdef VK_USE_PLATFORM_XCB_KHR
//VK_KHR_xcb_surface
PFN_vkCreateXcbSurfaceKHR vkCreateXcbSurfaceKHR;
#endif
#ifdef VK_USE_PLATFORM_XLIB_KHR
//VK_KHR_xlib_surface
PFN_vkCreateXlibSurfaceKHR vkCreateXlibSurfaceKHR;
#endif
#ifdef VK_USE_PLATFORM_DIRECTFB_EXT
//VK_EXT_directfb_surface
PFN_vkCreateDirectFBSurfaceEXT vkCreateDirectFBSurfaceEXT;
#endif
#ifdef VK_USE_PLATFORM_GGP
//VK_GGP_stream_descriptor_surface
PFN_vkCreateStreamDescriptorSurfaceGGP vkCreateStreamDescriptorSurfaceGGP;
#endif
#ifdef VK_USE_PLATFORM_SCREEN_QNX
//VK_QNX_screen_surface
PFN_vkCreateScreenSurfaceQNX vkCreateScreenSurfaceQNX;
#endif



//VkPhysicalDevice dispatched functions
//VK_VERSION_1_0
PFN_vkGetPhysicalDeviceFeatures                                       vkGetPhysicalDeviceFeatures;
PFN_vkGetPhysicalDeviceFormatProperties                               vkGetPhysicalDeviceFormatProperties;
PFN_vkGetPhysicalDeviceImageFormatProperties                          vkGetPhysicalDeviceImageFormatProperties;
PFN_vkGetPhysicalDeviceProperties                                     vkGetPhysicalDeviceProperties;
PFN_vkGetPhysicalDeviceQueueFamilyProperties                          vkGetPhysicalDeviceQueueFamilyProperties;
PFN_vkGetPhysicalDeviceMemoryProperties                               vkGetPhysicalDeviceMemoryProperties;
PFN_vkCreateDevice                                                    vkCreateDevice;
PFN_vkEnumerateDeviceExtensionProperties                              vkEnumerateDeviceExtensionProperties;
PFN_vkEnumerateDeviceLayerProperties                                  vkEnumerateDeviceLayerProperties;
PFN_vkGetPhysicalDeviceSparseImageFormatProperties                    vkGetPhysicalDeviceSparseImageFormatProperties;
//VK_VERSION_1_1
PFN_vkGetPhysicalDeviceFeatures2                                      vkGetPhysicalDeviceFeatures2;
PFN_vkGetPhysicalDeviceProperties2                                    vkGetPhysicalDeviceProperties2;
PFN_vkGetPhysicalDeviceFormatProperties2                              vkGetPhysicalDeviceFormatProperties2;
PFN_vkGetPhysicalDeviceImageFormatProperties2                         vkGetPhysicalDeviceImageFormatProperties2;
PFN_vkGetPhysicalDeviceQueueFamilyProperties2                         vkGetPhysicalDeviceQueueFamilyProperties2;
PFN_vkGetPhysicalDeviceMemoryProperties2                              vkGetPhysicalDeviceMemoryProperties2;
PFN_vkGetPhysicalDeviceSparseImageFormatProperties2                   vkGetPhysicalDeviceSparseImageFormatProperties2;
PFN_vkGetPhysicalDeviceExternalBufferProperties                       vkGetPhysicalDeviceExternalBufferProperties;
PFN_vkGetPhysicalDeviceExternalFenceProperties                        vkGetPhysicalDeviceExternalFenceProperties;
PFN_vkGetPhysicalDeviceExternalSemaphoreProperties                    vkGetPhysicalDeviceExternalSemaphoreProperties;
//VK_VERSION_1_3
PFN_vkGetPhysicalDeviceToolProperties                                 vkGetPhysicalDeviceToolProperties;
//VK_KHR_surface
PFN_vkGetPhysicalDeviceSurfaceSupportKHR                              vkGetPhysicalDeviceSurfaceSupportKHR;
PFN_vkGetPhysicalDeviceSurfaceCapabilitiesKHR                         vkGetPhysicalDeviceSurfaceCapabilitiesKHR;
PFN_vkGetPhysicalDeviceSurfaceFormatsKHR                              vkGetPhysicalDeviceSurfaceFormatsKHR;
PFN_vkGetPhysicalDeviceSurfacePresentModesKHR                         vkGetPhysicalDeviceSurfacePresentModesKHR;
//VK_KHR_swapchain
PFN_vkGetPhysicalDevicePresentRectanglesKHR                           vkGetPhysicalDevicePresentRectanglesKHR;
//VK_KHR_display
PFN_vkGetPhysicalDeviceDisplayPropertiesKHR                           vkGetPhysicalDeviceDisplayPropertiesKHR;
PFN_vkGetPhysicalDeviceDisplayPlanePropertiesKHR                      vkGetPhysicalDeviceDisplayPlanePropertiesKHR;
PFN_vkGetDisplayPlaneSupportedDisplaysKHR                             vkGetDisplayPlaneSupportedDisplaysKHR;
PFN_vkGetDisplayModePropertiesKHR                                     vkGetDisplayModePropertiesKHR;
PFN_vkCreateDisplayModeKHR                                            vkCreateDisplayModeKHR;
PFN_vkGetDisplayPlaneCapabilitiesKHR                                  vkGetDisplayPlaneCapabilitiesKHR;
//VK_KHR_video_queue
PFN_vkGetPhysicalDeviceVideoCapabilitiesKHR                           vkGetPhysicalDeviceVideoCapabilitiesKHR;
PFN_vkGetPhysicalDeviceVideoFormatPropertiesKHR                       vkGetPhysicalDeviceVideoFormatPropertiesKHR;
//VK_KHR_get_physical_device_properties2
PFN_vkGetPhysicalDeviceFeatures2KHR                                   vkGetPhysicalDeviceFeatures2KHR;
PFN_vkGetPhysicalDeviceProperties2KHR                                 vkGetPhysicalDeviceProperties2KHR;
PFN_vkGetPhysicalDeviceFormatProperties2KHR                           vkGetPhysicalDeviceFormatProperties2KHR;
PFN_vkGetPhysicalDeviceImageFormatProperties2KHR                      vkGetPhysicalDeviceImageFormatProperties2KHR;
PFN_vkGetPhysicalDeviceQueueFamilyProperties2KHR                      vkGetPhysicalDeviceQueueFamilyProperties2KHR;
PFN_vkGetPhysicalDeviceMemoryProperties2KHR                           vkGetPhysicalDeviceMemoryProperties2KHR;
PFN_vkGetPhysicalDeviceSparseImageFormatProperties2KHR                vkGetPhysicalDeviceSparseImageFormatProperties2KHR;
//VK_KHR_external_memory_capabilities
PFN_vkGetPhysicalDeviceExternalBufferPropertiesKHR                    vkGetPhysicalDeviceExternalBufferPropertiesKHR;
//VK_KHR_external_semaphore_capabilities
PFN_vkGetPhysicalDeviceExternalSemaphorePropertiesKHR                 vkGetPhysicalDeviceExternalSemaphorePropertiesKHR;
//VK_KHR_external_fence_capabilities
PFN_vkGetPhysicalDeviceExternalFencePropertiesKHR                     vkGetPhysicalDeviceExternalFencePropertiesKHR;
//VK_KHR_performance_query
PFN_vkEnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR   vkEnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR;
PFN_vkGetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR           vkGetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR;
//VK_KHR_get_surface_capabilities2
PFN_vkGetPhysicalDeviceSurfaceCapabilities2KHR                        vkGetPhysicalDeviceSurfaceCapabilities2KHR;
PFN_vkGetPhysicalDeviceSurfaceFormats2KHR                             vkGetPhysicalDeviceSurfaceFormats2KHR;
//VK_KHR_get_display_properties2
PFN_vkGetPhysicalDeviceDisplayProperties2KHR                          vkGetPhysicalDeviceDisplayProperties2KHR;
PFN_vkGetPhysicalDeviceDisplayPlaneProperties2KHR                     vkGetPhysicalDeviceDisplayPlaneProperties2KHR;
PFN_vkGetDisplayModeProperties2KHR                                    vkGetDisplayModeProperties2KHR;
PFN_vkGetDisplayPlaneCapabilities2KHR                                 vkGetDisplayPlaneCapabilities2KHR;
//VK_KHR_fragment_shading_rate
PFN_vkGetPhysicalDeviceFragmentShadingRatesKHR                        vkGetPhysicalDeviceFragmentShadingRatesKHR;
//VK_NV_external_memory_capabilities
PFN_vkGetPhysicalDeviceExternalImageFormatPropertiesNV                vkGetPhysicalDeviceExternalImageFormatPropertiesNV;
//VK_EXT_direct_mode_display
PFN_vkReleaseDisplayEXT                                               vkReleaseDisplayEXT;
//VK_EXT_display_surface_counter
PFN_vkGetPhysicalDeviceSurfaceCapabilities2EXT                        vkGetPhysicalDeviceSurfaceCapabilities2EXT;
//VK_EXT_sample_locations
PFN_vkGetPhysicalDeviceMultisamplePropertiesEXT                       vkGetPhysicalDeviceMultisamplePropertiesEXT;
//VK_EXT_calibrated_timestamps
PFN_vkGetPhysicalDeviceCalibrateableTimeDomainsEXT                    vkGetPhysicalDeviceCalibrateableTimeDomainsEXT;
//VK_EXT_tooling_info
PFN_vkGetPhysicalDeviceToolPropertiesEXT                              vkGetPhysicalDeviceToolPropertiesEXT;
//VK_NV_cooperative_matrix
PFN_vkGetPhysicalDeviceCooperativeMatrixPropertiesNV                  vkGetPhysicalDeviceCooperativeMatrixPropertiesNV;
//VK_NV_coverage_reduction_mode
PFN_vkGetPhysicalDeviceSupportedFramebufferMixedSamplesCombinationsNV vkGetPhysicalDeviceSupportedFramebufferMixedSamplesCombinationsNV;
//VK_EXT_acquire_drm_display
PFN_vkAcquireDrmDisplayEXT                                            vkAcquireDrmDisplayEXT;
PFN_vkGetDrmDisplayEXT                                                vkGetDrmDisplayEXT;
//VK_NV_optical_flow
PFN_vkGetPhysicalDeviceOpticalFlowImageFormatsNV                      vkGetPhysicalDeviceOpticalFlowImageFormatsNV;
#ifdef VK_USE_PLATFORM_WAYLAND_KHR
//VK_KHR_wayland_surface
PFN_vkGetPhysicalDeviceWaylandPresentationSupportKHR vkGetPhysicalDeviceWaylandPresentationSupportKHR;
#endif
#ifdef VK_USE_PLATFORM_WIN32_KHR
//VK_KHR_win32_surface
PFN_vkGetPhysicalDeviceWin32PresentationSupportKHR vkGetPhysicalDeviceWin32PresentationSupportKHR;
//VK_EXT_full_screen_exclusive
PFN_vkGetPhysicalDeviceSurfacePresentModes2EXT     vkGetPhysicalDeviceSurfacePresentModes2EXT;
//VK_NV_acquire_winrt_display
PFN_vkAcquireWinrtDisplayNV                        vkAcquireWinrtDisplayNV;
PFN_vkGetWinrtDisplayNV                            vkGetWinrtDisplayNV;
#endif
#ifdef VK_USE_PLATFORM_XCB_KHR
//VK_KHR_xcb_surface
PFN_vkGetPhysicalDeviceXcbPresentationSupportKHR vkGetPhysicalDeviceXcbPresentationSupportKHR;
#endif
#ifdef VK_USE_PLATFORM_XLIB_KHR
//VK_KHR_xlib_surface
PFN_vkGetPhysicalDeviceXlibPresentationSupportKHR vkGetPhysicalDeviceXlibPresentationSupportKHR;
#endif
#ifdef VK_USE_PLATFORM_DIRECTFB_EXT
//VK_EXT_directfb_surface
PFN_vkGetPhysicalDeviceDirectFBPresentationSupportEXT vkGetPhysicalDeviceDirectFBPresentationSupportEXT;
#endif
#ifdef VK_USE_PLATFORM_XLIB_XRANDR_EXT
//VK_EXT_acquire_xlib_display
PFN_vkAcquireXlibDisplayEXT    vkAcquireXlibDisplayEXT;
PFN_vkGetRandROutputDisplayEXT vkGetRandROutputDisplayEXT;
#endif
#ifdef VK_USE_PLATFORM_SCREEN_QNX
//VK_QNX_screen_surface
PFN_vkGetPhysicalDeviceScreenPresentationSupportQNX vkGetPhysicalDeviceScreenPresentationSupportQNX;
#endif



//VkDevice dispatched functions
//VK_VERSION_1_0
PFN_vkGetDeviceProcAddr                                      vkGetDeviceProcAddr;
PFN_vkDestroyDevice                                          vkDestroyDevice;
PFN_vkGetDeviceQueue                                         vkGetDeviceQueue;
PFN_vkDeviceWaitIdle                                         vkDeviceWaitIdle;
PFN_vkAllocateMemory                                         vkAllocateMemory;
PFN_vkFreeMemory                                             vkFreeMemory;
PFN_vkMapMemory                                              vkMapMemory;
PFN_vkUnmapMemory                                            vkUnmapMemory;
PFN_vkFlushMappedMemoryRanges                                vkFlushMappedMemoryRanges;
PFN_vkInvalidateMappedMemoryRanges                           vkInvalidateMappedMemoryRanges;
PFN_vkGetDeviceMemoryCommitment                              vkGetDeviceMemoryCommitment;
PFN_vkBindBufferMemory                                       vkBindBufferMemory;
PFN_vkBindImageMemory                                        vkBindImageMemory;
PFN_vkGetBufferMemoryRequirements                            vkGetBufferMemoryRequirements;
PFN_vkGetImageMemoryRequirements                             vkGetImageMemoryRequirements;
PFN_vkGetImageSparseMemoryRequirements                       vkGetImageSparseMemoryRequirements;
PFN_vkCreateFence                                            vkCreateFence;
PFN_vkDestroyFence                                           vkDestroyFence;
PFN_vkResetFences                                            vkResetFences;
PFN_vkGetFenceStatus                                         vkGetFenceStatus;
PFN_vkWaitForFences                                          vkWaitForFences;
PFN_vkCreateSemaphore                                        vkCreateSemaphore;
PFN_vkDestroySemaphore                                       vkDestroySemaphore;
PFN_vkCreateEvent                                            vkCreateEvent;
PFN_vkDestroyEvent                                           vkDestroyEvent;
PFN_vkGetEventStatus                                         vkGetEventStatus;
PFN_vkSetEvent                                               vkSetEvent;
PFN_vkResetEvent                                             vkResetEvent;
PFN_vkCreateQueryPool                                        vkCreateQueryPool;
PFN_vkDestroyQueryPool                                       vkDestroyQueryPool;
PFN_vkGetQueryPoolResults                                    vkGetQueryPoolResults;
PFN_vkCreateBuffer                                           vkCreateBuffer;
PFN_vkDestroyBuffer                                          vkDestroyBuffer;
PFN_vkCreateBufferView                                       vkCreateBufferView;
PFN_vkDestroyBufferView                                      vkDestroyBufferView;
PFN_vkCreateImage                                            vkCreateImage;
PFN_vkDestroyImage                                           vkDestroyImage;
PFN_vkGetImageSubresourceLayout                              vkGetImageSubresourceLayout;
PFN_vkCreateImageView                                        vkCreateImageView;
PFN_vkDestroyImageView                                       vkDestroyImageView;
PFN_vkCreateShaderModule                                     vkCreateShaderModule;
PFN_vkDestroyShaderModule                                    vkDestroyShaderModule;
PFN_vkCreatePipelineCache                                    vkCreatePipelineCache;
PFN_vkDestroyPipelineCache                                   vkDestroyPipelineCache;
PFN_vkGetPipelineCacheData                                   vkGetPipelineCacheData;
PFN_vkMergePipelineCaches                                    vkMergePipelineCaches;
PFN_vkCreateGraphicsPipelines                                vkCreateGraphicsPipelines;
PFN_vkCreateComputePipelines                                 vkCreateComputePipelines;
PFN_vkDestroyPipeline                                        vkDestroyPipeline;
PFN_vkCreatePipelineLayout                                   vkCreatePipelineLayout;
PFN_vkDestroyPipelineLayout                                  vkDestroyPipelineLayout;
PFN_vkCreateSampler                                          vkCreateSampler;
PFN_vkDestroySampler                                         vkDestroySampler;
PFN_vkCreateDescriptorSetLayout                              vkCreateDescriptorSetLayout;
PFN_vkDestroyDescriptorSetLayout                             vkDestroyDescriptorSetLayout;
PFN_vkCreateDescriptorPool                                   vkCreateDescriptorPool;
PFN_vkDestroyDescriptorPool                                  vkDestroyDescriptorPool;
PFN_vkResetDescriptorPool                                    vkResetDescriptorPool;
PFN_vkAllocateDescriptorSets                                 vkAllocateDescriptorSets;
PFN_vkFreeDescriptorSets                                     vkFreeDescriptorSets;
PFN_vkUpdateDescriptorSets                                   vkUpdateDescriptorSets;
PFN_vkCreateFramebuffer                                      vkCreateFramebuffer;
PFN_vkDestroyFramebuffer                                     vkDestroyFramebuffer;
PFN_vkCreateRenderPass                                       vkCreateRenderPass;
PFN_vkDestroyRenderPass                                      vkDestroyRenderPass;
PFN_vkGetRenderAreaGranularity                               vkGetRenderAreaGranularity;
PFN_vkCreateCommandPool                                      vkCreateCommandPool;
PFN_vkDestroyCommandPool                                     vkDestroyCommandPool;
PFN_vkResetCommandPool                                       vkResetCommandPool;
PFN_vkAllocateCommandBuffers                                 vkAllocateCommandBuffers;
PFN_vkFreeCommandBuffers                                     vkFreeCommandBuffers;
//VK_VERSION_1_1
PFN_vkBindBufferMemory2                                      vkBindBufferMemory2;
PFN_vkBindImageMemory2                                       vkBindImageMemory2;
PFN_vkGetDeviceGroupPeerMemoryFeatures                       vkGetDeviceGroupPeerMemoryFeatures;
PFN_vkGetImageMemoryRequirements2                            vkGetImageMemoryRequirements2;
PFN_vkGetBufferMemoryRequirements2                           vkGetBufferMemoryRequirements2;
PFN_vkGetImageSparseMemoryRequirements2                      vkGetImageSparseMemoryRequirements2;
PFN_vkTrimCommandPool                                        vkTrimCommandPool;
PFN_vkGetDeviceQueue2                                        vkGetDeviceQueue2;
PFN_vkCreateSamplerYcbcrConversion                           vkCreateSamplerYcbcrConversion;
PFN_vkDestroySamplerYcbcrConversion                          vkDestroySamplerYcbcrConversion;
PFN_vkCreateDescriptorUpdateTemplate                         vkCreateDescriptorUpdateTemplate;
PFN_vkDestroyDescriptorUpdateTemplate                        vkDestroyDescriptorUpdateTemplate;
PFN_vkUpdateDescriptorSetWithTemplate                        vkUpdateDescriptorSetWithTemplate;
PFN_vkGetDescriptorSetLayoutSupport                          vkGetDescriptorSetLayoutSupport;
//VK_VERSION_1_2
PFN_vkCreateRenderPass2                                      vkCreateRenderPass2;
PFN_vkResetQueryPool                                         vkResetQueryPool;
PFN_vkGetSemaphoreCounterValue                               vkGetSemaphoreCounterValue;
PFN_vkWaitSemaphores                                         vkWaitSemaphores;
PFN_vkSignalSemaphore                                        vkSignalSemaphore;
PFN_vkGetBufferDeviceAddress                                 vkGetBufferDeviceAddress;
PFN_vkGetBufferOpaqueCaptureAddress                          vkGetBufferOpaqueCaptureAddress;
PFN_vkGetDeviceMemoryOpaqueCaptureAddress                    vkGetDeviceMemoryOpaqueCaptureAddress;
//VK_VERSION_1_3
PFN_vkCreatePrivateDataSlot                                  vkCreatePrivateDataSlot;
PFN_vkDestroyPrivateDataSlot                                 vkDestroyPrivateDataSlot;
PFN_vkSetPrivateData                                         vkSetPrivateData;
PFN_vkGetPrivateData                                         vkGetPrivateData;
PFN_vkGetDeviceBufferMemoryRequirements                      vkGetDeviceBufferMemoryRequirements;
PFN_vkGetDeviceImageMemoryRequirements                       vkGetDeviceImageMemoryRequirements;
PFN_vkGetDeviceImageSparseMemoryRequirements                 vkGetDeviceImageSparseMemoryRequirements;
//VK_KHR_swapchain
PFN_vkCreateSwapchainKHR                                     vkCreateSwapchainKHR;
PFN_vkDestroySwapchainKHR                                    vkDestroySwapchainKHR;
PFN_vkGetSwapchainImagesKHR                                  vkGetSwapchainImagesKHR;
PFN_vkAcquireNextImageKHR                                    vkAcquireNextImageKHR;
PFN_vkGetDeviceGroupPresentCapabilitiesKHR                   vkGetDeviceGroupPresentCapabilitiesKHR;
PFN_vkGetDeviceGroupSurfacePresentModesKHR                   vkGetDeviceGroupSurfacePresentModesKHR;
PFN_vkAcquireNextImage2KHR                                   vkAcquireNextImage2KHR;
// VK_KHR_display_swapchain
PFN_vkCreateSharedSwapchainsKHR                              vkCreateSharedSwapchainsKHR;
//VK_KHR_video_queue
PFN_vkCreateVideoSessionKHR                                  vkCreateVideoSessionKHR;
PFN_vkDestroyVideoSessionKHR                                 vkDestroyVideoSessionKHR;
PFN_vkGetVideoSessionMemoryRequirementsKHR                   vkGetVideoSessionMemoryRequirementsKHR;
PFN_vkBindVideoSessionMemoryKHR                              vkBindVideoSessionMemoryKHR;
PFN_vkCreateVideoSessionParametersKHR                        vkCreateVideoSessionParametersKHR;
PFN_vkUpdateVideoSessionParametersKHR                        vkUpdateVideoSessionParametersKHR;
PFN_vkDestroyVideoSessionParametersKHR                       vkDestroyVideoSessionParametersKHR;
//VK_KHR_device_group
PFN_vkGetDeviceGroupPeerMemoryFeaturesKHR                    vkGetDeviceGroupPeerMemoryFeaturesKHR;
//VK_KHR_maintenance1
PFN_vkTrimCommandPoolKHR                                     vkTrimCommandPoolKHR;
//VK_KHR_external_memory_fd
PFN_vkGetMemoryFdKHR                                         vkGetMemoryFdKHR;
PFN_vkGetMemoryFdPropertiesKHR                               vkGetMemoryFdPropertiesKHR;
//VK_KHR_external_semaphore_fd
PFN_vkImportSemaphoreFdKHR                                   vkImportSemaphoreFdKHR;
PFN_vkGetSemaphoreFdKHR                                      vkGetSemaphoreFdKHR;
//VK_KHR_descriptor_update_template
PFN_vkCreateDescriptorUpdateTemplateKHR                      vkCreateDescriptorUpdateTemplateKHR;
PFN_vkDestroyDescriptorUpdateTemplateKHR                     vkDestroyDescriptorUpdateTemplateKHR;
PFN_vkUpdateDescriptorSetWithTemplateKHR                     vkUpdateDescriptorSetWithTemplateKHR;
//VK_KHR_create_renderpass2
PFN_vkCreateRenderPass2KHR                                   vkCreateRenderPass2KHR;
//VK_KHR_shared_presentable_image
PFN_vkGetSwapchainStatusKHR                                  vkGetSwapchainStatusKHR;
//VK_KHR_external_fence_fd
PFN_vkImportFenceFdKHR                                       vkImportFenceFdKHR;
PFN_vkGetFenceFdKHR                                          vkGetFenceFdKHR;
//VK_KHR_performance_query
PFN_vkAcquireProfilingLockKHR                                vkAcquireProfilingLockKHR;
PFN_vkReleaseProfilingLockKHR                                vkReleaseProfilingLockKHR;
//VK_KHR_get_memory_requirements2
PFN_vkGetImageMemoryRequirements2KHR                         vkGetImageMemoryRequirements2KHR;
PFN_vkGetBufferMemoryRequirements2KHR                        vkGetBufferMemoryRequirements2KHR;
PFN_vkGetImageSparseMemoryRequirements2KHR                   vkGetImageSparseMemoryRequirements2KHR;
//VK_KHR_sampler_ycbcr_conversion
PFN_vkCreateSamplerYcbcrConversionKHR                        vkCreateSamplerYcbcrConversionKHR;
PFN_vkDestroySamplerYcbcrConversionKHR                       vkDestroySamplerYcbcrConversionKHR;
//VK_KHR_bind_memory2
PFN_vkBindBufferMemory2KHR                                   vkBindBufferMemory2KHR;
PFN_vkBindImageMemory2KHR                                    vkBindImageMemory2KHR;
//VK_KHR_maintenance3
PFN_vkGetDescriptorSetLayoutSupportKHR                       vkGetDescriptorSetLayoutSupportKHR;
//VK_KHR_timeline_semaphore
PFN_vkGetSemaphoreCounterValueKHR                            vkGetSemaphoreCounterValueKHR;
PFN_vkWaitSemaphoresKHR                                      vkWaitSemaphoresKHR;
PFN_vkSignalSemaphoreKHR                                     vkSignalSemaphoreKHR;
//VK_KHR_present_wait
PFN_vkWaitForPresentKHR                                      vkWaitForPresentKHR;
//VK_KHR_buffer_device_address
PFN_vkGetBufferDeviceAddressKHR                              vkGetBufferDeviceAddressKHR;
PFN_vkGetBufferOpaqueCaptureAddressKHR                       vkGetBufferOpaqueCaptureAddressKHR;
PFN_vkGetDeviceMemoryOpaqueCaptureAddressKHR                 vkGetDeviceMemoryOpaqueCaptureAddressKHR;
//VK_KHR_deferred_host_operations
PFN_vkCreateDeferredOperationKHR                             vkCreateDeferredOperationKHR;
PFN_vkDestroyDeferredOperationKHR                            vkDestroyDeferredOperationKHR;
PFN_vkGetDeferredOperationMaxConcurrencyKHR                  vkGetDeferredOperationMaxConcurrencyKHR;
PFN_vkGetDeferredOperationResultKHR                          vkGetDeferredOperationResultKHR;
PFN_vkDeferredOperationJoinKHR                               vkDeferredOperationJoinKHR;
//VK_KHR_pipeline_executable_properties
PFN_vkGetPipelineExecutablePropertiesKHR                     vkGetPipelineExecutablePropertiesKHR;
PFN_vkGetPipelineExecutableStatisticsKHR                     vkGetPipelineExecutableStatisticsKHR;
PFN_vkGetPipelineExecutableInternalRepresentationsKHR        vkGetPipelineExecutableInternalRepresentationsKHR;
//VK_KHR_maintenance4
PFN_vkGetDeviceBufferMemoryRequirementsKHR                   vkGetDeviceBufferMemoryRequirementsKHR;
PFN_vkGetDeviceImageMemoryRequirementsKHR                    vkGetDeviceImageMemoryRequirementsKHR;
PFN_vkGetDeviceImageSparseMemoryRequirementsKHR              vkGetDeviceImageSparseMemoryRequirementsKHR;
//VK_EXT_debug_marker
PFN_vkDebugMarkerSetObjectTagEXT                             vkDebugMarkerSetObjectTagEXT;
PFN_vkDebugMarkerSetObjectNameEXT                            vkDebugMarkerSetObjectNameEXT;
//VK_NVX_binary_import
PFN_vkCreateCuModuleNVX                                      vkCreateCuModuleNVX;
PFN_vkCreateCuFunctionNVX                                    vkCreateCuFunctionNVX;
PFN_vkDestroyCuModuleNVX                                     vkDestroyCuModuleNVX;
PFN_vkDestroyCuFunctionNVX                                   vkDestroyCuFunctionNVX;
//VK_NVX_image_view_handle
PFN_vkGetImageViewHandleNVX                                  vkGetImageViewHandleNVX;
PFN_vkGetImageViewAddressNVX                                 vkGetImageViewAddressNVX;
//VK_AMD_shader_info
PFN_vkGetShaderInfoAMD                                       vkGetShaderInfoAMD;
//VK_EXT_display_control
PFN_vkDisplayPowerControlEXT                                 vkDisplayPowerControlEXT;
PFN_vkRegisterDeviceEventEXT                                 vkRegisterDeviceEventEXT;
PFN_vkRegisterDisplayEventEXT                                vkRegisterDisplayEventEXT;
PFN_vkGetSwapchainCounterEXT                                 vkGetSwapchainCounterEXT;
//VK_GOOGLE_display_timing
PFN_vkGetRefreshCycleDurationGOOGLE                          vkGetRefreshCycleDurationGOOGLE;
PFN_vkGetPastPresentationTimingGOOGLE                        vkGetPastPresentationTimingGOOGLE;
//VK_EXT_hdr_metadata
PFN_vkSetHdrMetadataEXT                                      vkSetHdrMetadataEXT;
//VK_EXT_debug_utils
PFN_vkSetDebugUtilsObjectNameEXT                             vkSetDebugUtilsObjectNameEXT;
PFN_vkSetDebugUtilsObjectTagEXT                              vkSetDebugUtilsObjectTagEXT;
//VK_EXT_image_drm_format_modifier
PFN_vkGetImageDrmFormatModifierPropertiesEXT                 vkGetImageDrmFormatModifierPropertiesEXT;
//VK_EXT_validation_cache
PFN_vkCreateValidationCacheEXT                               vkCreateValidationCacheEXT;
PFN_vkDestroyValidationCacheEXT                              vkDestroyValidationCacheEXT;
PFN_vkMergeValidationCachesEXT                               vkMergeValidationCachesEXT;
PFN_vkGetValidationCacheDataEXT                              vkGetValidationCacheDataEXT;
//VK_NV_ray_tracing
PFN_vkCreateAccelerationStructureNV                          vkCreateAccelerationStructureNV;
PFN_vkDestroyAccelerationStructureNV                         vkDestroyAccelerationStructureNV;
PFN_vkGetAccelerationStructureMemoryRequirementsNV           vkGetAccelerationStructureMemoryRequirementsNV;
PFN_vkBindAccelerationStructureMemoryNV                      vkBindAccelerationStructureMemoryNV;
PFN_vkCreateRayTracingPipelinesNV                            vkCreateRayTracingPipelinesNV;
PFN_vkGetRayTracingShaderGroupHandlesKHR                     vkGetRayTracingShaderGroupHandlesKHR;
PFN_vkGetRayTracingShaderGroupHandlesNV                      vkGetRayTracingShaderGroupHandlesNV;
PFN_vkGetAccelerationStructureHandleNV                       vkGetAccelerationStructureHandleNV;
PFN_vkCompileDeferredNV                                      vkCompileDeferredNV;
//VK_EXT_external_memory_host
PFN_vkGetMemoryHostPointerPropertiesEXT                      vkGetMemoryHostPointerPropertiesEXT;
//VK_EXT_calibrated_timestamps
PFN_vkGetCalibratedTimestampsEXT                             vkGetCalibratedTimestampsEXT;
//VK_INTEL_performance_query
PFN_vkInitializePerformanceApiINTEL                          vkInitializePerformanceApiINTEL;
PFN_vkUninitializePerformanceApiINTEL                        vkUninitializePerformanceApiINTEL;
PFN_vkAcquirePerformanceConfigurationINTEL                   vkAcquirePerformanceConfigurationINTEL;
PFN_vkReleasePerformanceConfigurationINTEL                   vkReleasePerformanceConfigurationINTEL;
PFN_vkGetPerformanceParameterINTEL                           vkGetPerformanceParameterINTEL;
//VK_AMD_display_native_hdr
PFN_vkSetLocalDimmingAMD                                     vkSetLocalDimmingAMD;
//VK_EXT_buffer_device_address
PFN_vkGetBufferDeviceAddressEXT                              vkGetBufferDeviceAddressEXT;
//VK_EXT_host_query_reset
PFN_vkResetQueryPoolEXT                                      vkResetQueryPoolEXT;
//VK_EXT_swapchain_maintenance1
PFN_vkReleaseSwapchainImagesEXT                              vkReleaseSwapchainImagesEXT;
//VK_NV_device_generated_commands
PFN_vkGetGeneratedCommandsMemoryRequirementsNV               vkGetGeneratedCommandsMemoryRequirementsNV;
PFN_vkCreateIndirectCommandsLayoutNV                         vkCreateIndirectCommandsLayoutNV;
PFN_vkDestroyIndirectCommandsLayoutNV                        vkDestroyIndirectCommandsLayoutNV;
//VK_EXT_private_data
PFN_vkCreatePrivateDataSlotEXT                               vkCreatePrivateDataSlotEXT;
PFN_vkDestroyPrivateDataSlotEXT                              vkDestroyPrivateDataSlotEXT;
PFN_vkSetPrivateDataEXT                                      vkSetPrivateDataEXT;
PFN_vkGetPrivateDataEXT                                      vkGetPrivateDataEXT;
//VK_EXT_descriptor_buffer
PFN_vkGetDescriptorSetLayoutSizeEXT                          vkGetDescriptorSetLayoutSizeEXT;
PFN_vkGetDescriptorSetLayoutBindingOffsetEXT                 vkGetDescriptorSetLayoutBindingOffsetEXT;
PFN_vkGetDescriptorEXT                                       vkGetDescriptorEXT;
PFN_vkGetBufferOpaqueCaptureDescriptorDataEXT                vkGetBufferOpaqueCaptureDescriptorDataEXT;
PFN_vkGetImageOpaqueCaptureDescriptorDataEXT                 vkGetImageOpaqueCaptureDescriptorDataEXT;
PFN_vkGetImageViewOpaqueCaptureDescriptorDataEXT             vkGetImageViewOpaqueCaptureDescriptorDataEXT;
PFN_vkGetSamplerOpaqueCaptureDescriptorDataEXT               vkGetSamplerOpaqueCaptureDescriptorDataEXT;
PFN_vkGetAccelerationStructureOpaqueCaptureDescriptorDataEXT vkGetAccelerationStructureOpaqueCaptureDescriptorDataEXT;
//VK_EXT_image_compression_control
PFN_vkGetImageSubresourceLayout2EXT                          vkGetImageSubresourceLayout2EXT;
//VK_EXT_device_fault
PFN_vkGetDeviceFaultInfoEXT                                  vkGetDeviceFaultInfoEXT;
//VK_HUAWEI_subpass_shading
PFN_vkGetDeviceSubpassShadingMaxWorkgroupSizeHUAWEI          vkGetDeviceSubpassShadingMaxWorkgroupSizeHUAWEI;
//VK_NV_external_memory_rdma
PFN_vkGetMemoryRemoteAddressNV                               vkGetMemoryRemoteAddressNV;
//VK_EXT_pipeline_properties
PFN_vkGetPipelinePropertiesEXT                               vkGetPipelinePropertiesEXT;
//VK_EXT_opacity_micromap
PFN_vkCreateMicromapEXT                                      vkCreateMicromapEXT;
PFN_vkDestroyMicromapEXT                                     vkDestroyMicromapEXT;
PFN_vkBuildMicromapsEXT                                      vkBuildMicromapsEXT;
PFN_vkCopyMicromapEXT                                        vkCopyMicromapEXT;
PFN_vkCopyMicromapToMemoryEXT                                vkCopyMicromapToMemoryEXT;
PFN_vkCopyMemoryToMicromapEXT                                vkCopyMemoryToMicromapEXT;
PFN_vkWriteMicromapsPropertiesEXT                            vkWriteMicromapsPropertiesEXT;
PFN_vkGetDeviceMicromapCompatibilityEXT                      vkGetDeviceMicromapCompatibilityEXT;
PFN_vkGetMicromapBuildSizesEXT                               vkGetMicromapBuildSizesEXT;
//VK_EXT_pageable_device_local_memory
PFN_vkSetDeviceMemoryPriorityEXT                             vkSetDeviceMemoryPriorityEXT;
//VK_VALVE_descriptor_set_host_mapping
PFN_vkGetDescriptorSetLayoutHostMappingInfoVALVE             vkGetDescriptorSetLayoutHostMappingInfoVALVE;
PFN_vkGetDescriptorSetHostMappingVALVE                       vkGetDescriptorSetHostMappingVALVE;
//VK_EXT_shader_module_identifier
PFN_vkGetShaderModuleIdentifierEXT                           vkGetShaderModuleIdentifierEXT;
PFN_vkGetShaderModuleCreateInfoIdentifierEXT                 vkGetShaderModuleCreateInfoIdentifierEXT;
//VK_NV_optical_flow
PFN_vkCreateOpticalFlowSessionNV                             vkCreateOpticalFlowSessionNV;
PFN_vkDestroyOpticalFlowSessionNV                            vkDestroyOpticalFlowSessionNV;
PFN_vkBindOpticalFlowSessionImageNV                          vkBindOpticalFlowSessionImageNV;
//VK_QCOM_tile_properties
PFN_vkGetFramebufferTilePropertiesQCOM                       vkGetFramebufferTilePropertiesQCOM;
PFN_vkGetDynamicRenderingTilePropertiesQCOM                  vkGetDynamicRenderingTilePropertiesQCOM;
//VK_KHR_acceleration_structure
PFN_vkCreateAccelerationStructureKHR                         vkCreateAccelerationStructureKHR;
PFN_vkDestroyAccelerationStructureKHR                        vkDestroyAccelerationStructureKHR;
PFN_vkBuildAccelerationStructuresKHR                         vkBuildAccelerationStructuresKHR;
PFN_vkCopyAccelerationStructureKHR                           vkCopyAccelerationStructureKHR;
PFN_vkCopyAccelerationStructureToMemoryKHR                   vkCopyAccelerationStructureToMemoryKHR;
PFN_vkCopyMemoryToAccelerationStructureKHR                   vkCopyMemoryToAccelerationStructureKHR;
PFN_vkWriteAccelerationStructuresPropertiesKHR               vkWriteAccelerationStructuresPropertiesKHR;
PFN_vkGetAccelerationStructureDeviceAddressKHR               vkGetAccelerationStructureDeviceAddressKHR;
PFN_vkGetDeviceAccelerationStructureCompatibilityKHR         vkGetDeviceAccelerationStructureCompatibilityKHR;
PFN_vkGetAccelerationStructureBuildSizesKHR                  vkGetAccelerationStructureBuildSizesKHR;
//VK_KHR_ray_tracing_pipeline
PFN_vkCreateRayTracingPipelinesKHR                           vkCreateRayTracingPipelinesKHR;
PFN_vkGetRayTracingCaptureReplayShaderGroupHandlesKHR        vkGetRayTracingCaptureReplayShaderGroupHandlesKHR;
PFN_vkGetRayTracingShaderGroupStackSizeKHR                   vkGetRayTracingShaderGroupStackSizeKHR;
#ifdef VK_USE_PLATFORM_ANDROID_KHR
//VK_ANDROID_external_memory_android_hardware_buffer
PFN_vkGetAndroidHardwareBufferPropertiesANDROID vkGetAndroidHardwareBufferPropertiesANDROID;
PFN_vkGetMemoryAndroidHardwareBufferANDROID     vkGetMemoryAndroidHardwareBufferANDROID;
#endif
#ifdef VK_USE_PLATFORM_FUCHSIA
//VK_FUCHSIA_external_memory
PFN_vkGetMemoryZirconHandleFUCHSIA                vkGetMemoryZirconHandleFUCHSIA;
PFN_vkGetMemoryZirconHandlePropertiesFUCHSIA      vkGetMemoryZirconHandlePropertiesFUCHSIA;
//VK_FUCHSIA_external_semaphore
PFN_vkImportSemaphoreZirconHandleFUCHSIA          vkImportSemaphoreZirconHandleFUCHSIA;
PFN_vkGetSemaphoreZirconHandleFUCHSIA             vkGetSemaphoreZirconHandleFUCHSIA;
//VK_FUCHSIA_buffer_collection
PFN_vkCreateBufferCollectionFUCHSIA               vkCreateBufferCollectionFUCHSIA;
PFN_vkSetBufferCollectionImageConstraintsFUCHSIA  vkSetBufferCollectionImageConstraintsFUCHSIA;
PFN_vkSetBufferCollectionBufferConstraintsFUCHSIA vkSetBufferCollectionBufferConstraintsFUCHSIA;
PFN_vkDestroyBufferCollectionFUCHSIA              vkDestroyBufferCollectionFUCHSIA;
PFN_vkGetBufferCollectionPropertiesFUCHSIA        vkGetBufferCollectionPropertiesFUCHSIA;
#endif
#ifdef VK_USE_PLATFORM_METAL_EXT
//VK_EXT_metal_objects
PFN_vkExportMetalObjectsEXT vkExportMetalObjectsEXT;
#endif
#ifdef VK_USE_PLATFORM_WIN32_KHR
//VK_KHR_external_memory_win32
PFN_vkGetMemoryWin32HandleKHR               vkGetMemoryWin32HandleKHR;
PFN_vkGetMemoryWin32HandlePropertiesKHR     vkGetMemoryWin32HandlePropertiesKHR;
//VK_KHR_external_semaphore_win32
PFN_vkImportSemaphoreWin32HandleKHR         vkImportSemaphoreWin32HandleKHR;
PFN_vkGetSemaphoreWin32HandleKHR            vkGetSemaphoreWin32HandleKHR;
//VK_KHR_external_fence_win32
PFN_vkImportFenceWin32HandleKHR             vkImportFenceWin32HandleKHR;
PFN_vkGetFenceWin32HandleKHR                vkGetFenceWin32HandleKHR;
//VK_NV_external_memory_win32
PFN_vkGetMemoryWin32HandleNV                vkGetMemoryWin32HandleNV;
//VK_EXT_full_screen_exclusive
PFN_vkAcquireFullScreenExclusiveModeEXT     vkAcquireFullScreenExclusiveModeEXT;
PFN_vkReleaseFullScreenExclusiveModeEXT     vkReleaseFullScreenExclusiveModeEXT;
PFN_vkGetDeviceGroupSurfacePresentModes2EXT vkGetDeviceGroupSurfacePresentModes2EXT;
#endif



//VkQueue dispatched functions
//VK_VERSION_1_0
PFN_vkQueueSubmit                                 vkQueueSubmit;
PFN_vkQueueWaitIdle                               vkQueueWaitIdle;
PFN_vkQueueBindSparse                             vkQueueBindSparse;
//VK_VERSION_1_3
PFN_vkQueueSubmit2                                vkQueueSubmit2;
//VK_KHR_swapchain
PFN_vkQueuePresentKHR                             vkQueuePresentKHR;
//VK_KHR_synchronization2
PFN_vkQueueSubmit2KHR                             vkQueueSubmit2KHR;
PFN_vkGetQueueCheckpointData2NV                   vkGetQueueCheckpointData2NV;
//VK_EXT_debug_utils
PFN_vkQueueBeginDebugUtilsLabelEXT                vkQueueBeginDebugUtilsLabelEXT;
PFN_vkQueueEndDebugUtilsLabelEXT                  vkQueueEndDebugUtilsLabelEXT;
PFN_vkQueueInsertDebugUtilsLabelEXT               vkQueueInsertDebugUtilsLabelEXT;
//VK_NV_device_diagnostic_checkpoints
PFN_vkGetQueueCheckpointDataNV                    vkGetQueueCheckpointDataNV;
//VK_INTEL_performance_query
PFN_vkQueueSetPerformanceConfigurationINTEL       vkQueueSetPerformanceConfigurationINTEL;

//VkCommandBuffer dispatched functions
//VK_VERSION_1_0
PFN_vkBeginCommandBuffer                          vkBeginCommandBuffer;
PFN_vkEndCommandBuffer                            vkEndCommandBuffer;
PFN_vkResetCommandBuffer                          vkResetCommandBuffer;
PFN_vkCmdBindPipeline                             vkCmdBindPipeline;
PFN_vkCmdSetViewport                              vkCmdSetViewport;
PFN_vkCmdSetScissor                               vkCmdSetScissor;
PFN_vkCmdSetLineWidth                             vkCmdSetLineWidth;
PFN_vkCmdSetDepthBias                             vkCmdSetDepthBias;
PFN_vkCmdSetBlendConstants                        vkCmdSetBlendConstants;
PFN_vkCmdSetDepthBounds                           vkCmdSetDepthBounds;
PFN_vkCmdSetStencilCompareMask                    vkCmdSetStencilCompareMask;
PFN_vkCmdSetStencilWriteMask                      vkCmdSetStencilWriteMask;
PFN_vkCmdSetStencilReference                      vkCmdSetStencilReference;
PFN_vkCmdBindDescriptorSets                       vkCmdBindDescriptorSets;
PFN_vkCmdBindIndexBuffer                          vkCmdBindIndexBuffer;
PFN_vkCmdBindVertexBuffers                        vkCmdBindVertexBuffers;
PFN_vkCmdDraw                                     vkCmdDraw;
PFN_vkCmdDrawIndexed                              vkCmdDrawIndexed;
PFN_vkCmdDrawIndirect                             vkCmdDrawIndirect;
PFN_vkCmdDrawIndexedIndirect                      vkCmdDrawIndexedIndirect;
PFN_vkCmdDispatch                                 vkCmdDispatch;
PFN_vkCmdDispatchIndirect                         vkCmdDispatchIndirect;
PFN_vkCmdCopyBuffer                               vkCmdCopyBuffer;
PFN_vkCmdCopyImage                                vkCmdCopyImage;
PFN_vkCmdBlitImage                                vkCmdBlitImage;
PFN_vkCmdCopyBufferToImage                        vkCmdCopyBufferToImage;
PFN_vkCmdCopyImageToBuffer                        vkCmdCopyImageToBuffer;
PFN_vkCmdUpdateBuffer                             vkCmdUpdateBuffer;
PFN_vkCmdFillBuffer                               vkCmdFillBuffer;
PFN_vkCmdClearColorImage                          vkCmdClearColorImage;
PFN_vkCmdClearDepthStencilImage                   vkCmdClearDepthStencilImage;
PFN_vkCmdClearAttachments                         vkCmdClearAttachments;
PFN_vkCmdResolveImage                             vkCmdResolveImage;
PFN_vkCmdSetEvent                                 vkCmdSetEvent;
PFN_vkCmdResetEvent                               vkCmdResetEvent;
PFN_vkCmdWaitEvents                               vkCmdWaitEvents;
PFN_vkCmdPipelineBarrier                          vkCmdPipelineBarrier;
PFN_vkCmdBeginQuery                               vkCmdBeginQuery;
PFN_vkCmdEndQuery                                 vkCmdEndQuery;
PFN_vkCmdResetQueryPool                           vkCmdResetQueryPool;
PFN_vkCmdWriteTimestamp                           vkCmdWriteTimestamp;
PFN_vkCmdCopyQueryPoolResults                     vkCmdCopyQueryPoolResults;
PFN_vkCmdPushConstants                            vkCmdPushConstants;
PFN_vkCmdBeginRenderPass                          vkCmdBeginRenderPass;
PFN_vkCmdNextSubpass                              vkCmdNextSubpass;
PFN_vkCmdEndRenderPass                            vkCmdEndRenderPass;
PFN_vkCmdExecuteCommands                          vkCmdExecuteCommands;
//VK_VERSION_1_1
PFN_vkCmdSetDeviceMask                            vkCmdSetDeviceMask;
PFN_vkCmdDispatchBase                             vkCmdDispatchBase;
//VK_VERSION_1_2
PFN_vkCmdDrawIndirectCount                        vkCmdDrawIndirectCount;
PFN_vkCmdDrawIndexedIndirectCount                 vkCmdDrawIndexedIndirectCount;
PFN_vkCmdBeginRenderPass2                         vkCmdBeginRenderPass2;
PFN_vkCmdNextSubpass2                             vkCmdNextSubpass2;
PFN_vkCmdEndRenderPass2                           vkCmdEndRenderPass2;
//VK_VERSION_1_3
PFN_vkCmdSetEvent2                                vkCmdSetEvent2;
PFN_vkCmdResetEvent2                              vkCmdResetEvent2;
PFN_vkCmdWaitEvents2                              vkCmdWaitEvents2;
PFN_vkCmdPipelineBarrier2                         vkCmdPipelineBarrier2;
PFN_vkCmdWriteTimestamp2                          vkCmdWriteTimestamp2;
PFN_vkCmdCopyBuffer2                              vkCmdCopyBuffer2;
PFN_vkCmdCopyImage2                               vkCmdCopyImage2;
PFN_vkCmdCopyBufferToImage2                       vkCmdCopyBufferToImage2;
PFN_vkCmdCopyImageToBuffer2                       vkCmdCopyImageToBuffer2;
PFN_vkCmdBlitImage2                               vkCmdBlitImage2;
PFN_vkCmdResolveImage2                            vkCmdResolveImage2;
PFN_vkCmdBeginRendering                           vkCmdBeginRendering;
PFN_vkCmdEndRendering                             vkCmdEndRendering;
PFN_vkCmdSetCullMode                              vkCmdSetCullMode;
PFN_vkCmdSetFrontFace                             vkCmdSetFrontFace;
PFN_vkCmdSetPrimitiveTopology                     vkCmdSetPrimitiveTopology;
PFN_vkCmdSetViewportWithCount                     vkCmdSetViewportWithCount;
PFN_vkCmdSetScissorWithCount                      vkCmdSetScissorWithCount;
PFN_vkCmdBindVertexBuffers2                       vkCmdBindVertexBuffers2;
PFN_vkCmdSetDepthTestEnable                       vkCmdSetDepthTestEnable;
PFN_vkCmdSetDepthWriteEnable                      vkCmdSetDepthWriteEnable;
PFN_vkCmdSetDepthCompareOp                        vkCmdSetDepthCompareOp;
PFN_vkCmdSetDepthBoundsTestEnable                 vkCmdSetDepthBoundsTestEnable;
PFN_vkCmdSetStencilTestEnable                     vkCmdSetStencilTestEnable;
PFN_vkCmdSetStencilOp                             vkCmdSetStencilOp;
PFN_vkCmdSetRasterizerDiscardEnable               vkCmdSetRasterizerDiscardEnable;
PFN_vkCmdSetDepthBiasEnable                       vkCmdSetDepthBiasEnable;
PFN_vkCmdSetPrimitiveRestartEnable                vkCmdSetPrimitiveRestartEnable;
//VK_KHR_video_queue
PFN_vkCmdBeginVideoCodingKHR                      vkCmdBeginVideoCodingKHR;
PFN_vkCmdEndVideoCodingKHR                        vkCmdEndVideoCodingKHR;
PFN_vkCmdControlVideoCodingKHR                    vkCmdControlVideoCodingKHR;
//VK_KHR_video_decode_queue
PFN_vkCmdDecodeVideoKHR                           vkCmdDecodeVideoKHR;
//VK_KHR_dynamic_rendering
PFN_vkCmdBeginRenderingKHR                        vkCmdBeginRenderingKHR;
PFN_vkCmdEndRenderingKHR                          vkCmdEndRenderingKHR;
//VK_KHR_device_group
PFN_vkCmdSetDeviceMaskKHR                         vkCmdSetDeviceMaskKHR;
PFN_vkCmdDispatchBaseKHR                          vkCmdDispatchBaseKHR;
//VK_KHR_push_descriptor
PFN_vkCmdPushDescriptorSetKHR                     vkCmdPushDescriptorSetKHR;
PFN_vkCmdPushDescriptorSetWithTemplateKHR         vkCmdPushDescriptorSetWithTemplateKHR;
//VK_KHR_create_renderpass2
PFN_vkCmdBeginRenderPass2KHR                      vkCmdBeginRenderPass2KHR;
PFN_vkCmdNextSubpass2KHR                          vkCmdNextSubpass2KHR;
PFN_vkCmdEndRenderPass2KHR                        vkCmdEndRenderPass2KHR;
//VK_KHR_draw_indirect_count
PFN_vkCmdDrawIndirectCountKHR                     vkCmdDrawIndirectCountKHR;
PFN_vkCmdDrawIndexedIndirectCountKHR              vkCmdDrawIndexedIndirectCountKHR;
//VK_KHR_fragment_shading_rate
PFN_vkCmdSetFragmentShadingRateKHR                vkCmdSetFragmentShadingRateKHR;
//VK_KHR_synchronization2
PFN_vkCmdSetEvent2KHR                             vkCmdSetEvent2KHR;
PFN_vkCmdResetEvent2KHR                           vkCmdResetEvent2KHR;
PFN_vkCmdWaitEvents2KHR                           vkCmdWaitEvents2KHR;
PFN_vkCmdPipelineBarrier2KHR                      vkCmdPipelineBarrier2KHR;
PFN_vkCmdWriteTimestamp2KHR                       vkCmdWriteTimestamp2KHR;
PFN_vkCmdWriteBufferMarker2AMD                    vkCmdWriteBufferMarker2AMD;
//VK_KHR_copy_commands2
PFN_vkCmdCopyBuffer2KHR                           vkCmdCopyBuffer2KHR;
PFN_vkCmdCopyImage2KHR                            vkCmdCopyImage2KHR;
PFN_vkCmdCopyBufferToImage2KHR                    vkCmdCopyBufferToImage2KHR;
PFN_vkCmdCopyImageToBuffer2KHR                    vkCmdCopyImageToBuffer2KHR;
PFN_vkCmdBlitImage2KHR                            vkCmdBlitImage2KHR;
PFN_vkCmdResolveImage2KHR                         vkCmdResolveImage2KHR;
//VK_KHR_ray_tracing_maintenance1
PFN_vkCmdTraceRaysIndirect2KHR                    vkCmdTraceRaysIndirect2KHR;
//VK_EXT_debug_marker
PFN_vkCmdDebugMarkerBeginEXT                      vkCmdDebugMarkerBeginEXT;
PFN_vkCmdDebugMarkerEndEXT                        vkCmdDebugMarkerEndEXT;
PFN_vkCmdDebugMarkerInsertEXT                     vkCmdDebugMarkerInsertEXT;
//VK_EXT_transform_feedback
PFN_vkCmdBindTransformFeedbackBuffersEXT          vkCmdBindTransformFeedbackBuffersEXT;
PFN_vkCmdBeginTransformFeedbackEXT                vkCmdBeginTransformFeedbackEXT;
PFN_vkCmdEndTransformFeedbackEXT                  vkCmdEndTransformFeedbackEXT;
PFN_vkCmdBeginQueryIndexedEXT                     vkCmdBeginQueryIndexedEXT;
PFN_vkCmdEndQueryIndexedEXT                       vkCmdEndQueryIndexedEXT;
PFN_vkCmdDrawIndirectByteCountEXT                 vkCmdDrawIndirectByteCountEXT;
//VK_NVX_binary_import
PFN_vkCmdCuLaunchKernelNVX                        vkCmdCuLaunchKernelNVX;
//VK_AMD_draw_indirect_count
PFN_vkCmdDrawIndirectCountAMD                     vkCmdDrawIndirectCountAMD;
PFN_vkCmdDrawIndexedIndirectCountAMD              vkCmdDrawIndexedIndirectCountAMD;
//VK_EXT_conditional_rendering
PFN_vkCmdBeginConditionalRenderingEXT             vkCmdBeginConditionalRenderingEXT;
PFN_vkCmdEndConditionalRenderingEXT               vkCmdEndConditionalRenderingEXT;
//VK_NV_clip_space_w_scaling
PFN_vkCmdSetViewportWScalingNV                    vkCmdSetViewportWScalingNV;
//VK_EXT_discard_rectangles
PFN_vkCmdSetDiscardRectangleEXT                   vkCmdSetDiscardRectangleEXT;
//VK_EXT_debug_utils
PFN_vkCmdBeginDebugUtilsLabelEXT                  vkCmdBeginDebugUtilsLabelEXT;
PFN_vkCmdEndDebugUtilsLabelEXT                    vkCmdEndDebugUtilsLabelEXT;
PFN_vkCmdInsertDebugUtilsLabelEXT                 vkCmdInsertDebugUtilsLabelEXT;
//VK_EXT_sample_locations
PFN_vkCmdSetSampleLocationsEXT                    vkCmdSetSampleLocationsEXT;
//VK_NV_shading_rate_image
PFN_vkCmdBindShadingRateImageNV                   vkCmdBindShadingRateImageNV;
PFN_vkCmdSetViewportShadingRatePaletteNV          vkCmdSetViewportShadingRatePaletteNV;
PFN_vkCmdSetCoarseSampleOrderNV                   vkCmdSetCoarseSampleOrderNV;
//VK_NV_ray_tracing
PFN_vkCmdBuildAccelerationStructureNV             vkCmdBuildAccelerationStructureNV;
PFN_vkCmdCopyAccelerationStructureNV              vkCmdCopyAccelerationStructureNV;
PFN_vkCmdTraceRaysNV                              vkCmdTraceRaysNV;
PFN_vkCmdWriteAccelerationStructuresPropertiesNV  vkCmdWriteAccelerationStructuresPropertiesNV;
//VK_AMD_buffer_marker
PFN_vkCmdWriteBufferMarkerAMD                     vkCmdWriteBufferMarkerAMD;
//VK_NV_mesh_shader
PFN_vkCmdDrawMeshTasksNV                          vkCmdDrawMeshTasksNV;
PFN_vkCmdDrawMeshTasksIndirectNV                  vkCmdDrawMeshTasksIndirectNV;
PFN_vkCmdDrawMeshTasksIndirectCountNV             vkCmdDrawMeshTasksIndirectCountNV;
//VK_NV_scissor_exclusive
PFN_vkCmdSetExclusiveScissorNV                    vkCmdSetExclusiveScissorNV;
//VK_NV_device_diagnostic_checkpoints
PFN_vkCmdSetCheckpointNV                          vkCmdSetCheckpointNV;
//VK_INTEL_performance_query
PFN_vkCmdSetPerformanceMarkerINTEL                vkCmdSetPerformanceMarkerINTEL;
PFN_vkCmdSetPerformanceStreamMarkerINTEL          vkCmdSetPerformanceStreamMarkerINTEL;
PFN_vkCmdSetPerformanceOverrideINTEL              vkCmdSetPerformanceOverrideINTEL;
//VK_EXT_line_rasterization
PFN_vkCmdSetLineStippleEXT                        vkCmdSetLineStippleEXT;
//VK_EXT_extended_dynamic_state
PFN_vkCmdSetCullModeEXT                           vkCmdSetCullModeEXT;
PFN_vkCmdSetFrontFaceEXT                          vkCmdSetFrontFaceEXT;
PFN_vkCmdSetPrimitiveTopologyEXT                  vkCmdSetPrimitiveTopologyEXT;
PFN_vkCmdSetViewportWithCountEXT                  vkCmdSetViewportWithCountEXT;
PFN_vkCmdSetScissorWithCountEXT                   vkCmdSetScissorWithCountEXT;
PFN_vkCmdBindVertexBuffers2EXT                    vkCmdBindVertexBuffers2EXT;
PFN_vkCmdSetDepthTestEnableEXT                    vkCmdSetDepthTestEnableEXT;
PFN_vkCmdSetDepthWriteEnableEXT                   vkCmdSetDepthWriteEnableEXT;
PFN_vkCmdSetDepthCompareOpEXT                     vkCmdSetDepthCompareOpEXT;
PFN_vkCmdSetDepthBoundsTestEnableEXT              vkCmdSetDepthBoundsTestEnableEXT;
PFN_vkCmdSetStencilTestEnableEXT                  vkCmdSetStencilTestEnableEXT;
PFN_vkCmdSetStencilOpEXT                          vkCmdSetStencilOpEXT;
//VK_NV_device_generated_commands
PFN_vkCmdPreprocessGeneratedCommandsNV            vkCmdPreprocessGeneratedCommandsNV;
PFN_vkCmdExecuteGeneratedCommandsNV               vkCmdExecuteGeneratedCommandsNV;
PFN_vkCmdBindPipelineShaderGroupNV                vkCmdBindPipelineShaderGroupNV;
//VK_EXT_descriptor_buffer
PFN_vkCmdBindDescriptorBuffersEXT                 vkCmdBindDescriptorBuffersEXT;
PFN_vkCmdSetDescriptorBufferOffsetsEXT            vkCmdSetDescriptorBufferOffsetsEXT;
PFN_vkCmdBindDescriptorBufferEmbeddedSamplersEXT  vkCmdBindDescriptorBufferEmbeddedSamplersEXT;
//VK_NV_fragment_shading_rate_enums
PFN_vkCmdSetFragmentShadingRateEnumNV             vkCmdSetFragmentShadingRateEnumNV;
//VK_EXT_vertex_input_dynamic_state
PFN_vkCmdSetVertexInputEXT                        vkCmdSetVertexInputEXT;
//VK_HUAWEI_subpass_shading
PFN_vkCmdSubpassShadingHUAWEI                     vkCmdSubpassShadingHUAWEI;
//VK_HUAWEI_invocation_mask
PFN_vkCmdBindInvocationMaskHUAWEI                 vkCmdBindInvocationMaskHUAWEI;
//VK_EXT_extended_dynamic_state2
PFN_vkCmdSetPatchControlPointsEXT                 vkCmdSetPatchControlPointsEXT;
PFN_vkCmdSetRasterizerDiscardEnableEXT            vkCmdSetRasterizerDiscardEnableEXT;
PFN_vkCmdSetDepthBiasEnableEXT                    vkCmdSetDepthBiasEnableEXT;
PFN_vkCmdSetLogicOpEXT                            vkCmdSetLogicOpEXT;
PFN_vkCmdSetPrimitiveRestartEnableEXT             vkCmdSetPrimitiveRestartEnableEXT;
//VK_EXT_color_write_enable
PFN_vkCmdSetColorWriteEnableEXT                   vkCmdSetColorWriteEnableEXT;
//VK_EXT_multi_draw
PFN_vkCmdDrawMultiEXT                             vkCmdDrawMultiEXT;
PFN_vkCmdDrawMultiIndexedEXT                      vkCmdDrawMultiIndexedEXT;
//VK_EXT_opacity_micromap
PFN_vkCmdBuildMicromapsEXT                        vkCmdBuildMicromapsEXT;
PFN_vkCmdCopyMicromapEXT                          vkCmdCopyMicromapEXT;
PFN_vkCmdCopyMicromapToMemoryEXT                  vkCmdCopyMicromapToMemoryEXT;
PFN_vkCmdCopyMemoryToMicromapEXT                  vkCmdCopyMemoryToMicromapEXT;
PFN_vkCmdWriteMicromapsPropertiesEXT              vkCmdWriteMicromapsPropertiesEXT;
//VK_NV_copy_memory_indirect
PFN_vkCmdCopyMemoryIndirectNV                     vkCmdCopyMemoryIndirectNV;
PFN_vkCmdCopyMemoryToImageIndirectNV              vkCmdCopyMemoryToImageIndirectNV;
//VK_NV_memory_decompression
PFN_vkCmdDecompressMemoryNV                       vkCmdDecompressMemoryNV;
PFN_vkCmdDecompressMemoryIndirectCountNV          vkCmdDecompressMemoryIndirectCountNV;
//VK_EXT_extended_dynamic_state3
PFN_vkCmdSetTessellationDomainOriginEXT           vkCmdSetTessellationDomainOriginEXT;
PFN_vkCmdSetDepthClampEnableEXT                   vkCmdSetDepthClampEnableEXT;
PFN_vkCmdSetPolygonModeEXT                        vkCmdSetPolygonModeEXT;
PFN_vkCmdSetRasterizationSamplesEXT               vkCmdSetRasterizationSamplesEXT;
PFN_vkCmdSetSampleMaskEXT                         vkCmdSetSampleMaskEXT;
PFN_vkCmdSetAlphaToCoverageEnableEXT              vkCmdSetAlphaToCoverageEnableEXT;
PFN_vkCmdSetAlphaToOneEnableEXT                   vkCmdSetAlphaToOneEnableEXT;
PFN_vkCmdSetLogicOpEnableEXT                      vkCmdSetLogicOpEnableEXT;
PFN_vkCmdSetColorBlendEnableEXT                   vkCmdSetColorBlendEnableEXT;
PFN_vkCmdSetColorBlendEquationEXT                 vkCmdSetColorBlendEquationEXT;
PFN_vkCmdSetColorWriteMaskEXT                     vkCmdSetColorWriteMaskEXT;
PFN_vkCmdSetRasterizationStreamEXT                vkCmdSetRasterizationStreamEXT;
PFN_vkCmdSetConservativeRasterizationModeEXT      vkCmdSetConservativeRasterizationModeEXT;
PFN_vkCmdSetExtraPrimitiveOverestimationSizeEXT   vkCmdSetExtraPrimitiveOverestimationSizeEXT;
PFN_vkCmdSetDepthClipEnableEXT                    vkCmdSetDepthClipEnableEXT;
PFN_vkCmdSetSampleLocationsEnableEXT              vkCmdSetSampleLocationsEnableEXT;
PFN_vkCmdSetColorBlendAdvancedEXT                 vkCmdSetColorBlendAdvancedEXT;
PFN_vkCmdSetProvokingVertexModeEXT                vkCmdSetProvokingVertexModeEXT;
PFN_vkCmdSetLineRasterizationModeEXT              vkCmdSetLineRasterizationModeEXT;
PFN_vkCmdSetLineStippleEnableEXT                  vkCmdSetLineStippleEnableEXT;
PFN_vkCmdSetDepthClipNegativeOneToOneEXT          vkCmdSetDepthClipNegativeOneToOneEXT;
PFN_vkCmdSetViewportWScalingEnableNV              vkCmdSetViewportWScalingEnableNV;
PFN_vkCmdSetViewportSwizzleNV                     vkCmdSetViewportSwizzleNV;
PFN_vkCmdSetCoverageToColorEnableNV               vkCmdSetCoverageToColorEnableNV;
PFN_vkCmdSetCoverageToColorLocationNV             vkCmdSetCoverageToColorLocationNV;
PFN_vkCmdSetCoverageModulationModeNV              vkCmdSetCoverageModulationModeNV;
PFN_vkCmdSetCoverageModulationTableEnableNV       vkCmdSetCoverageModulationTableEnableNV;
PFN_vkCmdSetCoverageModulationTableNV             vkCmdSetCoverageModulationTableNV;
PFN_vkCmdSetShadingRateImageEnableNV              vkCmdSetShadingRateImageEnableNV;
PFN_vkCmdSetRepresentativeFragmentTestEnableNV    vkCmdSetRepresentativeFragmentTestEnableNV;
PFN_vkCmdSetCoverageReductionModeNV               vkCmdSetCoverageReductionModeNV;
//VK_NV_optical_flow
PFN_vkCmdOpticalFlowExecuteNV                     vkCmdOpticalFlowExecuteNV;
//VK_KHR_acceleration_structure
PFN_vkCmdBuildAccelerationStructuresKHR           vkCmdBuildAccelerationStructuresKHR;
PFN_vkCmdBuildAccelerationStructuresIndirectKHR   vkCmdBuildAccelerationStructuresIndirectKHR;
PFN_vkCmdCopyAccelerationStructureKHR             vkCmdCopyAccelerationStructureKHR;
PFN_vkCmdCopyAccelerationStructureToMemoryKHR     vkCmdCopyAccelerationStructureToMemoryKHR;
PFN_vkCmdCopyMemoryToAccelerationStructureKHR     vkCmdCopyMemoryToAccelerationStructureKHR;
PFN_vkCmdWriteAccelerationStructuresPropertiesKHR vkCmdWriteAccelerationStructuresPropertiesKHR;
//VK_KHR_ray_tracing_pipeline
PFN_vkCmdTraceRaysKHR                             vkCmdTraceRaysKHR;
PFN_vkCmdTraceRaysIndirectKHR                     vkCmdTraceRaysIndirectKHR;
PFN_vkCmdSetRayTracingPipelineStackSizeKHR        vkCmdSetRayTracingPipelineStackSizeKHR;
//VK_EXT_mesh_shader
PFN_vkCmdDrawMeshTasksEXT                         vkCmdDrawMeshTasksEXT;
PFN_vkCmdDrawMeshTasksIndirectEXT                 vkCmdDrawMeshTasksIndirectEXT;
PFN_vkCmdDrawMeshTasksIndirectCountEXT            vkCmdDrawMeshTasksIndirectCountEXT;
#ifdef VK_ENABLE_BETA_EXTENSIONS
//VK_KHR_video_encode_queue
PFN_vkCmdEncodeVideoKHR vkCmdEncodeVideoKHR;
#endif


//extensions without function pointers
//VK_KHR_sampler_mirror_clamp_to_edge
//VK_KHR_video_decode_h264
//VK_KHR_multiview
//VK_KHR_shader_draw_parameters
//VK_KHR_external_memory
//VK_KHR_external_semaphore
//VK_KHR_shader_float16_int8
//VK_KHR_16bit_storage
//VK_KHR_incremental_present
//VK_KHR_imageless_framebuffer
//VK_KHR_external_fence
//VK_KHR_maintenance2
//VK_KHR_variable_pointers
//VK_KHR_dedicated_allocation
//VK_KHR_storage_buffer_storage_class
//VK_KHR_relaxed_block_layout
//VK_KHR_image_format_list
//VK_KHR_shader_subgroup_extended_types
//VK_KHR_8bit_storage
//VK_KHR_shader_atomic_int64
//VK_KHR_shader_clock
//VK_KHR_video_decode_h265
//VK_KHR_global_priority
//VK_KHR_driver_properties
//VK_KHR_shader_float_controls
//VK_KHR_depth_stencil_resolve
//VK_KHR_swapchain_mutable_format
//VK_KHR_vulkan_memory_model
//VK_KHR_shader_terminate_invocation
//VK_KHR_spirv_1_4
//VK_KHR_surface_protected_capabilities
//VK_KHR_separate_depth_stencil_layouts
//VK_KHR_uniform_buffer_standard_layout
//VK_KHR_shader_integer_dot_product
//VK_KHR_pipeline_library
//VK_KHR_shader_non_semantic_info
//VK_KHR_present_id
//VK_KHR_fragment_shader_barycentric
//VK_KHR_shader_subgroup_uniform_control_flow
//VK_KHR_zero_initialize_workgroup_memory
//VK_KHR_workgroup_memory_explicit_layout
//VK_KHR_format_feature_flags2
//VK_KHR_portability_enumeration
//VK_NV_glsl_shader
//VK_EXT_depth_range_unrestricted
//VK_IMG_filter_cubic
//VK_AMD_rasterization_order
//VK_AMD_shader_trinary_minmax
//VK_AMD_shader_explicit_vertex_parameter
//VK_AMD_gcn_shader
//VK_NV_dedicated_allocation
//VK_AMD_negative_viewport_height
//VK_AMD_gpu_shader_half_float
//VK_AMD_shader_ballot
//VK_AMD_texture_gather_bias_lod
//VK_AMD_shader_image_load_store_lod
//VK_NV_corner_sampled_image
//VK_IMG_format_pvrtc
//VK_NV_external_memory
//VK_EXT_validation_flags
//VK_EXT_shader_subgroup_ballot
//VK_EXT_shader_subgroup_vote
//VK_EXT_texture_compression_astc_hdr
//VK_EXT_astc_decode_mode
//VK_EXT_pipeline_robustness
//VK_NV_sample_mask_override_coverage
//VK_NV_geometry_shader_passthrough
//VK_NV_viewport_array2
//VK_NVX_multiview_per_view_attributes
//VK_NV_viewport_swizzle
//VK_EXT_conservative_rasterization
//VK_EXT_depth_clip_enable
//VK_EXT_swapchain_colorspace
//VK_EXT_external_memory_dma_buf
//VK_EXT_queue_family_foreign
//VK_EXT_sampler_filter_minmax
//VK_AMD_gpu_shader_int16
//VK_AMD_mixed_attachment_samples
//VK_AMD_shader_fragment_mask
//VK_EXT_inline_uniform_block
//VK_EXT_shader_stencil_export
//VK_EXT_blend_operation_advanced
//VK_NV_fragment_coverage_to_color
//VK_NV_framebuffer_mixed_samples
//VK_NV_fill_rectangle
//VK_NV_shader_sm_builtins
//VK_EXT_post_depth_coverage
//VK_EXT_descriptor_indexing
//VK_EXT_shader_viewport_index_layer
//VK_NV_representative_fragment_test
//VK_EXT_filter_cubic
//VK_QCOM_render_pass_shader_resolve
//VK_EXT_global_priority
//VK_AMD_pipeline_compiler_control
//VK_AMD_shader_core_properties
//VK_AMD_memory_overallocation_behavior
//VK_EXT_vertex_attribute_divisor
//VK_EXT_pipeline_creation_feedback
//VK_NV_shader_subgroup_partitioned
//VK_NV_compute_shader_derivatives
//VK_NV_fragment_shader_barycentric
//VK_NV_shader_image_footprint
//VK_INTEL_shader_integer_functions2
//VK_EXT_pci_bus_info
//VK_EXT_fragment_density_map
//VK_EXT_scalar_block_layout
//VK_GOOGLE_hlsl_functionality1
//VK_GOOGLE_decorate_string
//VK_EXT_subgroup_size_control
//VK_AMD_shader_core_properties2
//VK_AMD_device_coherent_memory
//VK_EXT_shader_image_atomic_int64
//VK_EXT_memory_budget
//VK_EXT_memory_priority
//VK_NV_dedicated_allocation_image_aliasing 1
//VK_EXT_separate_stencil_usage
//VK_EXT_validation_features
//VK_EXT_fragment_shader_interlock
//VK_EXT_ycbcr_image_arrays
//VK_EXT_provoking_vertex
//VK_EXT_shader_atomic_float
//VK_EXT_index_type_uint8
//VK_EXT_shader_atomic_float2
//VK_EXT_surface_maintenance1
//VK_EXT_shader_demote_to_helper_invocation
//VK_NV_inherited_viewport_scissor
//VK_EXT_texel_buffer_alignment
//VK_QCOM_render_pass_transform
//VK_EXT_device_memory_report
//VK_EXT_robustness2
//VK_EXT_custom_border_color
//VK_GOOGLE_user_type
//VK_NV_present_barrier
//VK_EXT_pipeline_creation_cache_control
//VK_NV_device_diagnostics_config
//VK_QCOM_render_pass_store_ops
//VK_EXT_graphics_pipeline_library
//VK_AMD_shader_early_and_late_fragment_tests
//VK_NV_ray_tracing_motion_blur
//VK_EXT_ycbcr_2plane_444_formats
//VK_EXT_fragment_density_map2
//VK_QCOM_rotated_copy_commands
//VK_EXT_image_robustness
//VK_EXT_attachment_feedback_loop_layout
//VK_EXT_4444_formats
//VK_ARM_rasterization_order_attachment_access
//VK_EXT_rgba10x6_formats
//VK_VALVE_mutable_descriptor_type
//VK_EXT_physical_device_drm
//VK_EXT_device_address_binding_report
//VK_EXT_depth_clip_control
//VK_EXT_primitive_topology_list_restart
//VK_EXT_multisampled_render_to_single_sampled
//VK_EXT_primitives_generated_query
//VK_EXT_global_priority_query
//VK_EXT_image_view_min_lod
//VK_EXT_image_2d_view_of_3d
//VK_EXT_load_store_op_none
//VK_EXT_border_color_swizzle
//VK_EXT_depth_clamp_zero_one
//VK_EXT_non_seamless_cube_map
//VK_QCOM_fragment_density_map_offset
//VK_NV_linear_color_attachment
//VK_GOOGLE_surfaceless_query
//VK_EXT_image_compression_control_swapchain
//VK_QCOM_image_processing
//VK_EXT_subpass_merge_feedback
//VK_LUNARG_direct_driver_loading
//VK_EXT_rasterization_order_attachment_access
//VK_EXT_legacy_dithering
//VK_EXT_pipeline_protected_access
//VK_SEC_amigo_profiling
//VK_QCOM_multiview_per_view_viewports
//VK_NV_ray_tracing_invocation_reorder
//VK_EXT_mutable_descriptor_type
//VK_ARM_shader_core_builtins
//VK_KHR_ray_query
#ifdef VK_USE_PLATFORM_WIN32_KHR
//VK_KHR_win32_keyed_mutex
//VK_NV_win32_keyed_mutex
#endif
#ifdef VK_USE_PLATFORM_GGP
//VK_GGP_frame_token
#endif
#ifdef VK_ENABLE_BETA_EXTENSIONS
//VK_KHR_portability_subset
//VK_EXT_video_encode_h264
//VK_EXT_video_encode_h265
#endif


//implemented down below
typedef void (*_vkad_proc) (void);
void      *_vkad_open (const char *path);
_vkad_proc _vkad_load (void *module, const char *name);
void       _vkad_close (void *module);



//modelled after GLFW, see win32_module.c and posix_module.c specifically
#if defined(_WIN32) || defined(__WIN32__) || defined(WIN32) || defined(__MINGW32__)
#define NOMINMAX
#define VC_EXTRALEAN
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
void *_vkad_open (const char *path) {
        return LoadLibraryA (path);
}
_vkad_proc _vkad_load (void *module, const char *name) {
        return (_vkad_proc) GetProcAddress ((HMODULE) module, name);
}
void _vkad_close (void *module) {
        FreeLibrary ((HMODULE) module);
}

#define _vkad_LIB_NAME "vulkan-1.dll"

#else /* Unix defaults otherwise */
#include <dlfcn.h>
void *_vkad_open (const char *path) {
        return dlopen (path, RTLD_LAZY | RTLD_LOCAL);
}
//ISO C compatibility type for GCC warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
typedef _vkad_proc (*_VKAD_ISO_C_COMPAT_dlsym) (void *module, const char *name);
_vkad_proc _vkad_load (void *module, const char *name) {
        _VKAD_ISO_C_COMPAT_dlsym compat_dlsym = (_VKAD_ISO_C_COMPAT_dlsym) dlsym;
        return (_vkad_proc) compat_dlsym (module, name);
}
void _vkad_close (void *module) {
        dlclose (module);
}

#if defined(__APPLE__)
#define _vkad_LIB_NAME "libvulkan.1.dylib"
#elif defined(__OpenBSD__) || defined(__NetBSD__)
#define _vkad_LIB_NAME "libvulkan.so"
#else
#define _vkad_LIB_NAME "libvulkan.so.1"
#endif

#endif /* _WIN32 */


void *_vkad_module = NULL;

void  _vkad_load_lib () {
        //don't load shared object twice
        if (_vkad_module != NULL) return;
        _vkad_module = _vkad_open (_vkad_LIB_NAME);
}

PFN_vkGetInstanceProcAddr _vkad_initalloaderDLL () {
        _vkad_load_lib();
        if (_vkad_module == NULL) {
                return NULL;
        }
        return (PFN_vkGetInstanceProcAddr) _vkad_load (_vkad_module, "vkGetInstanceProcAddr");
}

void _vkad_unload_lib () {
        if (_vkad_module != NULL) _vkad_close (_vkad_module);
}


void vkadLoadInitialLoaderFromPointer(PFN_vkGetInstanceProcAddr initial_loader) {
    vkGetInstanceProcAddr = initial_loader;
}

void vkadLoadInitialLoaderFromDLL () {
        vkGetInstanceProcAddr = _vkad_initalloaderDLL();
}

void vkadLoadVkGlobalFunctionsFromDLL () {
        //VK_VERSION_1_0
        vkEnumerateInstanceExtensionProperties = (PFN_vkEnumerateInstanceExtensionProperties) _vkad_load (_vkad_module, "vkEnumerateInstanceExtensionProperties");
        vkEnumerateInstanceLayerProperties     = (PFN_vkEnumerateInstanceLayerProperties) _vkad_load (_vkad_module, "vkEnumerateInstanceLayerProperties");
        vkCreateInstance                       = (PFN_vkCreateInstance) _vkad_load (_vkad_module, "vkCreateInstance");
        //VK_VERSION_1_1
        vkEnumerateInstanceVersion             = (PFN_vkEnumerateInstanceVersion) _vkad_load (_vkad_module, "vkEnumerateInstanceVersion");
}


void vkadLoadVkBaseFunctionsFromDLL () {
        //VkInstance dispatched functions
        //VK_VERSION_1_0
        vkDestroyInstance                  = (PFN_vkDestroyInstance) _vkad_load (_vkad_module, "PFN_vkDestroyInstance");
        vkEnumeratePhysicalDevices         = (PFN_vkEnumeratePhysicalDevices) _vkad_load (_vkad_module, "PFN_vkEnumeratePhysicalDevices");
        //VK_VERSION_1_1
        vkEnumeratePhysicalDeviceGroups    = (PFN_vkEnumeratePhysicalDeviceGroups) _vkad_load (_vkad_module, "vkEnumeratePhysicalDeviceGroups");
        
//VkPhysicalDevice dispatched functions
//VK_VERSION_1_0
vkGetPhysicalDeviceFeatures = (PFN_vkGetPhysicalDeviceFeatures) _vkad_load(_vkad_module, "vkGetPhysicalDeviceFeatures");
vkGetPhysicalDeviceFormatProperties = (PFN_vkGetPhysicalDeviceFormatProperties) _vkad_load(_vkad_module, "vkGetPhysicalDeviceFormatProperties");
vkGetPhysicalDeviceImageFormatProperties = (PFN_vkGetPhysicalDeviceImageFormatProperties) _vkad_load(_vkad_module, "vkGetPhysicalDeviceImageFormatProperties");
vkGetPhysicalDeviceProperties = (PFN_vkGetPhysicalDeviceProperties) _vkad_load(_vkad_module, "vkGetPhysicalDeviceProperties");
vkGetPhysicalDeviceQueueFamilyProperties = (PFN_vkGetPhysicalDeviceQueueFamilyProperties) _vkad_load(_vkad_module, "vkGetPhysicalDeviceQueueFamilyProperties");
vkGetPhysicalDeviceMemoryProperties = (PFN_vkGetPhysicalDeviceMemoryProperties) _vkad_load(_vkad_module, "vkGetPhysicalDeviceMemoryProperties");
vkCreateDevice = (PFN_vkCreateDevice) _vkad_load(_vkad_module, "vkCreateDevice");
vkEnumerateDeviceExtensionProperties = (PFN_vkEnumerateDeviceExtensionProperties) _vkad_load(_vkad_module, "vkEnumerateDeviceExtensionProperties");
vkEnumerateDeviceLayerProperties = (PFN_vkEnumerateDeviceLayerProperties) _vkad_load(_vkad_module, "vkEnumerateDeviceLayerProperties");
vkGetPhysicalDeviceSparseImageFormatProperties = (PFN_vkGetPhysicalDeviceSparseImageFormatProperties) _vkad_load(_vkad_module, "vkGetPhysicalDeviceSparseImageFormatProperties");
//VK_VERSION_1_1
vkGetPhysicalDeviceFeatures2 = (PFN_vkGetPhysicalDeviceFeatures2) _vkad_load(_vkad_module, "vkGetPhysicalDeviceFeatures2");
vkGetPhysicalDeviceProperties2 = (PFN_vkGetPhysicalDeviceProperties2) _vkad_load(_vkad_module, "vkGetPhysicalDeviceProperties2");
vkGetPhysicalDeviceFormatProperties2 = (PFN_vkGetPhysicalDeviceFormatProperties2) _vkad_load(_vkad_module, "vkGetPhysicalDeviceFormatProperties2");
vkGetPhysicalDeviceImageFormatProperties2 = (PFN_vkGetPhysicalDeviceImageFormatProperties2) _vkad_load(_vkad_module, "vkGetPhysicalDeviceImageFormatProperties2");
vkGetPhysicalDeviceQueueFamilyProperties2 = (PFN_vkGetPhysicalDeviceQueueFamilyProperties2) _vkad_load(_vkad_module, "vkGetPhysicalDeviceQueueFamilyProperties2");
vkGetPhysicalDeviceMemoryProperties2 = (PFN_vkGetPhysicalDeviceMemoryProperties2) _vkad_load(_vkad_module, "vkGetPhysicalDeviceMemoryProperties2");
vkGetPhysicalDeviceSparseImageFormatProperties2 = (PFN_vkGetPhysicalDeviceSparseImageFormatProperties2) _vkad_load(_vkad_module, "vkGetPhysicalDeviceSparseImageFormatProperties2");
vkGetPhysicalDeviceExternalBufferProperties = (PFN_vkGetPhysicalDeviceExternalBufferProperties) _vkad_load(_vkad_module, "vkGetPhysicalDeviceExternalBufferProperties");
vkGetPhysicalDeviceExternalFenceProperties = (PFN_vkGetPhysicalDeviceExternalFenceProperties) _vkad_load(_vkad_module, "vkGetPhysicalDeviceExternalFenceProperties");
vkGetPhysicalDeviceExternalSemaphoreProperties = (PFN_vkGetPhysicalDeviceExternalSemaphoreProperties) _vkad_load(_vkad_module, "vkGetPhysicalDeviceExternalSemaphoreProperties");
//VK_VERSION_1_3
vkGetPhysicalDeviceToolProperties = (PFN_vkGetPhysicalDeviceToolProperties) _vkad_load(_vkad_module, "vkGetPhysicalDeviceToolProperties");
        
        
}

void vkadLoadVkExtensionFunctionsFromDLL () {
        //VkInstance dispatched functions
        //VK_KHR_surface
        vkDestroySurfaceKHR                = (PFN_vkDestroySurfaceKHR) _vkad_load (_vkad_module, "vkDestroySurfaceKHR");
        //VK_KHR_display
        vkCreateDisplayPlaneSurfaceKHR     = (PFN_vkCreateDisplayPlaneSurfaceKHR) _vkad_load (_vkad_module, "vkCreateDisplayPlaneSurfaceKHR");
        //VK_KHR_device_group_creation
        vkEnumeratePhysicalDeviceGroupsKHR = (PFN_vkEnumeratePhysicalDeviceGroupsKHR) _vkad_load (_vkad_module, "vkEnumeratePhysicalDeviceGroupsKHR");
        //VK_EXT_debug_report
        vkCreateDebugReportCallbackEXT     = (PFN_vkCreateDebugReportCallbackEXT) _vkad_load (_vkad_module, "vkCreateDebugReportCallbackEXT");
        vkDestroyDebugReportCallbackEXT    = (PFN_vkDestroyDebugReportCallbackEXT) _vkad_load (_vkad_module, "vkDestroyDebugReportCallbackEXT");
        vkDebugReportMessageEXT            = (PFN_vkDebugReportMessageEXT) _vkad_load (_vkad_module, "vkDebugReportMessageEXT");
        //VK_EXT_debug_utils
        vkCreateDebugUtilsMessengerEXT     = (PFN_vkCreateDebugUtilsMessengerEXT) _vkad_load (_vkad_module, "vkCreateDebugUtilsMessengerEXT");
        vkDestroyDebugUtilsMessengerEXT    = (PFN_vkDestroyDebugUtilsMessengerEXT) _vkad_load (_vkad_module, "vkDestroyDebugUtilsMessengerEXT");
        vkSubmitDebugUtilsMessageEXT       = (PFN_vkSubmitDebugUtilsMessageEXT) _vkad_load (_vkad_module, "vkSubmitDebugUtilsMessageEXT");
        //VK_EXT_headless_surface
        vkCreateHeadlessSurfaceEXT         = (PFN_vkCreateHeadlessSurfaceEXT) _vkad_load (_vkad_module, "vkCreateHeadlessSurfaceEXT");
#ifdef VK_USE_PLATFORM_ANDROID_KHR
        //VK_KHR_android_surface
        vkCreateAndroidSurfaceKHR = (PFN_vkCreateAndroidSurfaceKHR) _vkad_load (_vkad_module, "vkCreateAndroidSurfaceKHR");
#endif
#ifdef VK_USE_PLATFORM_FUCHSIA
        //VK_FUCHSIA_imagepipe_surface
        vkCreateImagePipeSurfaceFUCHSIA = (PFN_vkCreateImagePipeSurfaceFUCHSIA) _vkad_load (_vkad_module, "vkCreateImagePipeSurfaceFUCHSIA");
#endif
#ifdef VK_USE_PLATFORM_IOS_MVK
        //VK_MVK_ios_surface
        vkCreateIOSSurfaceMVK = (PFN_vkCreateIOSSurfaceMVK) _vkad_load (_vkad_module, "vkCreateIOSSurfaceMVK");
#endif
#ifdef VK_USE_PLATFORM_MACOS_MVK
        //VK_MVK_macos_surface
        vkCreateMacOSSurfaceMVK = (PFN_vkCreateMacOSSurfaceMVK) _vkad_load (_vkad_module, "vkCreateMacOSSurfaceMVK");
#endif
#ifdef VK_USE_PLATFORM_METAL_EXT
        //VK_EXT_metal_surface
        vkCreateMetalSurfaceEXT = (PFN_vkCreateMetalSurfaceEXT) _vkad_load (_vkad_module, "vkCreateMetalSurfaceEXT");
#endif
#ifdef VK_USE_PLATFORM_VI_NN
        //VK_NN_vi_surface
        vkCreateViSurfaceNN = (PFN_vkCreateViSurfaceNN) _vkad_load (_vkad_module, "vkCreateViSurfaceNN");
#endif
#ifdef VK_USE_PLATFORM_WAYLAND_KHR
        //VK_KHR_wayland_surface
        vkCreateWaylandSurfaceKHR = (PFN_vkCreateWaylandSurfaceKHR) _vkad_load (_vkad_module, "vkCreateWaylandSurfaceKHR");
#endif
#ifdef VK_USE_PLATFORM_WIN32_KHR
        //VK_KHR_win32_surface
        vkCreateWin32SurfaceKHR = (PFN_vkCreateWin32SurfaceKHR) _vkad_load (_vkad_module, "vkCreateWin32SurfaceKHR");
#endif
#ifdef VK_USE_PLATFORM_XCB_KHR
        //VK_KHR_xcb_surface
        vkCreateXcbSurfaceKHR = (PFN_vkCreateXcbSurfaceKHR) _vkad_load (_vkad_module, "vkCreateXcbSurfaceKHR");
#endif
#ifdef VK_USE_PLATFORM_XLIB_KHR
        //VK_KHR_xlib_surface
        vkCreateXlibSurfaceKHR = (PFN_vkCreateXlibSurfaceKHR) _vkad_load (_vkad_module, "vkCreateXlibSurfaceKHR");
#endif
#ifdef VK_USE_PLATFORM_DIRECTFB_EXT
        //VK_EXT_directfb_surface
        vkCreateDirectFBSurfaceEXT = (PFN_vkCreateDirectFBSurfaceEXT) _vkad_load (_vkad_module, "vkCreateDirectFBSurfaceEXT");
#endif
#ifdef VK_USE_PLATFORM_GGP
        //VK_GGP_stream_descriptor_surface
        vkCreateStreamDescriptorSurfaceGGP = (PFN_vkCreateStreamDescriptorSurfaceGGP) _vkad_load (_vkad_module, "vkCreateStreamDescriptorSurfaceGGP");
#endif
#ifdef VK_USE_PLATFORM_SCREEN_QNX
        //VK_QNX_screen_surface
        vkCreateScreenSurfaceQNX = (PFN_vkCreateScreenSurfaceQNX) _vkad_load (_vkad_module, "vkCreateScreenSurfaceQNX");
#endif
        
        
        
//VkPhysicalDevice dispatched functions
//VK_KHR_surface
vkGetPhysicalDeviceSurfaceSupportKHR = (PFN_vkGetPhysicalDeviceSurfaceSupportKHR) _vkad_load (_vkad_module, "vkGetPhysicalDeviceSurfaceSupportKHR");
vkGetPhysicalDeviceSurfaceCapabilitiesKHR = (PFN_vkGetPhysicalDeviceSurfaceCapabilitiesKHR) _vkad_load (_vkad_module, "vkGetPhysicalDeviceSurfaceCapabilitiesKHR");        
vkGetPhysicalDeviceSurfaceFormatsKHR = (PFN_vkGetPhysicalDeviceSurfaceFormatsKHR) _vkad_load (_vkad_module, "vkGetPhysicalDeviceSurfaceFormatsKHR");        
vkGetPhysicalDeviceSurfacePresentModesKHR = (PFN_vkGetPhysicalDeviceSurfacePresentModesKHR) _vkad_load (_vkad_module, "vkGetPhysicalDeviceSurfacePresentModesKHR");        
//VK_KHR_swapchain
vkGetPhysicalDevicePresentRectanglesKHR = (PFN_vkGetPhysicalDevicePresentRectanglesKHR) _vkad_load (_vkad_module, "vkGetPhysicalDevicePresentRectanglesKHR"); 
//VK_KHR_display
vkGetPhysicalDeviceDisplayPropertiesKHR = (PFN_vkGetPhysicalDeviceDisplayPropertiesKHR) _vkad_load (_vkad_module, "vkGetPhysicalDeviceDisplayPropertiesKHR");
vkGetPhysicalDeviceDisplayPlanePropertiesKHR = (PFN_vkGetPhysicalDeviceDisplayPlanePropertiesKHR) _vkad_load (_vkad_module, "vkGetPhysicalDeviceDisplayPlanePropertiesKHR");        
vkGetDisplayPlaneSupportedDisplaysKHR = (PFN_vkGetDisplayPlaneSupportedDisplaysKHR) _vkad_load (_vkad_module, "vkGetDisplayPlaneSupportedDisplaysKHR");        
vkGetDisplayModePropertiesKHR = (PFN_vkGetDisplayModePropertiesKHR) _vkad_load (_vkad_module, "vkGetDisplayModePropertiesKHR");        
vkCreateDisplayModeKHR = (PFN_vkCreateDisplayModeKHR) _vkad_load (_vkad_module, "vkCreateDisplayModeKHR");        
vkGetDisplayPlaneCapabilitiesKHR = (PFN_vkGetDisplayPlaneCapabilitiesKHR) _vkad_load (_vkad_module, "vkGetDisplayPlaneCapabilitiesKHR");        
//VK_KHR_video_queue
vkGetPhysicalDeviceVideoCapabilitiesKHR = (PFN_vkGetPhysicalDeviceVideoCapabilitiesKHR) _vkad_load(_vkad_module, "vkGetPhysicalDeviceVideoCapabilitiesKHR");
vkGetPhysicalDeviceVideoFormatPropertiesKHR = (PFN_vkGetPhysicalDeviceVideoFormatPropertiesKHR) _vkad_load(_vkad_module, "vkGetPhysicalDeviceVideoFormatPropertiesKHR");
//VK_KHR_get_physical_device_properties2
vkGetPhysicalDeviceFeatures2KHR = (PFN_vkGetPhysicalDeviceFeatures2KHR) _vkad_load(_vkad_module, "vkGetPhysicalDeviceFeatures2KHR");
vkGetPhysicalDeviceProperties2KHR = (PFN_vkGetPhysicalDeviceProperties2KHR) _vkad_load(_vkad_module, "vkGetPhysicalDeviceProperties2KHR");
vkGetPhysicalDeviceFormatProperties2KHR = (PFN_vkGetPhysicalDeviceFormatProperties2KHR) _vkad_load(_vkad_module, "vkGetPhysicalDeviceFormatProperties2KHR");
vkGetPhysicalDeviceImageFormatProperties2KHR = (PFN_vkGetPhysicalDeviceImageFormatProperties2KHR) _vkad_load(_vkad_module, "vkGetPhysicalDeviceImageFormatProperties2KHR");
vkGetPhysicalDeviceQueueFamilyProperties2KHR = (PFN_vkGetPhysicalDeviceQueueFamilyProperties2KHR) _vkad_load(_vkad_module, "vkGetPhysicalDeviceQueueFamilyProperties2KHR");
vkGetPhysicalDeviceMemoryProperties2KHR = (PFN_vkGetPhysicalDeviceMemoryProperties2KHR) _vkad_load(_vkad_module, "vkGetPhysicalDeviceMemoryProperties2KHR");
vkGetPhysicalDeviceSparseImageFormatProperties2KHR = (PFN_vkGetPhysicalDeviceSparseImageFormatProperties2KHR) _vkad_load(_vkad_module, "vkGetPhysicalDeviceSparseImageFormatProperties2KHR");
//VK_KHR_external_memory_capabilities
vkGetPhysicalDeviceExternalBufferPropertiesKHR = (PFN_vkGetPhysicalDeviceExternalBufferPropertiesKHR) _vkad_load(_vkad_module, "vkGetPhysicalDeviceExternalBufferPropertiesKHR");
//VK_KHR_external_semaphore_capabilities
vkGetPhysicalDeviceExternalSemaphorePropertiesKHR = (PFN_vkGetPhysicalDeviceExternalSemaphorePropertiesKHR) _vkad_load(_vkad_module, "vkGetPhysicalDeviceExternalSemaphorePropertiesKHR");
//VK_KHR_external_fence_capabilities
PFN_vkGetPhysicalDeviceExternalFencePropertiesKHR                     vkGetPhysicalDeviceExternalFencePropertiesKHR;
//VK_KHR_performance_query
PFN_vkEnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR   vkEnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR;
PFN_vkGetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR           vkGetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR;
//VK_KHR_get_surface_capabilities2
PFN_vkGetPhysicalDeviceSurfaceCapabilities2KHR                        vkGetPhysicalDeviceSurfaceCapabilities2KHR;
PFN_vkGetPhysicalDeviceSurfaceFormats2KHR                             vkGetPhysicalDeviceSurfaceFormats2KHR;
//VK_KHR_get_display_properties2
PFN_vkGetPhysicalDeviceDisplayProperties2KHR                          vkGetPhysicalDeviceDisplayProperties2KHR;
PFN_vkGetPhysicalDeviceDisplayPlaneProperties2KHR                     vkGetPhysicalDeviceDisplayPlaneProperties2KHR;
PFN_vkGetDisplayModeProperties2KHR                                    vkGetDisplayModeProperties2KHR;
PFN_vkGetDisplayPlaneCapabilities2KHR                                 vkGetDisplayPlaneCapabilities2KHR;
//VK_KHR_fragment_shading_rate
PFN_vkGetPhysicalDeviceFragmentShadingRatesKHR                        vkGetPhysicalDeviceFragmentShadingRatesKHR;
//VK_NV_external_memory_capabilities
PFN_vkGetPhysicalDeviceExternalImageFormatPropertiesNV                vkGetPhysicalDeviceExternalImageFormatPropertiesNV;
//VK_EXT_direct_mode_display
PFN_vkReleaseDisplayEXT                                               vkReleaseDisplayEXT;
//VK_EXT_display_surface_counter
PFN_vkGetPhysicalDeviceSurfaceCapabilities2EXT                        vkGetPhysicalDeviceSurfaceCapabilities2EXT;
//VK_EXT_sample_locations
PFN_vkGetPhysicalDeviceMultisamplePropertiesEXT                       vkGetPhysicalDeviceMultisamplePropertiesEXT;
//VK_EXT_calibrated_timestamps
PFN_vkGetPhysicalDeviceCalibrateableTimeDomainsEXT                    vkGetPhysicalDeviceCalibrateableTimeDomainsEXT;
//VK_EXT_tooling_info
PFN_vkGetPhysicalDeviceToolPropertiesEXT                              vkGetPhysicalDeviceToolPropertiesEXT;
//VK_NV_cooperative_matrix
PFN_vkGetPhysicalDeviceCooperativeMatrixPropertiesNV                  vkGetPhysicalDeviceCooperativeMatrixPropertiesNV;
//VK_NV_coverage_reduction_mode
PFN_vkGetPhysicalDeviceSupportedFramebufferMixedSamplesCombinationsNV vkGetPhysicalDeviceSupportedFramebufferMixedSamplesCombinationsNV;
//VK_EXT_acquire_drm_display
PFN_vkAcquireDrmDisplayEXT                                            vkAcquireDrmDisplayEXT;
PFN_vkGetDrmDisplayEXT                                                vkGetDrmDisplayEXT;
//VK_NV_optical_flow
PFN_vkGetPhysicalDeviceOpticalFlowImageFormatsNV                      vkGetPhysicalDeviceOpticalFlowImageFormatsNV;
#ifdef VK_USE_PLATFORM_WAYLAND_KHR
//VK_KHR_wayland_surface
PFN_vkGetPhysicalDeviceWaylandPresentationSupportKHR vkGetPhysicalDeviceWaylandPresentationSupportKHR;
#endif
#ifdef VK_USE_PLATFORM_WIN32_KHR
//VK_KHR_win32_surface
PFN_vkGetPhysicalDeviceWin32PresentationSupportKHR vkGetPhysicalDeviceWin32PresentationSupportKHR;
//VK_EXT_full_screen_exclusive
PFN_vkGetPhysicalDeviceSurfacePresentModes2EXT     vkGetPhysicalDeviceSurfacePresentModes2EXT;
//VK_NV_acquire_winrt_display
PFN_vkAcquireWinrtDisplayNV                        vkAcquireWinrtDisplayNV;
PFN_vkGetWinrtDisplayNV                            vkGetWinrtDisplayNV;
#endif
#ifdef VK_USE_PLATFORM_XCB_KHR
//VK_KHR_xcb_surface
PFN_vkGetPhysicalDeviceXcbPresentationSupportKHR vkGetPhysicalDeviceXcbPresentationSupportKHR;
#endif
#ifdef VK_USE_PLATFORM_XLIB_KHR
//VK_KHR_xlib_surface
PFN_vkGetPhysicalDeviceXlibPresentationSupportKHR vkGetPhysicalDeviceXlibPresentationSupportKHR;
#endif
#ifdef VK_USE_PLATFORM_DIRECTFB_EXT
//VK_EXT_directfb_surface
PFN_vkGetPhysicalDeviceDirectFBPresentationSupportEXT vkGetPhysicalDeviceDirectFBPresentationSupportEXT;
#endif
#ifdef VK_USE_PLATFORM_XLIB_XRANDR_EXT
//VK_EXT_acquire_xlib_display
PFN_vkAcquireXlibDisplayEXT    vkAcquireXlibDisplayEXT;
PFN_vkGetRandROutputDisplayEXT vkGetRandROutputDisplayEXT;
#endif
#ifdef VK_USE_PLATFORM_SCREEN_QNX
//VK_QNX_screen_surface
PFN_vkGetPhysicalDeviceScreenPresentationSupportQNX vkGetPhysicalDeviceScreenPresentationSupportQNX;
#endif
}


void vkadLoadVkGlobalFunctionsFromInitialLoader () {
        //VK_VERSION_1_0
        vkEnumerateInstanceExtensionProperties = (PFN_vkEnumerateInstanceExtensionProperties) vkGetInstanceProcAddr (NULL, "vkEnumerateInstanceExtensionProperties");
        vkEnumerateInstanceLayerProperties     = (PFN_vkEnumerateInstanceLayerProperties) vkGetInstanceProcAddr (NULL, "vkEnumerateInstanceLayerProperties");
        vkCreateInstance                       = (PFN_vkCreateInstance) vkGetInstanceProcAddr (NULL, "vkCreateInstance");
        //VK_VERSION_1_1
        vkEnumerateInstanceVersion             = (PFN_vkEnumerateInstanceVersion) vkGetInstanceProcAddr (NULL, "vkEnumerateInstanceVersion");
}


void vkadLoadVkBaseFunctionsFromInstanceLoader (VkInstance instance) {
    
}


void vkadUpdateVkDeviceBaseFunctionsFromDeviceLoader (VkDevice device) { }


void vkadUpdateVkDeviceExtensionFunctionsFromDeviceLoader (VkDevice device) { }



void vkadLoadVk (PFN_vkGetInstanceProcAddr initial_loader) { }

void vkadLoadVkInstanceFunctions (VkInstance instance) { }

void vkadUpdateVkDeviceFunctions (VkDevice device) { }



