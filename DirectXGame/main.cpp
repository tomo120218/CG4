#include <Windows.h>

#include "GameScene.h"
#include "KamataEngine.h"
#include "TitleScene.h"
using namespace KamataEngine;

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) {

	// エンジンの初期化
	KamataEngine::Initialize(L"CG4_2026_各種機能");

	// DirectXCommon インスタンスの取得
	DirectXCommon* dxCommon = DirectXCommon::GetInstance();

	// ゲームシーンのインスタンス生成
	GameScene* gameScene = new GameScene();
	// ゲームシーンの初期化
	gameScene->Initialize();
	// タイトルシーンのインスタンス生成
	// TitleScene* titleScene = new TitleScene();
	//// タイトルシーンの初期化
	// titleScene->Initialize();

	// メインループ
	while (true) {
		// エンジンの更新
		if (KamataEngine::Update()) {
			break;
		}

		// ゲームシーンの更新
		gameScene->Update();
		// タイトルシーンの更新
		// titleScene->Update();

		// 描画開始
		dxCommon->PreDraw();

		// ゲームシーンの描画
		gameScene->Draw();
		// タイトルシーンの描画
		// titleScene->Draw();

		// 描画終了
		dxCommon->PostDraw();
	}

	// ゲームシーンの削除
	delete gameScene;
	// nullptrの代入
	gameScene = nullptr;

	// タイトルシーンの削除
	// delete titleScene;
	// nullptrの代入
	// titleScene = nullptr;

	// エンジンの終了処理
	KamataEngine::Finalize();

	return 0;
}