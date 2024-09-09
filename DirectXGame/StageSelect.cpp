#include "StageSelect.h"
#include "Input.h"

void StageSelect::Initialize() { isfinish = false; }

void StageSelect::Update() {
	if (Input::GetInstance()->TriggerKey(DIK_1)) {
		isfinish = true;
	}
}

void StageSelect::Draw() {

}