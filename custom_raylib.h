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

typedef struct buttonImage {
	Rectangle clickposition;
	Rectangle* renderposition;
	Rectangle* srcback;
	Rectangle* srcfront;
	Rectangle* srcclicked;
	Texture2D* backimage;
	Texture2D* frontimage;
	Texture2D* clickedimage;
	char pressed;
}buttonImage;

typedef struct buttonText {
	const char* text;
	Color backcolor;
	Color frontcolor;
	Rectangle position;//set only x and y
}buttonText;

char RenderButtonCustom(button* b, Font* f);

char RenderButtonImageCustom(buttonImage* b);

char RenderButtonTextCustom(buttonText* b, Font* f);

void InitButtonTextCustom(buttonText* b, Font* f);

//Animation-------------------------------------------

typedef struct animation {
	Texture2D* maintexture;
	DA* sourcerects;//Rectangle DA
	Rectangle* dest;
	Vector2 collisiondimensions;//the centered collision box dimensions in the dest render location for the animation batch
	unsigned int framedurationms;
	char disabled;
	double animationstartms;
}animation;

void AddAnimationCustom(animation* anim);

void RemoveAnimationCustom(animation* anim);

void ClearAnimationCustom(void);

void DrawAnimationsCustom(void);