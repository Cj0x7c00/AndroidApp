#include <stdexcept>
#include "src/App.h"

class AnApp :
	public App
{
public:
	inline void OnSetup() override
	{
		
	}

	inline void OnUpdate() override
	{
	}

	inline void OnDestroy() override
	{

	}
};

int main()
{
	App* app = new App();

	app->Run();

	delete app;
}