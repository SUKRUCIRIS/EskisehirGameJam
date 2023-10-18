#include "characterselect.h"

Texture2D catidledown;
Texture2D catidleup;
Texture2D catidleleft;
Texture2D catidleright;

Texture2D catrundown;
Texture2D catrunup;
Texture2D catrunleft;
Texture2D catrunright;

Texture2D mouserundown;
Texture2D mouserunup;
Texture2D mouserunleft;
Texture2D mouserunright;

Texture2D mouseidledown;
Texture2D mouseidleup;
Texture2D mouseidleleft;
Texture2D mouseidleright;

DA* cat1_src = 0;
DA* cat2_src = 0;
DA* mouse1_src = 0;
DA* mouse2_src = 0;

animation catidledown_anim = {
	.maintexture = &catidledown,
	.dest = 0,
	.disabled = 1,
	.framedurationms = 120,
	.animationstartms = 0,
	.sourcerects = 0,
	.collisiondimensions = {23,15,46,21}
};

animation catidleup_anim = {
	.maintexture = &catidleup,
	.dest = 0,
	.disabled = 1,
	.framedurationms = 120,
	.animationstartms = 0,
	.sourcerects = 0,
	.collisiondimensions = {23,6,46,21}
};

animation catidleleft_anim = {
	.maintexture = &catidleleft,
	.dest = 0,
	.disabled = 1,
	.framedurationms = 120,
	.animationstartms = 0,
	.sourcerects = 0,
	.collisiondimensions = {6,23,21,46}
};

animation catidleright_anim = {
	.maintexture = &catidleright,
	.dest = 0,
	.disabled = 1,
	.framedurationms = 120,
	.animationstartms = 0,
	.sourcerects = 0,
	.collisiondimensions = {15,23,21,46}
};

animation catrundown_anim = {
	.maintexture = &catrundown,
	.dest = 0,
	.disabled = 1,
	.framedurationms = 120,
	.animationstartms = 0,
	.sourcerects = 0,
	.collisiondimensions = {23,15,46,21}
};

animation catrunup_anim = {
	.maintexture = &catrunup,
	.dest = 0,
	.disabled = 1,
	.framedurationms = 120,
	.animationstartms = 0,
	.sourcerects = 0,
	.collisiondimensions = {23,6,46,21}
};

animation catrunleft_anim = {
	.maintexture = &catrunleft,
	.dest = 0,
	.disabled = 1,
	.framedurationms = 120,
	.animationstartms = 0,
	.sourcerects = 0,
	.collisiondimensions = {6,23,21,46}
};

animation catrunright_anim = {
	.maintexture = &catrunright,
	.dest = 0,
	.disabled = 1,
	.framedurationms = 120,
	.animationstartms = 0,
	.sourcerects = 0,
	.collisiondimensions = {15,23,21,46}
};

animation catdashdown_anim = {
	.maintexture = &catrundown,
	.dest = 0,
	.disabled = 1,
	.framedurationms = 120,
	.animationstartms = 0,
	.sourcerects = 0,
	.collisiondimensions = {23,15,46,21}
};

animation catdashup_anim = {
	.maintexture = &catrunup,
	.dest = 0,
	.disabled = 1,
	.framedurationms = 120,
	.animationstartms = 0,
	.sourcerects = 0,
	.collisiondimensions = {23,6,46,21}
};

animation catdashleft_anim = {
	.maintexture = &catrunleft,
	.dest = 0,
	.disabled = 1,
	.framedurationms = 120,
	.animationstartms = 0,
	.sourcerects = 0,
	.collisiondimensions = {6,23,21,46}
};

animation catdashright_anim = {
	.maintexture = &catrunright,
	.dest = 0,
	.disabled = 1,
	.framedurationms = 120,
	.animationstartms = 0,
	.sourcerects = 0,
	.collisiondimensions = {15,23,21,46}
};

animation mouseidledown_anim = {
	.maintexture = &mouseidledown,
	.dest = 0,
	.disabled = 1,
	.framedurationms = 120,
	.animationstartms = 0,
	.sourcerects = 0,
	.collisiondimensions = {15,12,30,20}
};

