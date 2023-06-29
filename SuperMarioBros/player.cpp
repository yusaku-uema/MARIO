#include "player.h"
#include"DxLib.h"
#include <stdio.h>

//�ő�W�����v��
#define STRONG_JUMP 5.5

//�����X�s�[�h
#define WALKING_SPEED 5.0f
#define RUNNING_SPEED 8.0f

//�����X�s�[�h
#define ACCELERATION_SPEED  0.1f
#define ACCELERATION_MAX_SPEED 0.3f

//�W�����v��
#define MINIUM_JUMP 12.0f
#define INTERIM_JUMP 16.0f
#define MAX_JUMP 6.5f

//�W�����v����
#define JUMP_FALL_SPEED 0.6f

Player::Player()
{
	descent_speed = 0;
	movement_speed = 0;
	jumping_power = -INTERIM_JUMP;
	location.x = 30;
	location.y = 300;
	area.height = 32;
	area.width = 32;
	stick_x = 0;
	jump_flg = false;
}

Player::~Player()
{

}

void Player::Update()
{

	//�}���I�ړ��֌W
	Operation();

	//�W�����v��t
	if (PadInput::OnButton(XINPUT_BUTTON_B) && jump_flg == false)
	{
		jump_flg = true;
	}

	if (jump_flg == true)
	{
		MarioJump();
	}
}

void Player::Draw() const
{

	DrawBox(location.x - area.width / 2, location.y - area.height / 2,
		location.x + area.width / 2, location.y + area.height / 2,
		GetColor(255, 255, 0), TRUE);

	DrawFormatString(100, 100, 0xFFFFFF, "%f", movement_speed);
}

void Player::Operation()
{
	// �X�e�B�b�N��X���W���擾
	stick_x = PadInput::GetLStick().x;

	// �X�e�B�b�N�̊��x
	const int stick_sensitivity = 20000;

	//�X�e�B�b�N�̎�t
	if (stick_x > stick_sensitivity || stick_x < stick_sensitivity * -1)
	{

		// �X�e�B�b�N����Ɉړ������ꍇ
		if (stick_x > 0)
		{

		}
		// �X�e�B�b�N�����Ɉړ������ꍇ
		else if (stick_x < 0)
		{

		}
	}
	else if (PadInput::OnPressed(XINPUT_BUTTON_DPAD_RIGHT) || PadInput::OnPressed(XINPUT_BUTTON_DPAD_LEFT))
	{
		//A�{�^���������Ă���̂�
		if (PadInput::OnPressed(XINPUT_BUTTON_A))
		{
			//�\���L�[�̉E����������
			if (PadInput::OnPressed(XINPUT_BUTTON_DPAD_RIGHT))
			{
				//�ő�������x��菬������
				if (movement_speed <= RUNNING_SPEED)
				{
					movement_speed += ACCELERATION_MAX_SPEED;
				}

			}
			else if (PadInput::OnPressed(XINPUT_BUTTON_DPAD_LEFT))
			{
				if (movement_speed > -RUNNING_SPEED)
				{
					movement_speed -= ACCELERATION_MAX_SPEED;
				}
			}
		}
		//A�{�^����������Ă��Ȃ�������
		else
		{
			if (PadInput::OnPressed(XINPUT_BUTTON_DPAD_RIGHT))
			{

				if (movement_speed > WALKING_SPEED)
				{
					movement_speed -= ACCELERATION_SPEED;
				}
				else if (movement_speed <= WALKING_SPEED)
				{
					movement_speed += ACCELERATION_SPEED;
				}


			}
			else if (PadInput::OnPressed(XINPUT_BUTTON_DPAD_LEFT))
			{
				if (movement_speed > -WALKING_SPEED)
				{
					movement_speed -= ACCELERATION_SPEED;
				}
				else if (movement_speed < -WALKING_SPEED)
				{
					movement_speed += ACCELERATION_SPEED;
				}
			}

		}

		location.x += movement_speed;

	}
	//�������Ă��Ȃ���
	else
	{

		if (movement_speed > 0.1)
		{
			movement_speed -= ACCELERATION_SPEED;
		}
		else if (movement_speed <= -0.1)
		{
			movement_speed += ACCELERATION_SPEED;
		}
		else
		{
			movement_speed = 0;
		}


		location.x += movement_speed;

	}
}

void Player::MarioJump()
{
	descent_speed += JUMP_FALL_SPEED;
	location.y += jumping_power + descent_speed;


	//�f�o�b�N
	if (location.y > 460)
	{
		jump_flg = false;
		descent_speed= 0;
	}
}
