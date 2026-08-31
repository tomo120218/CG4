#pragma once

#include "KamataEngine.h"
#include "Particle.h"

#include <list>

// ゲームシーン
class GameScene {

public:
	// デストラクタ
	~GameScene();

	// 初期化
	void Initialize();

	// 更新
	void Update();

	// 描画
	void Draw();

private:
	// パーティクル3Dモデル
	KamataEngine::Model* modelParticle_ = nullptr;

	// カメラ
	KamataEngine::Camera camera_;

	// 流星パーティクル
	std::list<Particle*> particles_;

	// 流星を生成
	void ParticleBorn();
};