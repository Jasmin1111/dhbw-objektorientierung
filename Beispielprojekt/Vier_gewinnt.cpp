#include <Gosu/Gosu.hpp>
#include <Gosu/AutoLink.hpp>

class GameWindow : public Gosu::Window
{
public:

	GameWindow()
		: Window(800, 600)
	{
		set_caption("Hallo Fabio");
	}

	void draw() override
	{
	}

	void update() override
	{
	}
};

int main()
{
	GameWindow window;
	window.show();
}
