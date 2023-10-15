#include "characterselect.h"

player player1 = {
	.number = 1,
	.cat = 0,
	.mouse = 0
};

player player2 = {
	.number = 2,
	.cat = 0,
	.mouse = 0
};

characterstart whitecat = {
	.maxspeed = 6,
	.accel = 20,
	.maxstamina = 100,
	.staminaregen = 60,
	.dashspeed = 15,
	.dashcost = 100,
	.dashdurationms = 300,
	.type = 0,
	.name = "Tom"
};

characterstart blackcat = {
	.maxspeed = 6,
	.accel = 20,
	.maxstamina = 100,
	.staminaregen = 60,
	.dashspeed = 15,
	.dashcost = 100,
	.dashdurationms = 300,
	.type = 0,
	.name = "Black Tom"
};

characterstart whitemouse = {
	.maxspeed = 8,
	.accel = 25,
	.maxstamina = 100,
	.staminaregen = 75,
	.dashspeed = 17,
	.dashcost = 100,
	.dashdurationms = 100,
	.type = 1,
	.name = "Jerry"
};

characterstart blackmouse = {
	.maxspeed = 8,
	.accel = 25,
	.maxstamina = 100,
	.staminaregen = 75,
	.dashspeed = 17,
	.dashcost = 100,
	.dashdurationms = 100,
	.type = 1,
	.name = "Black Jerry"
};

characterstart* get_blackmouse(void) {
	return &blackmouse;
}

characterstart* get_whitemouse(void) {
	return &whitemouse;
}

characterstart* get_blackcat(void) {
	return &blackcat;
}

characterstart* get_whitecat(void) {
	return &whitecat;
}

player* get_player1(void) {
	return &player1;
}

player* get_player2(void) {
	return &player2;
}

void initcharacterstarts(void) {
	whitecat.portrait = LoadTexture("data/portraits/cat.png");
	whitecat.portraitsrc.x = 0; whitecat.portraitsrc.y = 0;
	whitecat.portraitsrc.width = 64; whitecat.portraitsrc.height = 64;
	blackcat.portrait = LoadTexture("data/portraits/cat2.png");
	blackcat.portraitsrc.x = 0; blackcat.portraitsrc.y = 0;
	blackcat.portraitsrc.width = 661; blackcat.portraitsrc.height = 571;
	whitemouse.portrait = LoadTexture("data/portraits/mouse.png");
	whitemouse.portraitsrc.x = 0; whitemouse.portraitsrc.y = 0;
	whitemouse.portraitsrc.width = 534; whitemouse.portraitsrc.height = 459;
	blackmouse.portrait = LoadTexture("data/portraits/mouse2.png");
	blackmouse.portraitsrc.x = 0; blackmouse.portraitsrc.y = 0;
	blackmouse.portraitsrc.width = 320; blackmouse.portraitsrc.height = 320;
}

void destroycharacterstarts(void) {
	UnloadTexture(whitecat.portrait);
	UnloadTexture(blackcat.portrait);
	UnloadTexture(whitemouse.portrait);
	UnloadTexture(blackmouse.portrait);
}

