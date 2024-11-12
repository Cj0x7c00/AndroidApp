#pragma once
namespace anv {

	class Window;
	
	class Context
	{
	public:
		static Context* Create(Window* _win);

	public:
		virtual void CreateBuffer() = 0;
	};
}
