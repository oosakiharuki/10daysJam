#pragma once

#include "Model.h"
#include "WorldTransform.h"
#include "ViewProjection.h"

class Boss {
public:

	void Initialize(Model* model, ViewProjection* viewProjection);

	void Updata();

	void Draw();

private:
	WorldTransform worldTransform_;

	Model* model_ = nullptr;

	ViewProjection* viewProjection_ = nullptr;

	float bossHp = 100.0f;
};