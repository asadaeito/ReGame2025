#pragma once
class Gameclear :public IGameObject
{
public:
	Gameclear();
	~Gameclear();
	void Update();
	void Render(RenderContext& rc);
	SpriteRender spriteRender;
	SoundSource* gameclearBGM;
};

