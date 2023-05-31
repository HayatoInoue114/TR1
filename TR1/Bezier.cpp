#include"Bezier.h"


Bezier::Bezier()
{
	//自機座標
	player.x = 400;
	player.y = 400;

	//変数初期化
	for (int i = 0; i < HOMINGMAX; i++)
	{
		homing[i].x = 0;
		homing[i].y = 0;
		homing[i].u = 0;
		homing[i].Counter = 0;
		homing[i].Counter2 = 0;
		homing[i].DivNum = 0;
		homing[i].P0 = {};
		homing[i].P1 = {};
		homing[i].P2 = {};
		homing[i].isLaserActive = 0;
	}
	DivNum = 50;
	isLoad = false;
	block1.pos = { 300,600 };
	block1.size = { 300,50 };
	count = 0;
	countNum = 1;
	preKey = false;
	for (int i = 0; i < HOMINGTRAILMAX; i++) {
		homingTrail[i] = {};
		isHomingTrail[i] = false;
		cd[i] = 0;
	}
	isSecond = false;
	isMove = false;
	isRight = false;
	isLeft = false;

	size = 10;

	P01, P12, P02 = {};
	
	textureHandle = Novice::LoadTexture("./Resource./ball.png");
}

Bezier::~Bezier() {

}

void Bezier::Init() {
	////自機座標
	//player.x = 400;
	//player.y = 400;

	////変数初期化
	//for (int i = 0; i < HOMINGMAX; i++)
	//{
	//	homing[i].x = 0;
	//	homing[i].y = 0;
	//	homing[i].u = 0;
	//	homing[i].Counter = 0;
	//	homing[i].Counter2 = 0;
	//	homing[i].DivNum = 0;
	//	homing[i].P0.x = 0;
	//	homing[i].P0.y = 0;
	//	homing[i].P1.x = 0;
	//	homing[i].P1.y = 0;
	//	homing[i].P2.x = 0;
	//	homing[i].P2.y = 0;
	//	homing[i].isLaserActive = false;
	//}
	//DivNum = 100;
	//isLoad = false;
	//block1.pos = { 300,600 };
	//block1.size = { 600,50 };
	//count = 0;
	//countNum = 10;
	//isSecond = false;
}

void Bezier::Update() {
	Move();
}

