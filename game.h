#pragma once
#include "custom_raylib.h"
#include "characterselect.h"

typedef struct character {
	characterstart* stats;
	float stamina;
	float xspeed;
	float yspeed;
	Rectangle position;
	Rectangle collisionbox1;
	Rectangle collisionbox2;//smaller collision box after the dash
	char dashing;
	double dashingstartms;
	double dashingendms;
	char player;//1,2
	char animselect;//1,...,9
}character;

char game(void);

void collisionRes(Rectangle* dynamicr, Rectangle* staticr);

void physicCharacter(character* x, DA* walls);

void inputCharacter(character* x, char playernum);

void renderCharacter(character* x);