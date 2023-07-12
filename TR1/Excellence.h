#include "MT.h"

#define EXCELLENCEHOMINGMAX 5//ホーミング総数
#define EXCELLENCEHOMINGTRAILMAX 300//残像ホーミング総数


class Excellence
{
public:
	Excellence();
	~Excellence();
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

		Vector2 tmpMidVector,tmpEndVector;
		bool isLaserActive;//レーザーの有無
		float easingAdjustValue;
	};

	//構造体宣言
	Player player;
	Player prePlayer;
	Player prePlayer2;
	Player tmpPlayerVector;
	Player homingTrail[EXCELLENCEHOMINGTRAILMAX];
	bool isHomingTrail[EXCELLENCEHOMINGTRAILMAX];
	homing_t homing[EXCELLENCEHOMINGMAX];
	homing_t homing2[EXCELLENCEHOMINGMAX];

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
	int cd[EXCELLENCEHOMINGTRAILMAX];
	bool preKey;
	bool isSecond;
	bool isAround;

	bool isMove;
	bool isRight;
	bool isLeft;

	int size;

	float midAdjustValue;
	float endAdjustValue;
	float trackingValue;

	int setFrame;
	float midLimitValue;
};


