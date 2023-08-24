#pragma once

class CameraWork
{
private:
		
	//スクロール系統？実験中
	int camerax;//カメラの左上座標
	int charx;//自キャラ位置
	int view_charx;//自キャラの表示位置。この座標にdrawする。

public:

	//コンストラクタ
	CameraWork();

	//デストラクタ
	~CameraWork();

	//更新
	void Update(float player_location);

	//キャラクタの描画する位置
	int GetViewCharX();

	//ステージ描画位置をずらす
	int GetCameraX();

};

