#pragma once
#include "Window.h"

class App
{
public:
	App();
	~App();

	void Run();

public:
	virtual void OnSetup()   {};
	virtual void OnUpdate()  {};
	virtual void OnDestroy() {};

private:
	Window* m_Win;
};

