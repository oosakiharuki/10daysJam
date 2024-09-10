#include "Audio.h"
#include "AxisIndicator.h"
#include "DirectXCommon.h"
#include "GameScene.h"
#include "ImGuiManager.h"
#include "PrimitiveDrawer.h"
#include "TextureManager.h"
#include "WinApp.h"

#include "Title.h"
#include "StageSelect.h"
#include "ClearScene.h"
enum class Scene {
	title,
	stageselect,
	game,
	clear
};

Title* title = nullptr;

GameScene* gameScene = nullptr;
StageSelect* stageselect = nullptr;
ClearScene* clearScene = nullptr;
Scene scene_;


//シーンチェンジ
void ChangeScene() {
	switch (scene_) {
	case Scene::title:
		
		if (title->IsNextScene()) {
			scene_ = Scene::stageselect;
			delete title;
			title = nullptr;

			stageselect = new StageSelect();
			stageselect->Initialize();
		}

		break;
	case Scene::stageselect:
		if (stageselect->IsNextScene()) {
			scene_ = Scene::game;
			delete stageselect;
			stageselect = nullptr;

			gameScene = new GameScene();
			gameScene->Initialize();
		}
		break;
	case Scene::game:
		if (gameScene->IsNextScene()) {
			scene_ = Scene::clear;
			delete gameScene;
			gameScene = nullptr;

			clearScene = new ClearScene();
			clearScene->Initialize();
		}

		break;
	case Scene::clear:
		if (clearScene->IsNextScene()) {
			scene_ = Scene::title;
			delete clearScene;
			clearScene = nullptr;

			title = new Title();
			title->Initialize();
		}
		break;
	}

}

//更新
void ChangeUpdate() {
	switch (scene_) {
	case Scene::title:
		title->Update();
		break;
	case Scene::stageselect:
		stageselect->Update();
		break;
	case Scene::game:
		gameScene->Update();
		break;
	case Scene::clear:
		clearScene->Update();
		break;
	}
}

//描画
void ChangeDraw() {
	switch (scene_) {
	case Scene::title:
		title->Draw();
		break;
	case Scene::stageselect:
		stageselect->Draw();
		break;
	case Scene::game:
		gameScene->Draw();
		break;
	case Scene::clear:
		clearScene->Draw();
		break;
	}
}


// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	WinApp* win = nullptr;
	DirectXCommon* dxCommon = nullptr;
	// 汎用機能
	Input* input = nullptr;
	Audio* audio = nullptr;
	AxisIndicator* axisIndicator = nullptr;
	PrimitiveDrawer* primitiveDrawer = nullptr;
	//GameScene* gameScene = nullptr;

	// ゲームウィンドウの作成
	win = WinApp::GetInstance();
	win->CreateGameWindow();

	// DirectX初期化処理
	dxCommon = DirectXCommon::GetInstance();
	dxCommon->Initialize(win);

#pragma region 汎用機能初期化
	// ImGuiの初期化
	ImGuiManager* imguiManager = ImGuiManager::GetInstance();
	imguiManager->Initialize(win, dxCommon);

	// 入力の初期化
	input = Input::GetInstance();
	input->Initialize();

	// オーディオの初期化
	audio = Audio::GetInstance();
	audio->Initialize();

	// テクスチャマネージャの初期化
	TextureManager::GetInstance()->Initialize(dxCommon->GetDevice());
	TextureManager::Load("white1x1.png");

	// スプライト静的初期化
	Sprite::StaticInitialize(dxCommon->GetDevice(), WinApp::kWindowWidth, WinApp::kWindowHeight);

	// 3Dモデル静的初期化
	Model::StaticInitialize();

	// 軸方向表示初期化
	axisIndicator = AxisIndicator::GetInstance();
	axisIndicator->Initialize();

	primitiveDrawer = PrimitiveDrawer::GetInstance();
	primitiveDrawer->Initialize();
#pragma endregion

	// ゲームシーンの初期化
	scene_ = Scene::title;

	title = new Title();
	title->Initialize();

	// メインループ
	while (true) {
		// メッセージ処理
		if (win->ProcessMessage()) {
			break;
		}

		// ImGui受付開始
		imguiManager->Begin();
		// 入力関連の毎フレーム処理
		input->Update();
		// ゲームシーンの毎フレーム処理
		
		ChangeScene();
		ChangeUpdate();
		
		// 軸表示の更新
		axisIndicator->Update();
		// ImGui受付終了
		imguiManager->End();

		// 描画開始
		dxCommon->PreDraw();
		// ゲームシーンの描画
		
		ChangeDraw();
		
		// 軸表示の描画
		axisIndicator->Draw();
		// プリミティブ描画のリセット
		primitiveDrawer->Reset();
		// ImGui描画
		imguiManager->Draw();
		// 描画終了
		dxCommon->PostDraw();
	}

	// 各種解放
	delete title;
	delete gameScene;
	// 3Dモデル解放
	Model::StaticFinalize();
	audio->Finalize();
	// ImGui解放
	imguiManager->Finalize();

	// ゲームウィンドウの破棄
	win->TerminateGameWindow();

	return 0;
}