#include "Renderer.h"
#include <Core/App.h>

namespace anv
{
	void Renderer::Init()
	{
		m_Context   = App::GetInstance()->GetMainWindow()->GetContext();
		m_Swapchain = Swapchain::Create(m_Context);
	}

	void Renderer::Shutdown()
	{

	}
}