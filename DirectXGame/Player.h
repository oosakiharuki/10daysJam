#pragma once
#include "Model.h"
#include "Vector3.h"
#include "WorldTransform.h"
class MapChipField;
class Player {
public:
	void Initialize(Model* model, ViewProjection* viewProjection);

	void Update();

	void Draw();
    //移動
	void Move();
	//セッタ
	void SetMapChipField(MapChipField* mapChipField) { mapChipField_ = mapChipField; }

private:
	// ワールド変換データ
	WorldTransform worldTransform_;
	// モデル
	Model* model_ = nullptr;
	// ビュープロジェクション
	ViewProjection* viewProjection_ = nullptr;
	//マップチップ
	MapChipField* mapChipField_ = nullptr;
};