void Bezier::Move() {
	count++;

	for (int i = 0; i < HOMINGMAX; i++)
	{//ホーミング弾出現処理
		//プレイヤーに届く
		//if (Novice::IsTriggerMouse(0) && !isEndPointSet) {
		//	isEndPointSet = true;
		//	homing[i].endPoint.x = player.x;
		//	homing[i].endPoint.y = player.y;
		//}

		//if (!isEndPointSet && !isMidPointSet) {
		//	homing[i].endPoint.x = player.x;
		//	homing[i].endPoint.y = player.y;
		//}


		////中間の制御点
		//if (Novice::IsTriggerMouse(1) && !isMidPointSet) {
		//	isMidPointSet = true;
		//	homing[i].midPoint.x = player.x;
		//	homing[i].midPoint.y = player.y;
		//}

		//if (isEndPointSet && !isMidPointSet) {
		//	homing[i].midPoint.x = player.x;
		//	homing[i].midPoint.y = player.y;
		//}

		////始点から出てくる
		//homing[i].startPoint.x = start.pos.x;
		//homing[i].startPoint.y = start.pos.y;

		if (Novice::CheckHitKey(DIK_SPACE))
		{
			if (!homing[i].isLaserActive)
			{
				homing[i].x = 0;
				homing[i].y = 0;
				homing[i].u = 0;
				homing[i].Counter = 0;
				homing[i].Counter2 = 0;
				homing[i].DivNum = 50;
				homing[i].P0.x = block1.pos.x + GetRandom(0.0f, block1.size.x);
				homing[i].P0.y = block1.pos.y;
				if (player.x >= homing[i].P0.x) {
					homing[i].P1.x = player.x + 200;
				}
				if (player.x <= homing[i].P0.x) {
					homing[i].P1.x = player.x - 200;
				}
				homing[i].P1.y = player.y;
				homing[i].P2.x = player.x;
				homing[i].P2.y = player.y;
				homing[i].isLaserActive = true;


			}
		}


	}

	// 軌跡
	for (int i = 0; i < HOMINGMAX; i++)
	{

		//赤のベジェ曲線の計算
		
		if (!homing[i].isLaserActive) continue;
		if (homing[i].isLaserActive)
		{

			for (int j = 0; j < DivNum; j++)
			{
				homing[i].u = (1.0f / homing[i].DivNum) * homing[i].Counter2;

				P01.x = (1.0f - homing[i].u) * homing[i].P0.x + homing[i].u * homing[i].P1.x;
				P01.y = (1.0f - homing[i].u) * homing[i].P0.y + homing[i].u * homing[i].P1.y;

				P12.x = (1.0f - homing[i].u) * homing[i].P1.x + homing[i].u * homing[i].P2.x;
				P12.y = (1.0f - homing[i].u) * homing[i].P1.y + homing[i].u * homing[i].P2.y;

				P02.x = (1.0f - homing[i].u) * P01.x + homing[i].u * P12.x; P02.y = (1.0f - homing[i].u) * P01.y + homing[i].u * P12.y;

				if (count % countNum == 0) {
					homing[i].x = (int)P02.x;
					homing[i].y = (int)P02.y;
				}




				Novice::DrawEllipse(homing[i].x - 1, homing[i].y - 1, 1, 1, 0.0f, RED, kFillModeSolid);	//ベジェ曲線を描画
				homing[i].Counter2++;
				if (homing[i].Counter2 == homing[i].DivNum) homing[i].Counter2 = 0;

			}
		}
	}

	for (int i = 0; i < HOMINGMAX; i++)
	{

		{//ベジェ曲線を描画
			

			if (homing[i].isLaserActive)
			{
				{//ベジェ曲線を描画

					homing[i].u = (1.0f / homing[i].DivNum) * homing[i].Counter;

					P01.x = (1.0f - homing[i].u) * homing[i].P0.x + homing[i].u * homing[i].P1.x;
					P01.y = (1.0f - homing[i].u) * homing[i].P0.y + homing[i].u * homing[i].P1.y;

					P12.x = (1.0f - homing[i].u) * homing[i].P1.x + homing[i].u * homing[i].P2.x;
					P12.y = (1.0f - homing[i].u) * homing[i].P1.y + homing[i].u * homing[i].P2.y;


					P02.x = (1.0f - homing[i].u) * P01.x + homing[i].u * P12.x; P02.y = (1.0f - homing[i].u) * P01.y + homing[i].u * P12.y;


					homing[i].x = (int)P02.x;
					homing[i].y = (int)P02.y;

					homing[i].Counter++;

					/*Novice::DrawSprite(homing[i].x, homing[i].y, textureHandle, 1, 1, 0, WHITE);*/

				/*Novice::DrawSprite(homing[i].x, homing[i].y, textureHandle, 1, 1, 0, WHITE);*/

					homing[i].Counter++;



					// もしカウンターが分割数に達していたら０に戻す
					if (homing[i].Counter == homing[i].DivNum && !isSecond)
					{
						homing[i].Counter = 0;
						homing[i].isLaserActive = false;//存在を無に
					}




					if (!isSecond) {
						homing[i].P2.x = player.x;
						homing[i].P2.y = player.y + 5;
					}
					else {
						homing[i].P2.x = player.x;
						homing[i].P2.y = player.y - 30;
					}


					for (int j = 0; j < HOMINGTRAILMAX; j++) {
						if (count % countNum == 0 && !isHomingTrail[j]) {
							homingTrail[j].x = homing[i].x;
							homingTrail[j].y = homing[i].y;
							isHomingTrail[j] = true;
							break;
						}

					}





				}

				if (homing[i].isLaserActive)
				{

				}

				if (isSecond) {
					homing[i].x = 0;
					homing[i].y = 0;
					homing[i].u = 0;
					homing[i].Counter = 0;
					homing[i].Counter2 = 0;
					homing[i].DivNum = 500;
					homing[i].P0.x = player.x;
					homing[i].P0.y = player.y + 5;
					if (player.x >= homing[i].P0.x) {
						homing[i].P1.x = player.x + 100;
					}
					if (player.x <= homing[i].P0.x) {
						homing[i].P1.x = player.x - 100;
					}
					homing[i].P1.y = player.y - 10;
					homing[i].P2.x = player.x;
					homing[i].P2.y = player.y - 30;
					homing[i].isLaserActive = true;
				}

			}


			for (int j = 0; j < HOMINGTRAILMAX; j++) {
				if (isHomingTrail[j]) {
					cd[j]++;
				}

				if (cd[j] >= 30 || Novice::CheckHitKey(DIK_SPACE) && !preKey) {
					cd[j] = 0;
					isHomingTrail[j] = false;
				}
			}


		}
	}

	if (Novice::CheckHitKey(DIK_UP)) {
		player.y -= 5;
		isMove = true;
	}
	if (Novice::CheckHitKey(DIK_DOWN)) {
		player.y += 5;
		isMove = true;
	}
	if (Novice::CheckHitKey(DIK_LEFT)) {
		player.x -= 5;
		isMove = true;
		isLeft = true;
	}
	if (Novice::CheckHitKey(DIK_RIGHT)) {
		player.x += 5;
		isMove = true;
		isRight = true;
	}
	if (!Novice::CheckHitKey(DIK_UP) && !Novice::CheckHitKey(DIK_DOWN) && !Novice::CheckHitKey(DIK_LEFT) && !Novice::CheckHitKey(DIK_RIGHT)) {
		isMove = false;
	}
	if (!Novice::CheckHitKey(DIK_LEFT)) {
		isLeft = false;
	}
	if (!Novice::CheckHitKey(DIK_RIGHT)) {
		isRight = false;
	}

	if (Novice::CheckHitKey(DIK_Z)) {
		preKey = true;
	}
}

void Bezier::Draw() {
	if (!isLoad) {
		
		
	}

	for (int i = 0; i < HOMINGMAX; i++) {
		if (homing[i].isLaserActive) {
			Novice::DrawSprite(homing[i].x, homing[i].y, textureHandle, 1, 1, 0, RED);
		}
	}
	for (int i = 0; i < HOMINGTRAILMAX; i++) {
		if (isHomingTrail[i]) {
			Novice::DrawSprite(homingTrail[i].x, homingTrail[i].y, textureHandle, 1, 1, 0, WHITE);
		}
	}
	
	Novice::DrawEllipse(player.x, player.y, size, size, 0, WHITE, kFillModeSolid);//自機表示
	Novice::DrawBox(block1.pos.x, block1.pos.y, block1.size.x, block1.size.y, 0, WHITE, kFillModeSolid);//敵表示

}


