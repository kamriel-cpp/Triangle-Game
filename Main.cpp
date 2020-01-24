#include <Include/Includes.h>
#include <Include/Constants.h>
#include <Include/Enumerations.h>
#include <Include/Game.h>
#include <windows.h>

int main()
{
	srand(time(NULL));

	#ifndef DEBUG_SHOW_CONSOLE
	HWND hConsole = GetConsoleWindow();
	ShowWindow(hConsole, SW_HIDE);
	#endif

	Game game;
	game.run();

	return 0;
}
