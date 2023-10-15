#include "custom_raylib.h"

RenderTexture2D target = { 0 };
Rectangle targetsource = { 0 };
Rectangle targetdest = { 0 };
Vector2 origin = { 0 };
Vector2 virtualres = { 0 };

DA* animations;

Sound click;

void InitRaylibCustom(int virtualwidth, int virtualheight) {
	virtualres.x = (float)virtualwidth;
	virtualres.y = (float)virtualheight;
	targetsource.x = 0;
	targetsource.y = 0;
	targetsource.width = (float)virtualwidth;
	targetsource.height = -(float)virtualheight;
	target = LoadRenderTexture(virtualwidth, virtualheight);
	SetTextureFilter(target.texture, TEXTURE_FILTER_ANISOTROPIC_16X);
	targetdest.x = 0;
	targetdest.y = 0;
	targetdest.width = (float)GetRenderWidth();
	targetdest.height = (float)GetRenderHeight();

	animations = create_DA(sizeof(animation*));
	click= LoadSound("data/bibip.wav");
}

void CloseRaylibCustom(void) {
	UnloadRenderTexture(target);
	UnloadSound(click);
	delete_DA(animations);
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

char RenderButtonImageCustom(buttonImage* b) {
	if (b->pressed == 0) {
		if (CheckCollisionPointRec(*GetMousePositionCustom(), b->clickposition)) {
			origin.x = 0;
			origin.y = 0;
			DrawTexturePro(*b->frontimage, *b->srcfront, *b->renderposition, origin, 0, WHITE);
			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
				b->pressed = 1;
			}
		}
		else {
			origin.x = 0;
			origin.y = 0;
			DrawTexturePro(*b->backimage, *b->srcback, *b->renderposition, origin, 0, WHITE);
		}
	}
	else {
		if (CheckCollisionPointRec(*GetMousePositionCustom(), b->clickposition)) {
			origin.x = 0;
			origin.y = 0;
			DrawTexturePro(*b->clickedimage, *b->srcclicked, *b->renderposition, origin, 0, WHITE);
			if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
				PlaySound(click);
				return 1;
			}
		}
		else {
			b->pressed = 0;
		}
	}
	return 0;
}

void InitButtonTextCustom(buttonText* b, Font* f) {
	origin = MeasureTextEx(*f, b->text, (float)f->baseSize, 0);
	b->position.width = origin.x;
	b->position.height = origin.y;
}

char RenderButtonTextCustom(buttonText* b, Font* f) {
	if (CheckCollisionPointRec(*GetMousePositionCustom(), b->position)) {
		origin.x = b->position.x;
		origin.y = b->position.y;
		DrawTextEx(*f, b->text, origin, (float)f->baseSize, 0, b->frontcolor);
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
			return 1;
		}
	}
	else {
		origin.x = b->position.x;
		origin.y = b->position.y;
		DrawTextEx(*f, b->text, origin, (float)f->baseSize, 0, b->backcolor);
	}
	return 0;
}

void AddAnimationCustom(animation* anim) {
	pushback_DA(animations, &anim);
}

void RemoveAnimationCustom(animation* anim) {
	remove_DA(animations, get_index_DA(animations, &anim));
}

void ClearAnimationCustom(void) {
	clear_DA(animations);
}

void DrawAnimationsCustom(void) {
	animation** anims = get_data_DA(animations);
	double currenttime = 0;
	unsigned int whichframe = 0;
	for (unsigned int i = 0; i < get_size_DA(animations); i++) {
		if (anims[i]->disabled == 0) {
			if (anims[i]->animationstartms == -1) {
				anims[i]->animationstartms = GetTime() * 1000;
			}
			currenttime = GetTime() * 1000;
			whichframe = (unsigned int)((currenttime - anims[i]->animationstartms) / anims[i]->framedurationms)
				% get_size_DA(anims[i]->sourcerects);
			origin.x = 0;
			origin.y = 0;
			DrawTexturePro(*anims[i]->maintexture, ((Rectangle*)get_data_DA(anims[i]->sourcerects))[whichframe],
				*anims[i]->dest, origin, 0, WHITE);
		}
		else {
			anims[i]->animationstartms = -1;
		}
	}
}