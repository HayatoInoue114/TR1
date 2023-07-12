#include "MT.h"

#define HOMINGMAX 5//�z�[�~���O����
#define HOMINGTRAILMAX 300//�c���z�[�~���O����

const int kWindowWidth = 1280;
const int kWindowHeight = 720;

class Prodigy
{
public:
	Prodigy();
	~Prodigy();
	void Init();
	void Update();
	void Move();
	void Draw();

private:
	struct Player {
		float x, y;
	};

	struct homing_t
	{
		//�z�[�~���O���W
		float x;
		float y;
		float t;

		//�x�W�F�Ȑ��p
		int Counter;
		int Counter2;
		int DivNum;

		// ����_
		Vector2 startPoint, midPoint, endPoint;

		Vector2 tmpMidVector, tmpEndVector;
		bool isLaserActive;//���[�U�[�̗L��
		float easingAdjustValue;
	};

	//�\���̐錾
	Player player;
	Player prePlayer;
	Player homingTrail[HOMINGTRAILMAX];
	bool isHomingTrail[HOMINGTRAILMAX];
	homing_t homing[HOMINGMAX];
	homing_t homing2[HOMINGMAX];

	//����_
	Vector2 P01, P12, P02;
	//
	int DivNum;

	int textureHandle;

	bool isLoad;

	struct Block {
		Vector2 pos;
		Vector2 size;
	};

	Block block1;

	int count;
	int countNum;
	int cd[HOMINGTRAILMAX];
	bool preKey;
	bool isSecond;

	bool isMove;
	bool isRight;
	bool isLeft;

	int size;

	float midAdjustValue;
	float endAdjustValue;
};


