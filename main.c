#include "custom_raylib.h"

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

    button btn = {
        .position = {50,50, 200,50},
        .backcolor = {100,20,100,255},
        .frontcolor = {200,30,200,255},
        .text = "QUIT",
        .textcolor = {255,255,255,255}
    };

    Font defont = LoadFontEx("data/x.ttf", 40, 0, 0);

    Texture2D walking = LoadTexture("data/walk.png");

    Rectangle character = { 500,500,128,128 };

    animation walkanim = {
        .animationstartms = -1,
        .dest = &character,
        .disabled = 0,
        .framedurationms = 200,
        .maintexture = &walking
    };

    walkanim.sourcerects = create_DA(sizeof(Rectangle));
    Rectangle src = { 0,0,220,220 };
    pushback_DA(walkanim.sourcerects, &src);
    src.x = 220;
    pushback_DA(walkanim.sourcerects, &src);
    src.x = 440;
    pushback_DA(walkanim.sourcerects, &src);
    src.x = 660;
    pushback_DA(walkanim.sourcerects, &src);

    AddAnimationCustom(&walkanim);

    while (!WindowShouldClose())
    {
        BeginDrawingCustom();

        ClearBackground(RAYWHITE);

        if (RenderButtonCustom(&btn, &defont)) {
            break;
        }

        DrawAnimationsCustom();

        EndDrawingCustom();
    }

    delete_DA(walkanim.sourcerects);

    UnloadFont(defont);

    CloseRaylibCustom();

    CloseWindow();

	return 0;
}