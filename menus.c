#include "menus.h"
#include "custom_raylib.h"

void intro(void) {
	Texture2D sc = LoadTexture("data/logos/sc.png");
	Texture2D km = LoadTexture("data/logos/km.png");
	Texture2D kagan = LoadTexture("data/logos/kagan.png");
	Texture2D nesk = LoadTexture("data/logos/nesk.png");
	for (int i = 0; i < 150; i++) {
		BeginDrawingCustom();
		DrawTexture(sc, 0, 0, WHITE);
		EndDrawingCustom();
	}
	for (int i = 0; i < 6; i++) {
		BeginDrawingCustom();
		ClearBackground(BLACK);
		EndDrawingCustom();
	}
	for (int i = 0; i < 90; i++) {
		BeginDrawingCustom();
		DrawTexture(kagan, 0, 0, WHITE);
		EndDrawingCustom();
	}
	for (int i = 0; i < 6; i++) {
		BeginDrawingCustom();
		ClearBackground(BLACK);
		EndDrawingCustom();
	}
	for (int i = 0; i < 90; i++) {
		BeginDrawingCustom();
		DrawTexture(nesk, 0, 0, WHITE);
		EndDrawingCustom();
	}
	for (int i = 0; i < 6; i++) {
		BeginDrawingCustom();
		ClearBackground(BLACK);
		EndDrawingCustom();
	}
	for (int i = 0; i < 90; i++) {
		BeginDrawingCustom();
		DrawTexture(km, 0, 0, WHITE);
		EndDrawingCustom();
	}
	UnloadTexture(sc);
	UnloadTexture(km);
	UnloadTexture(kagan);
	UnloadTexture(nesk);
}

char mainmenu(void) {

	char result = 0;

	Texture2D bg = LoadTexture("data/bg.png");

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

	Texture2D creditsx = LoadTexture("data/logos/kredi.png");

	Music music = LoadMusicStream("data/musics/mtless.mp3");

	PlayMusicStream(music);

	while (1) {
		UpdateMusicStream(music);
		BeginDrawingCustom();

		ClearBackground(BLACK);

		DrawTexture(bg, 0, 0, WHITE);

		if (RenderButtonImageCustom(&versus_mode)) {
			result = 0;
			WaitTime(0.1);
			break;
		}

		RenderButtonImageCustom(&online);
		
		if (RenderButtonImageCustom(&credits)) {
			while (!IsKeyPressed(KEY_ESCAPE)) {
				BeginDrawingCustom();
				DrawTexture(creditsx, 0, 0, WHITE);
				EndDrawingCustom();
			}
		}

		if (RenderButtonImageCustom(&exit)) {
			result = 1;
			WaitTime(0.1);
			break;
		}

		EndDrawingCustom();
	}

	StopMusicStream(music);

	UnloadMusicStream(music);

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

	UnloadTexture(creditsx);

	return result;
}