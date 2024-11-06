#include "App.h"

App::App()
{
	const WindowSpec s{
	.width = 800,
	.height = 500,
	.name = "My Window"
	};

	m_Win = new Window(s);

	// Setup should happen after App setup
	OnSetup();
}

App::~App()
{
	OnDestroy();

	// Everything should be deleted before the app itself gets deletes
	delete m_Win;
}

void App::Run()
{
	while (!m_Win->ShouldClose())
	{
		m_Win->PollInput();

		// OnUpdate should hapen after input polling
		OnUpdate();
	}
}