#include "TimeLimit.h"
#include "TextureManager.h"
#include "Sprite.h"

TimeLimit::~TimeLimit() {
	for (uint32_t i = 0; i < 3; i++) {
		delete sprite[i];
	}
}

void TimeLimit::Initalize() { 
	pos = {10, 10,0};
	Timer = 100;
	placeNum[0] = Timer / 100;
	Timer %= 1;

	placeNum[1] = Timer / 10;
	Timer %= 10;

	placeNum[2] = Timer / 1;
	Timer %= 1;

	textureHandle[0] = TextureManager::Load("Number/num0.png");
	textureHandle[1] = TextureManager::Load("Number/num1.png");
	textureHandle[2] = TextureManager::Load("Number/num2.png");
	textureHandle[3] = TextureManager::Load("Number/num3.png");
	textureHandle[4] = TextureManager::Load("Number/num4.png");
	textureHandle[5] = TextureManager::Load("Number/num5.png");
	textureHandle[6] = TextureManager::Load("Number/num6.png");
	textureHandle[7] = TextureManager::Load("Number/num7.png");
	textureHandle[8] = TextureManager::Load("Number/num8.png");
	textureHandle[9] = TextureManager::Load("Number/num9.png");

	for (uint32_t i = 0; i < 3; i++) {
		sprite[i] = Sprite::Create(textureHandle[placeNum[i]], {pos.x + i * 50, pos.y});
	}

}

void TimeLimit::Update() {
	placeNum[0] = Timer / 100;
	Timer %= 100;

	placeNum[1] = Timer / 10;
	Timer %= 10;

	placeNum[2] = Timer / 1;
	Timer %= 1;

	if ((int)limit > -1) {
		limit -= deltaTimer;
		Counter();
	} 
	else {
		isFinish_ = true;
	}
}

void TimeLimit::Draw() {
	for (uint32_t i = 0; i < 3; i++) {
		sprite[i]->Draw();
	}
}

void TimeLimit::Counter() {
	for (uint32_t i = 0; i < 3; i++) {
		delete sprite[i];
	}
	
	Timer += (int)limit;

	for (uint32_t i = 0; i < 3; i++) {
		sprite[i] = Sprite::Create(textureHandle[placeNum[i]], {pos.x + i * 50, pos.y});
	}
}