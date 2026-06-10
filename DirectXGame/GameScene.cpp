#include "GameScene.h"
#include <cstdlib>
#include <ctime>
#include <numbers>
#include <utility>

using namespace KamataEngine;
using namespace MathUtility;

GameScene::~GameScene() {

	Particle::StaticFinalize();

	stars_.clear();
}

void GameScene::Initialize() {

	srand((unsigned int)time(nullptr));
	Particle::StaticInitialize();

	// Particle_ = Particle::CreateSquare(1); // ←四角形 ()内の数字を増やすと個数が増え、四角形がぴったり並んで配置される
	/*Particle_ = Particle::CreateRing(8);*/

	Particle_ = Particle::CreateRhombus(10); // 菱形
	worldTransform_.Initialize();

	camera_.Initialize();

	textureHandle_ = TextureManager::Load("uvChecker.png");
}

void GameScene::StarBorn(Vector3 position) {
	/*stars_.emplace_back();

	Star& star = stars_.back();

	star.worldTransform.Initialize();

	star.objectColor = std::make_unique<ObjectColor>();
	star.objectColor->Initialize();

	star.worldTransform.translation_ = position;

	float scale = 0.3f + (float)(rand() % 100) / 100.0f;
	star.worldTransform.scale_ = {scale, scale, 1.0f};

	star.color = {1.0f, 1.0f, 1.0f, 1.0f};
	star.objectColor->SetColor(star.color);

	star.worldTransform.TransferMatrix();*/
	stars_.emplace_back();

	Star& star = stars_.back();

	star.worldTransform.Initialize();

	star.objectColor = std::make_unique<ObjectColor>();
	star.objectColor->Initialize();

	star.worldTransform.translation_ = position;

	star.worldTransform.scale_ = {1.0f, 1.0f, 1.0f};

	star.color = {1.0f, 1.0f, 1.0f, 1.0f};
	star.objectColor->SetColor(star.color);

	star.worldTransform.matWorld_ = MakeScaleMatrix(star.worldTransform.scale_) * MakeRotateZMatrix(star.worldTransform.rotation_.z) * MakeTranslateMatrix(star.worldTransform.translation_);

	star.worldTransform.TransferMatrix();
}

void GameScene::Update() {

	if (rand() % 20 == 0) {
		Vector3 pos = {
		    (float)(rand() % 100 - 50) / 10.0f, // -5.0 ～ 4.9
		    (float)(rand() % 60 - 30) / 10.0f,  // -3.0 ～ 2.9
		    0.0f};

		StarBorn(pos);
	}

	for (auto& star : stars_) {
		star.counter += 1.0f / 60.0f;

		float alpha = 1.0f - star.counter / star.lifeTime;
		if (alpha < 0.0f) {
			alpha = 0.0f;
		}

		star.color.w = alpha;
		star.objectColor->SetColor(star.color);

		if (star.counter >= star.lifeTime) {
			star.isFinished = true;
		}

		star.worldTransform.matWorld_ = MakeScaleMatrix(star.worldTransform.scale_) * MakeRotateZMatrix(star.worldTransform.rotation_.z) * MakeTranslateMatrix(star.worldTransform.translation_);

		star.worldTransform.TransferMatrix();
	}

	stars_.remove_if([](const Star& star) { return star.isFinished; });

	worldTransform_.TransferMatrix();
	camera_.TransferMatrix();
}

void GameScene::Draw() {
	ID3D12GraphicsCommandList* cmdList = DirectXCommon::GetInstance()->GetCommandList();

	// 描画開始
	Particle::PreDraw(cmdList);

	// モデル描画
	/*Particle_->Draw(worldTransform, camera_, textureHandle_);*/
	for (auto& star : stars_) {
		Particle_->Draw(star.worldTransform, camera_, textureHandle_, star.objectColor.get());
	}

	// 描画終了
	Particle::PostDraw();
}