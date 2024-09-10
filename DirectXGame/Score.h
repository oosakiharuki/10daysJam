#include "Vector3.h"

class Sprite;

class Score {
public:
	~Score();
	void Initialize();
	void Updata();
	void Draw();

	void ScoreCounter(int point);
	void NowHp(int hp) { score = hp; }

private:
	int textureHandle[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	int placeNum[5] = {0, 0, 0, 0, 0};
	int score;

	Vector3 pos;
	Sprite* sprite[5] = {};
};