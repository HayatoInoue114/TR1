#include "MT.h"

#define HOMINGMAX 10//ホーミング総数
#define HOMINGTRAILMAX 3000//残像ホーミング総数

const int kWindowWidth = 1280;
const int kWindowHeight = 720;

class Bezier
{
public:
	Bezier();
	~Bezier();
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
		//ホーミング座標
		float x;
		float y;
		float u;

		//ベジェ曲線用
		int Counter;
		int Counter2;
		int DivNum;

		// 制御点
		float P0[2];
		float P1[2];
		float P2[2];
		bool isLaserActive;//レーザーの有無
	};

	//構造体宣言
	Player player;
	Player homingTrail[HOMINGTRAILMAX];
	bool isHomingTrail[HOMINGTRAILMAX];
	homing_t homing[HOMINGMAX];

	//制御点
	double P01[2], P12[2], P02[2];
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
};


