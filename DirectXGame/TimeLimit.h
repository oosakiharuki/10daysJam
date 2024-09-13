#ifndef TIMELIMIT_H
#define TIMELIMIT_H

#include "Vector3.h"
class Sprite;

class TimeLimit{
public:
	~TimeLimit();
	void Initalize();
	void Update();
	void Draw();
	void Counter();
	bool GameOver() { return isFinish_; }

private:

	Vector3 pos;

	int textureHandle[10];
	int placeNum[3];

	int Timer = 100;
	float limit = 90.0f;
	int counter = 10;
	float deltaTimer = 1.0f / 60.0f;
	bool isFinish_ = false;

	Sprite* sprite[3];
};
#endif // TIMELIMIT_H