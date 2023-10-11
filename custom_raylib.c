#include "custom_raylib.h"

RenderTexture2D target = { 0 };
Rectangle targetsource = { 0 };
Rectangle targetdest = { 0 };
Vector2 origin = { 0 };
Vector2 virtualres = { 0 };

void InitRaylibCustom(int virtualwidth, int virtualheight) {
	virtualres.x = (float)virtualwidth;
	virtualres.y = (float)virtualheight;
	targetsource.x = 0;
	targetsource.y = 0;
	targetsource.width = (float)virtualwidth;
	targetsource.height = (float)virtualheight;
	target = LoadRenderTexture(virtualwidth, virtualheight);
	SetTextureFilter(target.texture, TEXTURE_FILTER_ANISOTROPIC_16X);
	targetdest.x = 0;
	targetdest.y = 0;
	targetdest.width = (float)GetRenderWidth();
	targetdest.height = (float)GetRenderHeight();
}

void CloseRaylibCustom(void) {
	UnloadRenderTexture(target);
}

void BeginDrawingCustom(void) {
	BeginTextureMode(target);
	ClearBackground(BLACK);
}

void EndDrawingCustom(void) {
	EndTextureMode();
	BeginDrawing();
	ClearBackground(BLACK);
	origin.x = 0;
	origin.y = 0;
	DrawTexturePro(target.texture, targetsource, targetdest, origin, 0, WHITE);
	EndDrawing();
}

Vector2* GetVirtualResCustom(void) {
	return &virtualres;
}

Vector2* GetMousePositionCustom(void) {
	origin.x = GetMousePosition().x * (virtualres.x / GetRenderWidth());
	origin.y = GetMousePosition().y * (virtualres.y / GetRenderHeight());
	return &origin;
}

char RenderButtonCustom(button* b, Font* f) {
	if (CheckCollisionPointRec(*GetMousePositionCustom(), b->position)) {
		DrawRectangleRec(b->position, b->frontcolor);
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
			return 1;
		}
	}
	else {
		DrawRectangleRec(b->position, b->backcolor);
	}
	origin = MeasureTextEx(*f, b->text, (float)f->baseSize, 0);
	origin.x = b->position.x + (b->position.width - origin.x) / 2.0f;
	origin.y = b->position.y + (b->position.height - origin.y) / 2.0f;
	DrawTextEx(*f, b->text, origin, (float)f->baseSize, 0, b->textcolor);
	return 0;
}