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
		homing[i].t = 0;
		homing[i].Counter = 0;
		homing[i].Counter2 = 0;
		homing[i].DivNum = 0;
		homing[i].startPoint = {start.pos};
		homing[i].midPoint[0] = {};
		homing[i].endPoint = {};
		homing[i].isLaserActive = 0;
	}
	DivNum = 50;
	isLoad = false;
	start.pos = { 300,600 };
	start.size = { 50,50 };
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
	velocity = 5;

	size = 10;

	P01, P12, P23, P03 = {};

	textureHandle = Novice::LoadTexture("./Resource./ball.png");
	
	isEndPointSet = false;
	for (int i = 0; i < SETMIDPOINTMAX; i++) {
		isMidPointSet[i] = false;
	}
	
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
	//	homing[i].t = 0;
	//	homing[i].Counter = 0;
	//	homing[i].Counter2 = 0;
	//	homing[i].DivNum = 0;
	//	homing[i].startPoint.x = 0;
	//	homing[i].startPoint.y = 0;
	//	homing[i].midPoint[0].x = 0;
	//	homing[i].midPoint[0].y = 0;
	//	homing[i].endPoint.x = 0;
	//	homing[i].endPoint.y = 0;
	//	homing[i].isLaserActive = false;
	//}
	//DivNum = 100;
	//isLoad = false;
	//start.pos = { 300,600 };
	//start.size = { 600,50 };
	//count = 0;
	//countNum = 10;
	//isSecond = false;
}

void Bezier::Update() {
	Move();
}

