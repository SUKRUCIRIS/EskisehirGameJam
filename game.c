#include "game.h"
#include <math.h>

Vector2 origingame = { 0,0 };

void physicCharacter(character* x, DA* walls, Rectangle* door) {
	x->position.x += x->xspeed;
	x->position.y += x->yspeed;
}

void inputCharacter(character* x, char playernum) {
	if (x->dashing == 1 && GetTime() * 1000 - x->dashingstartms >= x->dashdurationms) {
		if (x->type == 0) {
			x->xspeed *= 0.1f;
			x->yspeed *= 0.1f;
		}
		else if (x->type == 1) {
			x->xspeed *= 0.6f;
			x->yspeed *= 0.6f;
		}
		x->dashing = 0;
		x->dashingstartms = 0;
	}
	if (playernum == 1) {
		if (x->dashing == 0) {
			if (IsKeyDown(KEY_W)) {
				x->yspeed -= x->accel * GetFrameTime();
			}
			else if (x->yspeed < 0) {
				x->yspeed = 0;
			}
			if (IsKeyDown(KEY_S)) {
				x->yspeed += x->accel * GetFrameTime();
			}
			else if (x->yspeed > 0) {
				x->yspeed = 0;
			}
			if (IsKeyDown(KEY_A)) {
				x->xspeed -= x->accel * GetFrameTime();
			}
			else if (x->xspeed < 0) {
				x->xspeed = 0;
			}
			if (IsKeyDown(KEY_D)) {
				x->xspeed += x->accel * GetFrameTime();
			}
			else if (x->xspeed > 0) {
				x->xspeed = 0;
			}
		}
		if (IsKeyPressed(KEY_LEFT_CONTROL) && x->stamina >= x->dashcost && (x->yspeed != 0 || x->xspeed != 0) && x->dashing == 0) {
			x->dashing = 1;
			x->dashingstartms = GetTime() * 1000;
			//x->stamina -= x->dashcost;
		}
	}
	else if (playernum == 2) {
		if (x->dashing == 0) {
			if (IsKeyDown(KEY_UP)) {
				x->yspeed -= x->accel * GetFrameTime();
			}
			else if (x->yspeed < 0) {
				x->yspeed = 0;
			}
			if (IsKeyDown(KEY_DOWN)) {
				x->yspeed += x->accel * GetFrameTime();
			}
			else if (x->yspeed > 0) {
				x->yspeed = 0;
			}
			if (IsKeyDown(KEY_LEFT)) {
				x->xspeed -= x->accel * GetFrameTime();
			}
			else if (x->xspeed < 0) {
				x->xspeed = 0;
			}
			if (IsKeyDown(KEY_RIGHT)) {
				x->xspeed += x->accel * GetFrameTime();
			}
			else if (x->xspeed > 0) {
				x->xspeed = 0;
			}
		}
		if (IsKeyPressed(KEY_RIGHT_SHIFT) && x->stamina >= x->dashcost && (x->yspeed != 0 || x->xspeed != 0) && x->dashing == 0) {
			x->dashing = 1;
			x->dashingstartms = GetTime() * 1000;
			//x->stamina -= x->dashcost;
		}
	}

	if (x->dashing == 0) {
		if (sqrtf(x->xspeed * x->xspeed + x->yspeed * x->yspeed) >= x->maxspeed) {
			float scale = x->maxspeed / sqrtf(x->xspeed * x->xspeed + x->yspeed * x->yspeed);
			x->xspeed *= scale;
			x->yspeed *= scale;
		}
	}
	else {
		float scale = x->dashspeed / sqrtf(x->xspeed * x->xspeed + x->yspeed * x->yspeed);
		x->xspeed *= scale;
		x->yspeed *= scale;
	}
}

void renderCharacter(character* x) {
	DrawTexturePro(*x->texture, x->source, x->position, origingame, 0, WHITE);
}

char game(void) {
	button btn = {
	   .position = {50,50, 200,50},
	   .backcolor = {100,20,100,255},
	   .frontcolor = {200,30,200,255},
	   .text = "QUIT",
	   .textcolor = {255,255,255,255}
	};
	Font defont = LoadFontEx("data/x.ttf", 50, 0, 0);

	float arenawidth = 1000;
	float arenaheight = 850;
	float doorwidth = 70;
	float doorheight = 35;

	Rectangle arenaleft = { (1920 - arenawidth) / 2 - 10,1080 - arenaheight,10,arenaheight };
	Rectangle arenaright = { 1920 - ((1920 - arenawidth) / 2),1080 - arenaheight,10,arenaheight };
	Rectangle arenatop = { (1920 - arenawidth) / 2 - 10,1080 - arenaheight,arenawidth + 20,10 };
	Rectangle arenabottom = { (1920 - arenawidth) / 2 - 10,1080,arenawidth + 20,10 };

	Rectangle Door = { (arenatop.width - doorwidth) / 2 + arenatop.x,arenatop.y - doorheight + 10,doorwidth,doorheight };

	Texture2D catimage = LoadTexture("data/cat.png");
	Texture2D mouseimage = LoadTexture("data/mouse.png");
	Texture2D bg = LoadTexture("data/ck.png");

	character cat1 = {
		.stamina = 100,
		.maxstamina = 100,
		.staminaregen = 10,
		.accel = 20,
		.maxspeed = 6,
		.dashspeed = 15,
		.dashcost = 100,
		.dashdurationms = 300,
		.name = "Tom",
		.texture = &catimage,
		.position = {(arenatop.width - 64) / 2 + arenatop.x,280,64,64},
		.source = {0,0,64,64},
		.type = 0,
		.xspeed = 0,
		.yspeed = 0,
		.dashing = 0,
		.dashingstartms = 0
	};

	character mouse1 = {
		.stamina = 100,
		.maxstamina = 100,
		.staminaregen = 10,
		.accel = 25,
		.maxspeed = 8,
		.dashspeed = 17,
		.dashcost = 100,
		.dashdurationms = 100,
		.name = "Jerry",
		.texture = &mouseimage,
		.position = {(arenatop.width - 48) / 2 + arenatop.x,1000,48,48},
		.source = {0,0,534,459},
		.type = 1,
		.xspeed = 0,
		.yspeed = 0,
		.dashing = 0,
		.dashingstartms = 0
	};

	while (1) {
		BeginDrawingCustom();

		ClearBackground(RAYWHITE);

		DrawTexture(bg, 0, 0, WHITE);

		if (RenderButtonCustom(&btn, &defont)) {
			break;
		}

		DrawRectangleRec(arenaleft, BLACK);
		DrawRectangleRec(arenaright, BLACK);
		DrawRectangleRec(arenatop, BLACK);
		DrawRectangleRec(arenabottom, BLACK);
		DrawRectangleRec(Door, RED);

		inputCharacter(&cat1, 1);
		inputCharacter(&mouse1, 2);

		physicCharacter(&cat1, 0, 0);
		physicCharacter(&mouse1, 0, 0);

		renderCharacter(&cat1);
		renderCharacter(&mouse1);

		EndDrawingCustom();
	}
	UnloadFont(defont);

	return 0;
}