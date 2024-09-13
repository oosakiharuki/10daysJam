#include "Score.h"
#include "Sprite.h"
#include "TextureManager.h"

Score::~Score() {
	for (int i = 0; i < 5; i++) {
		delete sprite[i];
	}
	delete HPSprite_;
}

void Score::Initialize() {
	pos = {10, 600, 0};
	score = 40; // 初期スコア

	// テクスチャの読み込み
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

	// スプライトの初期化
	for (uint32_t i = 0; i < 5; i++) {
		sprite[i] = Sprite::Create(textureHandle[placeNum[i]], {pos.x + i * 50, pos.y});
	}

	hpTextureHandle_ = TextureManager::Load("bossHP.png");
	HPSprite_ = Sprite::Create(hpTextureHandle_, {20, 560});

	UpdatePlaceNum(); // 初期スコアの桁数を更新
}

void Score::Update() {
	// スコアに変更があった場合のみ、桁数を更新
	if (scoreChanged) {
		UpdatePlaceNum();
		scoreChanged = false; // スコアが更新されたことをリセット
	}
}

void Score::Draw() {
	for (uint32_t i = 0; i < 5; i++) {
		sprite[i]->Draw();
	}
	HPSprite_->Draw();
}

void Score::ScoreCounter(int point) {
	score += point;
	scoreChanged = true; // スコアが変更されたことをフラグで記録
}

void Score::NowHp(int hp) {
	score = hp;
	scoreChanged = true; // スコアが変更されたことをフラグで記録
}

void Score::UpdatePlaceNum() {
	int tempScore = score;

	placeNum[0] = tempScore / 10000;
	tempScore %= 10000;

	placeNum[1] = tempScore / 1000;
	tempScore %= 1000;

	placeNum[2] = tempScore / 100;
	tempScore %= 100;

	placeNum[3] = tempScore / 10;
	tempScore %= 10;

	placeNum[4] = tempScore / 1;

	// スプライトのテクスチャを更新する
	for (uint32_t i = 0; i < 5; i++) {
		sprite[i]->SetTextureHandle(textureHandle[placeNum[i]]); // テクスチャの再設定
	}
}
