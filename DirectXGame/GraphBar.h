#pragma once

#include "KamataEngine.h"

class GraphBar {
public:
	~GraphBar();

	void Initialize(uint32_t textureHandle);
	void Update(uint32_t hp);
	void Draw();

private:
	uint32_t textureHandle_ = 0;

	KamataEngine::Sprite* sprite_ = nullptr;
	KamataEngine::Sprite* sprite2_ = nullptr;
};