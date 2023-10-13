#pragma once
#include "custom_raylib.h"

typedef struct character {
	float maxstamina;
	float stamina;
	float staminaregen;
	float accel;
	float maxspeed;
	float xspeed;
	float yspeed;
	Rectangle position;
	Rectangle source;
	float dashspeed;
	float dashcost;
	float dashdurationms;
	const char* name;
	Texture2D* texture;
	char type;//0 cat, 1 mouse
	char dashing;
	double dashingstartms;
}character;

char game(void);

void collisionRes(Rectangle* dynamicr, Rectangle* staticr);

void physicCharacter(character* x, DA* walls);

void inputCharacter(character* x, char playernum);

void renderCharacter(character* x);