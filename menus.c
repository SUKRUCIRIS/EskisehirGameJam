#include "menus.h"
#include "custom_raylib.h"

void intro(void) {
	Texture2D logo = LoadTexture("data/logos/sukruciris.png");
	Rectangle logorect = { 810,200,300,300 };
	Rectangle logosrc = { 0,0,11,11 };
	Vector2 origin = { 0,0 };
	Font myfont = LoadFontEx("data/x.ttf", 150, 0, 350);
	Vector2 a = MeasureTextEx(myfont, u8"ÞÜKRÜ ÇÝRÝÞ ENGINE", 150, 0);
	Color textc = { 255,255,255,0 };
	a.x = (1920 - a.x) / 2;
	a.y = 700;
	for (int i = 0; i < 510; i++) {
		BeginDrawingCustom();

		ClearBackground(BLACK);
		DrawTextEx(myfont, u8"ÞÜKRÜ ÇÝRÝÞ ENGINE", a, 150, 0, textc);
		DrawTexturePro(logo, logosrc, logorect, origin, 0, textc);

		EndDrawingCustom();
		if (i < 127) {
			textc.a += 2;
		}
		else if (i > 383) {
			textc.a -= 2;
		}
	}
}

char mainmenu(void) {

	char result = 0;

	Texture2D bg = LoadTexture("data/ck.png");

	buttonText playbutton = {
		.backcolor = {0,0,0,255},
		.frontcolor = {255,0,42,255},
		.text = "PLAY",
		.position = {850,400,0,0}
	};

	buttonText quitbutton = {
		.backcolor = {0,0,0,255},
		.frontcolor = {255,0,42,255},
		.text = "QUIT",
		.position = {850,500,0,0}
	};

	Font defont = LoadFontEx("data/x.ttf", 100, 0, 0);

	InitButtonTextCustom(&playbutton, &defont);
	InitButtonTextCustom(&quitbutton, &defont);

	while (1) {
		BeginDrawingCustom();

		ClearBackground(BLACK);

		DrawTexture(bg, 0, 0, WHITE);

		if (RenderButtonTextCustom(&playbutton, &defont)) {
			result = 0;
			break;
		}

		if (RenderButtonTextCustom(&quitbutton, &defont)) {
			result = 1;
			break;
		}

		EndDrawingCustom();
	}

	UnloadTexture(bg);

	UnloadFont(defont);

	return result;
}