void Bezier::Move() {
	count++;

	Novice::GetMousePosition(&player.x, &player.y);

	for (int i = 0; i < HOMINGMAX; i++)
	{//ホーミング弾出現処理

		if (isEndPointSet && isMidPointSet[0] && isMidPointSet[1] && Novice::IsTriggerMouse(0)) {
			isEndPointSet = false;
			for (int i = 0; i < SETMIDPOINTMAX; i++) {
				isMidPointSet[i] = false;
			}
		}

		//プレイヤーに届く
		if (Novice::IsTriggerMouse(0) && !isEndPointSet && !isMidPointSet[0] && !isMidPointSet[1]) {
			isEndPointSet = true;
			homing[i].endPoint.x = player.x;
			homing[i].endPoint.y = player.y;
		}

		if (!isEndPointSet && !isMidPointSet[0] && !isMidPointSet[1]) {
			homing[i].endPoint.x = player.x;
			homing[i].endPoint.y = player.y;
		}


		//中間の制御点1
		if (Novice::IsTriggerMouse(1) && isEndPointSet && !isMidPointSet[0] && !isMidPointSet[1]) {
			isMidPointSet[0] = true;
			homing[i].midPoint[0].x = player.x;
			homing[i].midPoint[0].y = player.y;
		}

		if (isEndPointSet && !isMidPointSet && !isMidPointSet[1]) {
			homing[i].midPoint[0].x = player.x;
			homing[i].midPoint[0].y = player.y;
		}

		//中間の制御点2
		if (Novice::IsTriggerMouse(2) && isEndPointSet && isMidPointSet[0] && !isMidPointSet[1]) {
			isMidPointSet[1] = true;
			homing[i].midPoint[1].x = player.x;
			homing[i].midPoint[1].y = player.y;
		}

		if (isEndPointSet && isMidPointSet && !isMidPointSet[1]) {
			homing[i].midPoint[1].x = player.x;
			homing[i].midPoint[1].y = player.y;
		}

		Novice::ScreenPrintf(0, 20, "%d", isEndPointSet);
		Novice::ScreenPrintf(0, 40, "%d", isMidPointSet[0]);
		Novice::ScreenPrintf(0, 60, "%d", isMidPointSet[1]);

		//始点から出てくる
		homing[i].startPoint.x = start.pos.x;
		homing[i].startPoint.y = start.pos.y;

		homing[i].DivNum = 50;

		/*if (Novice::CheckHitKey(DIK_SPACE))
		{
			if (!homing[i].isLaserActive)
			{
				homing[i].x = 0;
				homing[i].y = 0;
				homing[i].t = 0;
				homing[i].Counter = 0;
				homing[i].Counter2 = 0;
				

				homing[i].isLaserActive = true;
				
			}
		}*/


	}

	// 軌跡
	for (int i = 0; i < HOMINGMAX; i++)
	{

		//赤のベジェ曲線の計算
		for (int j = 0; j < DivNum; j++)
		{
			homing[i].t = (1.0f / homing[i].DivNum) * homing[i].Counter2;

			P01.x = (1.0f - homing[i].t) * homing[i].startPoint.x + homing[i].t * homing[i].midPoint[0].x;
			P01.y = (1.0f - homing[i].t) * homing[i].startPoint.y + homing[i].t * homing[i].midPoint[0].y;

			P12.x = (1.0f - homing[i].t) * homing[i].midPoint[0].x + homing[i].t * homing[i].midPoint[1].x;
			P12.y = (1.0f - homing[i].t) * homing[i].midPoint[0].y + homing[i].t * homing[i].midPoint[1].y;

			P23.x = (1.0f - homing[i].t) * homing[i].midPoint[1].x + homing[i].t * homing[i].endPoint.x;
			P23.y = (1.0f - homing[i].t) * homing[i].midPoint[1].y + homing[i].t * homing[i].endPoint.y;



			P03.x = (1.0f - homing[i].t) * P01.x + homing[i].t * P12.x + homing[i].t * P23.x;
			P03.y = (1.0f - homing[i].t) * P01.y + homing[i].t * P12.y + homing[i].t * P23.y;

			if (count % countNum == 0) {
				homing[i].x = (int)P03.x;
				homing[i].y = (int)P03.y;
			}




			Novice::DrawEllipse(homing[i].x - 1, homing[i].y - 1, 1, 1, 0.0f, RED, kFillModeSolid);    //ベジェ曲線を描画
			homing[i].Counter2++;
			if (homing[i].Counter2 == homing[i].DivNum) homing[i].Counter2 = 0;

		}
		 if (!homing[i].isLaserActive) continue;
		if (homing[i].isLaserActive)
		{


		} 
	}

	for (int i = 0; i < HOMINGMAX; i++)
	{
		homing[i].t = (1.0f / homing[i].DivNum) * homing[i].Counter;

		P01.x = (1.0f - homing[i].t) * homing[i].startPoint.x + homing[i].t * homing[i].midPoint[0].x;
		P01.y = (1.0f - homing[i].t) * homing[i].startPoint.y + homing[i].t * homing[i].midPoint[0].y;

		P12.x = (1.0f - homing[i].t) * homing[i].midPoint[0].x + homing[i].t * homing[i].midPoint[1].x;
		P12.y = (1.0f - homing[i].t) * homing[i].midPoint[0].y + homing[i].t * homing[i].midPoint[1].y;

		P23.x = (1.0f - homing[i].t) * homing[i].midPoint[1].x + homing[i].t * homing[i].endPoint.x;
		P23.y = (1.0f - homing[i].t) * homing[i].midPoint[1].y + homing[i].t * homing[i].endPoint.y;



		P03.x = (1.0f - homing[i].t) * P01.x + homing[i].t * P12.x + homing[i].t * P23.x;
		P03.y = (1.0f - homing[i].t) * P01.y + homing[i].t * P12.y + homing[i].t * P23.y;


		homing[i].x = (int)P03.x;
		homing[i].y = (int)P03.y;

		homing[i].Counter++;

				// もしカウンターが分割数に達していたら０に戻す
				if (homing[i].Counter == homing[i].DivNum && !isSecond)
				{
					homing[i].Counter = 0;
					homing[i].isLaserActive = false;//存在を無に
				
				}

				/*Novice::DrawSprite(homing[i].x, homing[i].y, textureHandle, 1, 1, 0, WHITE);*/

				if (homing[i].isLaserActive)
				{
					{//ベジェ曲線を描画


						/*Novice::DrawEllipse(homing[i].x, homing[i].y, 20, 20, 0, WHITE, kFillModeSolid);*/
						/*Novice::DrawSprite(homing[i].x, homing[i].y, textureHandle, 1, 1, 0, WHITE);*/

						

						homing[i].Counter++;



						




				/*if (!isSecond) {
					homing[i].endPoint.x = player.x;
					homing[i].endPoint.y = player.y + 5;
				}
				else {
					homing[i].endPoint.x = player.x;
					homing[i].endPoint.y = player.y - 30;
				}


						for (int j = 0; j < HOMINGTRAILMAX; j++) {
							if (count % countNum == 0 && !isHomingTrail[j]) {
								homingTrail[j].x = homing[i].x;
								homingTrail[j].y = homing[i].y;
								isHomingTrail[j] = true;
								break;
							}

				}*/





					}
				}

		/*if (isSecond) {
			homing[i].x = 0;
			homing[i].y = 0;
			homing[i].t = 0;
			homing[i].Counter = 0;
			homing[i].Counter2 = 0;
			homing[i].DivNum = 500;
			homing[i].startPoint.x = player.x;
			homing[i].startPoint.y = player.y + 5;
			if (player.x >= homing[i].startPoint.x) {
				homing[i].midPoint[0].x = player.x + 100;
			}
			if (player.x <= homing[i].startPoint.x) {
				homing[i].midPoint[0].x = player.x - 100;
			}
			homing[i].midPoint[0].y = player.y - 10;
			homing[i].endPoint.x = player.x;
			homing[i].endPoint.y = player.y - 30;
			homing[i].isLaserActive = true;
		}*/

	}


	/*for (int j = 0; j < HOMINGTRAILMAX; j++) {
		if (isHomingTrail[j]) {
			cd[j]++;
		}

		if (cd[j] >= 30 || Novice::CheckHitKey(DIK_SPACE) && !preKey) {
			cd[j] = 0;
			isHomingTrail[j] = false;
		}
	}*/




	if (Novice::CheckHitKey(DIK_UP)) {
		player.y -= velocity;
		isMove = true;
	}
	if (Novice::CheckHitKey(DIK_DOWN)) {
		player.y += velocity;
		isMove = true;
	}
	if (Novice::CheckHitKey(DIK_LEFT)) {
		player.x -= velocity;
		isMove = true;
		isLeft = true;
	}
	if (Novice::CheckHitKey(DIK_RIGHT)) {
		player.x += velocity;
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
		start.pos.y -= velocity;
	}
	if (Novice::CheckHitKey(DIK_S)) {
		start.pos.y += velocity;
	}
	if (Novice::CheckHitKey(DIK_A)) {
		start.pos.x -= velocity;
	}
	if (Novice::CheckHitKey(DIK_D)) {
		start.pos.x += velocity;
	}
}

