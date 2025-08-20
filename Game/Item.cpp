#include "stdafx.h"
#include "Item.h"
#include"Player.h"

Item::Item()
{
	modelRender.Init("Assets/modelData/Item.tkm");

	player = FindGO<Player>("BattleCharacter");

}

Item::~Item()
{

}

bool Item::Start()
{
	
	return true;
}

void Item::Move()
{
	modelRender.SetPosition(position);
}

void Item::Rotation()
{
	//��]�����Z����B
	rotation.AddRotationDegY(2.0f);

	modelRender.SetRotation(rotation);
}

void Item::Update()
{
	Move();

	Rotation();

	//�v���C���[����Item�Ɍ������x�N�g�����v�Z�B
	Vector3 diff = player->m_position - position;
	//�x�N�g���̒�����120.0f��菬����������B
	if (diff.Length() <= 120.0f)
	{
		player->itemCount++;
		DeleteGO(this);
	}
	
	modelRender.Update();

}

void Item::Render(RenderContext& rc)
{
	modelRender.Draw(rc);
}
