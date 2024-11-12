#pragma once

#include "Context/Context.h"
#include "../Util/UMacros.h"
#include "Swapchain.h"

namespace anv {

    class Renderer
    {
    public:
        static 
        void Init();

        static 
        void Shutdown();

    private:
        inline static Context* m_Context   = nullptr;

        inline static 
            _unique(Swapchain) m_Swapchain = nullptr;

        // RenderQueue*  m_CmdQueue
        // RenderThread* m_RenderThread
    };
}
