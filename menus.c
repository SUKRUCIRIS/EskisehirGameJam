#include "menus.h"
#include "custom_raylib.h"

void intro(void) {
	Texture2D logo = LoadTexture("data/logos/sukruciris.png");
	Rectangle logorect = { 760,200,400,400 };
	Rectangle logosrc = { 0,0,11,11 };
	Vector2 origin = { 0,0 };
	Font myfont = LoadFontEx("data/x.ttf", 150, 0, 350);
	Vector2 a = MeasureTextEx(myfont, u8"ÞÜKRÜ ÇÝRÝÞ ENGINE", 150, 0);
	Color textc = { 255,255,255,0 };
	a.x = (1920 - a.x) / 2;
	a.y = 700;
	for (int i = 0; i < 400; i++) {
		BeginDrawingCustom();

		ClearBackground(BLACK);
		DrawTextEx(myfont, u8"ÞÜKRÜ ÇÝRÝÞ ENGINE", a, 150, 0, textc);
		DrawTexturePro(logo, logosrc, logorect, origin, 0, textc);

		EndDrawingCustom();
		if (i < 127) {
			textc.a += 2;
		}
		else if (i > 273) {
			textc.a -= 2;
		}
	}
}

char mainmenu(void) {

	char result = 0;

	Texture2D bg = LoadTexture("data/ck.png");

	Texture2D vsmode0 = LoadTexture("data/main_menu_buttons/vsmode0.png");
	Texture2D vsmode1 = LoadTexture("data/main_menu_buttons/vsmode1.png");
	Texture2D vsmode2 = LoadTexture("data/main_menu_buttons/vsmode2.png");

	Texture2D onl0 = LoadTexture("data/main_menu_buttons/onl0.png");
	Texture2D onl1 = LoadTexture("data/main_menu_buttons/onl1.png");
	Texture2D onl2 = LoadTexture("data/main_menu_buttons/onl2.png");

	Texture2D exit0 = LoadTexture("data/main_menu_buttons/exit0.png");
	Texture2D exit1 = LoadTexture("data/main_menu_buttons/exit1.png");
	Texture2D exit2 = LoadTexture("data/main_menu_buttons/exit2.png");

	Texture2D credits0 = LoadTexture("data/main_menu_buttons/credits0.png");
	Texture2D credits1 = LoadTexture("data/main_menu_buttons/credits1.png");
	Texture2D credits2 = LoadTexture("data/main_menu_buttons/credits2.png");

	Rectangle rect1 = { 0,0,1920,1080 };

	buttonImage versus_mode = {
		.backimage = &vsmode0,
		.frontimage = &vsmode1,
		.clickedimage = &vsmode2,
		.renderposition = &rect1,
		.srcback = &rect1,
		.srcfront = &rect1,
		.srcclicked = &rect1,
		.pressed = 0,
		.clickposition={543,125,812,300}
	};

	buttonImage online = {
		.backimage = &onl0,
		.frontimage = &onl1,
		.clickedimage = &onl2,
		.renderposition = &rect1,
		.srcback = &rect1,
		.srcfront = &rect1,
		.srcclicked = &rect1,
		.pressed = 0,
		.clickposition={736,498,434,70}
	};

	buttonImage exit = {
		.backimage = &exit0,
		.frontimage = &exit1,
		.clickedimage = &exit2,
		.renderposition = &rect1,
		.srcback = &rect1,
		.srcfront = &rect1,
		.srcclicked = &rect1,
		.pressed = 0,
		.clickposition= {843,788,232,103}
	};

	buttonImage credits = {
		.backimage = &credits0,
		.frontimage = &credits1,
		.clickedimage = &credits2,
		.renderposition = &rect1,
		.srcback = &rect1,
		.srcfront = &rect1,
		.srcclicked = &rect1,
		.pressed = 0,
		.clickposition= {730,652,454,75}
	};

	while (1) {
		BeginDrawingCustom();

		ClearBackground(BLACK);

		DrawTexture(bg, 0, 0, WHITE);

		if (RenderButtonImageCustom(&versus_mode)) {
			result = 0;
			WaitTime(0.1);
			break;
		}

		RenderButtonImageCustom(&online);
		
		RenderButtonImageCustom(&credits);

		if (RenderButtonImageCustom(&exit)) {
			result = 1;
			WaitTime(0.1);
			break;
		}

		EndDrawingCustom();
	}

	UnloadTexture(bg);

	UnloadTexture(vsmode0);
	UnloadTexture(vsmode1);
	UnloadTexture(vsmode2);

	UnloadTexture(onl0);
	UnloadTexture(onl1);
	UnloadTexture(onl2);

	UnloadTexture(exit0);
	UnloadTexture(exit1);
	UnloadTexture(exit2);

	UnloadTexture(credits0);
	UnloadTexture(credits1);
	UnloadTexture(credits2);

	return result;
}