animation mouseidleup_anim = {
	.maintexture = &mouseidleup,
	.dest = 0,
	.disabled = 1,
	.framedurationms = 120,
	.animationstartms = 0,
	.sourcerects = 0,
	.collisiondimensions = {15,8,30,20}
};

animation mouseidleleft_anim = {
	.maintexture = &mouseidleleft,
	.dest = 0,
	.disabled = 1,
	.framedurationms = 120,
	.animationstartms = 0,
	.sourcerects = 0,
	.collisiondimensions = {8,15,20,30}
};

animation mouseidleright_anim = {
	.maintexture = &mouseidleright,
	.dest = 0,
	.disabled = 1,
	.framedurationms = 120,
	.animationstartms = 0,
	.sourcerects = 0,
	.collisiondimensions = {12,15,20,30}
};

animation mouserundown_anim = {
	.maintexture = &mouserundown,
	.dest = 0,
	.disabled = 1,
	.framedurationms = 120,
	.animationstartms = 0,
	.sourcerects = 0,
	.collisiondimensions = {15,12,30,20}
};

animation mouserunup_anim = {
	.maintexture = &mouserunup,
	.dest = 0,
	.disabled = 1,
	.framedurationms = 120,
	.animationstartms = 0,
	.sourcerects = 0,
	.collisiondimensions = {15,8,30,20}
};

animation mouserunleft_anim = {
	.maintexture = &mouserunleft,
	.dest = 0,
	.disabled = 1,
	.framedurationms = 120,
	.animationstartms = 0,
	.sourcerects = 0,
	.collisiondimensions = {8,15,20,30}
};

animation mouserunright_anim = {
	.maintexture = &mouserunright,
	.dest = 0,
	.disabled = 1,
	.framedurationms = 120,
	.animationstartms = 0,
	.sourcerects = 0,
	.collisiondimensions = {12,15,20,30}
};

animation mousedashdown_anim = {
	.maintexture = &mouserundown,
	.dest = 0,
	.disabled = 1,
	.framedurationms = 120,
	.animationstartms = 0,
	.sourcerects = 0,
	.collisiondimensions = {15,12,30,20}
};

animation mousedashup_anim = {
	.maintexture = &mouserunup,
	.dest = 0,
	.disabled = 1,
	.framedurationms = 120,
	.animationstartms = 0,
	.sourcerects = 0,
	.collisiondimensions = {15,8,30,20}
};

animation mousedashleft_anim = {
	.maintexture = &mouserunleft,
	.dest = 0,
	.disabled = 1,
	.framedurationms = 120,
	.animationstartms = 0,
	.sourcerects = 0,
	.collisiondimensions = {8,15,20,30}
};

animation mousedashright_anim = {
	.maintexture = &mouserunright,
	.dest = 0,
	.disabled = 1,
	.framedurationms = 120,
	.animationstartms = 0,
	.sourcerects = 0,
	.collisiondimensions = {12,15,20,30}
};

animation catidledown_anim2 = {
	.maintexture = &catidledown,
	.dest = 0,
	.disabled = 1,
	.framedurationms = 120,
	.animationstartms = 0,
	.sourcerects = 0,
	.collisiondimensions = {23,15,46,21}
};

animation catidleup_anim2 = {
	.maintexture = &catidleup,
	.dest = 0,
	.disabled = 1,
	.framedurationms = 120,
	.animationstartms = 0,
	.sourcerects = 0,
	.collisiondimensions = {23,6,46,21}
};

animation catidleleft_anim2 = {
	.maintexture = &catidleleft,
	.dest = 0,
	.disabled = 1,
	.framedurationms = 120,
	.animationstartms = 0,
	.sourcerects = 0,
	.collisiondimensions = {6,23,21,46}
};

animation catidleright_anim2 = {
	.maintexture = &catidleright,
	.dest = 0,
	.disabled = 1,
	.framedurationms = 120,
	.animationstartms = 0,
	.sourcerects = 0,
	.collisiondimensions = {15,23,21,46}
};

animation catrundown_anim2 = {
	.maintexture = &catrundown,
	.dest = 0,
	.disabled = 1,
	.framedurationms = 120,
	.animationstartms = 0,
	.sourcerects = 0,
	.collisiondimensions = {23,15,46,21}
};

