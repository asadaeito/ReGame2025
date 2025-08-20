#include "stdafx.h"
#include "GameCamera.h"
#include"Player.h"

GameCamera::GameCamera()
{

}

GameCamera::~GameCamera()
{

}

bool GameCamera::Start()
{
	//�����_���王�_�܂ł̃x�N�g����ݒ�B
	m_toCameraPos.Set(0.0f, 125.0f, -250.0f);
	//�v���C���[�̃C���X�^���X��T���B
	m_player = FindGO<Player>("BattleCharacter");

	//�J�����̃j�A�N���b�v�ƃt�@�[�N���b�v��ݒ肷��B
	g_camera3D->SetNear(1.0f);
	g_camera3D->SetFar(40000.0f);

	return true;
}

void GameCamera::Update()
{

	
	Vector3 target;
	target.x = m_player->m_position.x;

	target.y = m_player->m_position.y += 100.0f;
	target.z = m_player->m_position.z;

	g_camera3D->SetTarget(target);

	Vector3 cameraPos;
	cameraPos = target;

	cameraPos.z -= 300.0f;

	g_camera3D->SetPosition(cameraPos);
}

