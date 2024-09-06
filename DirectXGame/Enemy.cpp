#include "Enemy.h"
#include <cassert>
#include <fstream>

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
			float range = (float)std::atof(word.c_str());

			getline(line_stream, word, ',');
			if (word.find("revarse") == 0) {
				speed = -speed;
			}

			kLoad = 1.0f / speed;
			kRange = range;
		}
	}
}

void Enemy::Update() {

	worldTransform_.UpdateMatrix();

	kSpeed += kLoad; // 速度

	worldTransform_.translation_.x = move.x + std::sin(kSpeed) * kRange;

}

void Enemy::Draw() {

	model_->Draw(worldTransform_, *viewProjection_);

}