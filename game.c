#include "game.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

Vector2 origingame = { 0,0 };

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
	DrawTexturePro(x->stats->portrait, x->stats->portraitsrc, x->position, origingame, 0, WHITE);
}

char game(void) {

	HideCursor();

	float arenax = 513;
	float arenay = 229;
	float arenawidth = 894;
	float arenaheight = 779;

	Rectangle arenaleft = { arenax - 10,arenay,10,arenaheight };
	Rectangle arenaright = { arenax + arenawidth,arenay,10,arenaheight };
	Rectangle arenatop = { arenax - 10,arenay - 10,arenawidth + 20,10 };
	Rectangle arenabottom = { arenax - 10,arenay + arenaheight,arenawidth + 20,10 };

	Rectangle Door = { 918,188,77,44 };

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

	DA* walls = create_DA(sizeof(Rectangle));
	pushback_DA(walls, &arenaleft);
	pushback_DA(walls, &arenaright);
	pushback_DA(walls, &arenatop);
	pushback_DA(walls, &arenabottom);

	Font defont = LoadFontEx("data/x.ttf", 300, 0, 0);

	char quitted = 0;

	int player1score = 0;
	int player2score = 0;

	Vector2 playerscorepos = { 898,57 };

	char player_score_text[10] = { 0 };

	char arena_number_text[10] = { 0 };
	Vector2 arena_number_pos = { 894,14 };

	Rectangle bannedcatarea = { arenatop.x + 10,arenatop.y + 10,arenawidth,169 };
	double bannedcatlastenter = 0;

	character* current_cat_player = &player1cat;
	character* current_mouse_player = &player2mouse;

	Rectangle cheese1 = { 0,0,32,32 };
	Rectangle cheese2 = { 0,0,32,32 };
	Rectangle cheese3 = { 0,0,32,32 };
	Rectangle cheesesrc = { 0,0,32,32 };

	char bottomcheese = 0;

	int gatheredcheese = 0;

	srand((unsigned int)GetTime());

	Vector2 catindicator = { current_cat_player->position.x, current_cat_player->position.y - 20 };
	Vector2 mouseindicator = { current_mouse_player->position.x, current_mouse_player->position.y - 20 };

	double turnstart = 0;

	char counting = 1;

	Texture2D cheese_texture = LoadTexture("data/cheese.png");

	Texture2D stamina_p1_0 = LoadTexture("data/stamina_p1/0.png");
	Texture2D stamina_p1_1 = LoadTexture("data/stamina_p1/1.png");
	Texture2D stamina_p1_2 = LoadTexture("data/stamina_p1/2.png");
	Texture2D stamina_p1_3 = LoadTexture("data/stamina_p1/3.png");
	Texture2D stamina_p1_4 = LoadTexture("data/stamina_p1/4.png");
	Texture2D stamina_p1_5 = LoadTexture("data/stamina_p1/5.png");

	Texture2D stamina_p2_0 = LoadTexture("data/stamina_p2/0.png");
	Texture2D stamina_p2_1 = LoadTexture("data/stamina_p2/1.png");
	Texture2D stamina_p2_2 = LoadTexture("data/stamina_p2/2.png");
	Texture2D stamina_p2_3 = LoadTexture("data/stamina_p2/3.png");
	Texture2D stamina_p2_4 = LoadTexture("data/stamina_p2/4.png");
	Texture2D stamina_p2_5 = LoadTexture("data/stamina_p2/5.png");

	Texture2D count3 = LoadTexture("data/countdown/3.png");
	Texture2D count2 = LoadTexture("data/countdown/2.png");
	Texture2D count1 = LoadTexture("data/countdown/1.png");
	Texture2D countgo = LoadTexture("data/countdown/go.png");

	Texture2D cat_p1 = LoadTexture("data/cat_p1.png");
	Texture2D mouse_p1 = LoadTexture("data/mouse_p1.png");
	Texture2D p1p2 = LoadTexture("data/p1p2.png");

	Texture2D mid1 = LoadTexture("data/mid_game/1.png");
	Texture2D mid2 = LoadTexture("data/mid_game/2.png");
	Texture2D mid3 = LoadTexture("data/mid_game/3.png");
	Texture2D mid4 = LoadTexture("data/mid_game/4.png");
	Texture2D mid5 = LoadTexture("data/mid_game/5.png");
	Texture2D mid6 = LoadTexture("data/mid_game/6.png");
	Texture2D mid7 = LoadTexture("data/mid_game/7.png");
	Texture2D midp1fare = LoadTexture("data/mid_game/p1fare.png");
	Texture2D midp1kedi = LoadTexture("data/mid_game/p1kedi.png");
	Texture2D kedidead = LoadTexture("data/kedidead.png");

	Rectangle screen = { 0,0,1920,1080 };

	char catbantext[10] = { 0 };

	Vector2 catbanpos = { arenaright.x - 40,arenatop.y + arenatop.height + 5 };

	Color catbancolor = { 156,2,28,255 };

	Vector2 mid_p2_pos = { 1209,450 };
	Vector2 mid_p1_pos = { 595,450 };
	char mid_p1_text[10] = { 0 };
	char mid_p2_text[10] = { 0 };

	Color kedideadcolor = { 255,255,255,0 };

	char kedideadstate = 0;//0 up, 1 down

	double kedideadstatetime = 0;

	for (int i = 0; i < 8; i++) {
		current_cat_player->collisionbox1.x = catstartpos.x;
		current_cat_player->collisionbox1.y = catstartpos.y;
		current_mouse_player->collisionbox1.x = mousestartpos.x;
		current_mouse_player->collisionbox1.y = mousestartpos.y;

		bottomcheese = 0;

		gatheredcheese = 0;

	try0:

		cheese1.x = arenaleft.x + arenaleft.width + rand() % (int)(arenaright.x - arenaleft.x - arenaleft.width);
		cheese1.y = arenatop.y + arenatop.height + rand() % (int)(arenaleft.height - 32);

		if (cheese1.y > arenatop.y + arenatop.height + arenaleft.height / 2) {
			bottomcheese++;
		}

		if (CheckCollisionRecs(bannedcatarea, cheese1)) {
			goto try0;
		}

	try1:

		cheese2.x = arenaleft.x + arenaleft.width + rand() % (int)(arenaright.x - arenaleft.x - arenaleft.width);
		cheese2.y = arenatop.y + arenatop.height + rand() % (int)(arenaleft.height - 32);

		if (cheese2.y > arenatop.y + arenatop.height + arenaleft.height / 2) {
			bottomcheese++;
			if (bottomcheese > 1) {
				goto try1;
			}
		}

		if (CheckCollisionRecs(bannedcatarea, cheese2)) {
			goto try1;
		}

	try2:

		cheese3.x = arenaleft.x + arenaleft.width + rand() % (int)(arenaright.x - arenaleft.x - arenaleft.width);
		cheese3.y = arenatop.y + arenatop.height + rand() % (int)(arenaleft.height - 32);

		if (cheese3.y > arenatop.y + arenatop.height + arenaleft.height / 2) {
			bottomcheese++;
			if (bottomcheese > 1) {
				goto try2;
			}
		}

		if (CheckCollisionRecs(bannedcatarea, cheese3)) {
			goto try2;
		}

		turnstart = GetTime();

		counting = 1;

		current_cat_player->xspeed = 0;
		current_cat_player->yspeed = 0;

		current_mouse_player->xspeed = 0;
		current_mouse_player->yspeed = 0;

		while (1) {
			BeginDrawingCustom();

			DrawTexture(bg, 0, 0, WHITE);

			if (IsKeyPressed(KEY_ESCAPE) && !counting) {
				quitted = 1;
				break;
			}

			DrawTexturePro(cheese_texture, cheesesrc, cheese1, origingame, 0, WHITE);
			DrawTexturePro(cheese_texture, cheesesrc, cheese2, origingame, 0, WHITE);
			DrawTexturePro(cheese_texture, cheesesrc, cheese3, origingame, 0, WHITE);

			if (current_cat_player->player == 1) {
				DrawTexturePro(cat_p1, screen, screen, origingame, 0, WHITE);
			}
			else {
				DrawTexturePro(mouse_p1, screen, screen, origingame, 0, WHITE);
			}

			DrawTexturePro(p1p2, screen, screen, origingame, 0, WHITE);

			if (current_cat_player->player == 1) {
				if (current_cat_player->stamina < current_cat_player->stats->maxstamina * (1.0f / 5)) {
					DrawTexturePro(stamina_p1_0, screen, screen, origingame, 0, WHITE);
				}
				else if (current_cat_player->stamina < current_cat_player->stats->maxstamina * (2.0f / 5)) {
					DrawTexturePro(stamina_p1_1, screen, screen, origingame, 0, WHITE);
				}
				else if (current_cat_player->stamina < current_cat_player->stats->maxstamina * (3.0f / 5)) {
					DrawTexturePro(stamina_p1_2, screen, screen, origingame, 0, WHITE);
				}
				else if (current_cat_player->stamina < current_cat_player->stats->maxstamina * (4.0f / 5)) {
					DrawTexturePro(stamina_p1_3, screen, screen, origingame, 0, WHITE);
				}
				else if (current_cat_player->stamina < current_cat_player->stats->maxstamina) {
					DrawTexturePro(stamina_p1_4, screen, screen, origingame, 0, WHITE);
				}
				else {
					DrawTexturePro(stamina_p1_5, screen, screen, origingame, 0, WHITE);
				}

				if (current_mouse_player->stamina < current_mouse_player->stats->maxstamina * (1.0f / 5)) {
					DrawTexturePro(stamina_p2_0, screen, screen, origingame, 0, WHITE);
				}
				else if (current_mouse_player->stamina < current_mouse_player->stats->maxstamina * (2.0f / 5)) {
					DrawTexturePro(stamina_p2_1, screen, screen, origingame, 0, WHITE);
				}
				else if (current_mouse_player->stamina < current_mouse_player->stats->maxstamina * (3.0f / 5)) {
					DrawTexturePro(stamina_p2_2, screen, screen, origingame, 0, WHITE);
				}
				else if (current_mouse_player->stamina < current_mouse_player->stats->maxstamina * (4.0f / 5)) {
					DrawTexturePro(stamina_p2_3, screen, screen, origingame, 0, WHITE);
				}
				else if (current_mouse_player->stamina < current_mouse_player->stats->maxstamina) {
					DrawTexturePro(stamina_p2_4, screen, screen, origingame, 0, WHITE);
				}
				else {
					DrawTexturePro(stamina_p2_5, screen, screen, origingame, 0, WHITE);
				}
			}
			else {
				if (current_cat_player->stamina < current_cat_player->stats->maxstamina * (1.0f / 5)) {
					DrawTexturePro(stamina_p2_0, screen, screen, origingame, 0, WHITE);
				}
				else if (current_cat_player->stamina < current_cat_player->stats->maxstamina * (2.0f / 5)) {
					DrawTexturePro(stamina_p2_1, screen, screen, origingame, 0, WHITE);
				}
				else if (current_cat_player->stamina < current_cat_player->stats->maxstamina * (3.0f / 5)) {
					DrawTexturePro(stamina_p2_2, screen, screen, origingame, 0, WHITE);
				}
				else if (current_cat_player->stamina < current_cat_player->stats->maxstamina * (4.0f / 5)) {
					DrawTexturePro(stamina_p2_3, screen, screen, origingame, 0, WHITE);
				}
				else if (current_cat_player->stamina < current_cat_player->stats->maxstamina) {
					DrawTexturePro(stamina_p2_4, screen, screen, origingame, 0, WHITE);
				}
				else {
					DrawTexturePro(stamina_p2_5, screen, screen, origingame, 0, WHITE);
				}

				if (current_mouse_player->stamina < current_mouse_player->stats->maxstamina * (1.0f / 5)) {
					DrawTexturePro(stamina_p1_0, screen, screen, origingame, 0, WHITE);
				}
				else if (current_mouse_player->stamina < current_mouse_player->stats->maxstamina * (2.0f / 5)) {
					DrawTexturePro(stamina_p1_1, screen, screen, origingame, 0, WHITE);
				}
				else if (current_mouse_player->stamina < current_mouse_player->stats->maxstamina * (3.0f / 5)) {
					DrawTexturePro(stamina_p1_2, screen, screen, origingame, 0, WHITE);
				}
				else if (current_mouse_player->stamina < current_mouse_player->stats->maxstamina * (4.0f / 5)) {
					DrawTexturePro(stamina_p1_3, screen, screen, origingame, 0, WHITE);
				}
				else if (current_mouse_player->stamina < current_mouse_player->stats->maxstamina) {
					DrawTexturePro(stamina_p1_4, screen, screen, origingame, 0, WHITE);
				}
				else {
					DrawTexturePro(stamina_p1_5, screen, screen, origingame, 0, WHITE);
				}
			}

			if (!counting) {
				inputCharacter(current_cat_player, current_cat_player->player);
				inputCharacter(current_mouse_player, current_mouse_player->player);
			}

			physicCharacter(current_cat_player, walls);
			physicCharacter(current_mouse_player, walls);

			current_cat_player->stamina += current_cat_player->stats->staminaregen * GetFrameTime();
			if (current_cat_player->stamina > current_cat_player->stats->maxstamina) {
				current_cat_player->stamina = current_cat_player->stats->maxstamina;
			}

			current_mouse_player->stamina += current_mouse_player->stats->staminaregen * GetFrameTime();
			if (current_mouse_player->stamina > current_mouse_player->stats->maxstamina) {
				current_mouse_player->stamina = current_mouse_player->stats->maxstamina;
			}

			sprintf(player_score_text, "%d-%d", player1score, player2score);

			sprintf(arena_number_text, "turn %d", i);

			if (counting == 0) {
				playerscorepos.x = MeasureTextEx(defont, player_score_text, 80, 0).x;
				playerscorepos.x = (1920 - playerscorepos.x) / 2;
				DrawTextEx(defont, player_score_text, playerscorepos, 80, 0, WHITE);

				DrawTextEx(defont, arena_number_text, arena_number_pos, 50, 0, WHITE);
			}
			catindicator.x = current_cat_player->position.x;
			catindicator.y = current_cat_player->position.y - 20;
			mouseindicator.x = current_mouse_player->position.x;
			mouseindicator.y = current_mouse_player->position.y - 20;

			if (current_cat_player->player == 1) {
				DrawTextEx(defont, "P1", catindicator, 20, 0, BLUE);
			}
			else if (current_cat_player->player == 2) {
				DrawTextEx(defont, "P2", catindicator, 20, 0, RED);
			}

			if (current_mouse_player->player == 1) {
				DrawTextEx(defont, "P1", mouseindicator, 20, 0, BLUE);
			}
			else if (current_mouse_player->player == 2) {
				DrawTextEx(defont, "P2", mouseindicator, 20, 0, RED);
			}

			if (counting == 1 && i == 0) {
				if (GetTime() - turnstart <= 1) {
					DrawTexturePro(count3, screen, screen, origingame, 0, WHITE);
				}
				else if (GetTime() - turnstart <= 2) {
					DrawTexturePro(count2, screen, screen, origingame, 0, WHITE);
				}
				else if (GetTime() - turnstart <= 3) {
					DrawTexturePro(count1, screen, screen, origingame, 0, WHITE);
				}
				else if (GetTime() - turnstart <= 4) {
					DrawTexturePro(countgo, screen, screen, origingame, 0, WHITE);
				}
				else {
					counting = 0;
				}
			}
			else if (counting == 1 && i != 0) {
				if (i == 1) {
					DrawTexturePro(mid1, screen, screen, origingame, 0, WHITE);
				}
				else if (i == 2) {
					DrawTexturePro(mid2, screen, screen, origingame, 0, WHITE);
				}
				else if (i == 3) {
					DrawTexturePro(mid3, screen, screen, origingame, 0, WHITE);
				}
				else if (i == 4) {
					DrawTexturePro(mid4, screen, screen, origingame, 0, WHITE);
				}
				else if (i == 5) {
					DrawTexturePro(mid5, screen, screen, origingame, 0, WHITE);
				}
				else if (i == 6) {
					DrawTexturePro(mid6, screen, screen, origingame, 0, WHITE);
				}
				else if (i == 7) {
					DrawTexturePro(mid7, screen, screen, origingame, 0, WHITE);
				}
				if (current_cat_player->player == 1) {
					DrawTexturePro(midp1kedi, screen, screen, origingame, 0, WHITE);
				}
				else {
					DrawTexturePro(midp1fare, screen, screen, origingame, 0, WHITE);
				}
				if (GetTime() - turnstart > 1) {
					counting = 0;
				}
				sprintf(mid_p1_text, "%d", player1score);
				sprintf(mid_p2_text, "%d", player2score);
				mid_p1_pos = MeasureTextEx(defont, mid_p1_text, 300, 0);
				mid_p1_pos.y = 450;
				mid_p1_pos.x = 730 - mid_p1_pos.x;
				DrawTextEx(defont, mid_p1_text, mid_p1_pos, 300, 0, WHITE);
				mid_p2_pos.y = 450;
				mid_p2_pos.x = 1195;
				DrawTextEx(defont, mid_p2_text, mid_p2_pos, 300, 0, WHITE);
			}

			if (CheckCollisionRecs(current_mouse_player->collisionbox1, Door)) {
				if (current_mouse_player->player == 1) {
					player1score += gatheredcheese;
				}
				if (current_mouse_player->player == 2) {
					player2score += gatheredcheese;
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
					else {
						sprintf(catbantext, "%d", 3 - (int)(GetTime() - bannedcatlastenter));
						DrawTextPro(defont, catbantext, catbanpos, origingame, 0, 50, 0, catbancolor);
						DrawTexturePro(kedidead, screen, screen, origingame, 0, kedideadcolor);
						if (kedideadstate == 0) {
							if (kedideadcolor.a >= 225) {
								kedideadcolor.a = 255;
								kedideadstate = 1;
								kedideadstatetime = GetTime() * 1000;
							}
							else {
								kedideadcolor.a += 30;
							}
						}
						else if (kedideadstate == 1 && GetTime() * 1000 - kedideadstatetime > 100) {
							if (kedideadcolor.a <= 30) {
								kedideadcolor.a = 0;
								kedideadstate = 0;
							}
							else {
								kedideadcolor.a -= 30;
							}
						}
					}
				}
				else {
					bannedcatlastenter = GetTime();
				}
			}
			else {
				bannedcatlastenter = 0;
			}
			if (CheckCollisionRecs(cheese1, current_mouse_player->collisionbox1)) {
				gatheredcheese++;
				cheese1.x = -1000;
			}
			if (CheckCollisionRecs(cheese2, current_mouse_player->collisionbox1)) {
				gatheredcheese++;
				cheese2.x = -1000;
			}
			if (CheckCollisionRecs(cheese3, current_mouse_player->collisionbox1)) {
				gatheredcheese++;
				cheese3.x = -1000;
			}
			renderCharacter(current_cat_player);
			renderCharacter(current_mouse_player);

			EndDrawingCustom();
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

	/*if (quitted == 0) {
		while (1) {

		}
	}*/

	UnloadTexture(mid1);
	UnloadTexture(mid2);
	UnloadTexture(mid3);
	UnloadTexture(mid4);
	UnloadTexture(mid5);
	UnloadTexture(mid6);
	UnloadTexture(mid7);
	UnloadTexture(midp1fare);
	UnloadTexture(midp1kedi);

	UnloadTexture(count3);
	UnloadTexture(count2);
	UnloadTexture(count1);
	UnloadTexture(countgo);

	UnloadTexture(stamina_p1_0);
	UnloadTexture(stamina_p1_1);
	UnloadTexture(stamina_p1_2);
	UnloadTexture(stamina_p1_3);
	UnloadTexture(stamina_p1_4);
	UnloadTexture(stamina_p1_5);

	UnloadTexture(stamina_p2_0);
	UnloadTexture(stamina_p2_1);
	UnloadTexture(stamina_p2_2);
	UnloadTexture(stamina_p2_3);
	UnloadTexture(stamina_p2_4);
	UnloadTexture(stamina_p2_5);

	UnloadTexture(p1p2);
	UnloadTexture(cat_p1);
	UnloadTexture(mouse_p1);
	UnloadTexture(cheese_texture);
	UnloadTexture(bg);
	UnloadFont(defont);
	delete_DA(walls);

	ShowCursor();

	return 0;
}