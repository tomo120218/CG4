#include "GameScene.h"
using namespace KamataEngine;

// デストラクタ
GameScene::~GameScene();

void GameScene::Initialize() { 


	camera_.Initialize();

	// ファイル名を指定してテキスチャを読み込む
	textureHandle_ = TextureManager::Load("uvChecker.png");

	// ワールド
	worldTransform_.Initialize();
}

void GameScene::Update() {


}

void GameScene::Draw() {


}