void Bezier::Draw() {
	Novice::ScreenPrintf(0, 0, "endPointSet : leftClick  ,  midPoint[0]Set : rightClick");
	

	for (int i = 0; i < HOMINGMAX; i++) {
		

		if (homing[i].isLaserActive) {
			
			/*Novice::DrawSprite(homing[i].x, homing[i].y, textureHandle, 1, 1, 0, RED);*/
		}
		/*Novice::DrawEllipse(homing[i].x, homing[i].y, 10, 10, 0.0f, RED, kFillModeSolid);*/
	}
	/*for (int i = 0; i < HOMINGTRAILMAX; i++) {
		if (isHomingTrail[i]) {
			
		}

		Novice::DrawSprite(homingTrail[i].x, homingTrail[i].y, textureHandle, 1, 1, 0, WHITE);
	}*/
	
	//Novice::DrawEllipse(player.x, player.y, size, size, 0, WHITE, kFillModeSolid);//自機表示
	Novice::DrawEllipse(start.pos.x, start.pos.y, start.size.x, start.size.y, 0, WHITE, kFillModeSolid);//敵表示


	
	for (int i = 0; i < HOMINGMAX; i++) {
		//制御点
		Novice::DrawEllipse(homing[i].startPoint.x, homing[i].startPoint.y, 5, 5, 0.0f, RED, kFillModeSolid);
		Novice::DrawEllipse(homing[i].midPoint[0].x, homing[i].midPoint[0].y, 5, 5, 0.0f, RED, kFillModeSolid);
		Novice::DrawEllipse(homing[i].endPoint.x, homing[i].endPoint.y, 5, 5, 0.0f, RED, kFillModeSolid);

		//制御点同士を結んだ線
		Novice::DrawLine(homing[i].startPoint.x, homing[i].startPoint.y, homing[i].midPoint[0].x, homing[i].midPoint[0].y, WHITE);
		Novice::DrawLine(homing[i].midPoint[0].x, homing[i].midPoint[0].y, homing[i].endPoint.x, homing[i].endPoint.y, WHITE);

		/*Novice::DrawEllipse(homing[i].t, homing[i].t, 5, 5, 0, RED, kFillModeSolid);*/
	}

	////t同士を結んだ線
	//Novice::DrawLine(P01.x, P01.y, P12.x, P12.y, WHITE);
	//Novice::DrawLine(P12.x, P12.y, P03.x, P03.y, WHITE);
	
	
	
}


