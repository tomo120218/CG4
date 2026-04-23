#pragma once
#include "KamataEngine.h"

// ゲームシーン
class GameScene {

	public:

		// 初期化
	    void Initialize();

		// 更新
	    void Update();

		// 描画
	    void Draw();

		// デストラクタ
	    ~GameScene();

		
private:

	// カメラ
	KamataEngine::Camera camera_;

	// テキスチャハンドル
	uint32_t textureHandle_ = 0;

	//
	Model* model_ = nullptr;

	WorldTransform worldTransform_;
};
