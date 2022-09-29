// VillainEditor.cpp : Defines the entry point for the application.
//

#include "VillainEditor.hpp"
#include "window.hpp"

using namespace villain;
int main()
{
	WindowProperties props("Editor", 1080, 720);
	Window* window = Window::create(props);

	return 0;
}
