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
		x->collisionbox1.x += xstep;
		x->collisionbox1.y += ystep;
		for (unsigned int i = 0; i < get_size_DA(walls); i++) {
			collisionRes(&x->collisionbox1, &walls_data[i]);
		}
	}

	x->collisionbox2.x = x->collisionbox1.x + (x->collisionbox1.width - x->collisionbox2.width) / 2;
	x->collisionbox2.y = x->collisionbox1.y + (x->collisionbox1.height - x->collisionbox2.height) / 2;

	x->position.x = x->collisionbox1.x + (x->collisionbox1.width - x->position.width) / 2;
	x->position.y = x->collisionbox1.y + (x->collisionbox1.height - x->position.height) / 2;
}

void inputCharacter(character* x, char playernum) {
	if (x->dashing == 1 && GetTime() * 1000 - x->dashingstartms >= x->stats->dashdurationms) {
		if (x->stats->type == 0) {
			x->xspeed *= 0.1f;
			x->yspeed *= 0.1f;
		}
		else if (x->stats->type == 1) {
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
				x->yspeed -= x->stats->accel * GetFrameTime();
			}
			else if (x->yspeed < 0) {
				x->yspeed = 0;
			}
			if (IsKeyDown(KEY_S)) {
				x->yspeed += x->stats->accel * GetFrameTime();
			}
			else if (x->yspeed > 0) {
				x->yspeed = 0;
			}
			if (IsKeyDown(KEY_A)) {
				x->xspeed -= x->stats->accel * GetFrameTime();
			}
			else if (x->xspeed < 0) {
				x->xspeed = 0;
			}
			if (IsKeyDown(KEY_D)) {
				x->xspeed += x->stats->accel * GetFrameTime();
			}
			else if (x->xspeed > 0) {
				x->xspeed = 0;
			}
		}
		if (IsKeyPressed(KEY_LEFT_CONTROL) && x->stamina >= x->stats->dashcost && (x->yspeed != 0 || x->xspeed != 0) && x->dashing == 0) {
			x->dashing = 1;
			x->dashingstartms = GetTime() * 1000;
			x->stamina -= x->stats->dashcost;
		}
	}
	else if (playernum == 2) {
		if (x->dashing == 0) {
			if (IsKeyDown(KEY_UP)) {
				x->yspeed -= x->stats->accel * GetFrameTime();
			}
			else if (x->yspeed < 0) {
				x->yspeed = 0;
			}
			if (IsKeyDown(KEY_DOWN)) {
				x->yspeed += x->stats->accel * GetFrameTime();
			}
			else if (x->yspeed > 0) {
				x->yspeed = 0;
			}
			if (IsKeyDown(KEY_LEFT)) {
				x->xspeed -= x->stats->accel * GetFrameTime();
			}
			else if (x->xspeed < 0) {
				x->xspeed = 0;
			}
			if (IsKeyDown(KEY_RIGHT)) {
				x->xspeed += x->stats->accel * GetFrameTime();
			}
			else if (x->xspeed > 0) {
				x->xspeed = 0;
			}
		}
		if (IsKeyPressed(KEY_RIGHT_SHIFT) && x->stamina >= x->stats->dashcost && (x->yspeed != 0 || x->xspeed != 0) && x->dashing == 0) {
			x->dashing = 1;
			x->dashingstartms = GetTime() * 1000;
			x->dashingendms = 0;
			x->stamina -= x->stats->dashcost;
		}
	}

	if (x->dashing == 0) {
		if (sqrtf(x->xspeed * x->xspeed + x->yspeed * x->yspeed) >= x->stats->maxspeed) {
			float scale = x->stats->maxspeed / sqrtf(x->xspeed * x->xspeed + x->yspeed * x->yspeed);
			x->xspeed *= scale;
			x->yspeed *= scale;
		}
	}
	else {
		float scale = x->stats->dashspeed / sqrtf(x->xspeed * x->xspeed + x->yspeed * x->yspeed);
		x->xspeed *= scale;
		x->yspeed *= scale;
	}
}

