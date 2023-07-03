#include "player.h"
#include"DxLib.h"
#include <stdio.h>
#define _USE_MATH_DEFINES
#include <math.h>

//�A�j���[�V�����؂�ւ�����
#define SWITCHING_TIME 6

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

	LoadDivGraph("image/mario/mario.png", 9, 9, 1, 32, 32, tiny_mario);
	LoadDivGraph("Images/Enemy/Doragon/tktk_Other_4L.png", 3, 3, 1, 32, 64, power_up_image);

	animation = 0;
	animation_time = 0;
	animation_count = 0;
	power_up_animation = 0;

	descent_speed = 0;
	movement_speed = 0;
	b_button_press_time = 0;
	jumping_power = -MINIUM_JUMP;
	location.x = 30;
	location.y = 300;
	area.height = 32;
	area.width = 32;
	stick_x = 0;

	jump_flg = false;
	left_move = false;
	power_up_flg = false;
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


	if (movement_speed != 0)
	{
		if (++animation_time % SWITCHING_TIME == 0)
		{
			animation++;

			if (animation > 3)
			{
				animation = 0;
			}
		}

		if (movement_speed > 0)
		{
			//���ɓ����Ă���̂�
			left_move = false;
		}
		else
		{
			//���ɓ����Ă���̂�
			left_move = true;

		}

	}


}

void Player::Draw() const
{

	DrawBox(location.x - area.width / 2, location.y - area.height / 2,
		location.x + area.width / 2, location.y + area.height / 2,
		GetColor(255, 255, 0), TRUE);

	DrawFormatString(100, 100, 0xFFFFFF, "%f", movement_speed);

	DrawFormatString(100, 300, 0xFFFFFF, "%f", b_button_press_time);

	DrawRotaGraphF(location.x, location.y, 0.7f,
		M_PI  / 180, tiny_mario[animation], TRUE, left_move);

}

void Player::Operation()
{
	// �X�e�B�b�N��X���W���擾
	stick_x = PadInput::GetLStick().x;

	// �X�e�B�b�N�̊��x
	const int stick_sensitivity = 200;

	//�X�e�B�b�N�̎�t
	if (stick_x > stick_sensitivity || stick_x < stick_sensitivity * -1)
	{

		//A�{�^���������Ă���̂�
		if (PadInput::OnPressed(XINPUT_BUTTON_A))
		{
			// �X�e�B�b�N����Ɉړ������ꍇ
			if (stick_x > 0)
			{
				//�ő�������x��菬������
				if (movement_speed <= RUNNING_SPEED)
				{
					movement_speed += ACCELERATION_MAX_SPEED;
				}
			}
			// �X�e�B�b�N�����Ɉړ������ꍇ
			else if (stick_x < 0)
			{
				if (movement_speed > -RUNNING_SPEED)
				{
					movement_speed -= ACCELERATION_MAX_SPEED;
				}
			}
		}

		//A�{�^���������Ă��Ȃ��Ƃ�
		else
		{
			// �X�e�B�b�N����Ɉړ������ꍇ
			if (stick_x > 0)
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
			// �X�e�B�b�N�����Ɉړ������ꍇ
			else if (stick_x < 0)
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
	}
	else if (PadInput::OnPressed(XINPUT_BUTTON_DPAD_RIGHT) || PadInput::OnPressed(XINPUT_BUTTON_DPAD_LEFT)
		|| stick_x > stick_sensitivity || stick_x < stick_sensitivity * -1)
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
	}

	location.x += movement_speed;

}

void Player::MarioJump()
{
	//B�{�^���������Ă��钷��
	if (PadInput::OnPressed(XINPUT_BUTTON_B))
	{
		b_button_press_time += 0.1;
	}

	//B�{�^���������Ă��鎞�Ԃɂ���Ĕ�ԗ͂�ς���
	if (b_button_press_time < 0.6)
	{
		jumping_power = -MINIUM_JUMP;
	}
	else if (b_button_press_time >= 0.6 && b_button_press_time <1 )
	{
		jumping_power = -INTERIM_JUMP;
	}

	//�W�����v�J�n
	descent_speed += JUMP_FALL_SPEED;
	location.y += jumping_power + descent_speed;


	//�f�o�b�N
	if (location.y > 460)
	{
		jump_flg = false;
		descent_speed= 0;
		b_button_press_time = 0;
	}

}


void Player::PowerUp()
{
	switch (animation_count)
	{
	case 0:
		animation
	default:
		break;
	}
}