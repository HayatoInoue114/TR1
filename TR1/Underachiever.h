#include "MT.h"

#define UNDERCHIEVERHOMINGMAX 6//�z�[�~���O����
#define UNDERCHIEVERHOMINGTRAILMAX 300//�c���z�[�~���O����

class Underachiever
{
public:
	Underachiever();
	~Underachiever();
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
		bool isLaserActive;//���[�U�[�̗L��
	};

	//�\���̐錾
	Player player;
	Player homingTrail[UNDERCHIEVERHOMINGTRAILMAX];
	bool isHomingTrail[UNDERCHIEVERHOMINGTRAILMAX];
	homing_t homing[UNDERCHIEVERHOMINGMAX];

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
	int cd[UNDERCHIEVERHOMINGTRAILMAX];
	bool preKey;
	bool isSecond;

	bool isMove;
	bool isRight;
	bool isLeft;

	int size;
};