void renderCharacter(character* x) {
	Vector2 origingame = { 0,0 };
	DrawTexturePro(x->stats->portrait, x->stats->portraitsrc, x->position, origingame, 0, WHITE);
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

	Vector2 catstartpos = { (arenatop.width - 64) / 2 + arenatop.x,400 };
	Vector2 mousestartpos = { (arenatop.width - 48) / 2 + arenatop.x,1000 };

	character player1cat = {
		.stats = get_player1()->cat,
		.stamina = get_player1()->cat->maxstamina,
		.position = {catstartpos.x,catstartpos.y,64,64},
		.collisionbox1 = {catstartpos.x,catstartpos.y,64,64},
		.collisionbox2 = {catstartpos.x,catstartpos.y,64,64},
		.xspeed = 0,
		.yspeed = 0,
		.dashing = 0,
		.dashingstartms = 0,
		.dashingendms = 0,
		.player = 1
	};

	character player1mouse = {
		.stats = get_player1()->mouse,
		.stamina = get_player1()->mouse->maxstamina,
		.position = {mousestartpos.x,mousestartpos.y,48,48},
		.collisionbox1 = {mousestartpos.x,mousestartpos.y,48,48},
		.collisionbox2 = {mousestartpos.x + 20,mousestartpos.y + 20,8,8},
		.xspeed = 0,
		.yspeed = 0,
		.dashing = 0,
		.dashingstartms = 0,
		.dashingendms = 0,
		.player = 1
	};

	character player2cat = {
		.stats = get_player2()->cat,
		.stamina = get_player2()->cat->maxstamina,
		.position = {catstartpos.x,catstartpos.y,64,64},
		.collisionbox1 = {catstartpos.x,catstartpos.y,64,64},
		.collisionbox2 = {catstartpos.x,catstartpos.y,64,64},
		.xspeed = 0,
		.yspeed = 0,
		.dashing = 0,
		.dashingstartms = 0,
		.dashingendms = 0,
		.player = 2
	};

	character player2mouse = {
		.stats = get_player2()->mouse,
		.stamina = get_player2()->mouse->maxstamina,
		.position = {mousestartpos.x,mousestartpos.y,48,48},
		.collisionbox1 = {mousestartpos.x,mousestartpos.y,48,48},
		.collisionbox2 = {mousestartpos.x + 20,mousestartpos.y + 20,8,8},
		.xspeed = 0,
		.yspeed = 0,
		.dashing = 0,
		.dashingstartms = 0,
		.dashingendms = 0,
		.player = 2
	};

	Texture2D bg = LoadTexture("data/ck.png");

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

	character* current_cat_player = &player1cat;
	character* current_mouse_player = &player2mouse;

	for (int i = 0; i < 8; i++) {
		current_cat_player->collisionbox1.x = catstartpos.x;
		current_cat_player->collisionbox1.y = catstartpos.y;
		current_mouse_player->collisionbox1.x = mousestartpos.x;
		current_mouse_player->collisionbox1.y = mousestartpos.y;
		while (1) {
			BeginDrawingCustom();

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

			inputCharacter(current_cat_player, current_cat_player->player);
			inputCharacter(current_mouse_player, current_mouse_player->player);

			physicCharacter(current_cat_player, walls);
			physicCharacter(current_mouse_player, walls);

			renderCharacter(current_cat_player);
			renderCharacter(current_mouse_player);

			current_cat_player->stamina += current_cat_player->stats->staminaregen * GetFrameTime();
			if (current_cat_player->stamina > current_cat_player->stats->maxstamina) {
				current_cat_player->stamina = current_cat_player->stats->maxstamina;
			}

			current_mouse_player->stamina += current_mouse_player->stats->staminaregen * GetFrameTime();
			if (current_mouse_player->stamina > current_mouse_player->stats->maxstamina) {
				current_mouse_player->stamina = current_mouse_player->stats->maxstamina;
			}

			sprintf(cat1_stamina_text, "Cat: %.1f/%.1f", current_cat_player->stamina, current_cat_player->stats->maxstamina);
			sprintf(mouse1_stamina_text, "Mouse: %.1f/%.1f", current_mouse_player->stamina, current_mouse_player->stats->maxstamina);

			sprintf(player1_score_text, "Player1: %d", player1score);
			sprintf(player2_score_text, "PLayer2: %d", player2score);

			sprintf(arena_number_text, "Turn: %d", i);

			DrawTextEx(defont, cat1_stamina_text, cat1_sta_pos, 40, 0, WHITE);
			DrawTextEx(defont, mouse1_stamina_text, mouse1_sta_pos, 40, 0, WHITE);

			DrawTextEx(defont, player1_score_text, player1scorepos, 40, 0, WHITE);
			DrawTextEx(defont, player2_score_text, player2scorepos, 40, 0, WHITE);

			DrawTextEx(defont, arena_number_text, arena_number_pos, 40, 0, WHITE);

			EndDrawingCustom();

			if (CheckCollisionRecs(current_mouse_player->collisionbox1, Door)) {
				if (current_mouse_player->player == 1) {
					player1score += 3;
				}
				if (current_mouse_player->player == 2) {
					player2score += 3;
				}
				break;
			}
			if (CheckCollisionRecs(current_mouse_player->collisionbox1, current_cat_player->collisionbox1) && current_mouse_player->dashing == 0
				&& !(GetTime() * 1000 - current_mouse_player->dashingendms <= 350 && !CheckCollisionRecs(current_mouse_player->collisionbox2, current_cat_player->collisionbox1))) {
				if (current_cat_player->player == 1) {
					player1score += 3;
				}
				if (current_cat_player->player == 2) {
					player2score += 3;
				}
				break;
			}
			if (CheckCollisionRecs(bannedcatarea, current_cat_player->collisionbox1)) {
				if (bannedcatlastenter != 0) {
					if (GetTime() - bannedcatlastenter >= 3) {
						if (current_mouse_player->player == 1) {
							player1score += 3;
						}
						if (current_mouse_player->player == 2) {
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
		if (current_cat_player == &player1cat) {
			current_cat_player = &player2cat;
			current_mouse_player = &player1mouse;
		}
		else {
			current_cat_player = &player1cat;
			current_mouse_player = &player2mouse;
		}
	}
	UnloadTexture(bg);
	UnloadFont(defont);
	delete_DA(walls);
	return 0;
}