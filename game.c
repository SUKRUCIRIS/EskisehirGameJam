#include "game.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

void collisionRes(Rectangle* dynamicr, Rectangle* staticr) {
	if (CheckCollisionRecs(*dynamicr, *staticr)) {
		float x1_overlap = max(dynamicr->x, staticr->x);
		float y1_overlap = max(dynamicr->y, staticr->y);
		float x2_overlap = min(dynamicr->x + dynamicr->width, staticr->x + staticr->width);
		float y2_overlap = min(dynamicr->y + dynamicr->height, staticr->y + staticr->height);

		// Calculate the width and height of the overlapping rectangle
		float overlapX = x2_overlap - x1_overlap;
		float overlapY = y2_overlap - y1_overlap;

		if (overlapX < overlapY) {
			if (dynamicr->x < staticr->x) {
				dynamicr->x = staticr->x - dynamicr->width;
			}
			else {
				dynamicr->x = staticr->x + staticr->width;
			}
		}
		else {
			if (dynamicr->y < staticr->y) {
				dynamicr->y = staticr->y - dynamicr->height;
			}
			else {
				dynamicr->y = staticr->y + staticr->height;
			}
		}
	}
}

void physicCharacter(character* x, DA* walls) {
	int physicsloopnumber = 10;
	Rectangle* walls_data = get_data_DA(walls);
	float xstep = (x->xspeed / physicsloopnumber);
	float ystep = (x->yspeed / physicsloopnumber);

	for (int i = 0; i < physicsloopnumber; i++) {
		x->position.x += xstep;
		x->position.y += ystep;
		for (unsigned int i = 0; i < get_size_DA(walls); i++) {
			collisionRes(&x->position, &walls_data[i]);
		}
	}

	x->position2.x = x->position.x + (x->position.width - x->position2.width) / 2;
	x->position2.y = x->position.y + (x->position.height - x->position2.height) / 2;
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
		x->dashingendms = GetTime() * 1000;
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
			x->stamina -= x->dashcost;
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
			x->dashingendms = 0;
			x->stamina -= x->dashcost;
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
	Vector2 origingame = { 0,0 };
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

	float arenawidth = 1000;
	float arenaheight = 850;
	float doorwidth = 70;
	float doorheight = 35;

	Rectangle arenaleft = { (1920 - arenawidth) / 2 - 10,1080 - arenaheight,10,arenaheight };
	Rectangle arenaright = { 1920 - ((1920 - arenawidth) / 2),1080 - arenaheight,10,arenaheight };
	Rectangle arenatop = { (1920 - arenawidth) / 2 - 10,1080 - arenaheight,arenawidth + 20,10 };
	Rectangle arenabottom = { (1920 - arenawidth) / 2 - 10,1080,arenawidth + 20,10 };

	Rectangle Door = { (arenatop.width - doorwidth) / 2 + arenatop.x,arenatop.y - doorheight + 10,doorwidth,doorheight + 5 };

	Texture2D catimage = LoadTexture("data/cat.png");
	Texture2D mouseimage = LoadTexture("data/mouse.png");
	Texture2D bg = LoadTexture("data/ck.png");

	character cat1 = {
		.stamina = 100,
		.maxstamina = 100,
		.staminaregen = 60,
		.accel = 20,
		.maxspeed = 6,
		.dashspeed = 15,
		.dashcost = 100,
		.dashdurationms = 300,
		.name = "Tom",
		.texture = &catimage,
		.position = {(arenatop.width - 64) / 2 + arenatop.x,400,64,64},
		.position2 = {0},
		.source = {0,0,64,64},
		.type = 0,
		.xspeed = 0,
		.yspeed = 0,
		.dashing = 0,
		.dashingstartms = 0,
		.dashingendms = 0,
		.player = 1
	};

	character mouse1 = {
		.stamina = 100,
		.maxstamina = 100,
		.staminaregen = 75,
		.accel = 25,
		.maxspeed = 8,
		.dashspeed = 17,
		.dashcost = 100,
		.dashdurationms = 100,
		.name = "Jerry",
		.texture = &mouseimage,
		.position = {(arenatop.width - 48) / 2 + arenatop.x,1000,48,48},
		.position2 = {(arenatop.width - 48) / 2 + arenatop.x + 20,1020,8,8},
		.source = {0,0,534,459},
		.type = 1,
		.xspeed = 0,
		.yspeed = 0,
		.dashing = 0,
		.dashingstartms = 0,
		.dashingendms = 0,
		.player = 2
	};

	char cat1_stamina_text[30] = { 0 };
	char mouse1_stamina_text[30] = { 0 };

	Vector2 cat1_sta_pos = { 50, 400 };
	Vector2 mouse1_sta_pos = { 50, 500 };

	DA* walls = create_DA(sizeof(Rectangle));
	pushback_DA(walls, &arenaleft);
	pushback_DA(walls, &arenaright);
	pushback_DA(walls, &arenatop);
	pushback_DA(walls, &arenabottom);

	Font defont = LoadFontEx("data/x.ttf", 50, 0, 0);

	char quitted = 0;

	int player1score = 0;
	int player2score = 0;

	Vector2 player1scorepos = { 1600,400 };
	Vector2 player2scorepos = { 1600,500 };

	char player1_score_text[30] = { 0 };
	char player2_score_text[30] = { 0 };

	char arena_number_text[30] = { 0 };
	Vector2 arena_number_pos = { 1600,300 };

	Rectangle bannedcatarea = { arenatop.x + 10,arenatop.y + 10,arenawidth,128 };
	double bannedcatlastenter = 0;

	for (int i = 0; i < 100; i++) {
		cat1.position.x = (arenatop.width - 64) / 2 + arenatop.x;
		cat1.position.y = 400;
		mouse1.position.x = (arenatop.width - 48) / 2 + arenatop.x;
		mouse1.position.y = 1000;
		while (1) {
			BeginDrawingCustom();

			ClearBackground(RAYWHITE);

			DrawTexture(bg, 0, 0, WHITE);

			if (RenderButtonCustom(&btn, &defont)) {
				quitted = 1;
				break;
			}

			DrawRectangleRec(arenaleft, BLACK);
			DrawRectangleRec(arenaright, BLACK);
			DrawRectangleRec(arenatop, BLACK);
			DrawRectangleRec(arenabottom, BLACK);
			DrawRectangleRec(Door, RED);
			DrawRectangleRec(bannedcatarea, ORANGE);

			inputCharacter(&cat1, cat1.player);
			inputCharacter(&mouse1, mouse1.player);

			physicCharacter(&cat1, walls);
			physicCharacter(&mouse1, walls);

			renderCharacter(&cat1);
			renderCharacter(&mouse1);

			cat1.stamina += cat1.staminaregen * GetFrameTime();
			if (cat1.stamina > cat1.maxstamina) {
				cat1.stamina = cat1.maxstamina;
			}

			mouse1.stamina += mouse1.staminaregen * GetFrameTime();
			if (mouse1.stamina > mouse1.maxstamina) {
				mouse1.stamina = mouse1.maxstamina;
			}

			sprintf(cat1_stamina_text, "Cat: %.1f/%.1f", cat1.stamina, cat1.maxstamina);
			sprintf(mouse1_stamina_text, "Mouse: %.1f/%.1f", mouse1.stamina, mouse1.maxstamina);

			sprintf(player1_score_text, "Player1: %d", player1score);
			sprintf(player2_score_text, "PLayer2: %d", player2score);

			sprintf(arena_number_text, "Turn: %d", i);

			DrawTextEx(defont, cat1_stamina_text, cat1_sta_pos, 40, 0, WHITE);
			DrawTextEx(defont, mouse1_stamina_text, mouse1_sta_pos, 40, 0, WHITE);

			DrawTextEx(defont, player1_score_text, player1scorepos, 40, 0, WHITE);
			DrawTextEx(defont, player2_score_text, player2scorepos, 40, 0, WHITE);

			DrawTextEx(defont, arena_number_text, arena_number_pos, 40, 0, WHITE);

			EndDrawingCustom();

			if (CheckCollisionRecs(mouse1.position, Door)) {
				if (mouse1.player == 1) {
					player1score += 3;
				}
				if (mouse1.player == 2) {
					player2score += 3;
				}
				break;
			}
			if (CheckCollisionRecs(mouse1.position, cat1.position) && mouse1.dashing == 0
				&& !(GetTime() * 1000 - mouse1.dashingendms <= 350 && !CheckCollisionRecs(mouse1.position2, cat1.position))) {
				if (cat1.player == 1) {
					player1score += 3;
				}
				if (cat1.player == 2) {
					player2score += 3;
				}
				break;
			}
			if (CheckCollisionRecs(bannedcatarea, cat1.position)) {
				if (bannedcatlastenter != 0) {
					if (GetTime() - bannedcatlastenter >= 3) {
						if (mouse1.player == 1) {
							player1score += 3;
						}
						if (mouse1.player == 2) {
							player2score += 3;
						}
						break;
					}
				}
				else {
					bannedcatlastenter = GetTime();
				}
			}
			else {
				bannedcatlastenter = 0;
			}
		}
		if (quitted == 1) {
			break;
		}
		quitted = cat1.player;
		cat1.player = mouse1.player;
		mouse1.player = quitted;
		quitted = 0;
	}
	UnloadTexture(catimage);
	UnloadTexture(mouseimage);
	UnloadTexture(bg);
	UnloadFont(defont);
	delete_DA(walls);
	return 0;
}