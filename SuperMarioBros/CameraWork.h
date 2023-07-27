#pragma once

class CameraWork
{
private:
		
	// 描画するマップ座標値
	int map_draw_point_x; 
	int map_draw_point_y;	

	// 描画するマップチップの数
	int draw_map_chip_num_x;	
	int	draw_map_chip_num_y;	

	// プレイヤーの位置
	float player_x;
	float player_y;

public:

	//コンストラクタ
	CameraWork();

	//デストラクタ
	~CameraWork();

	//スクロール
	void Scroll(int scroll_x, int scroll_y);

};

