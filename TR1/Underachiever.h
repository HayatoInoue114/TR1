#include "MT.h"

#define UNDERCHIEVERHOMINGMAX 6//ホーミング総数
#define UNDERCHIEVERHOMINGTRAILMAX 300//残像ホーミング総数

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
		//ホーミング座標
		float x;
		float y;
		float t;

		//ベジェ曲線用
		int Counter;
		int Counter2;
		int DivNum;

		// 制御点
		Vector2 startPoint, midPoint, endPoint;
		bool isLaserActive;//レーザーの有無
	};

	//構造体宣言
	Player player;
	Player homingTrail[UNDERCHIEVERHOMINGTRAILMAX];
	bool isHomingTrail[UNDERCHIEVERHOMINGTRAILMAX];
	homing_t homing[UNDERCHIEVERHOMINGMAX];

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
	int cd[UNDERCHIEVERHOMINGTRAILMAX];
	bool preKey;
	bool isSecond;

	bool isMove;
	bool isRight;
	bool isLeft;

	int size;
};


