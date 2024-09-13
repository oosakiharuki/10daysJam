#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "Audio.h"

class Skydome;

class GameOver {

public:
	~GameOver();
	void Initialize();
	void Update();
	void Draw();
	bool IsNextScene() { return isfinish; }

private:
	WorldTransform worldTransform_;
	ViewProjection viewProjection_;
	Model* model_ = nullptr;
	Model* modelSkydome_;
	Skydome* skydome_ = nullptr;
	bool isfinish = false;


	float moveSpeed_ = 0.01f; // 移動速度
	float moveRange_ = 1.0f;  // 移動範囲
	int moveDirection_ = 1;   // 1: 右移動, -1: 左移動
	float initialPositionX_;  // 初期位置のX座標

	Audio* audio_ = nullptr;
	uint32_t soundDataHandle_ = 0;
	uint32_t soundDataHandle2_ = 0;
	uint32_t voiceHandle_ = 0;
};