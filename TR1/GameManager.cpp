#include"GameManager.h"

GameManager::GameManager()
{
	mode_ = 0;
}

GameManager::~GameManager()
{

}


void GameManager::Init(Excellence* excellence, Underachiever* underachiever, Prodigy* prodigy) {
	excellence_ = excellence;
	underachiever_ = underachiever;
	prodigy_ = prodigy;
	
	excellence_->Init();
	underachiever_->Init();
	prodigy_->Init();
}

void GameManager::Update() {
	if (Novice::CheckHitKey(DIK_M)) {
		mode_++;
	}
	if (mode_ == 2) {
		mode_ = 0;
	}

	switch (mode_)
	{
	case 0:
		excellence_->Update();
		underachiever_->Update();
		prodigy_->Update();
		break;

	case 1:
		if (Novice::CheckHitKey(DIK_UP) || Novice::CheckHitKey(DIK_DOWN) || Novice::CheckHitKey(DIK_LEFT) || Novice::CheckHitKey(DIK_RIGHT)) {
			excellence_->Update();
			underachiever_->Update();
			prodigy_->Update();
		}
		break;

	default:
		break;
	}
	
	
}

void GameManager::Draw() {
	excellence_->Draw();
	underachiever_->Draw();
	prodigy_->Draw();
}