#include <Include/Game.h>
#include <windows.h>

int main()
{
	srand(time(NULL));
	//HWND hConsole = GetConsoleWindow();
	//ShowWindow(hConsole, SW_HIDE);

	Game game;
	game.run();

	return 0;
}
