#include "custom_raylib.h"
#include "game.h"
#include "menus.h"

//SUKRU CIRIS 2023
//msvc compiler
//linker commandline: /NODEFAULTLIB:LIBCMT /subsystem:windows /entry:mainCRTStartup /ignore:4099
//linker: raylib.lib msvcrt.lib winmm.lib

int main() {
	InitWindow(GetScreenWidth(), GetScreenHeight(), "GameJam");

	SetWindowState(FLAG_WINDOW_HIGHDPI | FLAG_VSYNC_HINT | FLAG_WINDOW_ALWAYS_RUN |
		FLAG_WINDOW_UNDECORATED | FLAG_WINDOW_MAXIMIZED | FLAG_FULLSCREEN_MODE | FLAG_MSAA_4X_HINT);

	SetTargetFPS(60);

	SetExitKey(0);

	ToggleFullscreen();

	InitRaylibCustom(1920, 1080);

	intro();

	char x = 0;

	while (1) {

		x = mainmenu();

		if (x == 1) {
			break;
		}
		else if (x == 0) {
			initcharacterstarts();
			noselectscreen();
			x = game();
			destroycharacterstarts();
		}

	}

	CloseRaylibCustom();

	CloseWindow();

	return 0;
}