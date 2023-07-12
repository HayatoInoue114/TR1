#include"Excellence.h"


Excellence::Excellence()
{
	//自機座標
	player.x = kWindowWidth / 2;
	player.y = 200;

	//変数初期化
	for (int i = 0; i < EXCELLENCEHOMINGMAX; i++)
	{
		homing[i].x = 0;
		homing[i].y = 0;
		homing[i].t = 0;
		homing[i].Counter = 0;
		homing[i].Counter2 = 0;
		homing[i].DivNum = 0;
		homing[i].startPoint = {};
		homing[i].midPoint = {};
		homing[i].endPoint = {};
		homing[i].isLaserActive = 0;
		homing[i].easingAdjustValue = 0.7f;

		homing2[i].x = 0;
		homing2[i].y = 0;
		homing2[i].t = 0;
		homing2[i].Counter = 0;
		homing2[i].Counter2 = 0;
		homing2[i].DivNum = 0;
		homing2[i].startPoint = {};
		homing2[i].midPoint = {};
		homing2[i].endPoint = {};
		homing2[i].isLaserActive = 0;
		homing2[i].easingAdjustValue = homing[i].easingAdjustValue;
	}
	DivNum = 40;
	isLoad = false;
	
	block1.size = { 300,50 };
	block1.pos = { 0 ,700 };

	count = 0;
	countNum = 1;
	preKey = false;
	for (int i = 0; i < EXCELLENCEHOMINGTRAILMAX; i++) {
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

	textureHandle = Novice::LoadTexture("./Resource./yuu.png");

	//制御点の距離を調整する値
	midAdjustValue = 1.0f;
	endAdjustValue = 1.3f;

	//今のところ使わない
	setFrame = 20;

	//周回用フラグ
	isAround = false;

	//ホーミング強度
	trackingValue = 0.8f;

	//midPointの限界値
	midLimitValue = 400;


}

Excellence::~Excellence() {

}

void Excellence::Init() {
	////自機座標
	//player.x = 400;
	//player.y = 400;

	////変数初期化
	//for (int i = 0; i < EXCELLENCEHOMINGMAX; i++)
	//{
	//	homing[i].x = 0;
	//	homing[i].y = 0;
	//	homing[i].t = 0;
	//	homing[i].Counter = 0;
	//	homing[i].Counter2 = 0;
	//	homing[i].DivNum = 0;
	//	homing[i].startPoint.x = 0;
	//	homing[i].startPoint.y = 0;
	//	homing[i].midPoint.x = 0;
	//	homing[i].midPoint.y = 0;
	//	homing[i].endPoint.x = 0;
	//	homing[i].endPoint.y = 0;
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

void Excellence::Update() {
	Move();
}

void Excellence::Move() {
	count++;

	for (int i = 0; i < EXCELLENCEHOMINGMAX; i++)
	{//ホーミング弾出現処理
		if (Novice::CheckHitKey(DIK_SPACE))
		{
			prePlayer = player;
			

			if (!homing[i].isLaserActive && !homing2[i].isLaserActive)
			{
				homing[i].x = 0;
				homing[i].y = 0;
				homing[i].t = 0;
				homing[i].Counter = 0;
				homing[i].Counter2 = 0;
				homing[i].DivNum = DivNum;
				/*homing[i].easingAdjustValue = GetRandom(0.3f, 0.4f);*/

				//制御点をいじる場所
				homing[i].startPoint.x = block1.pos.x + GetRandom(0.0f, block1.size.x);
				homing[i].startPoint.y = block1.pos.y;

				if (player.x >= homing[i].startPoint.x) {
					homing[i].midPoint.x = player.x - GetRandom(200,600);
				}
				if (player.x <= homing[i].startPoint.x) {
					homing[i].midPoint.x = player.x + GetRandom(200, 600);
				}
				homing[i].midPoint.y = player.y + GetRandom(300,700);
				homing[i].endPoint.x = player.x;
				homing[i].endPoint.y = player.y + 5;
				homing[i].isLaserActive = true;

				
			}
		}

		

	}

	/*// 軌跡
	//for (int i = 0; i < EXCELLENCEHOMINGMAX; i++)
	//{
	//	if (!homing[i].isLaserActive) continue;
	//	if (homing[i].isLaserActive)
	//	{

	//		//赤のベジェ曲線の計算
	//		for (int j = 0; j < DivNum; j++)
	//		{
	//			homing[i].t = (1.0f / homing[i].DivNum) * homing[i].Counter2 * (1.0f / homing[i].DivNum) * homing[i].Counter2 * (1.0f / homing[i].DivNum) * homing[i].Counter2 * (1.0f / homing[i].DivNum) * homing[i].Counter2;

	//			P01.x = (1.0f - homing[i].t) * homing[i].startPoint.x + homing[i].t * homing[i].midPoint.x;
	//			P01.y = (1.0f - homing[i].t) * homing[i].startPoint.y + homing[i].t * homing[i].midPoint.y;

	//			P12.x = (1.0f - homing[i].t) * homing[i].midPoint.x + homing[i].t * homing[i].endPoint.x;
	//			P12.y = (1.0f - homing[i].t) * homing[i].midPoint.y + homing[i].t * homing[i].endPoint.y;

	//			P02.x = (1.0f - homing[i].t) * P01.x + homing[i].t * P12.x; P02.y = (1.0f - homing[i].t) * P01.y + homing[i].t * P12.y;

	//			if (count % countNum == 0) {
	//				homing[i].x = (int)P02.x;
	//				homing[i].y = (int)P02.y;
	//			}
	//			
	//			
	//			

	//			
	//			homing[i].Counter2++;
	//			if (homing[i].Counter2 == homing[i].DivNum) {
	//				homing[i].Counter2 = 0;
	//			}
	//			
	//		}
	//	}
	//}*/



	//1個目の軌道/////////////////////////////////////////
	for (int i = 0; i < EXCELLENCEHOMINGMAX; i++)
	{
		

		if (homing[i].isLaserActive)
		{
			prePlayer = player;
			{//ベジェ曲線を描画
				homing[i].t = (1.0f / homing[i].DivNum) * homing[i].Counter * homing[i].easingAdjustValue;

				P01.x = (1.0f - homing[i].t) * homing[i].startPoint.x + homing[i].t * homing[i].midPoint.x; 
				P01.y = (1.0f - homing[i].t) * homing[i].startPoint.y + homing[i].t * homing[i].midPoint.y;

				P12.x = (1.0f - homing[i].t) * homing[i].midPoint.x + homing[i].t * homing[i].endPoint.x; 
				P12.y = (1.0f - homing[i].t) * homing[i].midPoint.y + homing[i].t * homing[i].endPoint.y;


				P02.x = (1.0f - homing[i].t) * P01.x + homing[i].t * P12.x;
				P02.y = (1.0f - homing[i].t) * P01.y + homing[i].t * P12.y;


				homing[i].x = (int)P02.x;
				homing[i].y = (int)P02.y;

				homing[i].Counter++;



				// もしtが1になったら0に戻す
				if (homing[i].t >= 1.0f)
				{

					homing[i].Counter = 0;
					isSecond = true;//2個目の軌道のフラグを立てる
					homing[i].isLaserActive = false;//存在を無くす
					isAround = false;//ここで周回フラグを折る
				}
			


				for (int j = 0; j < EXCELLENCEHOMINGTRAILMAX; j++) {
					if (count % countNum == 0 && !isHomingTrail[j]) {
						homingTrail[j].x = homing[i].x;
						homingTrail[j].y = homing[i].y;
						isHomingTrail[j] = true;
						break;
					}

				}
			}
		}
	}


	///////////////////////2個目の軌道/////////////////////////////////////////
	for (int i = 0; i < EXCELLENCEHOMINGMAX; i++)
	{
		if (!homing2[i].isLaserActive && isSecond)
		{
			homing2[i].tmpEndVector = { player.x - prePlayer.x , player.y - prePlayer.y };
			homing2[i].x = 0;
			homing2[i].y = 0;
			homing2[i].t = 0;
			homing2[i].Counter = 0;
			homing2[i].Counter2 = 0;
			homing2[i].DivNum = DivNum;
			/*homing2[i].easingAdjustValue = GetRandom(0.3f, 0.4f);*/
			/*if (midAdjustValue >= 0.8f) {
				midAdjustValue -= 0.05f;
			}*/

			//制御点をいじる場所
			homing2[i].startPoint = homing[i].endPoint;

			homing2[i].tmpMidVector.x = homing[i].endPoint.x - homing[i].midPoint.x;
			homing2[i].tmpMidVector.y = homing[i].endPoint.y - homing[i].midPoint.y;

			homing2[i].midPoint.x = homing2[i].startPoint.x + homing2[i].tmpMidVector.x * midAdjustValue;
			homing2[i].midPoint.y = homing2[i].startPoint.y + homing2[i].tmpMidVector.y * midAdjustValue;

			

			homing2[i].endPoint.x = player.x;
			homing2[i].endPoint.y = player.y;

			homing2[i].isLaserActive = true;

			
		}


		if (homing2[i].isLaserActive)
		{
			{//ベジェ曲線を描画
				homing2[i].t = (1.0f / homing2[i].DivNum) * homing2[i].Counter * homing2[i].easingAdjustValue;

				P01.x = (1.0f - homing2[i].t) * homing2[i].startPoint.x + homing2[i].t * homing2[i].midPoint.x;
				P01.y = (1.0f - homing2[i].t) * homing2[i].startPoint.y + homing2[i].t * homing2[i].midPoint.y;

				P12.x = (1.0f - homing2[i].t) * homing2[i].midPoint.x + homing2[i].t * homing2[i].endPoint.x;
				P12.y = (1.0f - homing2[i].t) * homing2[i].midPoint.y + homing2[i].t * homing2[i].endPoint.y;

				P02.x = (1.0f - homing2[i].t) * P01.x + homing2[i].t * P12.x;
				P02.y = (1.0f - homing2[i].t) * P01.y + homing2[i].t * P12.y;

				homing2[i].x = (int)P02.x;
				homing2[i].y = (int)P02.y;

				homing2[i].Counter++;



				// もしtが1になったら0に戻す
				if (homing2[i].t >= 1.0f)
				{
					homing2[i].Counter = 0;
					homing2[i].isLaserActive = false;//存在を無くす
					isSecond = false;//2個目の軌道のフラグを折る
					isAround = true;//ここで周回用のフラグを立てる
				}



				for (int j = 0; j < EXCELLENCEHOMINGTRAILMAX; j++) {
					if (count % countNum == 0 && !isHomingTrail[j]) {
						homingTrail[j].x = homing2[i].x;
						homingTrail[j].y = homing2[i].y;
						isHomingTrail[j] = true;
						break;
					}

				}
			}

			//周回用の初期化
			if (!homing[i].isLaserActive && !homing2[i].isLaserActive && isAround)
			{
				homing[i].x = 0;
				homing[i].y = 0;
				homing[i].t = 0;
				homing[i].Counter = 0;
				homing[i].Counter2 = 0;
				homing[i].DivNum = DivNum;
				/*homing[i].easingAdjustValue = GetRandom(0.3f, 0.4f);*/

				//制御点をいじる場所
				homing[i].startPoint = homing2[i].endPoint;

				homing[i].tmpMidVector.x = homing2[i].endPoint.x - homing2[i].midPoint.x;
				homing[i].tmpMidVector.y = homing2[i].endPoint.y - homing2[i].midPoint.y;

				homing[i].midPoint.x = homing[i].startPoint.x + homing[i].tmpMidVector.x * midAdjustValue;
				homing[i].midPoint.y = homing[i].startPoint.y + homing[i].tmpMidVector.y * midAdjustValue;

				homing[i].endPoint.x = player.x;
				homing[i].endPoint.y = player.y;

				homing[i].isLaserActive = true;
			}
		}
	}

	//残像が生きているか
	for (int j = 0; j < EXCELLENCEHOMINGTRAILMAX; j++) {
		if (isHomingTrail[j]) {
			cd[j]++;
		}

		if (cd[j] >= 30 || Novice::CheckHitKey(DIK_SPACE) && !preKey) {
			cd[j] = 0;
			isHomingTrail[j] = false;
		}
	}

	////////////////////////////////ここでプレイヤーを追跡///////////////////////////////////////
	for (int i = 0; i < EXCELLENCEHOMINGMAX; i++) {
		if (homing[i].t <= trackingValue ) {
			homing[i].tmpEndVector = { -1.0f ,-1.0f };
			homing[i].endPoint.x = player.x;
			homing[i].endPoint.y = player.y;
		}
		if (homing2[i].t <= trackingValue) {
			homing[i].tmpEndVector = { -1.0f ,-1.0f };
			homing2[i].endPoint.x = player.x;
			homing2[i].endPoint.y = player.y;
		}


		/*if (homing[i].t >= trackingValue) {
			tmpPlayerVector.x = player.x - prePlayer.x;
			tmpPlayerVector.y = player.y - prePlayer.y;
			homing[i].endPoint.x = player.x - tmpPlayerVector.x;
			homing[i].endPoint.y = player.y - tmpPlayerVector.y;
		}
		if (homing2[i].t >= trackingValue) {
			
			homing[i].tmpEndVector.x -= 1.0f;
			homing[i].tmpEndVector.y -= 1.0f;
			homing2[i].endPoint.x = player.x;
			homing2[i].endPoint.y = player.y;
			homing[i].endPoint.x -= homing[i].tmpEndVector.x;
			homing[i].endPoint.y -= homing[i].tmpEndVector.y;
		}*/
	}
	

	//制御点が広くなりすぎないように
	for (int i = 0; i < EXCELLENCEHOMINGMAX; i++) {
		if (homing[i].tmpMidVector.x >= midLimitValue || homing[i].tmpMidVector.y >= midLimitValue) {
			midAdjustValue = 1.0f;
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

	if (Novice::CheckHitKey(DIK_W)) {
		block1.pos.y -= 5;
	}
	if (Novice::CheckHitKey(DIK_S)) {
		block1.pos.y += 5;
	}
	if (Novice::CheckHitKey(DIK_A)) {
		block1.pos.x -= 5;
	}
	if (Novice::CheckHitKey(DIK_D)) {
		block1.pos.x += 5;
	}
}

void Excellence::Draw() {
	//残像
	for (int i = 0; i < EXCELLENCEHOMINGTRAILMAX; i++) {
		if (isHomingTrail[i]) {
			Novice::DrawEllipse(homingTrail[i].x, homingTrail[i].y, 10, 10, 0, BLUE, kFillModeSolid);
			/*Novice::DrawSprite(homingTrail[i].x, homingTrail[i].y, textureHandle, 1, 1, 0, WHITE);*/
		}
	}

	//ホーミング弾
	for (int i = 0; i < EXCELLENCEHOMINGMAX; i++) {
		if (homing[i].isLaserActive) {
			/*Novice::DrawEllipse(homing[i].x, homing[i].y, 20, 20, 0, RED, kFillModeSolid);*/
			Novice::DrawSprite(homing[i].x, homing[i].y, textureHandle, 1, 1, 0, BLUE);
		}
		if (homing2[i].isLaserActive) {
		    /*Novice::DrawEllipse(homing2[i].x, homing2[i].y, 20, 20, 0, RED, kFillModeSolid);*/
			Novice::DrawSprite(homing2[i].x + 5, homing2[i].y + 5, textureHandle, 1, 1, 0, BLUE);
		}
	}
	
	
	Novice::DrawEllipse(player.x, player.y, size, size, 0, WHITE, kFillModeSolid);//自機表示
	Novice::DrawBox(block1.pos.x, block1.pos.y, block1.size.x, block1.size.y, 0, WHITE, kFillModeSolid);//敵表示

	for (int i = 0; i < EXCELLENCEHOMINGMAX; i++) {
		//制御点
		Novice::DrawEllipse(homing[i].startPoint.x, homing[i].startPoint.y, 5, 5, 0.0f, RED, kFillModeSolid);
		Novice::DrawEllipse(homing[i].midPoint.x, homing[i].midPoint.y, 5, 5, 0.0f, RED, kFillModeSolid);
		Novice::DrawEllipse(homing[i].endPoint.x, homing[i].endPoint.y, 5, 5, 0.0f, RED, kFillModeSolid);

		Novice::DrawEllipse(homing2[i].startPoint.x, homing2[i].startPoint.y, 5, 5, 0.0f, BLUE, kFillModeSolid);
		Novice::DrawEllipse(homing2[i].midPoint.x, homing2[i].midPoint.y, 5, 5, 0.0f, BLUE, kFillModeSolid);
		Novice::DrawEllipse(homing2[i].endPoint.x, homing2[i].endPoint.y, 5, 5, 0.0f, BLUE, kFillModeSolid);

		//制御点同士を結んだ線
		Novice::DrawLine(homing[i].startPoint.x, homing[i].startPoint.y, homing[i].midPoint.x, homing[i].midPoint.y, RED);
		Novice::DrawLine(homing[i].midPoint.x, homing[i].midPoint.y, homing[i].endPoint.x, homing[i].endPoint.y, RED);

		Novice::DrawLine(homing2[i].startPoint.x, homing2[i].startPoint.y, homing2[i].midPoint.x, homing2[i].midPoint.y, BLUE);
		Novice::DrawLine(homing2[i].midPoint.x, homing2[i].midPoint.y, homing2[i].endPoint.x, homing2[i].endPoint.y, BLUE);
		/*Novice::DrawEllipse(homing[i].t, homing[i].t, 5, 5, 0, RED, kFillModeSolid);*/
	}


	Novice::ScreenPrintf(0, 0, "SPACE : Fire");
	Novice::ScreenPrintf(0, 20, "WASD : Player");
	////t同士を結んだ線
	//Novice::DrawLine(P01.x, P01.y, P12.x, P12.y, WHITE);
	//Novice::DrawLine(P12.x, P12.y, P02.x, P02.y, WHITE);

}