char selectscreen(void) {
	player1.cat = 0;
	player1.mouse = 0;
	player2.cat = 0;
	player2.mouse = 0;

	Rectangle characterback = { 460,0,1000,1080 };
	Rectangle p1back = { 0,0,460,1080 };
	Rectangle p2back = { 1460,0,460,1080 };
	Vector2 origin = { 0,0 };

	float portraitwidth = 128;
	float spacewidth = (characterback.width - 6 * portraitwidth) / 7;

	Rectangle kitty1 = { characterback.x + spacewidth,200,portraitwidth,portraitwidth };
	Rectangle kitty2 = { characterback.x + 2 * spacewidth + portraitwidth,200,portraitwidth,portraitwidth };

	Rectangle mice1 = { kitty1.x,600,portraitwidth ,portraitwidth };
	Rectangle mice2 = { kitty2.x,600,portraitwidth ,portraitwidth };

	Font defont = LoadFontEx("data/x.ttf", 50, 0, 0);
	Vector2 kitty = { characterback.x + 20,100 };
	Vector2 mice = { kitty.x,500 };

	int characternumber = 2;

	int p1catselector = 1;
	int p1mouseselector = 0;
	char p1catchosen = 0;
	char p1mousechosen = 0;
	int p2catselector = 1;
	int p2mouseselector = 0;
	char p2catchosen = 0;
	char p2mousechosen = 0;
	Vector2 p1catselectortext = { 0 };
	Vector2 p1mouselectortext = { 0 };
	Vector2 p2catselectortext = { 0 };
	Vector2 p2mouselectortext = { 0 };

	Vector2 p1title = { 200,150 };

	Vector2 p2title = { 1660,150 };

	Rectangle p1catdes = { p1back.x + (p1back.width - portraitwidth) / 2,200,portraitwidth,portraitwidth };
	Rectangle p1mousedes = { p1back.x + (p1back.width - portraitwidth) / 2,600,portraitwidth,portraitwidth };
	Rectangle p2catdes = { p2back.x + (p2back.width - portraitwidth) / 2,200,portraitwidth,portraitwidth };
	Rectangle p2mousedes = { p2back.x + (p2back.width - portraitwidth) / 2,600,portraitwidth,portraitwidth };

	while (1) {
		BeginDrawingCustom();

		DrawRectangleRec(characterback, BLACK);
		DrawRectangleRec(p1back, WHITE);
		DrawRectangleRec(p2back, WHITE);

		DrawRectangleLinesEx((Rectangle) { kitty1.x - 5, kitty1.y - 5, kitty1.width + 10, kitty1.height + 10 }, 10, WHITE);
		DrawRectangleLinesEx((Rectangle) { kitty2.x - 5, kitty2.y - 5, kitty2.width + 10, kitty2.height + 10 }, 10, WHITE);
		DrawTexturePro(whitecat.portrait, whitecat.portraitsrc, kitty1, origin, 0, WHITE);
		DrawTexturePro(blackcat.portrait, blackcat.portraitsrc, kitty2, origin, 0, WHITE);

		DrawRectangleLinesEx((Rectangle) { mice1.x - 5, mice1.y - 5, mice1.width + 10, mice1.height + 10 }, 10, WHITE);
		DrawRectangleLinesEx((Rectangle) { mice2.x - 5, mice2.y - 5, mice2.width + 10, mice2.height + 10 }, 10, WHITE);
		DrawTexturePro(whitemouse.portrait, whitemouse.portraitsrc, mice1, origin, 0, WHITE);
		DrawTexturePro(blackmouse.portrait, blackmouse.portraitsrc, mice2, origin, 0, WHITE);

		DrawTextEx(defont, "KITTY", kitty, 50, 0, WHITE);
		DrawTextEx(defont, "MICE", mice, 50, 0, WHITE);

		p1catselectortext.x = p1catselector * spacewidth + (p1catselector - 1) * portraitwidth + characterback.x;
		p1catselectortext.y = kitty1.y - 30;

		p2catselectortext.x = p2catselector * spacewidth + (p2catselector - 1) * portraitwidth + portraitwidth / 2 + characterback.x;
		p2catselectortext.y = kitty1.y - 30;

		p1mouselectortext.x = p1mouseselector * spacewidth + (p1mouseselector - 1) * portraitwidth + characterback.x;
		p1mouselectortext.y = mice1.y - 30;

		p2mouselectortext.x = p2mouseselector * spacewidth + (p2mouseselector - 1) * portraitwidth + portraitwidth / 2 + characterback.x;
		p2mouselectortext.y = mice1.y - 30;

		DrawTextEx(defont, "P1", p1catselectortext, 25, 0, BLUE);
		DrawTextEx(defont, "P2", p2catselectortext, 25, 0, RED);

		if (p1mouseselector != 0) {
			DrawTextEx(defont, "P1", p1mouselectortext, 25, 0, BLUE);
		}
		if (p2mouseselector != 0) {
			DrawTextEx(defont, "P2", p2mouselectortext, 25, 0, RED);
		}

		DrawTextEx(defont, "P1", p1title, 50, 0, BLUE);
		DrawTextEx(defont, "P2", p2title, 50, 0, RED);

		if (player1.cat != 0) {
			DrawTexturePro(player1.cat->portrait, player1.cat->portraitsrc, p1catdes, origin, 0, WHITE);
		}
		if (player1.mouse != 0) {
			DrawTexturePro(player1.mouse->portrait, player1.mouse->portraitsrc, p1mousedes, origin, 0, WHITE);
		}
		if (player2.cat != 0) {
			DrawTexturePro(player2.cat->portrait, player2.cat->portraitsrc, p2catdes, origin, 0, WHITE);
		}
		if (player2.mouse != 0) {
			DrawTexturePro(player2.mouse->portrait, player2.mouse->portraitsrc, p2mousedes, origin, 0, WHITE);
		}

		EndDrawingCustom();

		if (IsKeyPressed(KEY_ESCAPE)) {
			UnloadFont(defont);
			return 1;
		}
		if (p1mousechosen == 1 && p2mousechosen == 1) {
			UnloadFont(defont);
			return 0;
		}
		if (IsKeyPressed(KEY_A) && p1mousechosen == 0) {
			if (!p1catchosen) {
				if (p1catselector > 1) {
					p1catselector--;
				}
			}
			else {
				if (p1mouseselector > 1) {
					p1mouseselector--;
				}
			}
		}
		if (IsKeyPressed(KEY_D) && p1mousechosen == 0) {
			if (!p1catchosen) {
				if (p1catselector < characternumber) {
					p1catselector++;
				}
			}
			else {
				if (p1mouseselector < characternumber) {
					p1mouseselector++;
				}
			}
		}
		if (IsKeyPressed(KEY_LEFT_CONTROL) && p1mousechosen == 0) {
			if (p1catchosen == 0) {
				p1catchosen = 1;
				p1mouseselector = 1;
				if (p1catselector == 1) {
					player1.cat = &whitecat;
				}
				else if (p1catselector == 2) {
					player1.cat = &blackcat;
				}
			}
			else if (p1mousechosen == 0) {
				p1mousechosen = 1;
				if (p1mouseselector == 1) {
					player1.mouse = &whitemouse;
				}
				else if (p1mouseselector == 2) {
					player1.mouse = &blackmouse;
				}
			}
		}
		if (IsKeyPressed(KEY_LEFT) && p2mousechosen == 0) {
			if (!p2catchosen) {
				if (p2catselector > 1) {
					p2catselector--;
				}
			}
			else {
				if (p2mouseselector > 1) {
					p2mouseselector--;
				}
			}
		}
		if (IsKeyPressed(KEY_RIGHT) && p2mousechosen == 0) {
			if (!p2catchosen) {
				if (p2catselector < characternumber) {
					p2catselector++;
				}
			}
			else {
				if (p2mouseselector < characternumber) {
					p2mouseselector++;
				}
			}
		}
		if (IsKeyPressed(KEY_RIGHT_SHIFT) && p2mousechosen == 0) {
			if (p2catchosen == 0) {
				p2catchosen = 1;
				p2mouseselector = 1;
				if (p2catselector == 1) {
					player2.cat = &whitecat;
				}
				else if (p2catselector == 2) {
					player2.cat = &blackcat;
				}
			}
			else if (p2mousechosen == 0) {
				p2mousechosen = 1;
				if (p2mouseselector == 1) {
					player2.mouse = &whitemouse;
				}
				else if (p2mouseselector == 2) {
					player2.mouse = &blackmouse;
				}
			}
		}
	}
}

void noselectscreen(void) {
	player1.cat = &whitecat;
	player1.mouse = &whitemouse;
	player2.cat = &whitecat;
	player2.mouse = &whitemouse;
}