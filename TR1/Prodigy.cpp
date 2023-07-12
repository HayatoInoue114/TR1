#include"Prodigy.h"


Prodigy::Prodigy()
{
	//���@���W
	player.x = kWindowWidth / 2;
	player.y = 200;

	//�ϐ�������
	for (int i = 0; i < HOMINGMAX; i++)
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
		homing[i].easingAdjustValue = 0.8f;

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
	block1.pos = { kWindowWidth / 2 - block1.size.x / 2,600 };

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
	midAdjustValue = 0.6f;
	endAdjustValue = 1.3f;
}

Prodigy::~Prodigy() {

}

void Prodigy::Init() {
	////���@���W
	//player.x = 400;
	//player.y = 400;

	////�ϐ�������
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

void Prodigy::Update() {
	Move();
}

void Prodigy::Move() {
	count++;

	for (int i = 0; i < HOMINGMAX; i++)
	{//�z�[�~���O�e�o������
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
				/*homing[i].easingAdjustValue = GetRandom(0.5f, 1.0f);*/


				//����_��������ꏊ
				homing[i].startPoint.x = block1.pos.x + GetRandom(0.0f, block1.size.x);
				homing[i].startPoint.y = block1.pos.y;

				if (player.x >= homing[i].startPoint.x) {
					homing[i].midPoint.x = player.x - GetRandom(200, 600);
				}
				if (player.x <= homing[i].startPoint.x) {
					homing[i].midPoint.x = player.x + GetRandom(200, 600);
				}
				homing[i].midPoint.y = player.y + GetRandom(300, 700);
				homing[i].endPoint.x = player.x;
				homing[i].endPoint.y = player.y + 5;
				homing[i].isLaserActive = true;


			}
		}


	}

	// �O��
	/*for (int i = 0; i < HOMINGMAX; i++)
	{
		if (!homing[i].isLaserActive) continue;
		if (homing[i].isLaserActive)
		{

			//�Ԃ̃x�W�F�Ȑ��̌v�Z
			for (int j = 0; j < DivNum; j++)
			{
				homing[i].t = (1.0f / homing[i].DivNum) * homing[i].Counter2 * (1.0f / homing[i].DivNum) * homing[i].Counter2 * (1.0f / homing[i].DivNum) * homing[i].Counter2 * (1.0f / homing[i].DivNum) * homing[i].Counter2;

				P01.x = (1.0f - homing[i].t) * homing[i].startPoint.x + homing[i].t * homing[i].midPoint.x;
				P01.y = (1.0f - homing[i].t) * homing[i].startPoint.y + homing[i].t * homing[i].midPoint.y;

				P12.x = (1.0f - homing[i].t) * homing[i].midPoint.x + homing[i].t * homing[i].endPoint.x;
				P12.y = (1.0f - homing[i].t) * homing[i].midPoint.y + homing[i].t * homing[i].endPoint.y;

				P02.x = (1.0f - homing[i].t) * P01.x + homing[i].t * P12.x; P02.y = (1.0f - homing[i].t) * P01.y + homing[i].t * P12.y;

				if (count % countNum == 0) {
					homing[i].x = (int)P02.x;
					homing[i].y = (int)P02.y;
				}




				Novice::DrawEllipse(homing[i].x - 1, homing[i].y - 1,10,10,0.0f,RED,kFillModeSolid);	//�x�W�F�Ȑ���`��
				homing[i].Counter2++;
				if (homing[i].Counter2 == homing[i].DivNum) {
					homing[i].Counter2 = 0;
				}

			}
		}
	}*/

	//1�ڂ̋O��/////////////////////////////////////////
	for (int i = 0; i < HOMINGMAX; i++)
	{

		if (homing[i].isLaserActive)
		{
			{//�x�W�F�Ȑ���`��
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



				// �����J�E���^�[���������ɒB���Ă�����O�ɖ߂�
				if (homing[i].t >= 1.0f)
				{
					homing[i].Counter = 0;
					isSecond = true;
					homing[i].isLaserActive = false;//���݂𖳂���
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
		}
	}


	///////////////////////2�ڂ̋O��/////////////////////////////////////////
	for (int i = 0; i < HOMINGMAX; i++)
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
			/*homing2[i].easingAdjustValue = GetRandom(0.5f, 1.0f);*/

			//����_��������ꏊ
			homing2[i].startPoint = homing[i].endPoint;

			homing2[i].tmpMidVector.x = homing[i].endPoint.x - homing[i].midPoint.x;
			homing2[i].tmpMidVector.y = homing[i].endPoint.y - homing[i].midPoint.y;

			homing2[i].midPoint.x = homing2[i].startPoint.x + homing2[i].tmpMidVector.x * midAdjustValue;
			homing2[i].midPoint.y = homing2[i].startPoint.y + homing2[i].tmpMidVector.y * midAdjustValue;



			homing2[i].endPoint.x = player.x + homing2[i].tmpEndVector.x * endAdjustValue;
			homing2[i].endPoint.y = player.y + homing2[i].tmpEndVector.y * endAdjustValue;

			homing2[i].isLaserActive = true;


		}


		if (homing2[i].isLaserActive)
		{
			{//�x�W�F�Ȑ���`��
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



				// ����t��1���傫���Ȃ�����x�N�g����ێ������܂܂ɂ���
				if (homing2[i].t >= 1.0f)
				{
					isSecond = false;

					if (homing2[i].x >= kWindowWidth || homing[i].x <= 0 || homing2[i].y >= kWindowHeight || homing2[i].y <= 0) {
						homing2[i].isLaserActive = false;//���݂𖳂���
					}
				}





				for (int j = 0; j < HOMINGTRAILMAX; j++) {
					if (count % countNum == 0 && !isHomingTrail[j]) {
						homingTrail[j].x = homing2[i].x;
						homingTrail[j].y = homing2[i].y;
						isHomingTrail[j] = true;
						break;
					}

				}
			}
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

void Prodigy::Draw() {


	//�c��
	for (int i = 0; i < HOMINGTRAILMAX; i++) {
		if (isHomingTrail[i]) {
			Novice::DrawEllipse(homingTrail[i].x, homingTrail[i].y, 10, 10, 0, BLUE, kFillModeSolid);
			/*Novice::DrawSprite(homingTrail[i].x, homingTrail[i].y, textureHandle, 1, 1, 0, WHITE);*/
		}
	}

	//�z�[�~���O�e
	for (int i = 0; i < HOMINGMAX; i++) {
		if (homing[i].isLaserActive) {
			Novice::DrawEllipse(homing[i].x, homing[i].y, 20, 20, 0, RED, kFillModeSolid);
			/*Novice::DrawSprite(homing[i].x, homing[i].y, textureHandle, 1, 1, 0, RED);*/
		}
		if (homing2[i].isLaserActive) {
			Novice::DrawEllipse(homing2[i].x, homing2[i].y, 20, 20, 0, RED, kFillModeSolid);
			/*Novice::DrawSprite(homing[i].x, homing[i].y, textureHandle, 1, 1, 0, RED);*/
		}
	}


	Novice::DrawEllipse(player.x, player.y, size, size, 0, WHITE, kFillModeSolid);//���@�\��
	Novice::DrawBox(block1.pos.x, block1.pos.y, block1.size.x, block1.size.y, 0, WHITE, kFillModeSolid);//�G�\��

	for (int i = 0; i < HOMINGMAX; i++) {
		//����_
		Novice::DrawEllipse(homing[i].startPoint.x, homing[i].startPoint.y, 5, 5, 0.0f, RED, kFillModeSolid);
		Novice::DrawEllipse(homing[i].midPoint.x, homing[i].midPoint.y, 5, 5, 0.0f, RED, kFillModeSolid);
		Novice::DrawEllipse(homing[i].endPoint.x, homing[i].endPoint.y, 5, 5, 0.0f, RED, kFillModeSolid);

		Novice::DrawEllipse(homing2[i].startPoint.x, homing2[i].startPoint.y, 5, 5, 0.0f, BLUE, kFillModeSolid);
		Novice::DrawEllipse(homing2[i].midPoint.x, homing2[i].midPoint.y, 5, 5, 0.0f, BLUE, kFillModeSolid);
		Novice::DrawEllipse(homing2[i].endPoint.x, homing2[i].endPoint.y, 5, 5, 0.0f, BLUE, kFillModeSolid);

		//����_���m�����񂾐�
		Novice::DrawLine(homing[i].startPoint.x, homing[i].startPoint.y, homing[i].midPoint.x, homing[i].midPoint.y, RED);
		Novice::DrawLine(homing[i].midPoint.x, homing[i].midPoint.y, homing[i].endPoint.x, homing[i].endPoint.y, RED);

		Novice::DrawLine(homing2[i].startPoint.x, homing2[i].startPoint.y, homing2[i].midPoint.x, homing2[i].midPoint.y, BLUE);
		Novice::DrawLine(homing2[i].midPoint.x, homing2[i].midPoint.y, homing2[i].endPoint.x, homing2[i].endPoint.y, BLUE);
		///*Novice::DrawEllipse(homing[i].t, homing[i].t, 5, 5, 0, RED, kFillModeSolid);*/
	}


	Novice::ScreenPrintf(0, 0, "SPACE : Fire");
	Novice::ScreenPrintf(0, 20, "WASD : Player");
	////t���m�����񂾐�
	//Novice::DrawLine(P01.x, P01.y, P12.x, P12.y, WHITE);
	//Novice::DrawLine(P12.x, P12.y, P02.x, P02.y, WHITE);

}

