#include "Vector3.h"

class Sprite;

class Score {
public:
	~Score();
	void Initialize();
	void Update();
	void Draw();

	void ScoreCounter(int point); // スコアを加算するメソッド
	void NowHp(int hp);           // 現在のHPを設定するメソッド

private:
	void UpdatePlaceNum(); // スコアの桁数を更新する関数

	int textureHandle[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	int hpTextureHandle_ = 0;
	int placeNum[5] = {0, 0, 0, 0, 0};
	int score = 0;             // スコア
	bool scoreChanged = false; // スコアが変更されたかどうかのフラグ

	Vector3 pos;
	Sprite* sprite[5] = {}; // 5桁のスプライト
	Sprite* HPSprite_ = nullptr;
};
