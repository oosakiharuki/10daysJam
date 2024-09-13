#ifndef INSTRUCTION
#define INSTRUCTION

#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "Skydome.h"
#include "Audio.h"

class Instruction {
public:
	~Instruction();
	void Initialize();
	void Update();
	void Draw();
	bool IsNextScene() { return isfinish; }

private:
	WorldTransform worldTransform_;
	ViewProjection viewProjection_;
	Model* modelBackground_ = nullptr;
	Model* modelSkyDome_ = nullptr;
	Skydome* skydome_ = nullptr;
	bool isfinish = false;

	Audio* audio_ = nullptr;
	uint32_t soundDataHandle_ = 0;
	uint32_t soundDataHandle2_ = 0;
	uint32_t voiceHandle_ = 0;
};


#endif / INSTRUCTION
