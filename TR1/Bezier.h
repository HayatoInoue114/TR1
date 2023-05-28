#include "MT.h"

#define HOMINGMAX 10//ホーミング総数
#define HOMINGTRAILMAX 300//残像ホーミング総数

const int kWindowWidth = 1280;
const int kWindowHeight = 720;

class Bezier
{
public:
	Bezier();
	void Init();
	void Update();
	void Move();
	void Draw();

private:
	struct Player {//自機構造体
		float x, y;//自機座標
	};

	struct homing_t
	{
		float x;//ホーミング座標
		float y;
		float u;
		int Counter;//ベジェ曲線用
		int Counter2;//ベジェ曲線用
		int DivNum;//ベジェ曲線用
		float P0[2];// 制御点
		float P1[2];// 制御点
		float P2[2];// 制御点
		int f;//レーザーの有無
	};

	//構造体宣言
	Player player;
	Player zhomi[HOMINGTRAILMAX];
	bool isZHomi[HOMINGTRAILMAX];
	homing_t homing[HOMINGMAX];

	//制御点
	double P01[2], P12[2];
	double P02[2];
	//
	int i, j, DivNum;

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


