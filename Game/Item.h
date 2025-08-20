#pragma once

class Player;
class Item:public IGameObject
{
public:
	Item();
	~Item();
	
	bool Start();
	void Update();
	void Render(RenderContext& rc);
	void Move();
	void Rotation();
	
	Vector3 position;
	Player* player;
private:
	ModelRender modelRender;
	Quaternion rotation;
};

