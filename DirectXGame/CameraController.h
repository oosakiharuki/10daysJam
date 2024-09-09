#pragma once
#include "ViewProjection.h"

struct Rect {
	float left = 0.0f;   // 左端
	float right = 1.0f;  // 右端
	float bottom = 0.0f; // 下端
	float top = 1.0f;    // 上端
};
class Player;
class CameraController {
public:
	void Initialize(ViewProjection* viewProjection,Rect movableArea);
	void Update();
	// リセット
	void Reset();
	// セッタ
	void SetTarget(Player* target) { target_ = target; }
	void SetMovableArea(Rect area) { movableArea_ = area; }

private:
	// ビュープロジェクション
	ViewProjection* viewProjection_;
	// 追従対象のポインタ
	Player* target_ = nullptr;
	// 追従対象とカメラの座標の差(オフセット)
	Vector3 targetOffset_ = {18, -15, -45.0f};
	// カメラ移動範囲
	Rect movableArea_ = {};
	//カメラの目標座標
	Vector3 targetpos_ = {};
	//座標補間割合
	static inline const float kInterpolationRate = 0.8f;
	//速度掛け率
	static inline const float kVelocityBias = 2.0f;
	/*
	//追従対象の各方向へのカメラ移動範囲
	static inline const Rect margin = {-5.0f, 5.0f, -5.0f, 5.0f};
	*/
};
