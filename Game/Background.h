#pragma once
class Background:public IGameObject
{
public:
	Background();
	~Background();

	void Render(RenderContext& rc);

	PhysicsStaticObject physicsStaticObject;
	ModelRender modelRender;
};

