#pragma once
#include "Effect.h"
#include "KamataEngine.h"
#include <list>
#include <memory>

// ゲームシーン
class GameScene {
public:
	// デストラクタ
	/*GameScene();*/
	~GameScene();

	// 初期化
	void Initialize();

	void StarBorn(KamataEngine::Vector3 position);

	// 更新
	void Update();

	// 描画
	void Draw();

private:
	KamataEngine::Effect* effect_ = nullptr;
	KamataEngine::WorldTransform worldTransform_;
	KamataEngine::Camera camera_;

	uint32_t textureHandle_ = 0;

	struct Star {
		KamataEngine::WorldTransform worldTransform;
		std::unique_ptr<KamataEngine::ObjectColor> objectColor;

		float counter = 0.0f;
		float lifeTime = 1.0f;
		bool isFinished = false;

		KamataEngine::Vector4 color = {1, 1, 1, 1};
	};

	std::list<Star> stars_;
};
