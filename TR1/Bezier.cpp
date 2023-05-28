#include"Bezier.h"


Bezier::Bezier()
{
	//自機座標
	player.x = 400;
	player.y = 400;

	//変数初期化
	for (i = 0; i < HOMINGMAX; i++)
	{
		homing[i].x = 0;
		homing[i].y = 0;
		homing[i].u = 0;
		homing[i].Counter = 0;
		homing[i].Counter2 = 0;
		homing[i].DivNum = 0;
		homing[i].P0[0] = 0;
		homing[i].P0[1] = 0;
		homing[i].P1[0] = 0;
		homing[i].P1[1] = 0;
		homing[i].P2[0] = 0;
		homing[i].P2[1] = 0;
		homing[i].f = 0;
	}
	DivNum = 50;
	isLoad = false;
	block1.pos = { 300,600 };
	block1.size = { 300,50 };
	count = 0;
	countNum = 1;
	preKey = false;
	for (int i = 0; i < HOMINGTRAILMAX; i++) {
		zhomi[i] = {};
		isZHomi[i] = false;
	}
	isSecond = false;
	isMove = false;
	isRight = false;
	isLeft = false;

	size = 10;

	
}

void Bezier::Init() {
	//自機座標
	player.x = 400;
	player.y = 400;

	//変数初期化
	for (i = 0; i < HOMINGMAX; i++)
	{
		homing[i].x = 0;
		homing[i].y = 0;
		homing[i].u = 0;
		homing[i].Counter = 0;
		homing[i].Counter2 = 0;
		homing[i].DivNum = 0;
		homing[i].P0[0] = 0;
		homing[i].P0[1] = 0;
		homing[i].P1[0] = 0;
		homing[i].P1[1] = 0;
		homing[i].P2[0] = 0;
		homing[i].P2[1] = 0;
		homing[i].f = 0;
	}
	DivNum = 50;
	isLoad = false;
	block1.pos = { 300,600 };
	block1.size = { 600,50 };
	count = 0;
	countNum = 10;
	isSecond = false;
}

void Bezier::Update() {
	Move();
}