animation catrunup_anim2 = {
	.maintexture = &catrunup,
	.dest = 0,
	.disabled = 1,
	.framedurationms = 120,
	.animationstartms = 0,
	.sourcerects = 0,
	.collisiondimensions = {23,6,46,21}
};

animation catrunleft_anim2 = {
	.maintexture = &catrunleft,
	.dest = 0,
	.disabled = 1,
	.framedurationms = 120,
	.animationstartms = 0,
	.sourcerects = 0,
	.collisiondimensions = {6,23,21,46}
};

animation catrunright_anim2 = {
	.maintexture = &catrunright,
	.dest = 0,
	.disabled = 1,
	.framedurationms = 120,
	.animationstartms = 0,
	.sourcerects = 0,
	.collisiondimensions = {15,23,21,46}
};

animation catdashdown_anim2 = {
	.maintexture = &catrundown,
	.dest = 0,
	.disabled = 1,
	.framedurationms = 120,
	.animationstartms = 0,
	.sourcerects = 0,
	.collisiondimensions = {23,15,46,21}
};

animation catdashup_anim2 = {
	.maintexture = &catrunup,
	.dest = 0,
	.disabled = 1,
	.framedurationms = 120,
	.animationstartms = 0,
	.sourcerects = 0,
	.collisiondimensions = {23,6,46,21}
};

animation catdashleft_anim2 = {
	.maintexture = &catrunleft,
	.dest = 0,
	.disabled = 1,
	.framedurationms = 120,
	.animationstartms = 0,
	.sourcerects = 0,
	.collisiondimensions = {6,23,21,46}
};

animation catdashright_anim2 = {
	.maintexture = &catrunright,
	.dest = 0,
	.disabled = 1,
	.framedurationms = 120,
	.animationstartms = 0,
	.sourcerects = 0,
	.collisiondimensions = {15,23,21,46}
};

animation mouseidledown_anim2 = {
	.maintexture = &mouseidledown,
	.dest = 0,
	.disabled = 1,
	.framedurationms = 120,
	.animationstartms = 0,
	.sourcerects = 0,
	.collisiondimensions = {15,12,30,20}
};

animation mouseidleup_anim2 = {
	.maintexture = &mouseidleup,
	.dest = 0,
	.disabled = 1,
	.framedurationms = 120,
	.animationstartms = 0,
	.sourcerects = 0,
	.collisiondimensions = {15,8,30,20}
};

animation mouseidleleft_anim2 = {
	.maintexture = &mouseidleleft,
	.dest = 0,
	.disabled = 1,
	.framedurationms = 120,
	.animationstartms = 0,
	.sourcerects = 0,
	.collisiondimensions = {8,15,20,30}
};

animation mouseidleright_anim2 = {
	.maintexture = &mouseidleright,
	.dest = 0,
	.disabled = 1,
	.framedurationms = 120,
	.animationstartms = 0,
	.sourcerects = 0,
	.collisiondimensions = {12,15,20,30}
};

animation mouserundown_anim2 = {
	.maintexture = &mouserundown,
	.dest = 0,
	.disabled = 1,
	.framedurationms = 120,
	.animationstartms = 0,
	.sourcerects = 0,
	.collisiondimensions = {15,12,30,20}
};

animation mouserunup_anim2 = {
	.maintexture = &mouserunup,
	.dest = 0,
	.disabled = 1,
	.framedurationms = 120,
	.animationstartms = 0,
	.sourcerects = 0,
	.collisiondimensions = {15,8,30,20}
};

animation mouserunleft_anim2 = {
	.maintexture = &mouserunleft,
	.dest = 0,
	.disabled = 1,
	.framedurationms = 120,
	.animationstartms = 0,
	.sourcerects = 0,
	.collisiondimensions = {8,15,20,30}
};

animation mouserunright_anim2 = {
	.maintexture = &mouserunright,
	.dest = 0,
	.disabled = 1,
	.framedurationms = 120,
	.animationstartms = 0,
	.sourcerects = 0,
	.collisiondimensions = {12,15,20,30}
};

