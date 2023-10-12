#pragma once
#include <raylib.h>
#include "dynamic.h"

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

//Animation-------------------------------------------

typedef struct animation {
	Texture2D* maintexture;
	DA* sourcerects;//Rectangle DA
	Rectangle* dest;
	unsigned int framedurationms;
	char disabled;
	double animationstartms;
}animation;

void AddAnimationCustom(animation* anim);

void RemoveAnimationCustom(animation* anim);

void ClearAnimationCustom(void);

void DrawAnimationsCustom(void);