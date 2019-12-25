#include <Include/Game.h>
//#include <windows.h>

int main()
{
	srand(time(NULL));

	//This code removes the console when the application starts using the <Windows.h> library
	//HWND hConsole = GetCon!soleWindow();
	//ShowWindow(hConsole, SW_HIDE);
	
	Game game;
	game.run();

	return 0;
}