animation mousedashdown_anim2 = {
	.maintexture = &mouserundown,
	.dest = 0,
	.disabled = 1,
	.framedurationms = 120,
	.animationstartms = 0,
	.sourcerects = 0,
	.collisiondimensions = {15,12,30,20}
};

animation mousedashup_anim2 = {
	.maintexture = &mouserunup,
	.dest = 0,
	.disabled = 1,
	.framedurationms = 120,
	.animationstartms = 0,
	.sourcerects = 0,
	.collisiondimensions = {15,8,30,20}
};

animation mousedashleft_anim2 = {
	.maintexture = &mouserunleft,
	.dest = 0,
	.disabled = 1,
	.framedurationms = 120,
	.animationstartms = 0,
	.sourcerects = 0,
	.collisiondimensions = {8,15,20,30}
};

animation mousedashright_anim2 = {
	.maintexture = &mouserunright,
	.dest = 0,
	.disabled = 1,
	.framedurationms = 120,
	.animationstartms = 0,
	.sourcerects = 0,
	.collisiondimensions = {12,15,20,30}
};

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
	.name = "Tom",
	.idledown = &catidledown_anim,
	.idleup = &catidleup_anim,
	.idleleft = &catidleleft_anim,
	.idleright = &catidleright_anim,
	.dashdown = &catdashdown_anim,
	.dashup = &catdashup_anim,
	.dashleft = &catdashleft_anim,
	.dashright = &catdashright_anim,
	.walkdown = &catrundown_anim,
	.walkup = &catrunup_anim,
	.walkleft = &catrunleft_anim,
	.walkright = &catrunright_anim
};

characterstart whitecat2 = {
	.maxspeed = 6,
	.accel = 20,
	.maxstamina = 100,
	.staminaregen = 60,
	.dashspeed = 15,
	.dashcost = 100,
	.dashdurationms = 300,
	.type = 0,
	.name = "Tom",
	.idledown = &catidledown_anim2,
	.idleup = &catidleup_anim2,
	.idleleft = &catidleleft_anim2,
	.idleright = &catidleright_anim2,
	.dashdown = &catdashdown_anim2,
	.dashup = &catdashup_anim2,
	.dashleft = &catdashleft_anim2,
	.dashright = &catdashright_anim2,
	.walkdown = &catrundown_anim2,
	.walkup = &catrunup_anim2,
	.walkleft = &catrunleft_anim2,
	.walkright = &catrunright_anim2
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
	.name = "Jerry",
	.idledown = &mouseidledown_anim,
	.idleup = &mouseidleup_anim,
	.idleleft = &mouseidleleft_anim,
	.idleright = &mouseidleright_anim,
	.dashdown = &mousedashdown_anim,
	.dashup = &mousedashup_anim,
	.dashleft = &mousedashleft_anim,
	.dashright = &mousedashright_anim,
	.walkdown = &mouserundown_anim,
	.walkup = &mouserunup_anim,
	.walkleft = &mouserunleft_anim,
	.walkright = &mouserunright_anim
};

