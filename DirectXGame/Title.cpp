#include "Title.h"
#include "Input.h"

void Title::Initialize() { 
	isfinish = false;
}

void Title::Update() { 
	if (Input::GetInstance()->TriggerKey(DIK_SPACE)) {
		isfinish = true;
	} 
}

void Title::Draw() {

}