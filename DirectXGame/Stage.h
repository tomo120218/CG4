#pragma once

#include "KamataEngine.h"

class Stage {
public:
	~Stage();

	void Initialize(uint32_t textureHandle);
	void Update();
	void Draw();

private:
	uint32_t textureHandle_ = 0;

	KamataEngine::Sprite* sprite_ = nullptr;
	KamataEngine::Sprite* sprite2_ = nullptr;
};