#pragma once
#include"DxLib.h"

#define BUTTONS 16


//スティック
struct Stick
{
	short x;	//横軸値
	short y;	//縦軸値
};

class PadInput
{
		
private:

	static char now_key[BUTTONS]; //今回の入力キー
	static char old_key[BUTTONS]; //前回の入力キー
	static XINPUT_STATE input; //パッド
	static Stick r_stick; //右スティック
	static Stick l_stick; //左スティック

private:

	//コンストラクタ
	PadInput() = default;
public:

	//パッド情報の更新
	static void UpdateKey();

	//ボタンを押された瞬間
	static bool OnButton(int button);

	//ボタンを押してる間
	static bool OnPressed(int button);

	//ボタンを離した瞬間
	static bool OnRelease(int button);

	//右スティックの取得
	static Stick GetRStick();

	//左スティックの取得
	static Stick GetLStick();

	static char GetOldKey(const int i);

	static char GetNowKey(const int i);
};

