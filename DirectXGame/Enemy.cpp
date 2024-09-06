#include "Enemy.h"
#include <cassert>
#include <fstream>
#include "MyMath.h"

void Enemy::Initialize(Model* model, ViewProjection* viewProjection, Vector3 position) { 
	
	assert(model);

	model_ = model;
	worldTransform_.Initialize();
	viewProjection_ = viewProjection;

	worldTransform_.translation_ = position;

	move = position;

}

void Enemy::LoadEnemyMoveData() {

	std::ifstream file;
	file.open("Resources/EnemyMove.csv");
	assert(file.is_open());

	enemyMoveCommands << file.rdbuf();

	file.close();
}

void Enemy::UpdateEnemyPopCommands(uint32_t number) {

	std::string line;

	while (getline(enemyMoveCommands, line)) {

		std::istringstream line_stream(line);
		std::string word;

		if (word.find("//") == 0) {
			continue;
		}

		getline(line_stream, word, ',');
		float number_ = (float)std::atof(word.c_str());

		if (number_ == number) {
			getline(line_stream, word, ',');
			float speed = (float)std::atof(word.c_str());

			getline(line_stream, word, ',');
			float rangeX = (float)std::atof(word.c_str());

			getline(line_stream, word, ',');
			float rangeY = (float)std::atof(word.c_str());

			getline(line_stream, word, ',');
			if (word.find("revarse") == 0) {
				speed = -speed;
			}

			getline(line_stream, word, ',');
			if (word.find("circle") == 0) {
				rotateFlag = true;
			}


			kLoad = 1.0f / speed;
			kRange.x = rangeX;
			kRange.y = rangeY;
		}
	}
}

void Enemy::Update() {

	worldTransform_.UpdateMatrix();

	kSpeed += kLoad; // 速度

	worldTransform_.translation_.x = move.x + std::sin(kSpeed) * kRange.x;
	

	if (rotateFlag) {
		worldTransform_.translation_.y = move.y + std::cos(kSpeed) * kRange.y;
	} else {
		worldTransform_.translation_.y = move.y + std::sin(kSpeed) * kRange.y;
	}
}

void Enemy::Draw() {

	model_->Draw(worldTransform_, *viewProjection_);

}

Vector3 Enemy::GetWorldPosition() {
	Vector3 worldPos;

	worldPos.x = worldTransform_.translation_.x;
	worldPos.y = worldTransform_.translation_.y;
	worldPos.z = worldTransform_.translation_.z;

	return worldPos;
}

AABB Enemy::GetAABB() {
	Vector3 worldPos = GetWorldPosition();

	AABB aabb;

	aabb.min = {worldPos.x - kWidth / 2.0f, worldPos.y - kHeight / 2.0f, worldPos.z - kWidth / 2.0f};
	aabb.max = {worldPos.x + kWidth / 2.0f, worldPos.y + kHeight / 2.0f, worldPos.z + kWidth / 2.0f};

	return aabb;
}