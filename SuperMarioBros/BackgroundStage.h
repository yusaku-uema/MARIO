#pragma once

//当たり判定なし。
class BackgroundStage
{
private:

	//画像
	int image;
	
	//描画する座標
	int x; 
	int y;

	//動かない背景データ
	int data[301] = {};
		
	//背景画像を呼び出すのか
	bool call_flg;

	//処理停止するのか
	bool processing_halt;

public:

	//コンストラクタ
	BackgroundStage();

	//デストラクタ
	~BackgroundStage();

	//更新
	void Update();

	//描画に関することを実装
	void Draw() const;
};

