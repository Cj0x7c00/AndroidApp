#include "Context.h"
#include "Vulkan/VulkanContext.h"
#include "Core/Window.h"

namespace anv {
    Context* Context::Create(Window* _win)
    {
        return new VulkanContext(_win);
    }
}