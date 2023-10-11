#include "custom_raylib.h"

//SUKRU CIRIS 2023
//linker commandline: /NODEFAULTLIB:LIBCMT /subsystem:windows /entry:mainCRTStartup
//linker: raylib.lib msvcrt.lib winmm.lib

int main() {
	InitWindow(GetScreenWidth(), GetScreenHeight(), "GameJam");

    SetWindowState(FLAG_WINDOW_HIGHDPI | FLAG_VSYNC_HINT | FLAG_WINDOW_ALWAYS_RUN |
        FLAG_WINDOW_UNDECORATED | FLAG_WINDOW_MAXIMIZED | FLAG_FULLSCREEN_MODE | FLAG_MSAA_4X_HINT);

    SetTargetFPS(60);

    SetExitKey(0);

    ToggleFullscreen();

    InitRaylibCustom(1920, 1080);

    while (!WindowShouldClose())
    {
        BeginDrawingCustom();

        EndDrawingCustom();
    }

    CloseRaylibCustom();

    CloseWindow();

	return 0;
}