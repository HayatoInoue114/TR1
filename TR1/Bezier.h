#include "MT.h"

#define HOMINGMAX 1//ホーミング総数
#define HOMINGTRAILMAX 100//残像ホーミング総数
#define SETMIDPOINTMAX 2

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
		int x, y;
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
		Vector2 startPoint, midPoint[SETMIDPOINTMAX], endPoint;
		bool isLaserActive;//レーザーの有無
	};

	//構造体宣言
	Player player;
	Player homingTrail[HOMINGTRAILMAX];
	bool isHomingTrail[HOMINGTRAILMAX];
	homing_t homing[HOMINGMAX];

	//制御点
	Vector2 P01, P12, P23;
	Vector2	 P02, P03, P13;
	//
	int DivNum;

	int textureHandle;

	bool isLoad;

	struct Start {
		Vector2 pos;
		Vector2 size;
	};

	Start start;

	int count;
	int countNum;
	int cd[HOMINGTRAILMAX];
	bool preKey;
	bool isSecond;
	int velocity;

	bool isMove;
	bool isRight;
	bool isLeft;

	unsigned int color[5];
	
	int size;

	bool isEndPointSet;
	bool isMidPointSet[SETMIDPOINTMAX];
};


