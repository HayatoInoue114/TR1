#include "MT.h"

#define HOMINGMAX 1//ホーミング総数
#define HOMINGTRAILMAX 300//残像ホーミング総数

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
		float t;

		//ベジェ曲線用
		int Counter;
		int Counter2;
		int DivNum;

		// 制御点
		Vector2 P0, P1, P2;
		bool isLaserActive;//レーザーの有無
	};

	//構造体宣言
	Player player;
	Player homingTrail[HOMINGTRAILMAX];
	bool isHomingTrail[HOMINGTRAILMAX];
	homing_t homing[HOMINGMAX];

	//制御点
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
};