characterstart whitemouse2 = {
	.maxspeed = 8,
	.accel = 25,
	.maxstamina = 100,
	.staminaregen = 75,
	.dashspeed = 17,
	.dashcost = 100,
	.dashdurationms = 100,
	.type = 1,
	.name = "Jerry",
	.idledown = &mouseidledown_anim2,
	.idleup = &mouseidleup_anim2,
	.idleleft = &mouseidleleft_anim2,
	.idleright = &mouseidleright_anim2,
	.dashdown = &mousedashdown_anim2,
	.dashup = &mousedashup_anim2,
	.dashleft = &mousedashleft_anim2,
	.dashright = &mousedashright_anim2,
	.walkdown = &mouserundown_anim2,
	.walkup = &mouserunup_anim2,
	.walkleft = &mouserunleft_anim2,
	.walkright = &mouserunright_anim2
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
	catidledown = LoadTexture("data/cat_anim/idledown.png");
	catidleup = LoadTexture("data/cat_anim/idleup.png");
	catidleleft = LoadTexture("data/cat_anim/idleleft.png");
	catidleright = LoadTexture("data/cat_anim/idleright.png");

	catrundown = LoadTexture("data/cat_anim/rundown.png");
	catrunup = LoadTexture("data/cat_anim/runup.png");
	catrunleft = LoadTexture("data/cat_anim/runleft.png");
	catrunright = LoadTexture("data/cat_anim/runright.png");

	mouserundown = LoadTexture("data/mouse_anim/rundown.png");
	mouserunup = LoadTexture("data/mouse_anim/runup.png");
	mouserunleft = LoadTexture("data/mouse_anim/runleft.png");
	mouserunright = LoadTexture("data/mouse_anim/runright.png");

	mouseidledown = LoadTexture("data/mouse_anim/idledown.png");
	mouseidleup = LoadTexture("data/mouse_anim/idleup.png");
	mouseidleleft = LoadTexture("data/mouse_anim/idleleft.png");
	mouseidleright = LoadTexture("data/mouse_anim/idleright.png");

	cat1_src = create_DA(sizeof(Rectangle));
	cat2_src = create_DA(sizeof(Rectangle));
	mouse1_src = create_DA(sizeof(Rectangle));
	mouse2_src = create_DA(sizeof(Rectangle));
	Rectangle x = { 0,0,64,64 };
	Rectangle y = { 64,0,64,64 };
	pushback_DA(cat1_src, &x);
	pushback_DA(cat2_src, &x);
	pushback_DA(cat2_src, &y);
	x.width = 48;
	x.height = 48;
	y.x = 48;
	y.width = 48;
	y.height = 48;
	pushback_DA(mouse1_src, &x);
	pushback_DA(mouse2_src, &x);
	pushback_DA(mouse2_src, &y);

	whitecat.idledown->sourcerects = cat1_src;
	whitecat.idleup->sourcerects = cat1_src;
	whitecat.idleleft->sourcerects = cat1_src;
	whitecat.idleright->sourcerects = cat1_src;

	whitecat.dashdown->sourcerects = cat1_src;
	whitecat.dashup->sourcerects = cat1_src;
	whitecat.dashleft->sourcerects = cat1_src;
	whitecat.dashright->sourcerects = cat1_src;

	whitecat.walkdown->sourcerects = cat2_src;
	whitecat.walkup->sourcerects = cat2_src;
	whitecat.walkleft->sourcerects = cat2_src;
	whitecat.walkright->sourcerects = cat2_src;

	whitemouse.idledown->sourcerects = mouse1_src;
	whitemouse.idleup->sourcerects = mouse1_src;
	whitemouse.idleleft->sourcerects = mouse1_src;
	whitemouse.idleright->sourcerects = mouse1_src;

	whitemouse.dashdown->sourcerects = mouse1_src;
	whitemouse.dashup->sourcerects = mouse1_src;
	whitemouse.dashleft->sourcerects = mouse1_src;
	whitemouse.dashright->sourcerects = mouse1_src;

	whitemouse.walkdown->sourcerects = mouse2_src;
	whitemouse.walkup->sourcerects = mouse2_src;
	whitemouse.walkleft->sourcerects = mouse2_src;
	whitemouse.walkright->sourcerects = mouse2_src;

	whitecat2.idledown->sourcerects = cat1_src;
	whitecat2.idleup->sourcerects = cat1_src;
	whitecat2.idleleft->sourcerects = cat1_src;
	whitecat2.idleright->sourcerects = cat1_src;

	whitecat2.dashdown->sourcerects = cat1_src;
	whitecat2.dashup->sourcerects = cat1_src;
	whitecat2.dashleft->sourcerects = cat1_src;
	whitecat2.dashright->sourcerects = cat1_src;

	whitecat2.walkdown->sourcerects = cat2_src;
	whitecat2.walkup->sourcerects = cat2_src;
	whitecat2.walkleft->sourcerects = cat2_src;
	whitecat2.walkright->sourcerects = cat2_src;

	whitemouse2.idledown->sourcerects = mouse1_src;
	whitemouse2.idleup->sourcerects = mouse1_src;
	whitemouse2.idleleft->sourcerects = mouse1_src;
	whitemouse2.idleright->sourcerects = mouse1_src;

	whitemouse2.dashdown->sourcerects = mouse1_src;
	whitemouse2.dashup->sourcerects = mouse1_src;
	whitemouse2.dashleft->sourcerects = mouse1_src;
	whitemouse2.dashright->sourcerects = mouse1_src;

	whitemouse2.walkdown->sourcerects = mouse2_src;
	whitemouse2.walkup->sourcerects = mouse2_src;
	whitemouse2.walkleft->sourcerects = mouse2_src;
	whitemouse2.walkright->sourcerects = mouse2_src;

	AddAnimationCustom(whitecat.idledown);
	AddAnimationCustom(whitecat.idleup);
	AddAnimationCustom(whitecat.idleleft);
	AddAnimationCustom(whitecat.idleright);

	AddAnimationCustom(whitecat.dashdown);
	AddAnimationCustom(whitecat.dashup);
	AddAnimationCustom(whitecat.dashleft);
	AddAnimationCustom(whitecat.dashright);

	AddAnimationCustom(whitecat.walkdown);
	AddAnimationCustom(whitecat.walkup);
	AddAnimationCustom(whitecat.walkleft);
	AddAnimationCustom(whitecat.walkright);

	AddAnimationCustom(whitemouse.idledown);
	AddAnimationCustom(whitemouse.idleup);
	AddAnimationCustom(whitemouse.idleleft);
	AddAnimationCustom(whitemouse.idleright);

	AddAnimationCustom(whitemouse.dashdown);
	AddAnimationCustom(whitemouse.dashup);
	AddAnimationCustom(whitemouse.dashleft);
	AddAnimationCustom(whitemouse.dashright);

	AddAnimationCustom(whitemouse.walkdown);
	AddAnimationCustom(whitemouse.walkup);
	AddAnimationCustom(whitemouse.walkleft);
	AddAnimationCustom(whitemouse.walkright);

	AddAnimationCustom(whitecat2.idledown);
	AddAnimationCustom(whitecat2.idleup);
	AddAnimationCustom(whitecat2.idleleft);
	AddAnimationCustom(whitecat2.idleright);

	AddAnimationCustom(whitecat2.dashdown);
	AddAnimationCustom(whitecat2.dashup);
	AddAnimationCustom(whitecat2.dashleft);
	AddAnimationCustom(whitecat2.dashright);

	AddAnimationCustom(whitecat2.walkdown);
	AddAnimationCustom(whitecat2.walkup);
	AddAnimationCustom(whitecat2.walkleft);
	AddAnimationCustom(whitecat2.walkright);

	AddAnimationCustom(whitemouse2.idledown);
	AddAnimationCustom(whitemouse2.idleup);
	AddAnimationCustom(whitemouse2.idleleft);
	AddAnimationCustom(whitemouse2.idleright);

	AddAnimationCustom(whitemouse2.dashdown);
	AddAnimationCustom(whitemouse2.dashup);
	AddAnimationCustom(whitemouse2.dashleft);
	AddAnimationCustom(whitemouse2.dashright);

	AddAnimationCustom(whitemouse2.walkdown);
	AddAnimationCustom(whitemouse2.walkup);
	AddAnimationCustom(whitemouse2.walkleft);
	AddAnimationCustom(whitemouse2.walkright);
}

void destroycharacterstarts(void) {
	UnloadTexture(catidledown);
	UnloadTexture(catidleup);
	UnloadTexture(catidleleft);
	UnloadTexture(catidleright);

	UnloadTexture(catrundown);
	UnloadTexture(catrunup);
	UnloadTexture(catrunleft);
	UnloadTexture(catrunright);

	UnloadTexture(mouserundown);
	UnloadTexture(mouserunup);
	UnloadTexture(mouserunleft);
	UnloadTexture(mouserunright);

	UnloadTexture(mouseidledown);
	UnloadTexture(mouseidleup);
	UnloadTexture(mouseidleleft);
	UnloadTexture(mouseidleright);

	delete_DA(cat1_src);
	delete_DA(cat2_src);
	delete_DA(mouse1_src);
	delete_DA(mouse2_src);
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
	player2.cat = &whitecat2;
	player2.mouse = &whitemouse2;
}