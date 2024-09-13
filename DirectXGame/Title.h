#ifndef TITLE_H
#define TITLE_H

#include "Model.h"
#include "WorldTransform.h"
#include "ViewProjection.h"
#include "Skydome.h"
#include "Audio.h"

class Title {
public:
	~Title();
	void Initialize();
	void Update();
	void Draw();
	bool IsNextScene() { return isfinish; }

	private:
	WorldTransform worldTransform_;
    WorldTransform startWorldTransform_;
	ViewProjection viewProjection_;
	Model* modelBack_ = nullptr;
	Model* modelFlont_ = nullptr;
	Model* modelSkyDome_ = nullptr;
	Model* modelStart_ = nullptr;
	bool isfinish = false;

	Skydome* skydome_ = nullptr;

	float moveSpeed_ = 0.01f; // 移動速度
	float moveRange_ = 1.0f;  // 移動範囲
	int moveDirection_ = 1;   // 1: 右移動, -1: 左移動
	float initialPositionX_;  // 初期位置のX座標

    Audio* audio_ = nullptr;
	// サウンドデータハンドル
	uint32_t soundDataHandle_ = 0;
	uint32_t soundDataHadle2_ = 0;
	//音声再生ハンドル
	uint32_t voiceJandle_ = 0;
};

#endif // TITLE_H