void Bezier::Move() {
	count++;

	for (int i = 0; i < HOMINGMAX; i++)
	{//レーザー出現処理
		if (Novice::CheckHitKey(DIK_Z))
		{
			if (homing[i].f == 0)
			{
				homing[i].x = 0;
				homing[i].y = 0;
				homing[i].u = 0;
				homing[i].Counter = 0;
				homing[i].Counter2 = 0;
				homing[i].DivNum = 50;
				homing[i].P0[0] = block1.pos.x + GetRandom(0.0f, block1.size.x);
				homing[i].P0[1] = block1.pos.y;
				if (player.x >= homing[i].P0[0]) {
					homing[i].P1[0] = player.x + 200;
				}
				if (player.x <= homing[i].P0[0]) {
					homing[i].P1[0] = player.x - 200;
				}
				homing[i].P1[1] = player.y;
				homing[i].P2[0] = player.x;
				homing[i].P2[1] = player.y + 5;
				homing[i].f = 1;


			}
		}


	}

	// 軌跡表示
	for (int i = 0; i < HOMINGMAX; i++)
	{
		if (homing[i].f == 0) continue;
		if (homing[i].f == 1)
		{

			// ベジェ曲線の計算をしているところ
			for (j = 0; j < DivNum; j++)
			{//灰色ベジェ曲線を描画
				homing[i].u = (1.0 / homing[i].DivNum) * homing[i].Counter2;

				P01[0] = (1.0 - homing[i].u) * homing[i].P0[0] + homing[i].u * homing[i].P1[0]; P01[1] = (1.0 - homing[i].u) * homing[i].P0[1] + homing[i].u * homing[i].P1[1];
				P12[0] = (1.0 - homing[i].u) * homing[i].P1[0] + homing[i].u * homing[i].P2[0]; P12[1] = (1.0 - homing[i].u) * homing[i].P1[1] + homing[i].u * homing[i].P2[1];

				P02[0] = (1.0 - homing[i].u) * P01[0] + homing[i].u * P12[0]; P02[1] = (1.0 - homing[i].u) * P01[1] + homing[i].u * P12[1];

				if (count % countNum == 0) {
					homing[i].x = (int)P02[0];
					homing[i].y = (int)P02[1];
				}
				
				
				

				Novice::DrawSprite(homing[i].x - 1, homing[i].y - 1, textureHandle, 1, 1, 0, WHITE);	//ベジェ曲線を描画
				homing[i].Counter2++;
				if (homing[i].Counter2 == homing[i].DivNum) homing[i].Counter2 = 0;
				
			}
		}
	}

	for (int i = 0; i < HOMINGMAX; i++)
	{

		if (homing[i].f == 1)
		{
			{//赤いベジェ曲線を描画
				homing[i].u = (1.0 / homing[i].DivNum) * homing[i].Counter;

				P01[0] = (1.0 - homing[i].u) * homing[i].P0[0] + homing[i].u * homing[i].P1[0]; P01[1] = (1.0 - homing[i].u) * homing[i].P0[1] + homing[i].u * homing[i].P1[1];
				P12[0] = (1.0 - homing[i].u) * homing[i].P1[0] + homing[i].u * homing[i].P2[0]; P12[1] = (1.0 - homing[i].u) * homing[i].P1[1] + homing[i].u * homing[i].P2[1];


				P02[0] = (1.0 - homing[i].u) * P01[0] + homing[i].u * P12[0]; P02[1] = (1.0 - homing[i].u) * P01[1] + homing[i].u * P12[1];


				homing[i].x = (int)P02[0];
				homing[i].y = (int)P02[1];


				Novice::DrawSprite(homing[i].x, homing[i].y, textureHandle, 1, 1, 0, RED);

				homing[i].Counter++;



				// もしカウンターが分割数に達していたら０に戻す
				if (homing[i].Counter == homing[i].DivNum && !isSecond)
				{
					homing[i].Counter = 0;
					homing[i].f = 0;//存在を無に
					/*isSecond = true;*/
				}
				if (homing[i].Counter == homing[i].DivNum && isSecond) {
					homing[i].Counter = 0;
					homing[i].f = 0;//存在を無に
					isSecond = false;
				}



				if (!isSecond) {
					homing[i].P2[0] = player.x;
					homing[i].P2[1] = player.y + 5;
				}
				else {
					homing[i].P2[0] = player.x;
					homing[i].P2[1] = player.y - 30;
				}


				for (int j = 0; j < HOMINGTRAILMAX; j++) {
					if (count % countNum == 0 && !isZHomi[j]) {
						zhomi[j].x = homing[i].x;
						zhomi[j].y = homing[i].y;
						isZHomi[j] = true;
						break;
					}

				}





			}
		}

		if (isSecond) {
			homing[i].x = 0;
			homing[i].y = 0;
			homing[i].u = 0;
			homing[i].Counter = 0;
			homing[i].Counter2 = 0;
			homing[i].DivNum = 500;
			homing[i].P0[0] = player.x;
			homing[i].P0[1] = player.y + 5;
			if (player.x >= homing[i].P0[0]) {
				homing[i].P1[0] = player.x + 100;
			}
			if (player.x <= homing[i].P0[0]) {
				homing[i].P1[0] = player.x - 100;
			}
			homing[i].P1[1] = player.y - 10;
			homing[i].P2[0] = player.x;
			homing[i].P2[1] = player.y - 30;
			homing[i].f = 1;
		}

	}


	for (int j = 0; j < HOMINGTRAILMAX; j++) {
		if (isZHomi[j]) {
			cd[j]++;
		}

		if (cd[j] >= 30 || Novice::CheckHitKey(DIK_SPACE) && !preKey) {
			cd[j] = 0;
			isZHomi[j] = false;
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
		textureHandle = Novice::LoadTexture("./Resource./hotMilk.png");
		
	}

	for (int i = 0; i < HOMINGMAX; i++) {
		Novice::DrawSprite(homing[i].x, homing[i].y, textureHandle, 1, 1, 0, RED);
	}
	for (int i = 0; i < HOMINGTRAILMAX; i++) {
		if (isZHomi[i]) {
			Novice::DrawSprite(zhomi[i].x, zhomi[i].y, textureHandle, 1, 1, 0, WHITE);
		}
	}
	
	Novice::DrawEllipse(player.x, player.y, size, size, 0, WHITE, kFillModeSolid);//自機表示
	Novice::DrawBox(block1.pos.x, block1.pos.y, block1.size.x, block1.size.y, 0, WHITE, kFillModeSolid);//敵表示

}


