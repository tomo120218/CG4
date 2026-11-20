#include "GameScene.h"

#include <algorithm>
#include <cstdlib>
#include <ctime>

using namespace KamataEngine;
using namespace MathUtility;

// デストラクタ
GameScene::~GameScene() {

	delete stage_;
	delete player_;
	delete graphBar_;
	delete drawNumber_;
	delete modelPlayer_;

	// 流星を削除
	for (Particle* particle : particles_) {
		delete particle;
	}
	particles_.clear();

	delete modelParticle_;
}

// 初期化
void GameScene::Initialize() {

	// 乱数初期化
	srand(static_cast<unsigned int>(time(nullptr)));

	// テクスチャ読み込み
	textureHandleStage_ = TextureManager::Load("stage.png");
	textureHandleGraph_ = TextureManager::Load("white1x1.png");
	textureHandleNumber_ = TextureManager::Load("number.png");

	// モデル読み込み
	modelPlayer_ = Model::CreateFromOBJ("player");

	// 流星用モデル
	modelParticle_ = Model::CreateFromOBJ("goal", true);
	// カメラ初期化
	camera_.translation_ = {0, 0, -20};
	camera_.Initialize();

	// ステージ
	stage_ = new Stage();
	stage_->Initialize(textureHandleStage_);

	// プレイヤー
	player_ = new Player();
	player_->Initialize(modelPlayer_);

	// HPゲージ
	graphBar_ = new GraphBar();
	graphBar_->Initialize(textureHandleGraph_);

	// スコア表示
	drawNumber_ = new DrawNumber();
	drawNumber_->Initialize(textureHandleNumber_);

	// 流星発生カウンター
	spawnCounter_ = 0;
}

// 更新
void GameScene::Update() {

	// HP処理
	hp_--;
	if (hp_ < 0) {
		hp_ = 200;
	}

	// スコア処理
	gameScore_++;

	// 既存の更新処理
	stage_->Update();
	player_->Update();

	graphBar_->Update(hp_);
	drawNumber_->Update(gameScore_);

	// ========================================
	// 流星群の発生
	// ========================================

	spawnCounter_++;

	// 15フレームごとに流星を発生させる
	if (spawnCounter_ >= 15) {
		ParticleBorn();
		spawnCounter_ = 0;
	}

	// ========================================
	// 流星の更新
	// ========================================

	for (Particle* particle : particles_) {
		particle->Update();
	}

	// 寿命が終わった流星を削除
	particles_.remove_if([](Particle* particle) {
		if (particle->IsFinished()) {
			delete particle;
			return true;
		}
		return false;
	});
}

// 描画
void GameScene::Draw() {

	// DirectXCommon取得
	DirectXCommon* dxCommon = DirectXCommon::GetInstance();

	// ========================================
	// ステージ描画
	// ========================================

	Sprite::PreDraw(dxCommon->GetCommandList());

	stage_->Draw();

	Sprite::PostDraw();

	// 深度バッファクリア
	dxCommon->ClearDepthBuffer();

	// ========================================
	// 3Dモデル描画
	// ========================================

	Model::PreDraw();

	// プレイヤー
	player_->Draw(camera_);

	// 流星群
	for (Particle* particle : particles_) {
		particle->Draw(camera_);
	}

	Model::PostDraw();

	// ========================================
	// UI描画
	// ========================================

	Sprite::PreDraw(dxCommon->GetCommandList());

	graphBar_->Draw();
	drawNumber_->Draw();

	Sprite::PostDraw();
}

// ========================================
// 流星の発生処理
// ========================================
void GameScene::ParticleBorn() {

	// 発生位置
	float x = 28.0f + static_cast<float>(rand() % 12);
	float y = 10.0f + static_cast<float>(rand() % 18);

	Vector3 position = {x, y, 0.0f};

	float speed = 0.5f + static_cast<float>(rand() % 30) / 100.0f;

	Vector3 velocity = {-0.75f * speed, -0.55f * speed, 0.0f};

	// 流星生成
	Particle* particle = new Particle();

	particle->Initialize(modelParticle_, position, velocity);

	particles_.push_back(particle);
}