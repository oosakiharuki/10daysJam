#include "Score.h"
#include "TextureManager.h"
#include "Sprite.h"

Score::~Score() {
	for (int i = 0; i < 5; i++) {
		delete sprite[i];
	}
}



void Score::Initialize() {

	pos = {10, 10,0};
	score = 0;

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

	for (uint32_t i = 0; i < 5; i++) {
		sprite[i] = Sprite::Create(textureHandle[placeNum[i]], {pos.x + i * 50, pos.y});	
	}
}


void Score::Updata() {
	placeNum[0] = score / 10000;
	score %= 10000;

	placeNum[1] = score / 1000;
	score %= 1000;

	placeNum[2] = score / 100;
	score %= 100;

	placeNum[3] = score / 10;
	score %= 10;

	placeNum[4] = score / 1;
	score %= 1;
}


void Score::Draw() { 
	for (uint32_t i = 0; i < 5; i++) {
		sprite[i]->Draw();
	}
}

void Score::ScoreCounter(int point) {
	for (uint32_t i = 0; i < 5; i++) {
		delete sprite[i];
	}	
	score += point;
	for (uint32_t i = 0; i < 5; i++) {
		sprite[i] = Sprite::Create(textureHandle[placeNum[i]], {pos.x + i * 50, pos.y});
	}
}