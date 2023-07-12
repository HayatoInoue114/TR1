#pragma once
#include"Excellence.h"
#include"Underachiever.h"
#include"Prodigy.h"

class GameManager
{
public:
	GameManager();
	~GameManager();

	void Init(Excellence* excellence, Underachiever* underachiever, Prodigy* prodigy);
	void Update();
	void Draw();

private:
	Excellence *excellence_;
	Underachiever* underachiever_;
	Prodigy* prodigy_;

	int mode_;
};

