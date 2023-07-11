#pragma once
#include"BoxCollider.h"



//背景と違ってこっちには当たり判定がある
class Stage : public  BoxCollider
{
private:
	
	//ブロックの種類
	int image[20];

	int deta[];

public:

	//コンストラクタ
	Stage();

	//デストラクタ
	~Stage();

	//更新
	void Update();

	//描画に関することを実装
	void Draw() const;
};

