#include "stdafx.h"
#include "Player.h"

Player::Player()
{
	animationClips[enAnimationClip_Idle].Load("Assets/animData/idle.tka");
	animationClips[enAnimationClip_Idle].SetLoopFlag(true);
	animationClips[enAnimationClip_Walk].Load("Assets/animData/walk.tka");
	animationClips[enAnimationClip_Walk].SetLoopFlag(true);
	animationClips[enAnimationClip_Run].Load("Assets/animData/run.tka");
	animationClips[enAnimationClip_Run].SetLoopFlag(true);
	animationClips[enAnimationClip_Jump].Load("Assets/animData/jump.tka");
	animationClips[enAnimationClip_Jump].SetLoopFlag(false);

	m_modelRender.Init("Assets/modelData/unityChan.tkm", animationClips, enAnimationClip_Num, enModelUpAxisY);

	characterController.Init(25.0f, 75.0f, m_position);

}

Player::~Player()
{

}

void Player::Update()
{

	//�ړ�����
	Move();
	//��]����
	Rotation();
	//�X�e�[�g�̊Ǘ�
	ManageState();
	//�A�j���[�V�����̍Đ�
	PlayAnimation();
	m_modelRender.Update();
}

void Player::Move()
{
	moveSpeed.x = 0.0f;
	moveSpeed.z = 0.0f;

	//�X�e�B�b�N���擾
	Vector3 stickL;
	stickL.x = g_pad[0]->GetLStickXF();
	stickL.y = g_pad[0]->GetLStickYF();

	//�O�㍶�E�x�N�g���擾
	Vector3 forward = g_camera3D->GetForward();
	Vector3 right = g_camera3D->GetRight();
	forward.y = 0.0f;
	right.y = 0.0f;

	//�_�b�V������ƃX�s�[�h�ݒ�

	isDashing = g_pad[0]->IsPress(enButtonB);//B�{�^���������ςȂ��Ń_�b�V���B

	//�O�����Z�q�Ń_�b�V�����������ŃX�s�[�h��ς���
	float speed = isDashing ? 300.0f : 120.0f;

	//�X�e�B�b�N�̕����ɃX�s�[�h�𔽉f
	right *= stickL.x * speed;
	forward *= stickL.y * speed;
	
	//i�ړ����x�ɉ��Z
	moveSpeed += right + forward;


	//�W�����v����
	if (characterController.IsOnGround())
	{
		moveSpeed.y = 0.0f;
		jumpcount = 0;
		
		if (g_pad[0]->IsTrigger(enButtonA))
		{
			moveSpeed.y = 600.0f;
			jumpcount++;
		}
	}
	else
	{
		moveSpeed.y -= 10.0f;

		if (g_pad[0]->IsTrigger(enButtonA) && jumpcount <2)
		{
			moveSpeed.y = 500.0f;
			jumpcount++;
		}
	}

	//�_�b�V����Ԃ��m�F
	right *= stickL.x * speed;
	forward *= stickL.y * speed;

	m_position = characterController.Execute(moveSpeed, 1.0f / 60.0f);

	m_modelRender.SetPosition(m_position);
}

void Player::Rotation()
{
	if (fabsf(moveSpeed.x) >= 0.001f || fabsf(moveSpeed.z) >= 0.001f)
	{
		rotation.SetRotationYFromDirectionXZ(moveSpeed);

		m_modelRender.SetRotation(rotation);
	}
}

void Player::ManageState()
{
	//�n�ʂɒ����Ă��Ȃ�������B
	if (characterController.IsOnGround() == false)
	{
		playerState = 1;//��
		return;
	}

	if (fabsf(moveSpeed.x) >= 0.001f || fabsf(moveSpeed.z) >= 0.001f)
	{
		if (isDashing)
		{
			playerState = 3;//�_�b�V��
		}
		else 
		{
			playerState = 2;//����

		}
	}
	//x,z�̈ړ����x���Ȃ�������~
	else
	{
		playerState = 0;//�ҋ@
	}
}

void Player::PlayAnimation()
{
	switch (playerState)
	{
	case 0:
		m_modelRender.PlayAnimation(enAnimationClip_Idle);
		break;
	case 1:
		m_modelRender.PlayAnimation(enAnimationClip_Jump);
		break;
	case 2:
		m_modelRender.PlayAnimation(enAnimationClip_Walk);
		break;
	case 3:
		m_modelRender.PlayAnimation(enAnimationClip_Run);
		break;
	}

}

void Player::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}
