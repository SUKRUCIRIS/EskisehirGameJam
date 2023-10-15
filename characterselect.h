#pragma once
#include "custom_raylib.h"

typedef struct characterstart {
	Texture2D portrait;
	Rectangle portraitsrc;
	float maxspeed;
	float accel;
	float maxstamina;
	float staminaregen;
	float dashspeed;
	float dashcost;
	float dashdurationms;
	char type;
	const char* name;
	animation* walkdown;
	animation* walkup;
	animation* walkleft;
	animation* walkright;
	animation* idle;
	animation* dashdown;
	animation* dashup;
	animation* dashleft;
	animation* dashright;
}characterstart;

typedef struct player {
	char number;
	characterstart* cat;
	characterstart* mouse;
}player;

characterstart* get_blackmouse(void);

characterstart* get_whitemouse(void);

characterstart* get_blackcat(void);

characterstart* get_whitecat(void);

player* get_player1(void);

player* get_player2(void);

void initcharacterstarts(void);

void destroycharacterstarts(void);

char selectscreen(void);

void noselectscreen(void);