#pragma once
#include <raylib.h>

//Virtual Resolution----------------------------------

void InitRaylibCustom(int virtualwidth, int virtualheight);

void CloseRaylibCustom(void);

void BeginDrawingCustom(void);

void EndDrawingCustom(void);

Vector2* GetVirtualResCustom(void);

Vector2* GetMousePositionCustom(void);

//Button-----------------------------------------------

typedef struct button {
	Rectangle position;
	const char* text;
	Color textcolor;
	Color backcolor;
	Color frontcolor;
}button;

char RenderButtonCustom(button* b, Font* f);