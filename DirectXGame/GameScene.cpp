#include "GameScene.h"

#include <cstdlib>
#include <ctime>

using namespace KamataEngine;

// ========================================
// デストラクタ
// ========================================
GameScene::~GameScene() {

	delete modelParticle_;

	for (Particle* particle : particles_) {
		delete particle;
	}

	particles_.clear();
}

// ========================================
// 初期化
// ========================================
void GameScene::Initialize() {

	srand((unsigned)time(NULL));

	// 球モデル
	modelParticle_ = Model::CreateSphere(4, 4);

	// カメラ
	camera_.Initialize();
}

// ========================================
// 更新
// ========================================
void GameScene::Update() {

	// ========================================
	// 流星を一定間隔で生成
	// ========================================

	static int spawnCounter = 0;

	spawnCounter++;

	// 約0.25秒に1回
	if (spawnCounter >= 15) {

		ParticleBorn();

		spawnCounter = 0;
	}

	// ========================================
	// パーティクル更新
	// ========================================

	for (Particle* particle : particles_) {

		particle->Update();
	}

	// ========================================
	// 終了したパーティクルを削除
	// ========================================

	particles_.remove_if([](Particle* particle) {
		if (particle->IsFinished()) {

			delete particle;

			return true;
		}

		return false;
	});
}

// ========================================
// 描画
// ========================================
void GameScene::Draw() {

	Model::PreDraw();

	for (Particle* particle : particles_) {

		particle->Draw(camera_);
	}

	Model::PostDraw();
}

// ========================================
// 流星生成
// ========================================
void GameScene::ParticleBorn() {

	// ========================================
	// 右上からランダムに発生
	// ========================================

	float startX = 28.0f + static_cast<float>(rand() % 12);

	float startY = 10.0f + static_cast<float>(rand() % 18);

	Vector3 position = {startX, startY, 0.0f};

	// ========================================
	// 左下方向への速度
	// ========================================

	float speed = 1.0f + static_cast<float>(rand() % 40) / 100.0f;

	Vector3 velocity = {-0.75f * speed, -0.55f * speed, 0.0f};

	// ========================================
	// 流星生成
	// ========================================

	Particle* particle = new Particle();

	particle->Initialize(modelParticle_, position, velocity);

	particles_.push_back(particle);
}