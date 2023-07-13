#pragma once
#include"BoxCollider.h"

//ブロックの種類や座標の設定
struct Block
{
	int x;
	int y;
	int type;
};

//背景と違ってこっちには当たり判定がある
class Stage : public  BoxCollider
{
private:
	
	//ブロックの種類
	int image;

	int deta[15][20];

	Block block[15][20];

public:

	//コンストラクタ
	Stage();

	//デストラクタ
	~Stage();

	//更新
	void Update();

	//描画に関することを実装
	void Draw() const;

	//ステージデータ読込み
	int DataRead();

	Block GetBlockDeta() const;

};

