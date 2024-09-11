#ifndef CLEARSCENE
#define CLEARSCENE

#include "Model.h"
#include "WorldTransform.h"
#include "ViewProjection.h"
#include "Skydome.h"

class ClearScene{
public:
	~ClearScene();
	void Initialize();
	void Update();
	void Draw();
	bool IsNextScene() { return isfinish; }

private:
	WorldTransform worldTransform_;
	ViewProjection viewProjection_;
	Model* modelBack_ = nullptr;
	Model* modelSkydome_;
	Skydome* skydome_ = nullptr;
	//Model* modelFlont_ = nullptr;
	bool isfinish = false;

	float moveSpeed_ = 0.01f; // 移動速度
	float moveRange_ = 1.0f;  // 移動範囲
	int moveDirection_ = 1;   // 1: 右移動, -1: 左移動
	float initialPositionX_;  // 初期位置のX座標
};

#endif // CLEARSCENE