#include "Context.h"
#include "Render/Platform/Vulkan/VulkanContext.h"
#include "Core/Window.h"

namespace anv {
    Context* Context::Create(Window* _win)
    {
        // TODO: user API switch
        return new VulkanContext(_win);
    }
}